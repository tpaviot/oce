project(TKFillet)

if (WIN32)
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__ChFiDS_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__ChFi2d_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__ChFi3d_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__ChFiKPart_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__Blend_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__BRepBlend_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__BlendFunc_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__BRepFilletAPI_DLL" )
  list( APPEND TKFillet_PRECOMPILED_DEFS "-D__FilletSurf_DLL" )
  string( REGEX REPLACE ";" " " TKFillet_PRECOMPILED_DEFS "${TKFillet_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKFillet_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/ChFiDS" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/ChFiDS" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/ChFi2d" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/ChFi2d" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/ChFi3d" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/ChFi3d" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/ChFiKPart" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/ChFiKPart" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/Blend" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/Blend" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/BRepBlend" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/BRepBlend" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/BlendFunc" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/BlendFunc" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/BRepFilletAPI" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/BRepFilletAPI" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../drv/FilletSurf" )
  list( APPEND TKFillet_COMPILER_DIRECTORIES "../../../src/FilletSurf" )

if (WIN32)
else()
endif()

  list( APPEND TKFillet_USED_LIBS TKBRep )
  list( APPEND TKFillet_USED_LIBS TKernel )
  list( APPEND TKFillet_USED_LIBS TKMath )
  list( APPEND TKFillet_USED_LIBS TKGeomBase )
  list( APPEND TKFillet_USED_LIBS TKGeomAlgo )
  list( APPEND TKFillet_USED_LIBS TKG2d )
  list( APPEND TKFillet_USED_LIBS TKTopAlgo )
  list( APPEND TKFillet_USED_LIBS TKG3d )
  list( APPEND TKFillet_USED_LIBS TKBool )
  list( APPEND TKFillet_USED_LIBS TKShHealing )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_HData_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_HData_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_HElSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_HElSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_IndexedDataMapNodeOfIndexedDataMapOfVertexListOfStripe_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_IndexedDataMapNodeOfIndexedDataMapOfVertexListOfStripe_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_IndexedDataMapOfVertexListOfStripe_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_IndexedDataMapOfVertexListOfStripe_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfListOfHElSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfListOfHElSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfListOfStripe_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfListOfStripe_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfRegularities_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListIteratorOfRegularities_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfListOfHElSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfListOfHElSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfListOfStripe_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfListOfStripe_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfRegularities_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListNodeOfRegularities_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListOfHElSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListOfHElSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_ListOfStripe_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_ListOfStripe_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_Regularities_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_Regularities_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SecArray1_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SecArray1_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SecHArray1_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SecHArray1_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSurfData_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SequenceNodeOfSequenceOfSurfData_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SequenceOfSpine_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SequenceOfSpine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_SequenceOfSurfData_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_SequenceOfSurfData_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiDS/ChFiDS_StripeArray1_0.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../drv/ChFiDS/ChFiDS_StripeArray1_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_ChamfSpine.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_ChamfSpine.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_CircSection.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_CircSection.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_CommonPoint.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_CommonPoint.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_ElSpine.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_ElSpine.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_FaceInterference.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_FaceInterference.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_FilSpine.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_FilSpine.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_Map.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_Map.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_Regul.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_Regul.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_Spine.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_Spine.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_Stripe.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_Stripe.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_StripeMap.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_StripeMap.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiDS/ChFiDS_SurfData.cxx" )
  SOURCE_GROUP (ChFiDS FILES "../../../src/ChFiDS/ChFiDS_SurfData.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_AnaFilletAlgo.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_AnaFilletAlgo.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_Builder.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_Builder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_Builder_0.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_Builder_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_ChamferAPI.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_ChamferAPI.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_FilletAPI.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_FilletAPI.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi2d/ChFi2d_FilletAlgo.cxx" )
  SOURCE_GROUP (ChFi2d FILES "../../../src/ChFi2d/ChFi2d_FilletAlgo.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_0.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_1.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_1.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_2.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_2.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_6.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_6.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_C1.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_C1.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_C2.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_C2.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_CnCrn.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_CnCrn.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_NotImp.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_NotImp.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Builder_SpKP.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Builder_SpKP.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_ChBuilder.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_ChBuilder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_ChBuilder_C2.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_ChBuilder_C2.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_ChBuilder_C3.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_ChBuilder_C3.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_Debug.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_Debug.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_FilBuilder.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_FilBuilder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_FilBuilder_C2.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_FilBuilder_C2.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_FilBuilder_C3.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_FilBuilder_C3.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFi3d/ChFi3d_SearchSing.cxx" )
  SOURCE_GROUP (ChFi3d FILES "../../../src/ChFi3d/ChFi3d_SearchSing.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiKPart/ChFiKPart_DataMapIteratorOfRstMap_0.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../drv/ChFiKPart/ChFiKPart_DataMapIteratorOfRstMap_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiKPart/ChFiKPart_DataMapNodeOfRstMap_0.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../drv/ChFiKPart/ChFiKPart_DataMapNodeOfRstMap_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/ChFiKPart/ChFiKPart_RstMap_0.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../drv/ChFiKPart/ChFiKPart_RstMap_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_CS.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_CS.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCon.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCon.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCyl.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnCyl.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnPln.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChAsymPlnPln.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCon.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCon.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCyl.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnCyl.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnPln.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_ChPlnPln.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Fcts.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Fcts.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCon.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCon.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCyl.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnCyl.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnPln.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_FilPlnPln.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Rotule.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Rotule.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Sphere.cxx" )
  SOURCE_GROUP (ChFiKPart FILES "../../../src/ChFiKPart/ChFiKPart_ComputeData_Sphere.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/Blend/Blend_SequenceNodeOfSequenceOfPoint_0.cxx" )
  SOURCE_GROUP (Blend FILES "../../../drv/Blend/Blend_SequenceNodeOfSequenceOfPoint_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/Blend/Blend_SequenceOfPoint_0.cxx" )
  SOURCE_GROUP (Blend FILES "../../../drv/Blend/Blend_SequenceOfPoint_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_AppFunction.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_AppFunction.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_CSFunction.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_CSFunction.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_CurvPointFuncInv.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_CurvPointFuncInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_Debug.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_Debug.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_FuncInv.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_FuncInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_Function.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_Function.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_Point.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_Point.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_RstRstFunction.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_RstRstFunction.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_SurfCurvFuncInv.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_SurfCurvFuncInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_SurfPointFuncInv.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_SurfPointFuncInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/Blend/Blend_SurfRstFunction.cxx" )
  SOURCE_GROUP (Blend FILES "../../../src/Blend/Blend_SurfRstFunction.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_AppSurf_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_AppSurf_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_CSWalking_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_CSWalking_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_Extremity_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_Extremity_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_HCurve2dTool_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_HCurve2dTool_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_HCurveTool_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_HCurveTool_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_Line_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_Line_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_PointOnRst_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_PointOnRst_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfLine_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfLine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfPointOnRst_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_SequenceNodeOfSequenceOfPointOnRst_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_SequenceOfLine_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_SequenceOfLine_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_SequenceOfPointOnRst_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_SequenceOfPointOnRst_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../drv/BRepBlend/BRepBlend_Walking_0.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../drv/BRepBlend/BRepBlend_Walking_0.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_AppFunc.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_AppFunc.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_AppFuncRoot.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_AppFuncRoot.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_AppFuncRst.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_AppFuncRst.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_AppFuncRstRst.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_AppFuncRstRst.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_AppSurface.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_AppSurface.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_BlendTool.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_BlendTool.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_CurvPointRadInv.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_CurvPointRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_RstRstConstRad.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_RstRstConstRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_RstRstEvolRad.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_RstRstEvolRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_RstRstLineBuilder.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_RstRstLineBuilder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfCurvConstRadInv.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfCurvConstRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfCurvEvolRadInv.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfCurvEvolRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfPointConstRadInv.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfPointConstRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfPointEvolRadInv.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfPointEvolRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfRstConstRad.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfRstConstRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfRstEvolRad.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfRstEvolRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepBlend/BRepBlend_SurfRstLineBuilder.cxx" )
  SOURCE_GROUP (BRepBlend FILES "../../../src/BRepBlend/BRepBlend_SurfRstLineBuilder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_CSCircular.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_CSCircular.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_CSConstRad.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_CSConstRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_ChAsym.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_ChAsym.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_ChAsymInv.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_ChAsymInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_ChamfInv.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_ChamfInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_Chamfer.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_Chamfer.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_ConstRad.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_ConstRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_ConstRadInv.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_ConstRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_Corde.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_Corde.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_EvolRad.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_EvolRad.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_EvolRadInv.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_EvolRadInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_Ruled.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_Ruled.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_RuledInv.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_RuledInv.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BlendFunc/BlendFunc_Tensor.cxx" )
  SOURCE_GROUP (BlendFunc FILES "../../../src/BlendFunc/BlendFunc_Tensor.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepFilletAPI/BRepFilletAPI_LocalOperation.cxx" )
  SOURCE_GROUP (BRepFilletAPI FILES "../../../src/BRepFilletAPI/BRepFilletAPI_LocalOperation.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeChamfer.cxx" )
  SOURCE_GROUP (BRepFilletAPI FILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeChamfer.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeFillet.cxx" )
  SOURCE_GROUP (BRepFilletAPI FILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeFillet.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeFillet2d.cxx" )
  SOURCE_GROUP (BRepFilletAPI FILES "../../../src/BRepFilletAPI/BRepFilletAPI_MakeFillet2d.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/FilletSurf/FilletSurf_Builder.cxx" )
  SOURCE_GROUP (FilletSurf FILES "../../../src/FilletSurf/FilletSurf_Builder.cxx")

  list( APPEND TKFillet_USED_SRCFILES "../../../src/FilletSurf/FilletSurf_InternalBuilder.cxx" )
  SOURCE_GROUP (FilletSurf FILES "../../../src/FilletSurf/FilletSurf_InternalBuilder.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKFillet)
 add_library( TKFillet SHARED ${TKFillet_USED_SRCFILES} )

 set_property(TARGET TKFillet PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKFillet
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKFillet.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKFillet PROPERTIES COMPILE_FLAGS "${TKFillet_PRECOMPILED_DEFS}" )
 include_directories( ${TKFillet_COMPILER_DIRECTORIES} )
 target_link_libraries( TKFillet ${TKFillet_USED_LIBS} )
endif()
