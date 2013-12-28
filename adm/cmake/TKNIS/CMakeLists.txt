project(TKNIS)

if (WIN32)
  list( APPEND TKNIS_PRECOMPILED_DEFS "-D__NIS_DLL" )
  string( REGEX REPLACE ";" " " TKNIS_PRECOMPILED_DEFS "${TKNIS_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKNIS_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKNIS_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKNIS_COMPILER_DIRECTORIES "../../../drv/NIS" )
  list( APPEND TKNIS_COMPILER_DIRECTORIES "../../../src/NIS" )

if (WIN32)
else()
endif()

  list( APPEND TKNIS_USED_LIBS TKBRep )
  list( APPEND TKNIS_USED_LIBS TKV3d )
  list( APPEND TKNIS_USED_LIBS TKMath )
  list( APPEND TKNIS_USED_LIBS TKernel )
  list( APPEND TKNIS_USED_LIBS TKService )
  list( APPEND TKNIS_USED_LIBS TKG2d )
  list( APPEND TKNIS_USED_LIBS TKG3d )
  list( APPEND TKNIS_USED_LIBS TKMesh )

if (WIN32)
  list( APPEND TKNIS_USED_LIBS opengl32.lib )
  list( APPEND TKNIS_USED_LIBS glu32.lib )
  list( APPEND TKNIS_USED_LIBS user32.lib )
  list( APPEND TKNIS_USED_LIBS gdi32.lib )
elseif(APPLE)
  find_library(FRAMEWORKS_OPENGL NAMES OpenGL)
  if(USE_GLX)
    list( APPEND TKNIS_USED_LIBS GL )
    list( APPEND TKNIS_USED_LIBS GLU )
  else()
    list( APPEND TKNIS_USED_LIBS ${FRAMEWORKS_OPENGL} )
  endif()
else()
  list( APPEND TKNIS_USED_LIBS GLU )
  list( APPEND TKNIS_USED_LIBS GL )
endif()

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_Allocator.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_Allocator.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_DrawList.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_DrawList.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_Drawer.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_Drawer.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_InteractiveContext.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_InteractiveContext.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_InteractiveObject.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_InteractiveObject.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_ObjectsIterator.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_ObjectsIterator.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_SelectFilter.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_SelectFilter.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_Surface.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_Surface.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_SurfaceDrawer.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_SurfaceDrawer.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_Triangulated.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_Triangulated.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_TriangulatedDrawer.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_TriangulatedDrawer.cxx")

  list( APPEND TKNIS_USED_SRCFILES "../../../src/NIS/NIS_View.cxx" )
  SOURCE_GROUP (NIS FILES "../../../src/NIS/NIS_View.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKNIS)
 add_library( TKNIS SHARED ${TKNIS_USED_SRCFILES} )

 set_property(TARGET TKNIS PROPERTY FOLDER Visualization)

 install( TARGETS TKNIS
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKNIS.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKNIS PROPERTIES COMPILE_FLAGS "${TKNIS_PRECOMPILED_DEFS}" )
 include_directories( ${TKNIS_COMPILER_DIRECTORIES} )
 target_link_libraries( TKNIS ${TKNIS_USED_LIBS} )
endif()
