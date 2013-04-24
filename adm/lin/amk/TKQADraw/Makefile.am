# Makefile.am for Open Cascade toolkit TKQADraw
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/QABugs : @top_srcdir@/src/QABugs: \
@top_srcdir@/drv/QADNaming : @top_srcdir@/src/QADNaming: \
@top_srcdir@/drv/QADraw : @top_srcdir@/src/QADraw: \
@top_srcdir@/drv/QANCollection : @top_srcdir@/src/QANCollection: \
@top_srcdir@/drv/QANewBRepNaming : @top_srcdir@/src/QANewBRepNaming: \
@top_srcdir@/drv/QANewDBRepNaming : @top_srcdir@/src/QANewDBRepNaming: \
@top_srcdir@/drv/QANewModTopOpe : @top_srcdir@/src/QANewModTopOpe


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_advapi32_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/QABugs -I@top_srcdir@/src/QABugs \
-I@top_srcdir@/drv/QADNaming -I@top_srcdir@/src/QADNaming \
-I@top_srcdir@/drv/QADraw -I@top_srcdir@/src/QADraw \
-I@top_srcdir@/drv/QANCollection -I@top_srcdir@/src/QANCollection \
-I@top_srcdir@/drv/QANewBRepNaming -I@top_srcdir@/src/QANewBRepNaming \
-I@top_srcdir@/drv/QANewDBRepNaming -I@top_srcdir@/src/QANewDBRepNaming \
-I@top_srcdir@/drv/QANewModTopOpe -I@top_srcdir@/src/QANewModTopOpe


lib_LTLIBRARIES=libTKQADraw.la

libTKQADraw_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKNIS/libTKNIS.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKG2d/libTKG2d.la \
../TKDraw/libTKDraw.la \
../PTKernel/libPTKernel.la \
../TKV3d/libTKV3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKG3d/libTKG3d.la \
../TKViewerTest/libTKViewerTest.la \
../TKCDF/libTKCDF.la \
../TKDCAF/libTKDCAF.la \
../TKLCAF/libTKLCAF.la \
../TKFillet/libTKFillet.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKHLR/libTKHLR.la \
../TKBool/libTKBool.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKPrim/libTKPrim.la \
../TKBO/libTKBO.la \
../TKShHealing/libTKShHealing.la \
../TKOffset/libTKOffset.la \
../TKFeat/libTKFeat.la \
../TKCAF/libTKCAF.la \
../TKIGES/libTKIGES.la \
../TKXSBase/libTKXSBase.la \
../TKMesh/libTKMesh.la \
../TKXCAF/libTKXCAF.la \
../TKSTEP/libTKSTEP.la \
../TKXDESTEP/libTKXDESTEP.la \
../TKXSDRAW/libTKXSDRAW.la \
../TKSTL/libTKSTL.la \
../TKAdvTools/libTKAdvTools.la \
$(STLPort_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_gdi32_LIB) $(CSF_advapi32_LIB) $(CSF_user32_LIB) $(CSF_TBB_LIB) 

libTKQADraw_la_SOURCES = \
@top_srcdir@/drv/QADNaming/QADNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx \
@top_srcdir@/drv/QADNaming/QADNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx \
@top_srcdir@/drv/QADNaming/QADNaming_DataMapOfShapeOfName_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DataMapIteratorOfDataMapOfRealPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DataMapNodeOfDataMapOfRealPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DataMapOfRealPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_DoubleMapOfRealInteger_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_IndexedDataMapNodeOfIndexedDataMapOfRealPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_IndexedDataMapOfRealPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_ListIteratorOfListOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_ListNodeOfListOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_ListOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_QueueNodeOfQueueOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_QueueOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_SListNodeOfSListOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_SListOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_StackIteratorOfStackOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_StackNodeOfStackOfPnt_0.cxx \
@top_srcdir@/drv/QANCollection/QANCollection_StackOfPnt_0.cxx \
@top_srcdir@/src/QABugs/QABugs.cxx \
@top_srcdir@/src/QABugs/QABugs_1.cxx \
@top_srcdir@/src/QABugs/QABugs_10.cxx \
@top_srcdir@/src/QABugs/QABugs_11.cxx \
@top_srcdir@/src/QABugs/QABugs_12.cxx \
@top_srcdir@/src/QABugs/QABugs_13.cxx \
@top_srcdir@/src/QABugs/QABugs_14.cxx \
@top_srcdir@/src/QABugs/QABugs_15.cxx \
@top_srcdir@/src/QABugs/QABugs_16.cxx \
@top_srcdir@/src/QABugs/QABugs_17.cxx \
@top_srcdir@/src/QABugs/QABugs_18.cxx \
@top_srcdir@/src/QABugs/QABugs_19.cxx \
@top_srcdir@/src/QABugs/QABugs_2.cxx \
@top_srcdir@/src/QABugs/QABugs_3.cxx \
@top_srcdir@/src/QABugs/QABugs_4.cxx \
@top_srcdir@/src/QABugs/QABugs_5.cxx \
@top_srcdir@/src/QABugs/QABugs_6.cxx \
@top_srcdir@/src/QABugs/QABugs_7.cxx \
@top_srcdir@/src/QABugs/QABugs_8.cxx \
@top_srcdir@/src/QABugs/QABugs_9.cxx \
@top_srcdir@/src/QABugs/QABugs_MyText.cxx \
@top_srcdir@/src/QABugs/QABugs_PresentableObject.cxx \
@top_srcdir@/src/QADNaming/QADNaming.cxx \
@top_srcdir@/src/QADNaming/QADNaming_BasicCommands.cxx \
@top_srcdir@/src/QADNaming/QADNaming_BuilderCommands.cxx \
@top_srcdir@/src/QADNaming/QADNaming_IteratorsCommands.cxx \
@top_srcdir@/src/QADNaming/QADNaming_Sample.cxx \
@top_srcdir@/src/QADNaming/QADNaming_SelectionCommands.cxx \
@top_srcdir@/src/QADNaming/QADNaming_ToolsCommands.cxx \
@top_srcdir@/src/QADraw/QADraw.cxx \
@top_srcdir@/src/QADraw/QADraw_Additional.cxx \
@top_srcdir@/src/QANCollection/QANCollection.cxx \
@top_srcdir@/src/QANCollection/QANCollection1.cxx \
@top_srcdir@/src/QANCollection/QANCollection2.cxx \
@top_srcdir@/src/QANCollection/QANCollection3.cxx \
@top_srcdir@/src/QANCollection/QANCollection4.cxx \
@top_srcdir@/src/QANCollection/QANCollectionTest.cxx \
@top_srcdir@/src/QANCollection/QANCollection_Common.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_BooleanOperation.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_BooleanOperationFeat.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Box.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Chamfer.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Common.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Cut.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Cylinder.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Fillet.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Fuse.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Gluing.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_ImportShape.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Intersection.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Limitation.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Loader.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_LoaderParent.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Prism.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Revol.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_Sphere.cxx \
@top_srcdir@/src/QANewBRepNaming/QANewBRepNaming_TopNaming.cxx \
@top_srcdir@/src/QANewDBRepNaming/QANewDBRepNaming.cxx \
@top_srcdir@/src/QANewDBRepNaming/QANewDBRepNaming_FeatureCommands.cxx \
@top_srcdir@/src/QANewDBRepNaming/QANewDBRepNaming_PrimitiveCommands.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue_SDFaces.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue_shell.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue_util.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue_vertex.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Glue_wire.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Intersection.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Limitation.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_ReShaper.cxx \
@top_srcdir@/src/QANewModTopOpe/QANewModTopOpe_Tools.cxx

