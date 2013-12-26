
# Instructs the MSVC toolset to use the precompiled header PRECOMPILED_HEADER
# for each source file given in the collection named by SOURCE_VARIABLE_NAME.
function(enable_precompiled_headers PHASE TARGET_NAME PRECOMPILED_HEADER SOURCE_VARIABLE_NAME)
	if(MSVC OR CMAKE_COMPILER_IS_GNUCXX)
		set(files ${${SOURCE_VARIABLE_NAME}})

		# Generate precompiled header translation unit
		get_filename_component(pch_basename ${PRECOMPILED_HEADER} NAME_WE)
		set(pch_unity ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.cpp)

		if(MSVC)
			set(pch_abs ${CMAKE_CURRENT_SOURCE_DIR}/${PRECOMPILED_HEADER})
		else()
			configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h ${CMAKE_CURRENT_BINARY_DIR}/Precompiled.h)
			set(pch_abs ${CMAKE_CURRENT_BINARY_DIR}/${PRECOMPILED_HEADER})
		endif()

		if (PHASE EQUAL 2)
			# A list of exclusions patterns. For the moment is global to the entire project
			set (excludes "OSD*" "WNT*" "AlienImage_BMPAlienData.cxx"
			              "Image_PixMap.cxx" "PlotMgt.cxx" "Visual3d_View.cxx" "V3d_View_Print.cxx" "OpenGl*"
			              "Viewer2dTest_ViewerCommands.cxx" "ViewerTest_*" )

			# GCC requires an additional target to build the PCH file.
			if(CMAKE_COMPILER_IS_GNUCXX)

				# PCH output file
				#set(pch_output "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.gch")
				set(pch_output "${pch_abs}.gch")

				# Detects compiler flags
				string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
				set(_compiler_FLAGS ${${_flags_var_name}})

				# Directory properties
				get_directory_property(_directory_flags INCLUDE_DIRECTORIES)
				foreach(item ${_directory_flags})
					list(APPEND _compiler_FLAGS "-I${item}")
				endforeach(item)

				get_target_property(target_compiler_FLAGS ${TARGET_NAME} COMPILE_FLAGS)
				if(target_compiler_FLAGS)
					list(APPEND _compiler_FLAGS ${target_compiler_FLAGS})
				endif()

				string(TOUPPER "COMPILE_DEFINITIONS_${CMAKE_BUILD_TYPE}" _defs_prop_name)

				get_directory_property(_directory_flags COMPILE_DEFINITIONS)
				if(_directory_flags)
					foreach(flag ${_directory_flags})
						list(APPEND _compiler_FLAGS -D${flag})
					endforeach(flag)
				endif(_directory_flags)

				get_directory_property(_directory_flags ${_defs_prop_name})
				if(_directory_flags)
					foreach(flag ${_directory_flags})
						list(APPEND _compiler_FLAGS -D${flag})
					endforeach(flag)
				endif(_directory_flags)

				get_target_property(_target_flags ${TARGET_NAME} COMPILE_DEFINITIONS)
				if(_target_flags)
					foreach(flag ${_target_flags})
						list(APPEND _compiler_FLAGS -D${flag})
					endforeach(flag)
				endif(_target_flags)

				get_target_property(_target_flags ${TARGET_NAME} ${_defs_prop_name})
				if(_target_flags)
					foreach(flag ${_target_flags})
						list(APPEND _compiler_FLAGS -D${flag})
					endforeach(flag)
				endif(_target_flags)

				#message("compiler flags :" ${_compiler_FLAGS})

				separate_arguments(_compiler_FLAGS)

				if(NOT WIN32)
					set(additionalCompilerFlags -fPIC)
				else()
					set(additionalCompilerFlags -mthreads)
				endif()

				add_custom_command(OUTPUT ${pch_output}
				                   COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header -o ${pch_output} ${pch_unity} ${additionalCompilerFlags}
				                   DEPENDS ${pch_unity} )
				add_custom_target(${TARGET_NAME}_gch DEPENDS ${pch_output})
				add_dependencies(${TARGET_NAME} ${TARGET_NAME}_gch)
			endif()

			# Update properties of source files to use the precompiled header.
			# Additionally, force the inclusion of the precompiled header at beginning of each source file.
			foreach(source_file ${files} )
				# Find if the file is on the exclusion list
				set(IsExclude FALSE)
				foreach (exc ${excludes})
					if(${source_file} MATCHES ${exc})
						set(IsExclude TRUE)
					endif()
				endforeach ()
				if (NOT IsExclude)
					get_filename_component(thisext ${source_file} EXT)
					if (${thisext} MATCHES ".cxx")
						if (MSVC)
							set_source_files_properties( ${source_file} PROPERTIES COMPILE_FLAGS "/Yu\"${PRECOMPILED_HEADER}\" /FI\"${PRECOMPILED_HEADER}\""     )
						endif()
						if (CMAKE_COMPILER_IS_GNUCXX)
							set_source_files_properties( ${source_file} PROPERTIES COMPILE_FLAGS "-include ${pch_abs} -Winvalid-pch")
						endif()
					endif()
				endif()
			endforeach(source_file)
		else(PHASE EQUAL 2)
			# Finally, update the source file collection to contain the precompiled header translation unit
			set(${SOURCE_VARIABLE_NAME} ${pch_unity} ${PRECOMPILED_HEADER} ${${SOURCE_VARIABLE_NAME}} PARENT_SCOPE)

			#set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${pch_abs}\"") #this may be useful for nmake
			if(MSVC)
				set_source_files_properties(${pch_unity} PROPERTIES COMPILE_FLAGS "/Yc\"${PRECOMPILED_HEADER}\"")
			endif()
		endif(PHASE EQUAL 2)
	endif()
endfunction(enable_precompiled_headers)

message(STATUS "Processing ToolKit: ${TOOLKIT} (${TOOLKIT_MODULES})")
list(APPEND OCE_ALL_BUILT_MODULES ${TOOLKIT_MODULES})
set(OCE_ALL_BUILT_MODULES ${OCE_ALL_BUILT_MODULES} PARENT_SCOPE)
set(TOOLKIT_SOURCE_FILES)
set(TOOLKIT_HEADER_FILES)
set(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${TOOLKIT_INCLUDE_DIRECTORIES})
foreach(MODULE ${TOOLKIT_MODULES})

	if(APPLE AND OCE_OSX_USE_COCOA)
		file(GLOB source_files
			${OCE_SOURCE_DIR}/src/${MODULE}/*.cxx
			${OCE_SOURCE_DIR}/src/${MODULE}/*.mm
			${OCE_SOURCE_DIR}/src/${MODULE}/*.c
			${OCE_SOURCE_DIR}/drv/${MODULE}/*.cxx
			${OCE_SOURCE_DIR}/drv/${MODULE}/*.c)
	# add all .cxx/*.c files or each module
	else(APPLE AND OCE_OSX_USE_COCOA)
		file(GLOB source_files
			${OCE_SOURCE_DIR}/src/${MODULE}/*.cxx
			${OCE_SOURCE_DIR}/src/${MODULE}/*.c
			${OCE_SOURCE_DIR}/drv/${MODULE}/*.cxx
			${OCE_SOURCE_DIR}/drv/${MODULE}/*.c)
	endif(APPLE AND OCE_OSX_USE_COCOA)
	set (header_files "")

	file(GLOB header_files
		${OCE_SOURCE_DIR}/src/${MODULE}/*.h
		${OCE_SOURCE_DIR}/src/${MODULE}/*.hxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.gxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.lxx)
	if(OCE_ADD_HEADERS)
		list(APPEND source_files ${header_files})
	endif(OCE_ADD_HEADERS)

	set(TOOLKIT_HEADER_FILES ${TOOLKIT_HEADER_FILES} ${header_files})
	set(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} ${OCE_SOURCE_DIR}/src/${MODULE})
	if(IS_DIRECTORY ${OCE_SOURCE_DIR}/drv/${MODULE})
	    set(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} ${OCE_SOURCE_DIR}/drv/${MODULE})
	endif(IS_DIRECTORY ${OCE_SOURCE_DIR}/drv/${MODULE})

	if (WIN32)
		# For compilers under Windows a define must be set per file to correctly set the export macro
		add_definitions("-D__${MODULE}_DLL")
	endif(WIN32)

	source_group (${MODULE} FILES ${source_files})

	# append these source files to the list of source files of the toolkit
	set(TOOLKIT_SOURCE_FILES ${TOOLKIT_SOURCE_FILES} ${source_files})
	# required include paths
endforeach(MODULE ${TOOLKIT_MODULES})

if(TOOLKIT_DEPENDS)
	foreach(tkit ${TOOLKIT_DEPENDS})
		set(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} ${OCE_${tkit}_INCLUDE_DIRECTORIES})
	endforeach(tkit ${TOOLKIT_DEPENDS})
	list(REMOVE_DUPLICATES OCE_${TOOLKIT}_INCLUDE_DIRECTORIES)
endif(TOOLKIT_DEPENDS)
set(OCE_${TOOLKIT}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES} PARENT_SCOPE)
include_directories(${OCE_${TOOLKIT}_INCLUDE_DIRECTORIES})

# Version info
if(NOT OCE_NO_LIBRARY_VERSION)
	if(MSVC)
		set(TOOLKIT_RESOURCES ${OCE_WIN32_RES_FILE})
	endif(MSVC)
endif(NOT OCE_NO_LIBRARY_VERSION)

# Precompiled Headers
if(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)
	if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
		#message("Using Precompiled.h")
		enable_precompiled_headers (1 ${TOOLKIT} Precompiled.h TOOLKIT_SOURCE_FILES)
		source_group (Precompiled FILES Precompiled.h Precompiled.cpp)
	endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
endif(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)

# Add the toolkit target
add_library(${TOOLKIT} ${OCE_LIBRARY_TYPE} ${TOOLKIT_SOURCE_FILES} ${TOOLKIT_RESOURCES} )

if(OCE_COMPILER_SUPPORTS_PCH AND OCE_USE_PCH)
	if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Precompiled.h)
		enable_precompiled_headers (2 ${TOOLKIT} Precompiled.h TOOLKIT_SOURCE_FILES)
	endif()
endif()

# TODO Add current toolkit header files into a source group?
# Add target specific locations of *.lxx and *.ixx files
if(NOT OCE_NO_LIBRARY_VERSION)
	set_target_properties(${TOOLKIT} PROPERTIES
	                      SOVERSION ${OCE_ABI_SOVERSION}
	                      VERSION ${OCE_ABI_VERSION}
	)
endif(NOT OCE_NO_LIBRARY_VERSION)

# Workaround for Cmake bug #0011240 (see http://public.kitware.com/Bug/view.php?id=11240)
# Win64+MSVC+static libs = linker error
if(MSVC AND NOT OCE_BUILD_SHARED_LIB AND BIT EQUAL 64)
	set_target_properties(${TOOLKIT} PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
endif()

# Set dependencies for thit ToolKit
if ( NOT "${TOOLKIT}" STREQUAL "TKernel" )
	list(REMOVE_DUPLICATES TOOLKIT_DEPENDS)
endif ( NOT "${TOOLKIT}" STREQUAL "TKernel" )
target_link_libraries(${TOOLKIT} ${TOOLKIT_DEPENDS} ${TOOLKIT_LIBS} ${WIN32_LIBS})

if(TOOLKIT_LIBS_OPTIMIZED)
	foreach(lib ${TOOLKIT_LIBS_OPTIMIZED})
		target_link_libraries(${TOOLKIT} optimized ${lib})
	endforeach(lib ${TOOLKIT_LIBS_OPTIMIZED})
endif(TOOLKIT_LIBS_OPTIMIZED)

if(TOOLKIT_LIBS_DEBUG)
	foreach(lib ${TOOLKIT_LIBS_DEBUG})
		target_link_libraries(${TOOLKIT} debug ${lib})
	endforeach(lib ${TOOLKIT_LIBS_DEBUG})
endif(TOOLKIT_LIBS_DEBUG)

if(TOOLKIT_DEPENDS)
	add_dependencies(${TOOLKIT} ${TOOLKIT_DEPENDS})
endif(TOOLKIT_DEPENDS)

# Only add the copy target if there are headers to copy.
if( TOOLKIT_HEADER_FILES AND OCE_COPY_HEADERS_BUILD )
  #
  # Install all toolkit header files into the include subdirectory of the OCE
  # build directory so they are available at build time.
  #
  set( toolkit_header_destination_dir "${OCE_BINARY_DIR}/include" )
  # With at least VS2012 and CMake 2.8.10.2, the -Dfiles_to_copy
  # command-line argument seemed to run into trouble when the length
  # of that argument was greater than 8192 (2^13).
  # The following breaks up the copy into multiple custom commands
  # to avoid exceeding max_argument_length.
  set( max_argument_length 6000 )
  # Add 5 because CMake separates files like so in Visual Studio:
  # -Dfiles_to_copy=one";"two";"three. 5 is a little more than 3
  # and that should hopefully cover complex escaping.
  set( file_separation_escape_length 5 )
  set( source_header_files "" )
  set( destination_header_files "" )
  set( all_destination_header_files "" )
  set( arg_length 0 )
  function( add_header_files_copy_command source_files_var destination_files_var )
    add_custom_command(
      OUTPUT ${${destination_files_var}}
      COMMAND ${CMAKE_COMMAND}
        "-Dfiles_to_copy=${${source_files_var}}"
        "-Ddestination_directory=${toolkit_header_destination_dir}"
        -P "${CMAKE_CURRENT_LIST_DIR}/CopyFiles.cmake"
      DEPENDS "${CMAKE_CURRENT_LIST_DIR}/CopyFiles.cmake" ${${source_files_var}}
      COMMENT "Copying headers for ${TOOLKIT}"
      VERBATIM
    )
  endfunction()
  foreach( source_header_file ${TOOLKIT_HEADER_FILES} )
    string( LENGTH "${source_header_file}" source_header_file_length )
    math( EXPR current_source_header_additional_length "${source_header_file_length} + ${file_separation_escape_length}" )
    math( EXPR arg_length "${arg_length} + ${current_source_header_additional_length}" )
    get_filename_component( source_header_filename "${source_header_file}" NAME )
    set( destination_header_file "${toolkit_header_destination_dir}/${source_header_filename}" )
    if( arg_length LESS max_argument_length )
      list( APPEND source_header_files "${source_header_file}" )
      list( APPEND destination_header_files "${destination_header_file}" )
    else()
      # Dump the current command
      add_header_files_copy_command( source_header_files destination_header_files )
      list( APPEND all_destination_header_files ${destination_header_files} )
      # Reset data structures
      set( source_header_files "" )
      set( destination_header_files "" )
      set( arg_length 0 )
      # Add current file
      list( APPEND source_header_files "${source_header_file}" )
      list( APPEND destination_header_files "${destination_header_file}" )
      math( EXPR arg_length "${arg_length} + ${current_source_header_additional_length}" )
    endif()
  endforeach()
  if( NOT source_header_files STREQUAL "" )
    add_header_files_copy_command( source_header_files destination_header_files )
    list( APPEND all_destination_header_files ${destination_header_files} )
  endif()

  add_custom_target( copy_${TOOLKIT}_headers ALL
    DEPENDS ${all_destination_header_files}
  )

endif()

###########
# INSTALL #
###########
set(TOOLKIT_INSTALL_BIN_DIR ${OCE_INSTALL_BIN_DIR})

macro(set_target_properties_install_rpath target dirs)
	if(OCE_RPATH_FILTER_SYSTEM_PATHS)
		set(non_system_paths "")
		foreach(dir ${dirs})
			list(FIND CMAKE_INSTALL_RPATH "${dir}" _exists)
			list(FIND CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "${dir}" _isSystem)
			if("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
				list(APPEND non_system_paths "${dir}")
			endif("${_exists}" LESS 0 AND "${_isSystem}" LESS 0)
		endforeach(dir ${dirs})
	else(OCE_RPATH_FILTER_SYSTEM_PATHS)
		set(non_system_paths "${dirs}")
	endif(OCE_RPATH_FILTER_SYSTEM_PATHS)
	if(NOT "${non_system_paths}" STREQUAL "")
		set_target_properties(${target} PROPERTIES INSTALL_RPATH "${non_system_paths}")
	endif(NOT "${non_system_paths}" STREQUAL "")
endmacro(set_target_properties_install_rpath target dir)

if(TOOLKIT_IS_PRIVATE)
	set(TOOLKIT_INSTALL_LIB_DIR ${OCE_INSTALL_PACKAGE_LIB_DIR})
	if(TOOLKIT_DEPENDS)
		set_target_properties_install_rpath(${TOOLKIT} "${OCE_INSTALL_PACKAGE_LIB_DIR_RPATH};${OCE_INSTALL_LIB_DIR_RPATH}")
	endif(TOOLKIT_DEPENDS)
else(TOOLKIT_IS_PRIVATE)
	set(TOOLKIT_INSTALL_LIB_DIR ${OCE_INSTALL_LIB_DIR})
	if(TOOLKIT_DEPENDS)
		set_target_properties_install_rpath(${TOOLKIT} "${OCE_INSTALL_LIB_DIR_RPATH}")
	endif(TOOLKIT_DEPENDS)
endif(TOOLKIT_IS_PRIVATE)

install(FILES ${TOOLKIT_HEADER_FILES}
	DESTINATION ${OCE_INSTALL_INCLUDE_DIR} COMPONENT Development
)

install(TARGETS ${TOOLKIT}
	EXPORT OCE-libraries
	RUNTIME DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
	LIBRARY DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
	ARCHIVE DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} COMPONENT Development
	)

if(MSVC AND OCE_INSTALL_PDB_FILES )
	if (CMAKE_CONFIGURATION_TYPES)
		install(FILES ${LIBRARY_OUTPUT_PATH}/RelWithDebInfo/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		install(FILES ${LIBRARY_OUTPUT_PATH}/Debug/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	else(CMAKE_CONFIGURATION_TYPES)
		install(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS RelWithDebInfo)
		install(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}${CMAKE_DEBUG_POSTFIX}.pdb DESTINATION ${TOOLKIT_INSTALL_LIB_DIR} CONFIGURATIONS Debug)
	endif (CMAKE_CONFIGURATION_TYPES)
endif(MSVC AND OCE_INSTALL_PDB_FILES )

if(BORLAND AND OCE_INSTALL_TDS_FILES )
	if (CMAKE_CONFIGURATION_TYPES)
		install(FILES ${LIBRARY_OUTPUT_PATH}/Debug/${TOOLKIT}.tds DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	else (CMAKE_CONFIGURATION_TYPES)
		install(FILES ${LIBRARY_OUTPUT_PATH}/${TOOLKIT}.tds DESTINATION ${TOOLKIT_INSTALL_BIN_DIR} CONFIGURATIONS Debug)
	endif (CMAKE_CONFIGURATION_TYPES)
endif(BORLAND AND OCE_INSTALL_TDS_FILES )
