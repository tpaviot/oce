# Makefile.am for Open Cascade toolkit TKService
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Aspect : @top_srcdir@/src/Aspect: \
@top_srcdir@/drv/InterfaceGraphic : @top_srcdir@/src/InterfaceGraphic: \
@top_srcdir@/drv/SelectBasics : @top_srcdir@/src/SelectBasics: \
@top_srcdir@/drv/Xw : @top_srcdir@/src/Xw: \
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
-I@top_srcdir@/drv/Image -I@top_srcdir@/src/Image \
-I@top_srcdir@/drv/Cocoa -I@top_srcdir@/src/Cocoa \
-I@top_srcdir@/drv/TColQuantity -I@top_srcdir@/src/TColQuantity \
-I@top_srcdir@/drv/Font -I@top_srcdir@/src/Font


lib_LTLIBRARIES=libTKService.la

libTKService_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKShHealing/libTKShHealing.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_XwLibs_LIB) $(CSF_dpsLibs_LIB) $(CSF_XmuLibs_LIB) $(CSF_objc_LIB) $(CSF_Appkit_LIB) $(CSF_IOKit_LIB) $(CSF_FreeImagePlus_LIB) $(CSF_FREETYPE_LIB) 

libTKService_la_SOURCES = \
@top_srcdir@/drv/Aspect/Aspect_Array1OfEdge_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectFillAreaDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectLineDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_AspectMarkerDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_BadAccess_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_DisplayConnectionDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_DriverDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_EdgeDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_GraphicDeviceDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_IdentDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceNodeOfSequenceOfColor_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_SequenceOfColor_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_WindowDefinitionError_0.cxx \
@top_srcdir@/drv/Aspect/Aspect_WindowError_0.cxx \
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
@top_srcdir@/src/Aspect/Aspect.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectFillArea.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectLine.cxx \
@top_srcdir@/src/Aspect/Aspect_AspectMarker.cxx \
@top_srcdir@/src/Aspect/Aspect_Background.cxx \
@top_srcdir@/src/Aspect/Aspect_CircularGrid.cxx \
@top_srcdir@/src/Aspect/Aspect_ColorScale.cxx \
@top_srcdir@/src/Aspect/Aspect_DisplayConnection.cxx \
@top_srcdir@/src/Aspect/Aspect_Edge.cxx \
@top_srcdir@/src/Aspect/Aspect_GenId.cxx \
@top_srcdir@/src/Aspect/Aspect_GradientBackground.cxx \
@top_srcdir@/src/Aspect/Aspect_Grid.cxx \
@top_srcdir@/src/Aspect/Aspect_RectangularGrid.cxx \
@top_srcdir@/src/Aspect/Aspect_Window.cxx \
@top_srcdir@/src/Font/Font_BRepFont.cxx \
@top_srcdir@/src/Font/Font_FTFont.cxx \
@top_srcdir@/src/Font/Font_FTLibrary.cxx \
@top_srcdir@/src/Font/Font_FontMgr.cxx \
@top_srcdir@/src/Font/Font_SystemFont.cxx \
@top_srcdir@/src/Image/Image_AlienPixMap.cxx \
@top_srcdir@/src/Image/Image_Diff.cxx \
@top_srcdir@/src/Image/Image_PixMap.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_BasicTool.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_EntityOwner.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SensitiveEntity.cxx \
@top_srcdir@/src/SelectBasics/SelectBasics_SortAlgo.cxx \
@top_srcdir@/src/Xw/Xw_Window.cxx

