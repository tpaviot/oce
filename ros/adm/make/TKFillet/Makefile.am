# Makefile.am for Open Cascade toolkit TKFillet
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/ChFiDS : @top_srcdir@/src/ChFiDS: \
@top_srcdir@/drv/ChFi2d : @top_srcdir@/src/ChFi2d: \
@top_srcdir@/drv/ChFi3d : @top_srcdir@/src/ChFi3d: \
@top_srcdir@/drv/ChFiKPart : @top_srcdir@/src/ChFiKPart: \
@top_srcdir@/drv/Blend : @top_srcdir@/src/Blend: \
@top_srcdir@/drv/BRepBlend : @top_srcdir@/src/BRepBlend: \
@top_srcdir@/drv/BlendFunc : @top_srcdir@/src/BlendFunc: \
@top_srcdir@/drv/BRepFilletAPI : @top_srcdir@/src/BRepFilletAPI: \
@top_srcdir@/drv/FilletSurf : @top_srcdir@/src/FilletSurf


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/ChFiDS -I@top_srcdir@/src/ChFiDS \
-I@top_srcdir@/drv/ChFi2d -I@top_srcdir@/src/ChFi2d \
-I@top_srcdir@/drv/ChFi3d -I@top_srcdir@/src/ChFi3d \
-I@top_srcdir@/drv/ChFiKPart -I@top_srcdir@/src/ChFiKPart \
-I@top_srcdir@/drv/Blend -I@top_srcdir@/src/Blend \
-I@top_srcdir@/drv/BRepBlend -I@top_srcdir@/src/BRepBlend \
-I@top_srcdir@/drv/BlendFunc -I@top_srcdir@/src/BlendFunc \
-I@top_srcdir@/drv/BRepFilletAPI -I@top_srcdir@/src/BRepFilletAPI \
-I@top_srcdir@/drv/FilletSurf -I@top_srcdir@/src/FilletSurf


lib_LTLIBRARIES=libTKFillet.la

libTKFillet_la_LIBADD = \
../TKernel/libTKernel.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKBool/libTKBool.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKMath/libTKMath.la \
../TKG2d/libTKG2d.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKBRep/libTKBRep.la \
$(STLPort_LIB) 

libTKFillet_la_SOURCES = \
@top_srcdir@/drv/BRepBlend/BRepBlend_AppSurf_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_CSWalking_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_Extremity_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_HCurve2dTool_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_HCurveTool_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_Line_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_PointOnRst_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfLine_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfPointOnRst_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_SequenceOfLine_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_SequenceOfPointOnRst_0.cxx \
@top_srcdir@/drv/BRepBlend/BRepBlend_Walking_0.cxx \
@top_srcdir@/drv/Blend/Blend_SequenceNodeOfSequenceOfPoint_0.cxx \
@top_srcdir@/drv/Blend/Blend_SequenceOfPoint_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_HData_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_HElSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_IndexedDataMapNodeOfIndexedDataMapOfVertexListOfStripe_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_IndexedDataMapOfVertexListOfStripe_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListIteratorOfListOfHElSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListIteratorOfListOfStripe_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListIteratorOfRegularities_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListNodeOfListOfHElSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListNodeOfListOfStripe_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListNodeOfRegularities_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListOfHElSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_ListOfStripe_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_Regularities_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SecArray1_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SecHArray1_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSurfData_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SequenceOfSpine_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_SequenceOfSurfData_0.cxx \
@top_srcdir@/drv/ChFiDS/ChFiDS_StripeArray1_0.cxx \
@top_srcdir@/drv/ChFiKPart/ChFiKPart_DataMapIteratorOfRstMap_0.cxx \
@top_srcdir@/drv/ChFiKPart/ChFiKPart_DataMapNodeOfRstMap_0.cxx \
@top_srcdir@/drv/ChFiKPart/ChFiKPart_RstMap_0.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_AppFunc.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_AppFuncRoot.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_AppFuncRst.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_AppFuncRstRst.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_AppSurface.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_BlendTool.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_CurvPointRadInv.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_RstRstConstRad.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_RstRstEvolRad.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_RstRstLineBuilder.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfCurvConstRadInv.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfCurvEvolRadInv.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfPointConstRadInv.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfPointEvolRadInv.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfRstConstRad.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfRstEvolRad.cxx \
@top_srcdir@/src/BRepBlend/BRepBlend_SurfRstLineBuilder.cxx \
@top_srcdir@/src/BRepFilletAPI/BRepFilletAPI_LocalOperation.cxx \
@top_srcdir@/src/BRepFilletAPI/BRepFilletAPI_MakeChamfer.cxx \
@top_srcdir@/src/BRepFilletAPI/BRepFilletAPI_MakeFillet.cxx \
@top_srcdir@/src/BRepFilletAPI/BRepFilletAPI_MakeFillet2d.cxx \
@top_srcdir@/src/Blend/Blend_AppFunction.cxx \
@top_srcdir@/src/Blend/Blend_CSFunction.cxx \
@top_srcdir@/src/Blend/Blend_CurvPointFuncInv.cxx \
@top_srcdir@/src/Blend/Blend_Debug.cxx \
@top_srcdir@/src/Blend/Blend_FuncInv.cxx \
@top_srcdir@/src/Blend/Blend_Function.cxx \
@top_srcdir@/src/Blend/Blend_Point.cxx \
@top_srcdir@/src/Blend/Blend_RstRstFunction.cxx \
@top_srcdir@/src/Blend/Blend_SurfCurvFuncInv.cxx \
@top_srcdir@/src/Blend/Blend_SurfPointFuncInv.cxx \
@top_srcdir@/src/Blend/Blend_SurfRstFunction.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_CSCircular.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_CSConstRad.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_ChAsym.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_ChAsymInv.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_ChamfInv.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_Chamfer.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_ConstRad.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_ConstRadInv.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_Corde.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_EvolRad.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_EvolRadInv.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_Ruled.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_RuledInv.cxx \
@top_srcdir@/src/BlendFunc/BlendFunc_Tensor.cxx \
@top_srcdir@/src/ChFi2d/ChFi2d.cxx \
@top_srcdir@/src/ChFi2d/ChFi2d_Builder.cxx \
@top_srcdir@/src/ChFi2d/ChFi2d_Builder_0.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_0.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_1.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_2.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_6.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_C1.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_C2.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_CnCrn.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_NotImp.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Builder_SpKP.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_ChBuilder.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_ChBuilder_C2.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_ChBuilder_C3.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_Debug.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_FilBuilder.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_FilBuilder_C2.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_FilBuilder_C3.cxx \
@top_srcdir@/src/ChFi3d/ChFi3d_SearchSing.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_ChamfSpine.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_CircSection.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_CommonPoint.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_ElSpine.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_FaceInterference.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_FilSpine.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_Map.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_Regul.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_Spine.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_Stripe.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_StripeMap.cxx \
@top_srcdir@/src/ChFiDS/ChFiDS_SurfData.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_CS.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCon.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCyl.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnPln.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCon.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCyl.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_ChPlnPln.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_Fcts.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCon.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCyl.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_FilPlnPln.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_Rotule.cxx \
@top_srcdir@/src/ChFiKPart/ChFiKPart_ComputeData_Sphere.cxx \
@top_srcdir@/src/FilletSurf/FilletSurf_Builder.cxx \
@top_srcdir@/src/FilletSurf/FilletSurf_InternalBuilder.cxx

