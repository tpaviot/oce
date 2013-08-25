
# Instructs the MSVC toolset to use the precompiled header PRECOMPILED_HEADER
# for each source file given in the collection named by SOURCE_VARIABLE_NAME.
FUNCTION(ENABLE_PRECOMPILED_HEADERS PHASE TARGET_NAME PRECOMPILED_HEADER SOURCE_VARIABLE_NAME)
	IF(MSVC OR CMAKE_COMPILER_IS_GNUCXX)
		set(files ${${SOURCE_VARIABLE_NAME}})

		# Generate precompiled header translation unit
		get_filename_component(pch_basename ${PRECOMPILED_HEADER} NAME_WE)
		set(pch_unity ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.cpp)
		
		IF(MSVC)
		    SET(pch_abs ${CMAKE_CURRENT_SOURCE_DIR}/${PRECOMPILED_HEADER})
		ELSE()
		    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h ${CMAKE_CURRENT_BINARY_DIR}/Precompiled.h)
		    SET(pch_abs ${CMAKE_CURRENT_BINARY_DIR}/${PRECOMPILED_HEADER})
		ENDIF()
		
		IF (PHASE EQUAL 2)
			# A list of exclusions patterns. For the moment is global to the entire project
			SET (excludes "OSD*" "WNT*" "AlienImage_BMPAlienData.cxx"
				      "Image_PixMap.cxx" "PlotMgt.cxx" "Visual3d_View.cxx" "V3d_View_Print.cxx" "OpenGl*"
				      "Viewer2dTest_ViewerCommands.cxx" "ViewerTest_*" )

			# GCC requires an additional target to build the PCH file.
			IF(CMAKE_COMPILER_IS_GNUCXX)
				
				# PCH output file
				#SET(pch_output "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.gch")
				SET(pch_output "${pch_abs}.gch")
				
				# Detects compiler flags
				STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
				SET(_compiler_FLAGS ${${_flags_var_name}})
				
				# Directory properties
				GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
				FOREACH(item ${_directory_flags})
				    LIST(APPEND _compiler_FLAGS "-I${item}")
				ENDFOREACH(item)

				GET_TARGET_PROPERTY(target_compiler_FLAGS ${TARGET_NAME} COMPILE_FLAGS)
				IF(target_compiler_FLAGS)
				    LIST(APPEND _compiler_FLAGS ${target_compiler_FLAGS})
				ENDIF()
							
				STRING(TOUPPER "COMPILE_DEFINITIONS_${CMAKE_BUILD_TYPE}" _defs_prop_name)
				
				GET_DIRECTORY_PROPERTY(_directory_flags COMPILE_DEFINITIONS)
				IF(_directory_flags)
				      FOREACH(flag ${_directory_flags})
					  LIST(APPEND _compiler_FLAGS -D${flag})
				      ENDFOREACH(flag)
				ENDIF(_directory_flags)
				
				GET_DIRECTORY_PROPERTY(_directory_flags ${_defs_prop_name})
				IF(_directory_flags)
				      FOREACH(flag ${_directory_flags})
					  LIST(APPEND _compiler_FLAGS -D${flag})
				      ENDFOREACH(flag)
				ENDIF(_directory_flags)

				GET_TARGET_PROPERTY(_target_flags ${TARGET_NAME} COMPILE_DEFINITIONS)
				IF(_target_flags)
					FOREACH(flag ${_target_flags})
						LIST(APPEND _compiler_FLAGS -D${flag})
					ENDFOREACH(flag)
				ENDIF(_target_flags)

				GET_TARGET_PROPERTY(_target_flags ${TARGET_NAME} ${_defs_prop_name})
				IF(_target_flags)
					FOREACH(flag ${_target_flags})
						LIST(APPEND _compiler_FLAGS -D${flag})
					ENDFOREACH(flag)
				ENDIF(_target_flags)
				
				#MESSAGE("compiler flags :" ${_compiler_FLAGS})

				SEPARATE_ARGUMENTS(_compiler_FLAGS)
				
				IF(NOT WIN32)
					SET(additionalCompilerFlags -fPIC)
				ELSE()
					SET(additionalCompilerFlags -mthreads)
				ENDIF()	      
					      
				ADD_CUSTOM_COMMAND(OUTPUT ${pch_output} 
				    COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header -o ${pch_output} ${pch_unity} ${additionalCompilerFlags}
				    DEPENDS ${pch_unity} )
				ADD_CUSTOM_TARGET(${TARGET_NAME}_gch DEPENDS ${pch_output})
				ADD_DEPENDENCIES(${TARGET_NAME} ${TARGET_NAME}_gch)
			ENDIF()
	    
			# Update properties of source files to use the precompiled header.
			# Additionally, force the inclusion of the precompiled header at beginning of each source file.
			foreach(source_file ${files} )
				# Find if the file is on the exclusion list
				SET(IsExclude FALSE)
				foreach (exc ${excludes})
					IF(${source_file} MATCHES ${exc})
						SET(IsExclude TRUE)
					ENDIF()
				endforeach ()
				IF (NOT IsExclude)
					GET_FILENAME_COMPONENT(thisext ${source_file} EXT)
					IF (${thisext} MATCHES ".cxx")
						IF (MSVC)
						  set_source_files_properties( ${source_file} PROPERTIES COMPILE_FLAGS "/Yu\"${PRECOMPILED_HEADER}\" /FI\"${PRECOMPILED_HEADER}\""     )
						ENDIF()
						IF (CMAKE_COMPILER_IS_GNUCXX)
						  SET_SOURCE_FILES_PROPERTIES( ${source_file} PROPERTIES COMPILE_FLAGS "-include ${pch_abs} -Winvalid-pch")
						ENDIF()
						
					ENDIF()
				ENDIF()
			endforeach(source_file)
		ELSE(PHASE EQUAL 2)
		    # Finally, update the source file collection to contain the precompiled header translation unit
		    set(${SOURCE_VARIABLE_NAME} ${pch_unity} ${PRECOMPILED_HEADER} ${${SOURCE_VARIABLE_NAME}} PARENT_SCOPE)
		    
		    #set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${pch_abs}\"") #this may be useful for nmake
		    IF(MSVC)
			set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${PRECOMPILED_HEADER}\"")
		    ENDIF()
		ENDIF(PHASE EQUAL 2)

	ENDIF()
ENDFUNCTION(ENABLE_PRECOMPILED_HEADERS)

MESSAGE(STATUS "Processing ToolKit: ${TOOLKIT} (${TOOLKIT_MODULES})")
LIST(APPEND OCE_ALL_BUILT_MODULES ${TOOLKIT_MODULES})
SET(OCE_ALL_BUILT_MODULES ${OCE_ALL_BUILT_MODULES} PARENT_SCOPE)
SET(TOOLKIT_SOURCE_FILES)
SET(TOOLKIT_HEADER_FILES)
SET(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${TOOLKIT_INCLUDE_DIRECTORIES})
FOREACH(MODULE ${TOOLKIT_MODULES})
	
	IF(APPLE AND OCE_OSX_USE_COCOA)
	  FILE(GLOB source_files
		${OCE_SOURCE_DIR}/src/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.mm
		${OCE_SOURCE_DIR}/src/${MODULE}/*.c
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.c)
	# add all .cxx/*.c files or each module
	ELSE(APPLE AND OCE_OSX_USE_COCOA)
	  FILE(GLOB source_files
		${OCE_SOURCE_DIR}/src/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.c
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.c)
	ENDIF(APPLE AND OCE_OSX_USE_COCOA)
	SET (header_files "")
	
	FILE(GLOB header_files
		${OCE_SOURCE_DIR}/src/${MODULE}/*.h
		${OCE_SOURCE_DIR}/src/${MODULE}/*.hxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.gxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.lxx)
	IF(OCE_ADD_HEADERS)
		LIST(APPEND source_files ${header_files})
	ENDIF(OCE_ADD_HEADERS)

	SET(TOOLKIT_HEADER_FILES ${TOOLKIT_HEADER_FILES} ${header_files})
	SET(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} ${OCE_SOURCE_DIR}/src/${MODULE} ${OCE_SOURCE_DIR}/drv/${MODULE})

	IF (WIN32)
		# For compilers under Windows a define must be set per file to correctly set the export macro
		ADD_DEFINITIONS("-D__${MODULE}_DLL")
	ENDIF(WIN32)

	SOURCE_GROUP (${MODULE} FILES ${source_files})

	# append these source files to the list of source files of the toolkit
	SET(TOOLKIT_SOURCE_FILES ${TOOLKIT_SOURCE_FILES} ${source_files})
	# required include paths
ENDFOREACH(MODULE ${TOOLKIT_MODULES})

IF(TOOLKIT_DEPENDS)
	FOREACH(tkit ${TOOLKIT_DEPENDS})
		SET(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} ${OCE_${tkit}_INCLUDE_DIRECTORIES})
	ENDFOREACH(tkit ${TOOLKIT_DEPENDS})
	LIST(REMOVE_DUPLICATES OCE_${TOOLKIT}_INCLUDE_DIRECTORIES)
ENDIF(TOOLKIT_DEPENDS)
SET(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} PARENT_SCOPE)
INCLUDE_DIRECTORIES(${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES})

# Version info
IF(NOT OCE_NO_LIBRARY_VERSION)
	IF(MSVC)
		SET(TOOLKIT_RESOURCES ${OCE_WIN32_RES_FILE})
	ENDIF(MSVC)
ENDIF(NOT OCE_NO_LIBRARY_VERSION)

# Precompiled Headers
IF(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)
	IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
		#MESSAGE("Using Precompiled.h")
		ENABLE_PRECOMPILED_HEADERS (1 ${TOOLKIT} Precompiled.h TOOLKIT_SOURCE_FILES)
		SOURCE_GROUP (Precompiled FILES Precompiled.h Precompiled.cpp)
	ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
ENDIF(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)

# Add the toolkit target
ADD_LIBRARY(${TOOLKIT} ${OCE_LIBRARY_TYPE} ${TOOLKIT_SOURCE_FILES} ${TOOLKIT_RESOURCES} )

IF(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)
	IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
	    ENABLE_PRECOMPILED_HEADERS (2 ${TOOLKIT} Precompiled.h TOOLKIT_SOURCE_FILES)
	ENDIF()
ENDIF()

# TODO Add current toolkit header files into a source group?
# Add target specific locations of *.lxx and *.ixx files
IF(NOT OCE_NO_LIBRARY_VERSION)
    SET_TARGET_PROPERTIES(${TOOLKIT} PROPERTIES
	    SOVERSION ${OCE_ABI_SOVERSION}
	    VERSION ${OCE_ABI_VERSION}
    )
ENDIF(NOT OCE_NO_LIBRARY_VERSION)

# Workaround for Cmake bug #0011240 (see http://public.kitware.com/Bug/view.php?id=11240)
# Win64+MSVC+static libs = linker error
IF(MSVC AND NOT OCE_BUILD_SHARED_LIB AND BIT EQUAL 64)
  set_target_properties(${TOOLKIT} PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
ENDIF()

# Set dependencies for thit ToolKit
IF ( NOT "${TOOLKIT}" STREQUAL "TKernel" )
	LIST(REMOVE_DUPLICATES TOOLKIT_DEPENDS)
ENDIF ( NOT "${TOOLKIT}" STREQUAL "TKernel" )
TARGET_LINK_LIBRARIES(${TOOLKIT} ${TOOLKIT_DEPENDS} ${TOOLKIT_LIBS} ${WIN32_LIBS})

IF(TOOLKIT_LIBS_OPTIMIZED)
	FOREACH(lib ${TOOLKIT_LIBS_OPTIMIZED})
		TARGET_LINK_LIBRARIES(${TOOLKIT} optimized ${lib})
	ENDFOREACH(lib ${TOOLKIT_LIBS_OPTIMIZED})
ENDIF(TOOLKIT_LIBS_OPTIMIZED)

IF(TOOLKIT_LIBS_DEBUG)
	FOREACH(lib ${TOOLKIT_LIBS_DEBUG})
		TARGET_LINK_LIBRARIES(${TOOLKIT} debug ${lib})
	ENDFOREACH(lib ${TOOLKIT_LIBS_DEBUG})
ENDIF(TOOLKIT_LIBS_DEBUG)

IF(TOOLKIT_DEPENDS)
	ADD_DEPENDENCIES(${TOOLKIT} ${TOOLKIT_DEPENDS})
ENDIF(TOOLKIT_DEPENDS)

###########
# INSTALL #
###########
SET(TOOLKIT_INSTALL_BIN_DIR ${OCE_INSTALL_BIN_DIR})

MACRO(SET_TARGET_PROPERTIES_INSTALL_RPATH target dirs)
	IF(OCE_RPATH_FILTER_SYSTEM_PATHS)
		SET(non_system_paths "")
		FOREACH(dir ${dirs})
			LIST(FIND CMAKE_INSTALL_RPATH "${dir}" _exists)
			LIST(FIND CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "${dir}" _isSystem)
			IF("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
				LIST(APPEND non_system_paths "${dir}")
			ENDIF("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
		ENDFOREACH(dir ${dirs})
	ELSE(OCE_RPATH_FILTER_SYSTEM_PATHS)
		SET(non_system_paths "${dirs}")
	ENDIF(OCE_RPATH_FILTER_SYSTEM_PATHS)
	IF(NOT "${non_system_paths}" STREQUAL "")
		SET_TARGET_PROPERTIES(${target} PROPERTIES INSTALL_RPATH "${non_system_paths}")
	ENDIF(NOT "${non_system_paths}" STREQUAL "")
ENDMACRO(SET_TARGET_PROPERTIES_INSTALL_RPATH target dir)

IF(TOOLKIT_IS_PRIVATE)
	SET(TOOLKIT_INSTALL_LIB_DIR ${OCE_INSTALL_PACKAGE_LIB_DIR})
	SET_TARGET_PROPERTIES_INSTALL_RPATH(${TOOLKIT} "${OCE_INSTALL_PACKAGE_LIB_DIR_RPATH};${OCE_INSTALL_LIB_DIR_RPATH}")
ELSE(TOOLKIT_IS_PRIVATE)
	SET(TOOLKIT_INSTALL_LIB_DIR ${OCE_INSTALL_LIB_DIR})
	SET_TARGET_PROPERTIES_INSTALL_RPATH(${TOOLKIT} "${OCE_INSTALL_LIB_DIR_RPATH}")
ENDIF(TOOLKIT_IS_PRIVATE)

INSTALL(FILES ${TOOLKIT_HEADER_FILES}
	DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development
)

INSTALL(TARGETS ${TOOLKIT}
	EXPORT OCE-libraries
	RUNTIME DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
	LIBRARY DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
	ARCHIVE DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT Development
	)

IF(MSVC AND OCE_INSTALL_PDB_FILES )
	IF (CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/RelWithDebInfo/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/Debug/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	ELSE(CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	ENDIF (CMAKE_CONFIGURATION_TYPES)
ENDIF(MSVC AND OCE_INSTALL_PDB_FILES )

IF(BORLAND AND OCE_INSTALL_TDS_FILES )
	IF (CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/Debug/${TOOLKIT}.tds DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	ELSE (CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}.tds DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	ENDIF (CMAKE_CONFIGURATION_TYPES)
ENDIF(BORLAND AND OCE_INSTALL_TDS_FILES )
