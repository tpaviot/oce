project(TKDraw)

if (WIN32)
  list( APPEND TKDraw_PRECOMPILED_DEFS "-D__Draw_DLL" )
  list( APPEND TKDraw_PRECOMPILED_DEFS "-D__DBRep_DLL" )
  list( APPEND TKDraw_PRECOMPILED_DEFS "-D__DrawTrSurf_DLL" )
  string( REGEX REPLACE ";" " " TKDraw_PRECOMPILED_DEFS "${TKDraw_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKDraw_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../drv/Draw" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../src/Draw" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../drv/DBRep" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../src/DBRep" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../drv/DrawTrSurf" )
  list( APPEND TKDraw_COMPILER_DIRECTORIES "../../../src/DrawTrSurf" )

if (WIN32)
else()
endif()

  list( APPEND TKDraw_USED_LIBS TKernel )
  list( APPEND TKDraw_USED_LIBS TKG2d )
  list( APPEND TKDraw_USED_LIBS TKGeomBase )
  list( APPEND TKDraw_USED_LIBS TKG3d )
  list( APPEND TKDraw_USED_LIBS TKMath )
  list( APPEND TKDraw_USED_LIBS TKBRep )
  list( APPEND TKDraw_USED_LIBS TKGeomAlgo )
  list( APPEND TKDraw_USED_LIBS TKTopAlgo )
  list( APPEND TKDraw_USED_LIBS TKMesh )
  list( APPEND TKDraw_USED_LIBS TKService )
  list( APPEND TKDraw_USED_LIBS TKHLR )

if (WIN32)
  list( APPEND TKDraw_USED_LIBS tcl85.lib )
  list( APPEND TKDraw_USED_LIBS tk85.lib )
  list( APPEND TKDraw_USED_LIBS gdi32.lib )
  list( APPEND TKDraw_USED_LIBS advapi32.lib )
  list( APPEND TKDraw_USED_LIBS user32.lib )
elseif(APPLE)
  list( APPEND TKDraw_USED_LIBS tcl8.5 )
  list( APPEND TKDraw_USED_LIBS tk8.5 )
  if(3RDPARTY_USE_GLX)
    find_package(X11 COMPONENTS X11 Xext Xmu Xi)
    list( APPEND TKDraw_USED_LIBS ${X11_LIBRARIES} )
    list( APPEND TKDraw_USED_LIBS ${X11_Xi_LIB} )
    list( APPEND TKDraw_USED_LIBS ${X11_Xmu_LIB} )
  endif()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKDraw_USED_LIBS tbb )
  endif()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKDraw_USED_LIBS tbbmalloc )
  endif()
  list( APPEND TKDraw_USED_LIBS objc )
  find_library(FRAMEWORKS_APPKIT NAMES Appkit)
  list( APPEND TKDraw_USED_LIBS ${FRAMEWORKS_APPKIT} )
  find_library(FRAMEWORKS_IOKIT NAMES IOKit)
  list( APPEND TKDraw_USED_LIBS ${FRAMEWORKS_IOKIT} )
else()
  list( APPEND TKDraw_USED_LIBS tcl8.5 )
  list( APPEND TKDraw_USED_LIBS tk8.5 )
  list( APPEND TKDraw_USED_LIBS X11 )
  if(3RDPARTY_USE_TBB)
    list( APPEND TKDraw_USED_LIBS tbb )
  endif()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKDraw_USED_LIBS tbbmalloc )
  endif()
endif()

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_DataMapIteratorOfMapOfFunctions_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_DataMapIteratorOfMapOfFunctions_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_DataMapIteratorOfVMap_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_DataMapIteratorOfVMap_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_DataMapNodeOfMapOfFunctions_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_DataMapNodeOfMapOfFunctions_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_DataMapNodeOfVMap_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_DataMapNodeOfVMap_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_Failure_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_Failure_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_IndexedMapNodeOfMapOfAsciiString_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_IndexedMapNodeOfMapOfAsciiString_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_MapOfAsciiString_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_MapOfAsciiString_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_MapOfFunctions_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_MapOfFunctions_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_SequenceNodeOfSequenceOfDrawable3D_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_SequenceNodeOfSequenceOfDrawable3D_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_SequenceOfDrawable3D_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_SequenceOfDrawable3D_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/Draw/Draw_VMap_0.cxx" )
  SOURCE_GROUP (Draw FILES "../../../drv/Draw/Draw_VMap_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/CommandWindow.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/CommandWindow.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Axis2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Axis2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Axis3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Axis3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_BasicCommands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_BasicCommands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Box.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Box.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Chronometer.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Chronometer.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Circle2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Circle2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Circle3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Circle3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Color.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Color.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Commands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Commands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Display.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Display.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Drawable2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Drawable2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Drawable3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Drawable3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_GraphicCommands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_GraphicCommands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Grid.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Grid.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Interpretor.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Interpretor.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Main.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Main.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Marker2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Marker2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Marker3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Marker3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Number.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Number.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_PloadCommands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_PloadCommands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Printer.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Printer.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_ProgressIndicator.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_ProgressIndicator.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Segment2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Segment2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Segment3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Segment3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Text2D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Text2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Text3D.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Text3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_UnitCommands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_UnitCommands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_VariableCommands.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_VariableCommands.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Viewer.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Viewer.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/Draw_Window.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/Draw_Window.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/MainWindow.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/MainWindow.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/Draw/init.cxx" )
  SOURCE_GROUP (Draw FILES "../../../src/Draw/init.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfEdge_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfEdge_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfFace_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfFace_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfHideData_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListIteratorOfListOfHideData_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListNodeOfListOfEdge_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListNodeOfListOfEdge_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListNodeOfListOfFace_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListNodeOfListOfFace_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListNodeOfListOfHideData_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListNodeOfListOfHideData_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListOfEdge_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListOfEdge_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListOfFace_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListOfFace_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../drv/DBRep/DBRep_ListOfHideData_0.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../drv/DBRep/DBRep_ListOfHideData_0.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_Debug.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_Debug.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_DrawableShape.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_DrawableShape.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_Edge.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_Edge.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_Face.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_Face.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_HideData.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_HideData.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DBRep/DBRep_IsoBuilder.cxx" )
  SOURCE_GROUP (DBRep FILES "../../../src/DBRep/DBRep_IsoBuilder.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineCurve.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineCurve.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineCurve2d.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineCurve2d.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineSurface.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BSplineSurface.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BezierCurve.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BezierCurve.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BezierCurve2d.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BezierCurve2d.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_BezierSurface.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_BezierSurface.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Curve.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Curve.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Curve2d.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Curve2d.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Debug.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Debug.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Drawable.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Drawable.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Point.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Point.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Polygon2D.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Polygon2D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Polygon3D.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Polygon3D.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Surface.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Surface.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Triangulation.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Triangulation.cxx")

  list( APPEND TKDraw_USED_SRCFILES "../../../src/DrawTrSurf/DrawTrSurf_Triangulation2D.cxx" )
  SOURCE_GROUP (DrawTrSurf FILES "../../../src/DrawTrSurf/DrawTrSurf_Triangulation2D.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKDraw)
 add_library( TKDraw SHARED ${TKDraw_USED_SRCFILES} )

 set_property(TARGET TKDraw PROPERTY FOLDER Draw)

 install( TARGETS TKDraw
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKDraw.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKDraw PROPERTIES COMPILE_FLAGS "${TKDraw_PRECOMPILED_DEFS}" )
 include_directories( ${TKDraw_COMPILER_DIRECTORIES} )
 target_link_libraries( TKDraw ${TKDraw_USED_LIBS} )
endif()
