set(TOOLKIT_APP DRAWEXE)

set(TOOLKIT_APP_MODULES
	DRAWEXE
)
set(TOOLKIT_APP_LIBS
	TKDraw
	TKMesh
	TKTopAlgo
	TKHLR
	TKGeomAlgo
	TKGeomBase
	TKG2d
	TKBRep
	TKMath
	TKG3d
	TKernel
	TKService
)

message(STATUS "Processing application: ${TOOLKIT_APP} (${TOOLKIT_APP_MODULES})")
set(TOOLKIT_APP_SOURCE_FILES)
foreach(MODULE ${TOOLKIT_APP_MODULES})
	# add all .cxx/*.c files or each module
	file(GLOB source_files
		${OCE_SOURCE_DIR}/src/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/src/${MODULE}/*.c
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.cxx
		${OCE_SOURCE_DIR}/drv/${MODULE}/*.c)
	#message(STATUS "${source_files}")
	foreach(module_source_file ${source_files})
		if (WIN32)
			# For compilers under Windows a define must be set per file to correctly set the export macro
			set_source_files_properties(${module_source_file} PROPERTIES COMPILE_FLAGS "-D__${MODULE}_DLL")
		endif(WIN32)
	endforeach(module_source_file ${source_files})

	# append these source files to the list of source files of the toolkit
	set(TOOLKIT_APP_SOURCE_FILES ${TOOLKIT_APP_SOURCE_FILES} ${source_files})
	# required include paths
	set(OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES} 
	    ${OCE_SOURCE_DIR}/src/${MODULE}
	    ${OCE_SOURCE_DIR}/drv/${MODULE})
endforeach(MODULE ${TOOLKIT_APP_MODULES})

if(TOOLKIT_APP_LIBS AND NOT OCE_COPY_HEADERS_BUILD)
	set(TOOLKIT_DEPENDS_INCLUDE_DIRECTORIES)
	foreach(tkit ${TOOLKIT_APP_LIBS})
		set(TOOLKIT_DEPENDS_INCLUDE_DIRECTORIES ${TOOLKIT_DEPENDS_INCLUDE_DIRECTORIES} ${OCE_${tkit}_INCLUDE_DIRECTORIES})
	endforeach(tkit ${TOOLKIT_APP_LIBS})
	list(REMOVE_DUPLICATES TOOLKIT_DEPENDS_INCLUDE_DIRECTORIES)
	set(OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES ${OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES}
	    ${TOOLKIT_DEPENDS_INCLUDE_DIRECTORIES})
endif(TOOLKIT_APP_LIBS AND NOT OCE_COPY_HEADERS_BUILD)

# Version info
if(NOT OCE_NO_LIBRARY_VERSION)
	if(MSVC)
		set(TOOLKIT_RESOURCES ${OCE_WIN32_RES_FILE})
		add_definitions("-DOCE_VERSION_INFO_IS_EXE")
	endif(MSVC)
endif(NOT OCE_NO_LIBRARY_VERSION)

add_executable(${TOOLKIT_APP} ${TOOLKIT_APP_SOURCE_FILES} ${TOOLKIT_RESOURCES} )

#if cmake is new enough, set include directories per-target 
#to avoid accumulating unnecessary directories
if(${CMAKE_VERSION} VERSION_GREATER "2.8.7")
	set_property(TARGET ${TOOLKIT_APP} APPEND PROPERTY
                 INCLUDE_DIRECTORIES "${OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES}")
else()
	include_directories(${OCE_${TOOLKIT_APP}_INCLUDE_DIRECTORIES})
endif()

set_target_properties_install_rpath(${TOOLKIT_APP} "${OCE_INSTALL_LIB_DIR_RPATH};${OCE_INSTALL_PACKAGE_LIB_DIR_RPATH}")

if(WIN32 AND (CMAKE_CONFIGURATION_TYPES OR NMAKE))
	set_target_properties(${TOOLKIT_APP} PROPERTIES
		DEBUG_OUTPUT_NAME ${TOOLKIT_APP}${CMAKE_DEBUG_POSTFIX}
	)
endif(WIN32 AND (CMAKE_CONFIGURATION_TYPES OR NMAKE))

# Set dependencies for thit ToolKit
list(REMOVE_DUPLICATES TOOLKIT_APP_LIBS)
target_link_libraries(${TOOLKIT_APP} ${TOOLKIT_APP_LIBS} ${WIN32_LIBS})

#  Those are private libraries
install(TARGETS ${TOOLKIT_APP}
	RUNTIME DESTINATION ${OCE_INSTALL_BIN_DIR}         COMPONENT RuntimeLibraries
	LIBRARY DESTINATION ${OCE_INSTALL_PACKAGE_LIB_DIR} COMPONENT RuntimeLibraries
	ARCHIVE DESTINATION ${OCE_INSTALL_PACKAGE_LIB_DIR} COMPONENT Development
)

