project(TKOpenGl)

if (WIN32)
  list( APPEND TKOpenGl_PRECOMPILED_DEFS "-D__OpenGl_DLL" )
  string( REGEX REPLACE ";" " " TKOpenGl_PRECOMPILED_DEFS "${TKOpenGl_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKOpenGl_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKOpenGl_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKOpenGl_COMPILER_DIRECTORIES "../../../drv/OpenGl" )
  list( APPEND TKOpenGl_COMPILER_DIRECTORIES "../../../src/OpenGl" )

if (WIN32)
else()
endif()

  list( APPEND TKOpenGl_USED_LIBS TKernel )
  list( APPEND TKOpenGl_USED_LIBS TKService )
  list( APPEND TKOpenGl_USED_LIBS TKV3d )

if (WIN32)
  list( APPEND TKOpenGl_USED_LIBS opengl32.lib )
  list( APPEND TKOpenGl_USED_LIBS glu32.lib )
  list( APPEND TKOpenGl_USED_LIBS user32.lib )
  list( APPEND TKOpenGl_USED_LIBS gdi32.lib )
  list( APPEND TKOpenGl_USED_LIBS ws2_32.lib )
  list( APPEND TKOpenGl_USED_LIBS vfw32.lib )
elseif(APPLE)
  find_library(FRAMEWORKS_OPENGL NAMES OpenGL)
  if(3RDPARTY_USE_GLX)
    list( APPEND TKOpenGl_USED_LIBS GL )
    list( APPEND TKOpenGl_USED_LIBS GLU )
  else()
    list( APPEND TKOpenGl_USED_LIBS ${FRAMEWORKS_OPENGL} )
  endif()
  list( APPEND TKOpenGl_USED_LIBS objc )
  find_library(FRAMEWORKS_APPKIT NAMES Appkit)
  list( APPEND TKOpenGl_USED_LIBS ${FRAMEWORKS_APPKIT} )
  find_library(FRAMEWORKS_IOKIT NAMES IOKit)
  list( APPEND TKOpenGl_USED_LIBS ${FRAMEWORKS_IOKIT} )
  list( APPEND TKOpenGl_USED_LIBS freetype )
  if(3RDPARTY_USE_GL2PS)
    list( APPEND TKOpenGl_USED_LIBS gl2ps )
  endif()
else()
  list( APPEND TKOpenGl_USED_LIBS GLU )
  list( APPEND TKOpenGl_USED_LIBS GL )
  list( APPEND TKOpenGl_USED_LIBS freetype )
  if(3RDPARTY_USE_GL2PS)
    list( APPEND TKOpenGl_USED_LIBS gl2ps )
  endif()
endif()

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_AVIWriter.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_AVIWriter.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_AspectFace.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_AspectFace.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_AspectLine.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_AspectLine.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_AspectMarker.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_AspectMarker.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_AspectText.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_AspectText.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Context.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Context.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Display.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Display.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Display_2.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Display_2.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Element.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Element.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Font.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Font.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_FrameBuffer.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_FrameBuffer.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraduatedTrihedron.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraduatedTrihedron.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_1.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_1.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_2.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_2.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_3.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_3.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_4.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_4.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_7.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_7.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_703.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_703.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_713.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_713.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_Export.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_Export.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_GraphicDriver_Layer.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_GraphicDriver_Layer.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Group.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Group.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_IndexBuffer.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_IndexBuffer.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_LayerList.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_LayerList.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Marker.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Marker.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_MarkerSet.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_MarkerSet.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Matrix.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Matrix.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_PrimitiveArray.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_PrimitiveArray.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_PrinterContext.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_PrinterContext.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_PriorityList.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_PriorityList.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Resource.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Resource.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Structure.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Structure.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Text.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Text.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_TextFormatter.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_TextFormatter.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Texture.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Texture.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_TextureBufferArb.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_TextureBufferArb.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Trihedron.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Trihedron.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_VertexBuffer.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_VertexBuffer.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_View.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_View.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_View_1.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_View_1.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_View_2.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_View_2.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Window.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Window.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Workspace.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Workspace.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Workspace_2.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Workspace_2.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Workspace_3.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Workspace_3.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_Workspace_5.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_Workspace_5.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_telem_util.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_telem_util.cxx")

  list( APPEND TKOpenGl_USED_SRCFILES "../../../src/OpenGl/OpenGl_telem_view.cxx" )
  SOURCE_GROUP (OpenGl FILES "../../../src/OpenGl/OpenGl_telem_view.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKOpenGl)
 add_library( TKOpenGl SHARED ${TKOpenGl_USED_SRCFILES} )

 set_property(TARGET TKOpenGl PROPERTY FOLDER Visualization)

 install( TARGETS TKOpenGl
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKOpenGl.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKOpenGl PROPERTIES COMPILE_FLAGS "${TKOpenGl_PRECOMPILED_DEFS}" )
 include_directories( ${TKOpenGl_COMPILER_DIRECTORIES} )
 target_link_libraries( TKOpenGl ${TKOpenGl_USED_LIBS} )
endif()
