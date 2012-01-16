
# Instructs the MSVC toolset to use the precompiled header PRECOMPILED_HEADER
# for each source file given in the collection named by SOURCE_VARIABLE_NAME.
FUNCTION(ENABLE_PRECOMPILED_HEADERS PRECOMPILED_HEADER SOURCE_VARIABLE_NAME)
	IF(MSVC)
		set(files ${${SOURCE_VARIABLE_NAME}})

		# Generate precompiled header translation unit
		get_filename_component(pch_basename ${PRECOMPILED_HEADER} NAME_WE)
		set(pch_abs ${CMAKE_CURRENT_SOURCE_DIR}/${PRECOMPILED_HEADER})
		set(pch_unity ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.cpp)
		#set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${pch_abs}\"") #this may be useful for nmake
		set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${PRECOMPILED_HEADER}\"")

		# A list of exclusions patterns. For the moment is global to the entire project
		SET (excludes "OSD*" "WNT*" "AlienImage_BMPAlienData.cxx"
		              "Image_PixMap.cxx" "PlotMgt.cxx" "Visual3d_View.cxx" "V3d_View_Print.cxx" "OpenGl*"
		              "Viewer2dTest_ViewerCommands.cxx" "ViewerTest_*" )

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
					set_source_files_properties( ${source_file} PROPERTIES COMPILE_FLAGS "/Yu\"${PRECOMPILED_HEADER}\" /FI\"${PRECOMPILED_HEADER}\""     )
				ENDIF()
			ENDIF()
		endforeach(source_file)

		# Finally, update the source file collection to contain the precompiled header translation unit
		set(${SOURCE_VARIABLE_NAME} ${pch_unity} ${PRECOMPILED_HEADER} ${${SOURCE_VARIABLE_NAME}} PARENT_SCOPE)

	ENDIF(MSVC)
ENDFUNCTION(ENABLE_PRECOMPILED_HEADERS)

MESSAGE(STATUS "Processing ToolKit: ${TOOLKIT} (${TOOLKIT_MODULES})")
SET(TOOLKIT_SOURCE_FILES)
IF(DEFINED TOOLKIT_INCLUDE_DIRECTORIES)
	INCLUDE_DIRECTORIES(${TOOLKIT_INCLUDE_DIRECTORIES})
ENDIF(DEFINED TOOLKIT_INCLUDE_DIRECTORIES)
FOREACH(MODULE ${TOOLKIT_MODULES})
	
	# add all .cxx/*.c files or each module
	FILE(GLOB source_files
		${${PROJECT_NAME}_SOURCE_DIR}/src/${MODULE}/*.cxx
		${${PROJECT_NAME}_SOURCE_DIR}/src/${MODULE}/*.c
		${${PROJECT_NAME}_SOURCE_DIR}/drv/${MODULE}/*.cxx
		${${PROJECT_NAME}_SOURCE_DIR}/drv/${MODULE}/*.c)
	SET (header_files "")
	
	IF(${PROJECT_NAME}_ADD_HEADERS)
		FILE(GLOB header_files  ${${PROJECT_NAME}_SOURCE_DIR}/inc/${MODULE}_*.hxx)
		LIST(APPEND source_files ${header_files})
	ENDIF(${PROJECT_NAME}_ADD_HEADERS)

	IF (WIN32)
		# For compilers under Windows a define must be set per file to correctly set the export macro
		ADD_DEFINITIONS("-D__${MODULE}_DLL")
	ENDIF(WIN32)

	SOURCE_GROUP (${MODULE} FILES ${source_files})

	# append these source files to the list of source files of the toolkit
	SET(TOOLKIT_SOURCE_FILES ${TOOLKIT_SOURCE_FILES} ${source_files})
	# required include paths
	INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/src/${MODULE} ${${PROJECT_NAME}_SOURCE_DIR}/drv/${MODULE})
ENDFOREACH(MODULE ${TOOLKIT_MODULES})

# Version info
IF(NOT ${PROJECT_NAME}_NO_LIBRARY_VERSION)
	IF(MSVC)
		SET(TOOLKIT_RESOURCES ${CMAKE_BINARY_DIR}/Version.rc)
	ENDIF(MSVC)
ENDIF(NOT ${PROJECT_NAME}_NO_LIBRARY_VERSION)

# Precompiled Headers
IF(${PROJECT_NAME}_COMPILER_SUPPORTS_PCH AND ${PROJECT_NAME}_USE_PCH)

	IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
		#MESSAGE("Using Precompiled.h")
		ENABLE_PRECOMPILED_HEADERS (Precompiled.h TOOLKIT_SOURCE_FILES)
		SOURCE_GROUP (Precompiled FILES Precompiled.h Precompiled.cpp)
	ENDIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
ENDIF(${PROJECT_NAME}_COMPILER_SUPPORTS_PCH AND ${PROJECT_NAME}_USE_PCH)

ADD_LIBRARY(${TOOLKIT} ${${PROJECT_NAME}_LIBRARY_TYPE} ${TOOLKIT_SOURCE_FILES} ${TOOLKIT_RESOURCES} )

IF(BORLAND AND BORLAND_VERSION_RS_XE2)
	# For bcc32 compiler v6.40 and up -x- compiler option must be passed as a compiler option
	# in stead of #pragma option -x- in code.
	IF(TOOLKIT STREQUAL "TKOpenGl")
		foreach(source_file ${TOOLKIT_SOURCE_FILES} )
			if((source_file MATCHES "OpenGl_attri.cxx") OR
			   (source_file MATCHES "OpenGl_depthcue.cxx") OR
			   (source_file MATCHES "OpenGl_pick.cxx") OR
			   (source_file MATCHES "OpenGl_telem_util.cxx") OR
			   (source_file MATCHES "OpenGl_undefined.cxx") OR
			   (source_file MATCHES "OpenGl_view.cxx"))
				MESSAGE(STATUS "(bcc32) Disabling exceptions for ${source_file}.")
				set_source_files_properties("${source_file}" PROPERTIES COMPILE_FLAGS "-x-")
			endif()
		endforeach(source_file)
	ENDIF()
ENDIF(BORLAND AND BORLAND_VERSION_RS_XE2)

# TODO Add current toolkit header files into a source group?
# Add target specific locations of *.lxx and *.ixx files
IF(NOT ${PROJECT_NAME}_NO_LIBRARY_VERSION)
    SET_TARGET_PROPERTIES(${TOOLKIT} PROPERTIES
	    SOVERSION ${${PROJECT_NAME}_ABI_SOVERSION}
	    VERSION ${${PROJECT_NAME}_ABI_VERSION}
    )
ENDIF(NOT ${PROJECT_NAME}_NO_LIBRARY_VERSION)

IF(DEFINED X11_FONT_PATH)
	SET_SOURCE_FILES_PROPERTIES("${${PROJECT_NAME}_SOURCE_DIR}/src/OSD/OSD_FontMgr.cxx" PROPERTIES COMPILE_FLAGS "-DX11_FONT_PATH=\"${X11_FONT_PATH}\"")
ENDIF(DEFINED X11_FONT_PATH)

# Workaround for Cmake bug #0011240 (see http://public.kitware.com/Bug/view.php?id=11240)
# Win64+MSVC+static libs = linker error
IF(MSVC AND NOT ${PROJECT_NAME}_BUILD_SHARED_LIB AND BIT EQUAL 64)
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
SET(TOOLKIT_INSTALL_BIN_DIR ${${PROJECT_NAME}_INSTALL_BIN_DIR})

MACRO(SET_TARGET_PROPERTIES_INSTALL_RPATH target dirs)
	IF(${PROJECT_NAME}_RPATH_FILTER_SYSTEM_PATHS)
		SET(non_system_paths "")
		FOREACH(dir ${dirs})
			LIST(FIND CMAKE_INSTALL_RPATH "${dir}" _exists)
			LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${dir}" _isSystem)
			IF("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
				LIST(APPEND non_system_paths "${dir}")
			ENDIF("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
		ENDFOREACH(dir ${dirs})
	ELSE(${PROJECT_NAME}_RPATH_FILTER_SYSTEM_PATHS)
		SET(non_system_paths "${dirs}")
	ENDIF(${PROJECT_NAME}_RPATH_FILTER_SYSTEM_PATHS)
	IF(NOT "${non_system_paths}" STREQUAL "")
		SET_TARGET_PROPERTIES(${target} PROPERTIES INSTALL_RPATH "${non_system_paths}")
	ENDIF(NOT "${non_system_paths}" STREQUAL "")
ENDMACRO(SET_TARGET_PROPERTIES_INSTALL_RPATH target dir)

IF(TOOLKIT_IS_PRIVATE)
	SET(TOOLKIT_INSTALL_LIB_DIR ${${PROJECT_NAME}_INSTALL_PACKAGE_LIB_DIR})
	SET_TARGET_PROPERTIES_INSTALL_RPATH(${TOOLKIT} "${${PROJECT_NAME}_INSTALL_PREFIX}/${${PROJECT_NAME}_INSTALL_PACKAGE_LIB_DIR};${${PROJECT_NAME}_INSTALL_PREFIX}/${${PROJECT_NAME}_INSTALL_LIB_DIR}")
ELSE(TOOLKIT_IS_PRIVATE)
	SET(TOOLKIT_INSTALL_LIB_DIR ${${PROJECT_NAME}_INSTALL_LIB_DIR})
	SET_TARGET_PROPERTIES_INSTALL_RPATH(${TOOLKIT} "${${PROJECT_NAME}_INSTALL_PREFIX}/${${PROJECT_NAME}_INSTALL_LIB_DIR}")
ENDIF(TOOLKIT_IS_PRIVATE)

INSTALL(TARGETS ${TOOLKIT}
	EXPORT ${PROJECT_NAME}-libraries
	RUNTIME DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
	LIBRARY DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
	ARCHIVE DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT Development
	)

IF(MSVC AND ${PROJECT_NAME}_INSTALL_PDB_FILES )
	IF (CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/RelWithDebInfo/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/Debug/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	ELSE(CMAKE_CONFIGURATION_TYPES)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		INSTALL(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	ENDIF (CMAKE_CONFIGURATION_TYPES)
ENDIF(MSVC AND ${PROJECT_NAME}_INSTALL_PDB_FILES )
