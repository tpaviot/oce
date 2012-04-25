# Makefile.am for Open Cascade toolkit TKFeat
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/LocOpe : @top_srcdir@/src/LocOpe: \
@top_srcdir@/drv/BRepFeat : @top_srcdir@/src/BRepFeat


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/LocOpe -I@top_srcdir@/src/LocOpe \
-I@top_srcdir@/drv/BRepFeat -I@top_srcdir@/src/BRepFeat


lib_LTLIBRARIES=libTKFeat.la

libTKFeat_la_LIBADD = $(CSF_OPT_LIBS) \
../TKBRep/libTKBRep.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKGeomBase/libTKGeomBase.la \
../TKPrim/libTKPrim.la \
../TKG2d/libTKG2d.la \
../TKBO/libTKBO.la \
../TKG3d/libTKG3d.la \
../TKBool/libTKBool.la


libTKFeat_la_SOURCES = \
@top_srcdir@/drv/LocOpe/LocOpe_DataMapIteratorOfDataMapOfShapePnt_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_DataMapNodeOfDataMapOfShapePnt_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_DataMapOfShapePnt_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfCirc_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfLin_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfPntFace_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceOfCirc_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceOfLin_0.cxx \
@top_srcdir@/drv/LocOpe/LocOpe_SequenceOfPntFace_0.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_Builder.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_Form.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_Gluer.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_LocalOperation.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakeCylindricalHole.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakeDPrism.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakeLinearForm.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakePipe.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakePrism.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakeRevol.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_MakeRevolutionForm.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_RibSlot.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_SplitShape.cxx \
@top_srcdir@/src/BRepFeat/BRepFeat_trace.cxx \
@top_srcdir@/src/LocOpe/LocOpe.cxx \
@top_srcdir@/src/LocOpe/LocOpe_BuildShape.cxx \
@top_srcdir@/src/LocOpe/LocOpe_BuildWires.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Builder.cxx \
@top_srcdir@/src/LocOpe/LocOpe_CSIntersector.cxx \
@top_srcdir@/src/LocOpe/LocOpe_CurveShapeIntersector.cxx \
@top_srcdir@/src/LocOpe/LocOpe_DPrism.cxx \
@top_srcdir@/src/LocOpe/LocOpe_FindEdges.cxx \
@top_srcdir@/src/LocOpe/LocOpe_FindEdgesInFace.cxx \
@top_srcdir@/src/LocOpe/LocOpe_GeneratedShape.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Generator.cxx \
@top_srcdir@/src/LocOpe/LocOpe_GluedShape.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Gluer.cxx \
@top_srcdir@/src/LocOpe/LocOpe_HBuilder.cxx \
@top_srcdir@/src/LocOpe/LocOpe_LinearForm.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Pipe.cxx \
@top_srcdir@/src/LocOpe/LocOpe_PntFace.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Prism.cxx \
@top_srcdir@/src/LocOpe/LocOpe_ProjectedWires.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Revol.cxx \
@top_srcdir@/src/LocOpe/LocOpe_RevolutionForm.cxx \
@top_srcdir@/src/LocOpe/LocOpe_SplitDrafts.cxx \
@top_srcdir@/src/LocOpe/LocOpe_SplitShape.cxx \
@top_srcdir@/src/LocOpe/LocOpe_Spliter.cxx \
@top_srcdir@/src/LocOpe/LocOpe_WiresOnShape.cxx

