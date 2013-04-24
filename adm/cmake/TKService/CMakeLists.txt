project(TKService)

if (WIN32)
  list( APPEND TKService_PRECOMPILED_DEFS "-D__Aspect_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__InterfaceGraphic_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__SelectBasics_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__AlienImage_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__Image_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__Cocoa_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__TColQuantity_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__Font_DLL" )
  list( APPEND TKService_PRECOMPILED_DEFS "-D__WNT_DLL" )
  string( REGEX REPLACE ";" " " TKService_PRECOMPILED_DEFS "${TKService_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKService_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/Aspect" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/Aspect" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/InterfaceGraphic" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/InterfaceGraphic" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/SelectBasics" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/SelectBasics" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/AlienImage" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/AlienImage" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/Image" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/Image" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/Cocoa" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/Cocoa" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/TColQuantity" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/TColQuantity" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/Font" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/Font" )

if (WIN32)
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/WNT" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/WNT" )
else()
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../drv/Xw" )
  list( APPEND TKService_COMPILER_DIRECTORIES "../../../src/Xw" )
endif()

  list( APPEND TKService_USED_LIBS TKernel )
  list( APPEND TKService_USED_LIBS TKMath )

if (WIN32)
  list( APPEND TKService_USED_LIBS opengl32.lib )
  list( APPEND TKService_USED_LIBS glu32.lib )
elseif(APPLE)
  find_library(FRAMEWORKS_OPENGL NAMES OpenGL)
  if(3RDPARTY_USE_GLX)
    list( APPEND TKService_USED_LIBS GL )
    list( APPEND TKService_USED_LIBS GLU )
  else()
    list( APPEND TKService_USED_LIBS ${FRAMEWORKS_OPENGL} )
  endif()
  list( APPEND TKService_USED_LIBS objc )
  find_library(FRAMEWORKS_APPKIT NAMES Appkit)
  list( APPEND TKService_USED_LIBS ${FRAMEWORKS_APPKIT} )
  find_library(FRAMEWORKS_IOKIT NAMES IOKit)
  list( APPEND TKService_USED_LIBS ${FRAMEWORKS_IOKIT} )
  if(3RDPARTY_USE_FREEIMAGE)
    list( APPEND TKService_USED_LIBS freeimage )
  endif()
  list( APPEND TKService_USED_LIBS freetype )
else()
  list( APPEND TKService_USED_LIBS GLU )
  list( APPEND TKService_USED_LIBS GL )
  list( APPEND TKService_USED_LIBS X11 )
  list( APPEND TKService_USED_LIBS Xext )
  list( APPEND TKService_USED_LIBS Xmu )
  list( APPEND TKService_USED_LIBS Xi )
  if(3RDPARTY_USE_FREEIMAGE)
    list( APPEND TKService_USED_LIBS freeimage )
  endif()
  list( APPEND TKService_USED_LIBS freetype )
endif()

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_Array1OfEdge_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_Array1OfEdge_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_AspectFillAreaDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_AspectFillAreaDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_AspectLineDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_AspectLineDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_AspectMarkerDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_AspectMarkerDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_BadAccess_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_BadAccess_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_ColorMapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_ColorMapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_DisplayConnectionDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_DisplayConnectionDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_DriverDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_DriverDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_DriverError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_DriverError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_EdgeDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_EdgeDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_FontMapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_FontMapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_FontStyleDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_FontStyleDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_GraphicDeviceDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_GraphicDeviceDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_IdentDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_IdentDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_LineStyleDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_LineStyleDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_LineWidthDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_LineWidthDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_MarkMapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_MarkMapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_MarkerStyleDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_MarkerStyleDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_PixmapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_PixmapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_PixmapError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_PixmapError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_PolyStyleDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_PolyStyleDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfColorMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfColorMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfColor_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfColor_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfFontMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfFontMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfMarkMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfMarkMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfTypeMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfTypeMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfWidthMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceNodeOfSequenceOfWidthMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfColorMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfColorMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfColor_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfColor_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfFontMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfFontMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfMarkMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfMarkMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfTypeMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfTypeMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_SequenceOfWidthMapEntry_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_SequenceOfWidthMapEntry_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_TypeMapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_TypeMapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_UndefinedMap_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_UndefinedMap_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_WidthMapDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_WidthMapDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_WindowDefinitionError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_WindowDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Aspect/Aspect_WindowError_0.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../drv/Aspect/Aspect_WindowError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_AspectFillArea.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_AspectFillArea.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_AspectLine.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_AspectLine.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_AspectMarker.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_AspectMarker.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Background.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Background.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_CLayer2d.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_CLayer2d.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_CircularGrid.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_CircularGrid.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorCubeColorMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorCubeColorMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorMapEntry.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorMapEntry.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorPixel.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorPixel.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorRampColorMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorRampColorMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_ColorScale.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_ColorScale.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_DisplayConnection.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_DisplayConnection.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Driver.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Driver.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Edge.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Edge.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_FStream.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_FStream.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_FontMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_FontMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_FontMapEntry.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_FontMapEntry.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_FontStyle.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_FontStyle.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_GenId.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_GenId.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_GenericColorMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_GenericColorMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_GradientBackground.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_GradientBackground.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Grid.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Grid.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Handle.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Handle.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_IFStream.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_IFStream.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_IndexPixel.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_IndexPixel.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_LineStyle.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_LineStyle.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_MarkMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_MarkMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_MarkMapEntry.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_MarkMapEntry.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_MarkerStyle.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_MarkerStyle.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Pixel.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Pixel.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_RGBPixel.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_RGBPixel.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_RectangularGrid.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_RectangularGrid.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_TypeMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_TypeMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_TypeMapEntry.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_TypeMapEntry.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_WidthMap.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_WidthMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_WidthMapEntry.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_WidthMapEntry.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_Window.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_Window.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Aspect/Aspect_WindowDriver.cxx" )
  SOURCE_GROUP (Aspect FILES "../../../src/Aspect/Aspect_WindowDriver.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/InterfaceGraphic/InterfaceGraphic_Palette.c" )
  SOURCE_GROUP (InterfaceGraphic FILES "../../../src/InterfaceGraphic/InterfaceGraphic_Palette.c")

  list( APPEND TKService_USED_SRCFILES "../../../src/InterfaceGraphic/InterfaceGraphic_cPrintf.cxx" )
  SOURCE_GROUP (InterfaceGraphic FILES "../../../src/InterfaceGraphic/InterfaceGraphic_cPrintf.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListIteratorOfListOfBox2d_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListIteratorOfListOfBox2d_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListIteratorOfListOfSensitive_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListIteratorOfListOfSensitive_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListNodeOfListOfBox2d_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListNodeOfListOfBox2d_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListNodeOfListOfSensitive_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListNodeOfListOfSensitive_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListOfBox2d_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListOfBox2d_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_ListOfSensitive_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_ListOfSensitive_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_SequenceNodeOfSequenceOfOwner_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_SequenceNodeOfSequenceOfOwner_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/SelectBasics/SelectBasics_SequenceOfOwner_0.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../drv/SelectBasics/SelectBasics_SequenceOfOwner_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/SelectBasics/SelectBasics.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../src/SelectBasics/SelectBasics.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/SelectBasics/SelectBasics_BasicTool.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../src/SelectBasics/SelectBasics_BasicTool.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/SelectBasics/SelectBasics_EntityOwner.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../src/SelectBasics/SelectBasics_EntityOwner.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/SelectBasics/SelectBasics_SensitiveEntity.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../src/SelectBasics/SelectBasics_SensitiveEntity.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/SelectBasics/SelectBasics_SortAlgo.cxx" )
  SOURCE_GROUP (SelectBasics FILES "../../../src/SelectBasics/SelectBasics_SortAlgo.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_AidaAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_AidaAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_AidaAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_AidaAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_AlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_AlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_AlienImageData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_AlienImageData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_AlienUserImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_AlienUserImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_BMPAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_BMPAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_BMPAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_BMPAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_BMPHeader.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_BMPHeader.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_EuclidAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_EuclidAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_EuclidAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_EuclidAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_GIFAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_GIFAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_GIFAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_GIFAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_GIFLZWDict.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_GIFLZWDict.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_MemoryOperations.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_MemoryOperations.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SGIRGBAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SGIRGBAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SGIRGBAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SGIRGBAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SGIRGBFileHeader.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SGIRGBFileHeader.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SUNRFFileHeader.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SUNRFFileHeader.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SunRFAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SunRFAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_SunRFAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_SunRFAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_X11XColor.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_X11XColor.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_X11XWDAlienData.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_X11XWDAlienData.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_X11XWDFileHeader.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_X11XWDFileHeader.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/AlienImage/AlienImage_XAlienImage.cxx" )
  SOURCE_GROUP (AlienImage FILES "../../../src/AlienImage/AlienImage_XAlienImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_ColorPixelDataMap_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_ColorPixelDataMap_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_ColorPixelMapHasher_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_ColorPixelMapHasher_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DColorImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DColorImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DIndexedImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DIndexedImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DataMapIteratorOfColorPixelDataMap_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DataMapIteratorOfColorPixelDataMap_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DataMapIteratorOfLookupTable_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DataMapIteratorOfLookupTable_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DataMapNodeOfColorPixelDataMap_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DataMapNodeOfColorPixelDataMap_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_DataMapNodeOfLookupTable_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_DataMapNodeOfLookupTable_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_IndexPixelMapHasher_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_IndexPixelMapHasher_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_LookupTable_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_LookupTable_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_PixelFieldOfDColorImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_PixelFieldOfDColorImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_PixelFieldOfDIndexedImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_PixelFieldOfDIndexedImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_PixelRowOfDColorImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_PixelRowOfDColorImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/Image/Image_PixelRowOfDIndexedImage_0.cxx" )
  SOURCE_GROUP (Image FILES "../../../drv/Image/Image_PixelRowOfDIndexedImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_AlienPixMap.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_AlienPixMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_AveragePixelInterpolation.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_AveragePixelInterpolation.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_BalancedPixelInterpolation.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_BalancedPixelInterpolation.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_BilinearPixelInterpolation.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_BilinearPixelInterpolation.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_ColorImage.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_ColorImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_Convertor.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_Convertor.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_Diff.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_Diff.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_Image.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_Image.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_PixMap.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_PixMap.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_PixelAddress.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_PixelAddress.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_PixelInterpolation.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_PixelInterpolation.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_PlanarPixelInterpolation.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_PlanarPixelInterpolation.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Image/Image_PseudoColorImage.cxx" )
  SOURCE_GROUP (Image FILES "../../../src/Image/Image_PseudoColorImage.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/TColQuantity/TColQuantity_Array1OfLength_0.cxx" )
  SOURCE_GROUP (TColQuantity FILES "../../../drv/TColQuantity/TColQuantity_Array1OfLength_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/TColQuantity/TColQuantity_Array2OfLength_0.cxx" )
  SOURCE_GROUP (TColQuantity FILES "../../../drv/TColQuantity/TColQuantity_Array2OfLength_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/TColQuantity/TColQuantity_HArray1OfLength_0.cxx" )
  SOURCE_GROUP (TColQuantity FILES "../../../drv/TColQuantity/TColQuantity_HArray1OfLength_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/TColQuantity/TColQuantity_HArray2OfLength_0.cxx" )
  SOURCE_GROUP (TColQuantity FILES "../../../drv/TColQuantity/TColQuantity_HArray2OfLength_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Font/Font_FTFont.cxx" )
  SOURCE_GROUP (Font FILES "../../../src/Font/Font_FTFont.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Font/Font_FTLibrary.cxx" )
  SOURCE_GROUP (Font FILES "../../../src/Font/Font_FTLibrary.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Font/Font_FontMgr.cxx" )
  SOURCE_GROUP (Font FILES "../../../src/Font/Font_FontMgr.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/Font/Font_SystemFont.cxx" )
  SOURCE_GROUP (Font FILES "../../../src/Font/Font_SystemFont.cxx")

if (WIN32)
  list( APPEND TKService_USED_SRCFILES "../../../drv/WNT/WNT_ClassDefinitionError_0.cxx" )
  SOURCE_GROUP (WNT FILES "../../../drv/WNT/WNT_ClassDefinitionError_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/WNT/WNT_ColorTable_0.cxx" )
  SOURCE_GROUP (WNT FILES "../../../drv/WNT/WNT_ColorTable_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/WNT/WNT_HColorTable_0.cxx" )
  SOURCE_GROUP (WNT FILES "../../../drv/WNT/WNT_HColorTable_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/WNT/WNT_SequenceNodeOfSequenceOfImage_0.cxx" )
  SOURCE_GROUP (WNT FILES "../../../drv/WNT/WNT_SequenceNodeOfSequenceOfImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../drv/WNT/WNT_SequenceOfImage_0.cxx" )
  SOURCE_GROUP (WNT FILES "../../../drv/WNT/WNT_SequenceOfImage_0.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/EHDC.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/EHDC.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/W32_Allocator.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/W32_Allocator.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/W95_Allocator.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/W95_Allocator.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Allocator.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Allocator.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_ColorRef.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_ColorRef.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Dword.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Dword.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Image.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Image.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_LogFont.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_LogFont.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Long.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Long.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Uint.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Uint.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_WClass.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_WClass.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_Window.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_Window.cxx")

  list( APPEND TKService_USED_SRCFILES "../../../src/WNT/WNT_WindowData.cxx" )
  SOURCE_GROUP (WNT FILES "../../../src/WNT/WNT_WindowData.cxx")

else()

  list( APPEND TKService_USED_SRCFILES "../../../src/Xw/Xw_Window.cxx" )
  SOURCE_GROUP (Xw FILES "../../../src/Xw/Xw_Window.cxx")

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKService)
 add_library( TKService SHARED ${TKService_USED_SRCFILES} )

 set_property(TARGET TKService PROPERTY FOLDER Visualization)

 install( TARGETS TKService
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKService.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKService PROPERTIES COMPILE_FLAGS "${TKService_PRECOMPILED_DEFS}" )
 include_directories( ${TKService_COMPILER_DIRECTORIES} )
 target_link_libraries( TKService ${TKService_USED_LIBS} )
endif()
