project(TKViewerTest)

if (WIN32)
  list( APPEND TKViewerTest_PRECOMPILED_DEFS "-D__ViewerTest_DLL" )
  string( REGEX REPLACE ";" " " TKViewerTest_PRECOMPILED_DEFS "${TKViewerTest_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKViewerTest_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKViewerTest_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKViewerTest_COMPILER_DIRECTORIES "../../../drv/ViewerTest" )
  list( APPEND TKViewerTest_COMPILER_DIRECTORIES "../../../src/ViewerTest" )

if (WIN32)
else()
endif()

  list( APPEND TKViewerTest_USED_LIBS TKGeomBase )
  list( APPEND TKViewerTest_USED_LIBS TKFillet )
  list( APPEND TKViewerTest_USED_LIBS TKBRep )
  list( APPEND TKViewerTest_USED_LIBS TKTopAlgo )
  list( APPEND TKViewerTest_USED_LIBS TKHLR )
  list( APPEND TKViewerTest_USED_LIBS TKernel )
  list( APPEND TKViewerTest_USED_LIBS TKMath )
  list( APPEND TKViewerTest_USED_LIBS TKNIS )
  list( APPEND TKViewerTest_USED_LIBS TKService )
  list( APPEND TKViewerTest_USED_LIBS TKShHealing )
  list( APPEND TKViewerTest_USED_LIBS TKBool )
  list( APPEND TKViewerTest_USED_LIBS TKPrim )
  list( APPEND TKViewerTest_USED_LIBS TKGeomAlgo )
  list( APPEND TKViewerTest_USED_LIBS TKG2d )
  list( APPEND TKViewerTest_USED_LIBS TKTopTest )
  list( APPEND TKViewerTest_USED_LIBS TKG3d )
  list( APPEND TKViewerTest_USED_LIBS TKOffset )
  list( APPEND TKViewerTest_USED_LIBS TKVoxel )
  list( APPEND TKViewerTest_USED_LIBS TKMesh )
  list( APPEND TKViewerTest_USED_LIBS TKV3d )
  list( APPEND TKViewerTest_USED_LIBS TKDraw )
  list( APPEND TKViewerTest_USED_LIBS TKOpenGl )

if (WIN32)
  list( APPEND TKViewerTest_USED_LIBS user32.lib )
  list( APPEND TKViewerTest_USED_LIBS gdi32.lib )
  list( APPEND TKViewerTest_USED_LIBS opengl32.lib )
  list( APPEND TKViewerTest_USED_LIBS glu32.lib )
elseif(APPLE)
  find_library(FRAMEWORKS_TCL NAMES Tcl)
  list( APPEND TKViewerTest_USED_LIBS ${FRAMEWORKS_TCL} )
  find_library(FRAMEWORKS_TK NAMES Tk)
  list( APPEND TKViewerTest_USED_LIBS ${FRAMEWORKS_TK} )
  find_library(FRAMEWORKS_OPENGL NAMES OpenGL)
  if(USE_GLX)
    list( APPEND TKViewerTest_USED_LIBS GL )
    list( APPEND TKViewerTest_USED_LIBS GLU )
  else()
    list( APPEND TKViewerTest_USED_LIBS ${FRAMEWORKS_OPENGL} )
  endif()
  list( APPEND TKViewerTest_USED_LIBS objc )
  find_library(FRAMEWORKS_APPKIT NAMES Appkit)
  list( APPEND TKViewerTest_USED_LIBS ${FRAMEWORKS_APPKIT} )
  find_library(FRAMEWORKS_IOKIT NAMES IOKit)
  list( APPEND TKViewerTest_USED_LIBS ${FRAMEWORKS_IOKIT} )
  list( APPEND TKViewerTest_USED_LIBS freetype )
else()
  list( APPEND TKViewerTest_USED_LIBS tcl8.6 )
  list( APPEND TKViewerTest_USED_LIBS X11 )
  list( APPEND TKViewerTest_USED_LIBS tk8.6 )
  list( APPEND TKViewerTest_USED_LIBS GLU )
  list( APPEND TKViewerTest_USED_LIBS GL )
  list( APPEND TKViewerTest_USED_LIBS freetype )
endif()

  list( APPEND TKViewerTest_USED_SRCFILES "../../../drv/ViewerTest/ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName_0.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../drv/ViewerTest/ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName_0.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../drv/ViewerTest/ViewerTest_DoubleMapNodeOfDoubleMapOfInteractiveAndName_0.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../drv/ViewerTest/ViewerTest_DoubleMapNodeOfDoubleMapOfInteractiveAndName_0.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../drv/ViewerTest/ViewerTest_DoubleMapOfInteractiveAndName_0.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../drv/ViewerTest/ViewerTest_DoubleMapOfInteractiveAndName_0.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_AviCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_AviCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_EventManager.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_EventManager.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_FilletCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_FilletCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_ObjectCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_ObjectCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_OpenGlCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_OpenGlCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_RelationCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_RelationCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_Tool.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_Tool.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_ViewerCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_ViewerCommands.cxx")

  list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_VoxelCommands.cxx" )
  SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_VoxelCommands.cxx")

if (WIN32)
else()

  if (APPLE)

    list( APPEND TKViewerTest_USED_SRCFILES "../../../src/ViewerTest/ViewerTest_ViewerCommands_1.mm" )
    SOURCE_GROUP (ViewerTest FILES "../../../src/ViewerTest/ViewerTest_ViewerCommands_1.mm")

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKViewerTest)
 add_library( TKViewerTest SHARED ${TKViewerTest_USED_SRCFILES} )

 set_property(TARGET TKViewerTest PROPERTY FOLDER Draw)

 install( TARGETS TKViewerTest
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKViewerTest.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKViewerTest PROPERTIES COMPILE_FLAGS "${TKViewerTest_PRECOMPILED_DEFS}" )
 include_directories( ${TKViewerTest_COMPILER_DIRECTORIES} )
 target_link_libraries( TKViewerTest ${TKViewerTest_USED_LIBS} )
endif()
