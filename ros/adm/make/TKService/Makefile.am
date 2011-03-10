# Makefile.am for Open Cascade toolkit TKService
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Aspect : @top_srcdir@/src/Aspect: \
@top_srcdir@/drv/InterfaceGraphic : @top_srcdir@/src/InterfaceGraphic: \
@top_srcdir@/drv/SelectBasics : @top_srcdir@/src/SelectBasics: \
@top_srcdir@/drv/Viewer : @top_srcdir@/src/Viewer: \
@top_srcdir@/drv/Xw : @top_srcdir@/src/Xw: \
@top_srcdir@/drv/MFT : @top_srcdir@/src/MFT: \
@top_srcdir@/drv/PS : @top_srcdir@/src/PS: \
@top_srcdir@/drv/CGM : @top_srcdir@/src/CGM: \
@top_srcdir@/drv/AlienImage : @top_srcdir@/src/AlienImage: \
@top_srcdir@/drv/Image : @top_srcdir@/src/Image: \
@top_srcdir@/drv/PlotMgt : @top_srcdir@/src/PlotMgt: \
@top_srcdir@/drv/ImageUtility : @top_srcdir@/src/ImageUtility: \
@top_srcdir@/drv/TColQuantity : @top_srcdir@/src/TColQuantity


AM_CXXFLAGS = 


AM_CFLAGS = -DXW


INCLUDES = $(STLPort_INCLUDES) $(CSF_XwLibs_INCLUDES) $(CSF_dpsLibs_INCLUDES) $(CSF_XmuLibs_INCLUDES) $(CSF_FreeImagePlus_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Aspect -I@top_srcdir@/src/Aspect \
-I@top_srcdir@/drv/InterfaceGraphic -I@top_srcdir@/src/InterfaceGraphic \
-I@top_srcdir@/drv/SelectBasics -I@top_srcdir@/src/SelectBasics \
-I@top_srcdir@/drv/Viewer -I@top_srcdir@/src/Viewer \
-I@top_srcdir@/drv/Xw -I@top_srcdir@/src/Xw \
-I@top_srcdir@/drv/MFT -I@top_srcdir@/src/MFT \
-I@top_srcdir@/drv/PS -I@top_srcdir@/src/PS \
-I@top_srcdir@/drv/CGM -I@top_srcdir@/src/CGM \
-I@top_srcdir@/drv/AlienImage -I@top_srcdir@/src/AlienImage \
-I@top_srcdir@/drv/Image -I@top_srcdir@/src/Image \
-I@top_srcdir@/drv/PlotMgt -I@top_srcdir@/src/PlotMgt \
-I@top_srcdir@/drv/ImageUtility -I@top_srcdir@/src/ImageUtility \
-I@top_srcdir@/drv/TColQuantity -I@top_srcdir@/src/TColQuantity


lib_LTLIBRARIES=libTKService.la

libTKService_la_LIBADD = \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
$(STLPort_LIB) $(CSF_XwLibs_LIB) $(CSF_dpsLibs_LIB) $(CSF_XmuLibs_LIB) $(CSF_FreeImagePlus_LIB) 

libTKService_la_SOURCES = \
@top_srcdir@/drv/Aspect/Aspect_Array1OfEdge_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectFillAreaDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectLineDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectMarkerDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_BadAccess_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_ColorMapDefinitionError_0.cxx \
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
@top_srcdir@/drv/MFT/MFT_FontManagerDefinitionError_0.cxx \
@top_srcdir@/drv/MFT/MFT_FontManagerError_0.cxx \
@top_srcdir@/drv/MFT/MFT_ListOfFontHandle_0.cxx \
@top_srcdir@/drv/MFT/MFT_SequenceNodeOfListOfFontHandle_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_HListOfMFTFonts_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_HListOfPlotterParameter_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_ListOfMFTFonts_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_ListOfPlotterParameter_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_PlotterAccessError_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_PlotterDefinitionError_0.cxx \
@top_srcdir@/drv/PlotMgt/PlotMgt_SequenceNodeOfListOfPlotterParameter_0.cxx \
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
@top_srcdir@/drv/Viewer/Viewer_BadValue_0.cxx \
@top_srcdir@/drv/Xw/Xw_HListOfMFTFonts_0.cxx \
@top_srcdir@/drv/Xw/Xw_ListOfMFTFonts_0.cxx \
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
@top_srcdir@/src/Aspect/Aspect_Driver.cxx \
@top_srcdir@/src/Aspect/Aspect_Edge.cxx \
@top_srcdir@/src/Aspect/Aspect_FStream.cxx \
@top_srcdir@/src/Aspect/Aspect_FontMap.cxx \
@top_srcdir@/src/Aspect/Aspect_FontMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_FontStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_GenId.cxx \
@top_srcdir@/src/Aspect/Aspect_GenericColorMap.cxx \
@top_srcdir@/src/Aspect/Aspect_GradientBackground.cxx \
@top_srcdir@/src/Aspect/Aspect_GraphicDevice.cxx \
@top_srcdir@/src/Aspect/Aspect_GraphicDriver.cxx \
@top_srcdir@/src/Aspect/Aspect_Grid.cxx \
@top_srcdir@/src/Aspect/Aspect_Handle.cxx \
@top_srcdir@/src/Aspect/Aspect_IFStream.cxx \
@top_srcdir@/src/Aspect/Aspect_IndexPixel.cxx \
@top_srcdir@/src/Aspect/Aspect_LineStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkMap.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_MarkerStyle.cxx \
@top_srcdir@/src/Aspect/Aspect_PixMap.cxx \
@top_srcdir@/src/Aspect/Aspect_Pixel.cxx \
@top_srcdir@/src/Aspect/Aspect_RGBPixel.cxx \
@top_srcdir@/src/Aspect/Aspect_RectangularGrid.cxx \
@top_srcdir@/src/Aspect/Aspect_TypeMap.cxx \
@top_srcdir@/src/Aspect/Aspect_TypeMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_WidthMap.cxx \
@top_srcdir@/src/Aspect/Aspect_WidthMapEntry.cxx \
@top_srcdir@/src/Aspect/Aspect_Window.cxx \
@top_srcdir@/src/Aspect/Aspect_WindowDriver.cxx \
@top_srcdir@/src/CGM/CGM_Driver.cxx \
@top_srcdir@/src/CGM/Gestfic.cxx \
@top_srcdir@/src/CGM/cgmobin.c \
@top_srcdir@/src/CGM/cgmochar.c \
@top_srcdir@/src/CGM/cgmotext.c \
@top_srcdir@/src/Image/Image.cxx \
@top_srcdir@/src/Image/Image_AveragePixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_BalancedPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_BilinearPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_ColorImage.cxx \
@top_srcdir@/src/Image/Image_Convertor.cxx \
@top_srcdir@/src/Image/Image_Image.cxx \
@top_srcdir@/src/Image/Image_PixMap.cxx \
@top_srcdir@/src/Image/Image_PixelAddress.cxx \
@top_srcdir@/src/Image/Image_PixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_PlanarPixelInterpolation.cxx \
@top_srcdir@/src/Image/Image_PseudoColorImage.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_X11Display.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_X11Dump.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_X11GC.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_X11Window.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_X11XImage.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_XPR.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_XWD.cxx \
@top_srcdir@/src/ImageUtility/ImageUtility_XWUD.cxx \
@top_srcdir@/src/InterfaceGraphic/InterfaceGraphic_Palette.c \
@top_srcdir@/src/InterfaceGraphic/InterfaceGraphic_cPrintf.cxx \
@top_srcdir@/src/MFT/MFT.cxx \
@top_srcdir@/src/MFT/MFT_CommandDescriptor.cxx \
@top_srcdir@/src/MFT/MFT_FileRecord.cxx \
@top_srcdir@/src/MFT/MFT_FontManager.cxx \
@top_srcdir@/src/MFT/MFT_TextManager.cxx \
@top_srcdir@/src/PS/PS_Driver.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_ImageDriver.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_Plotter.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_PlotterDriver.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_PlotterParameter.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_PlotterTools.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_Plotter_1.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_Plotter_2.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_TextManager.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_fillpolyarc.cxx \
@top_srcdir@/src/PlotMgt/PlotMgt_fillpolygon.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_BasicTool.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_EntityOwner.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SensitiveEntity.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SortAlgo.cxx \
@top_srcdir@/src/Viewer/Viewer_View.cxx \
@top_srcdir@/src/Viewer/Viewer_Viewer.cxx \
@top_srcdir@/src/Xw/Xw.cxx \
@top_srcdir@/src/Xw/Xw_ColorMap.cxx \
@top_srcdir@/src/Xw/Xw_Driver.cxx \
@top_srcdir@/src/Xw/Xw_FontMap.cxx \
@top_srcdir@/src/Xw/Xw_GraphicDevice.cxx \
@top_srcdir@/src/Xw/Xw_IconBox.cxx \
@top_srcdir@/src/Xw/Xw_MarkMap.cxx \
@top_srcdir@/src/Xw/Xw_PixMap.cxx \
@top_srcdir@/src/Xw/Xw_TextManager.cxx \
@top_srcdir@/src/Xw/Xw_TypeMap.cxx \
@top_srcdir@/src/Xw/Xw_WidthMap.cxx \
@top_srcdir@/src/Xw/Xw_Window.cxx \
@top_srcdir@/src/Xw/Xw_alloc_color.cxx \
@top_srcdir@/src/Xw/Xw_alloc_pixel.cxx \
@top_srcdir@/src/Xw/Xw_calc_points.cxx \
@top_srcdir@/src/Xw/Xw_convert_image.cxx \
@top_srcdir@/src/Xw/Xw_def_background_color.cxx \
@top_srcdir@/src/Xw/Xw_def_color.cxx \
@top_srcdir@/src/Xw/Xw_def_colormap.cxx \
@top_srcdir@/src/Xw/Xw_def_font.cxx \
@top_srcdir@/src/Xw/Xw_def_fontmap.cxx \
@top_srcdir@/src/Xw/Xw_def_highlight_color.cxx \
@top_srcdir@/src/Xw/Xw_def_marker.cxx \
@top_srcdir@/src/Xw/Xw_def_markmap.cxx \
@top_srcdir@/src/Xw/Xw_def_tile.cxx \
@top_srcdir@/src/Xw/Xw_def_tilemap.cxx \
@top_srcdir@/src/Xw/Xw_def_type.cxx \
@top_srcdir@/src/Xw/Xw_def_typemap.cxx \
@top_srcdir@/src/Xw/Xw_def_width.cxx \
@top_srcdir@/src/Xw/Xw_def_widthmap.cxx \
@top_srcdir@/src/Xw/Xw_def_window.cxx \
@top_srcdir@/src/Xw/Xw_draw_arc.cxx \
@top_srcdir@/src/Xw/Xw_draw_buffer.cxx \
@top_srcdir@/src/Xw/Xw_draw_image.cxx \
@top_srcdir@/src/Xw/Xw_draw_line.cxx \
@top_srcdir@/src/Xw/Xw_draw_marker.cxx \
@top_srcdir@/src/Xw/Xw_draw_point.cxx \
@top_srcdir@/src/Xw/Xw_draw_poly.cxx \
@top_srcdir@/src/Xw/Xw_draw_polyarc.cxx \
@top_srcdir@/src/Xw/Xw_draw_polytext.cxx \
@top_srcdir@/src/Xw/Xw_draw_segment.cxx \
@top_srcdir@/src/Xw/Xw_draw_text.cxx \
@top_srcdir@/src/Xw/Xw_draw_zoomed_image.cxx \
@top_srcdir@/src/Xw/Xw_erase_area.cxx \
@top_srcdir@/src/Xw/Xw_erase_window.cxx \
@top_srcdir@/src/Xw/Xw_flush.cxx \
@top_srcdir@/src/Xw/Xw_gamma_image.cxx \
@top_srcdir@/src/Xw/Xw_get_background_color.cxx \
@top_srcdir@/src/Xw/Xw_get_background_image.cxx \
@top_srcdir@/src/Xw/Xw_get_background_index.cxx \
@top_srcdir@/src/Xw/Xw_get_background_pixel.cxx \
@top_srcdir@/src/Xw/Xw_get_color.cxx \
@top_srcdir@/src/Xw/Xw_get_color_index.cxx \
@top_srcdir@/src/Xw/Xw_get_color_name.cxx \
@top_srcdir@/src/Xw/Xw_get_color_pixel.cxx \
@top_srcdir@/src/Xw/Xw_get_colormap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_colormap_visual.cxx \
@top_srcdir@/src/Xw/Xw_get_colormap_xid.cxx \
@top_srcdir@/src/Xw/Xw_get_cursor_position.cxx \
@top_srcdir@/src/Xw/Xw_get_display_info.cxx \
@top_srcdir@/src/Xw/Xw_get_display_visual.cxx \
@top_srcdir@/src/Xw/Xw_get_double_buffer.cxx \
@top_srcdir@/src/Xw/Xw_get_env.cxx \
@top_srcdir@/src/Xw/Xw_get_filename.cxx \
@top_srcdir@/src/Xw/Xw_get_font.cxx \
@top_srcdir@/src/Xw/Xw_get_font_index.cxx \
@top_srcdir@/src/Xw/Xw_get_fontmap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_highlight_color.cxx \
@top_srcdir@/src/Xw/Xw_get_image.cxx \
@top_srcdir@/src/Xw/Xw_get_image_info.cxx \
@top_srcdir@/src/Xw/Xw_get_marker_index.cxx \
@top_srcdir@/src/Xw/Xw_get_markmap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_mmscreen_pixelvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel_mmscreenvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel_screencoord.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel_screenvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel_windowcoord.cxx \
@top_srcdir@/src/Xw/Xw_get_pixel_windowvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_rgbpixel.cxx \
@top_srcdir@/src/Xw/Xw_get_screen_pixelcoord.cxx \
@top_srcdir@/src/Xw/Xw_get_screen_pixelvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_screen_size.cxx \
@top_srcdir@/src/Xw/Xw_get_text_size.cxx \
@top_srcdir@/src/Xw/Xw_get_tilemap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_type.cxx \
@top_srcdir@/src/Xw/Xw_get_type_index.cxx \
@top_srcdir@/src/Xw/Xw_get_typemap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_width.cxx \
@top_srcdir@/src/Xw/Xw_get_width_index.cxx \
@top_srcdir@/src/Xw/Xw_get_widthmap_info.cxx \
@top_srcdir@/src/Xw/Xw_get_window_info.cxx \
@top_srcdir@/src/Xw/Xw_get_window_pixelcoord.cxx \
@top_srcdir@/src/Xw/Xw_get_window_pixelvalue.cxx \
@top_srcdir@/src/Xw/Xw_get_window_position.cxx \
@top_srcdir@/src/Xw/Xw_get_window_visual.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_color.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_colormap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_display.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_font.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_fontmap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_image.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_marker.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_markmap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_tile.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_tilemap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_type.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_typemap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_width.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_widthmap.cxx \
@top_srcdir@/src/Xw/Xw_isdefine_window.cxx \
@top_srcdir@/src/Xw/Xw_load_bmp_image.cxx \
@top_srcdir@/src/Xw/Xw_load_gif_image.cxx \
@top_srcdir@/src/Xw/Xw_load_icons.cxx \
@top_srcdir@/src/Xw/Xw_load_image.cxx \
@top_srcdir@/src/Xw/Xw_load_xwd_image.cxx \
@top_srcdir@/src/Xw/Xw_open_display.cxx \
@top_srcdir@/src/Xw/Xw_open_image.cxx \
@top_srcdir@/src/Xw/Xw_open_pixmap.cxx \
@top_srcdir@/src/Xw/Xw_open_window.cxx \
@top_srcdir@/src/Xw/Xw_put_background_image.cxx \
@top_srcdir@/src/Xw/Xw_put_pixel.cxx \
@top_srcdir@/src/Xw/Xw_put_rgbpixel.cxx \
@top_srcdir@/src/Xw/Xw_resize_window.cxx \
@top_srcdir@/src/Xw/Xw_restore_area.cxx \
@top_srcdir@/src/Xw/Xw_restore_window.cxx \
@top_srcdir@/src/Xw/Xw_save_image.cxx \
@top_srcdir@/src/Xw/Xw_set_background_index.cxx \
@top_srcdir@/src/Xw/Xw_set_colormap.cxx \
@top_srcdir@/src/Xw/Xw_set_double_buffer.cxx \
@top_srcdir@/src/Xw/Xw_set_event.cxx \
@top_srcdir@/src/Xw/Xw_set_extended_text_attrib.cxx \
@top_srcdir@/src/Xw/Xw_set_fontmap.cxx \
@top_srcdir@/src/Xw/Xw_set_hard_cursor.cxx \
@top_srcdir@/src/Xw/Xw_set_internal_event.cxx \
@top_srcdir@/src/Xw/Xw_set_line_attrib.cxx \
@top_srcdir@/src/Xw/Xw_set_marker_attrib.cxx \
@top_srcdir@/src/Xw/Xw_set_markmap.cxx \
@top_srcdir@/src/Xw/Xw_set_poly_attrib.cxx \
@top_srcdir@/src/Xw/Xw_set_soft_cursor.cxx \
@top_srcdir@/src/Xw/Xw_set_text_attrib.cxx \
@top_srcdir@/src/Xw/Xw_set_tilemap.cxx \
@top_srcdir@/src/Xw/Xw_set_trace.cxx \
@top_srcdir@/src/Xw/Xw_set_typemap.cxx \
@top_srcdir@/src/Xw/Xw_set_widthmap.cxx \
@top_srcdir@/src/Xw/Xw_set_window_ratio.cxx \
@top_srcdir@/src/Xw/Xw_set_window_state.cxx \
@top_srcdir@/src/Xw/Xw_wait_event.cxx \
@top_srcdir@/src/Xw/Xw_zoom_image.cxx

