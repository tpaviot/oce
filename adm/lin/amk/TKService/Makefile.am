# Makefile.am for Open Cascade toolkit TKService
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Aspect : @top_srcdir@/src/Aspect: \
@top_srcdir@/drv/InterfaceGraphic : @top_srcdir@/src/InterfaceGraphic: \
@top_srcdir@/drv/SelectBasics : @top_srcdir@/src/SelectBasics: \
@top_srcdir@/drv/Xw : @top_srcdir@/src/Xw: \
@top_srcdir@/drv/AlienImage : @top_srcdir@/src/AlienImage: \
@top_srcdir@/drv/Image : @top_srcdir@/src/Image: \
@top_srcdir@/drv/Cocoa : @top_srcdir@/src/Cocoa: \
@top_srcdir@/drv/TColQuantity : @top_srcdir@/src/TColQuantity: \
@top_srcdir@/drv/Font : @top_srcdir@/src/Font


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_XwLibs_INCLUDES) $(CSF_dpsLibs_INCLUDES) $(CSF_XmuLibs_INCLUDES) $(CSF_objc_INCLUDES) $(CSF_Appkit_INCLUDES) $(CSF_IOKit_INCLUDES) $(CSF_FreeImagePlus_INCLUDES) $(CSF_FREETYPE_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Aspect -I@top_srcdir@/src/Aspect \
-I@top_srcdir@/drv/InterfaceGraphic -I@top_srcdir@/src/InterfaceGraphic \
-I@top_srcdir@/drv/SelectBasics -I@top_srcdir@/src/SelectBasics \
-I@top_srcdir@/drv/Xw -I@top_srcdir@/src/Xw \
-I@top_srcdir@/drv/AlienImage -I@top_srcdir@/src/AlienImage \
-I@top_srcdir@/drv/Image -I@top_srcdir@/src/Image \
-I@top_srcdir@/drv/Cocoa -I@top_srcdir@/src/Cocoa \
-I@top_srcdir@/drv/TColQuantity -I@top_srcdir@/src/TColQuantity \
-I@top_srcdir@/drv/Font -I@top_srcdir@/src/Font


lib_LTLIBRARIES=libTKService.la

libTKService_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
$(STLPort_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_XwLibs_LIB) $(CSF_dpsLibs_LIB) $(CSF_XmuLibs_LIB) $(CSF_objc_LIB) $(CSF_Appkit_LIB) $(CSF_IOKit_LIB) $(CSF_FreeImagePlus_LIB) $(CSF_FREETYPE_LIB) 

libTKService_la_SOURCES = \
@top_srcdir@/drv/Aspect/Aspect_Array1OfEdge_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectFillAreaDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectLineDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectMarkerDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_BadAccess_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_ColorMapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_DisplayConnectionDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_DriverDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_DriverError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_EdgeDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_FontMapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_FontStyleDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_GraphicDeviceDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_IdentDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_LineStyleDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_LineWidthDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_MarkMapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_MarkerStyleDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_PixmapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_PixmapError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_PolyStyleDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfColorMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfColor_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfFontMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfMarkMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfTypeMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfWidthMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfColorMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfColor_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfFontMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfMarkMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfTypeMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfWidthMapEntry_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_TypeMapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_UndefinedMap_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_WidthMapDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_WindowDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_WindowError_0.cxx \
@top_srcdir@/drv/Image/Image_ColorPixelDataMap_0.cxx \
@top_srcdir@/drv/Image/Image_ColorPixelMapHasher_0.cxx \
@top_srcdir@/drv/Image/Image_DColorImage_0.cxx \
@top_srcdir@/drv/Image/Image_DIndexedImage_0.cxx \
@top_srcdir@/drv/Image/Image_DataMapIteratorOfColorPixelDataMap_0.cxx \
@top_srcdir@/drv/Image/Image_DataMapIteratorOfLookupTable_0.cxx \
@top_srcdir@/drv/Image/Image_DataMapNodeOfColorPixelDataMap_0.cxx \
@top_srcdir@/drv/Image/Image_DataMapNodeOfLookupTable_0.cxx \
@top_srcdir@/drv/Image/Image_IndexPixelMapHasher_0.cxx \
@top_srcdir@/drv/Image/Image_LookupTable_0.cxx \
@top_srcdir@/drv/Image/Image_PixelFieldOfDColorImage_0.cxx \
@top_srcdir@/drv/Image/Image_PixelFieldOfDIndexedImage_0.cxx \
@top_srcdir@/drv/Image/Image_PixelRowOfDColorImage_0.cxx \
@top_srcdir@/drv/Image/Image_PixelRowOfDIndexedImage_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListIteratorOfListOfBox2d_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListIteratorOfListOfSensitive_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListNodeOfListOfBox2d_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListNodeOfListOfSensitive_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListOfBox2d_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_ListOfSensitive_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_SequenceNodeOfSequenceOfOwner_0.cxx \
@top_srcdir@/drv/SelectBasics/SelectBasics_SequenceOfOwner_0.cxx \
@top_srcdir@/drv/TColQuantity/TColQuantity_Array1OfLength_0.cxx \
@top_srcdir@/drv/TColQuantity/TColQuantity_Array2OfLength_0.cxx \
@top_srcdir@/drv/TColQuantity/TColQuantity_HArray1OfLength_0.cxx \
@top_srcdir@/drv/TColQuantity/TColQuantity_HArray2OfLength_0.cxx \
@top_srcdir@/src/AlienImage/AlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_AidaAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_AidaAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_AlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_AlienImageData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_AlienUserImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_BMPAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_BMPAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_BMPHeader.cxx \
@top_srcdir@/src/AlienImage/AlienImage_EuclidAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_EuclidAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_GIFAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_GIFAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_GIFLZWDict.cxx \
@top_srcdir@/src/AlienImage/AlienImage_MemoryOperations.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SGIRGBAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SGIRGBAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SGIRGBFileHeader.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SUNRFFileHeader.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SunRFAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_SunRFAlienImage.cxx \
@top_srcdir@/src/AlienImage/AlienImage_X11XColor.cxx \
@top_srcdir@/src/AlienImage/AlienImage_X11XWDAlienData.cxx \
@top_srcdir@/src/AlienImage/AlienImage_X11XWDFileHeader.cxx \
@top_srcdir@/src/AlienImage/AlienImage_XAlienImage.cxx \
@top_srcdir@/src/Aspect/Aspect.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectFillArea.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectLine.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectMarker.cxx \
@top_srcdir@/src/Aspect/Aspect_Background.cxx \
@top_srcdir@/src/Aspect/Aspect_CLayer2d.cxx \
@top_srcdir@/src/Aspect/Aspect_CircularGrid.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorCubeColorMap.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorMap.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorPixel.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorRampColorMap.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorScale.cxx \
@top_srcdir@/src/Aspect/Aspect_DisplayConnection.cxx \
@top_srcdir@/src/Aspect/Aspect_Driver.cxx \
@top_srcdir@/src/Aspect/Aspect_Edge.cxx \
@top_srcdir@/src/Aspect/Aspect_FStream.cxx \
@top_srcdir@/src/Aspect/Aspect_FontMap.cxx \
@top_srcdir@/src/Aspect/Aspect_FontMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_FontStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_GenId.cxx \
@top_srcdir@/src/Aspect/Aspect_GenericColorMap.cxx \
@top_srcdir@/src/Aspect/Aspect_GradientBackground.cxx \
@top_srcdir@/src/Aspect/Aspect_Grid.cxx \
@top_srcdir@/src/Aspect/Aspect_Handle.cxx \
@top_srcdir@/src/Aspect/Aspect_IFStream.cxx \
@top_srcdir@/src/Aspect/Aspect_IndexPixel.cxx \
@top_srcdir@/src/Aspect/Aspect_LineStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkMap.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkerStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_Pixel.cxx \
@top_srcdir@/src/Aspect/Aspect_RGBPixel.cxx \
@top_srcdir@/src/Aspect/Aspect_RectangularGrid.cxx \
@top_srcdir@/src/Aspect/Aspect_TypeMap.cxx \
@top_srcdir@/src/Aspect/Aspect_TypeMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_WidthMap.cxx \
@top_srcdir@/src/Aspect/Aspect_WidthMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_Window.cxx \
@top_srcdir@/src/Aspect/Aspect_WindowDriver.cxx \
@top_srcdir@/src/Font/Font_FTFont.cxx \
@top_srcdir@/src/Font/Font_FTLibrary.cxx \
@top_srcdir@/src/Font/Font_FontMgr.cxx \
@top_srcdir@/src/Font/Font_SystemFont.cxx \
@top_srcdir@/src/Image/Image.cxx \
@top_srcdir@/src/Image/Image_AlienPixMap.cxx \
@top_srcdir@/src/Image/Image_AveragePixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_BalancedPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_BilinearPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_ColorImage.cxx \
@top_srcdir@/src/Image/Image_Convertor.cxx \
@top_srcdir@/src/Image/Image_Diff.cxx \
@top_srcdir@/src/Image/Image_Image.cxx \
@top_srcdir@/src/Image/Image_PixMap.cxx \
@top_srcdir@/src/Image/Image_PixelAddress.cxx \
@top_srcdir@/src/Image/Image_PixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_PlanarPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_PseudoColorImage.cxx \
@top_srcdir@/src/InterfaceGraphic/InterfaceGraphic_Palette.c \
@top_srcdir@/src/InterfaceGraphic/InterfaceGraphic_cPrintf.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_BasicTool.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_EntityOwner.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SensitiveEntity.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SortAlgo.cxx \
@top_srcdir@/src/Xw/Xw_Window.cxx

