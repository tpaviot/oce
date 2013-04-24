project(TKVRML)

if (WIN32)
  list( APPEND TKVRML_PRECOMPILED_DEFS "-D__VrmlConverter_DLL" )
  list( APPEND TKVRML_PRECOMPILED_DEFS "-D__VrmlAPI_DLL" )
  list( APPEND TKVRML_PRECOMPILED_DEFS "-D__Vrml_DLL" )
  list( APPEND TKVRML_PRECOMPILED_DEFS "-D__VrmlData_DLL" )
  string( REGEX REPLACE ";" " " TKVRML_PRECOMPILED_DEFS "${TKVRML_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKVRML_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../drv/VrmlConverter" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../src/VrmlConverter" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../drv/VrmlAPI" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../src/VrmlAPI" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../drv/Vrml" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../src/Vrml" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../drv/VrmlData" )
  list( APPEND TKVRML_COMPILER_DIRECTORIES "../../../src/VrmlData" )

if (WIN32)
else()
endif()

  list( APPEND TKVRML_USED_LIBS TKBRep )
  list( APPEND TKVRML_USED_LIBS TKTopAlgo )
  list( APPEND TKVRML_USED_LIBS TKMath )
  list( APPEND TKVRML_USED_LIBS TKGeomBase )
  list( APPEND TKVRML_USED_LIBS TKernel )
  list( APPEND TKVRML_USED_LIBS TKPrim )
  list( APPEND TKVRML_USED_LIBS TKG2d )
  list( APPEND TKVRML_USED_LIBS TKG3d )
  list( APPEND TKVRML_USED_LIBS TKMesh )
  list( APPEND TKVRML_USED_LIBS TKHLR )
  list( APPEND TKVRML_USED_LIBS TKService )
  list( APPEND TKVRML_USED_LIBS TKGeomAlgo )
  list( APPEND TKVRML_USED_LIBS TKV3d )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_Curve.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_Curve.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_DeflectionCurve.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_DeflectionCurve.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_Drawer.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_Drawer.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_HLRShape.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_HLRShape.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_IsoAspect.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_IsoAspect.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_LineAspect.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_LineAspect.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_PointAspect.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_PointAspect.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_Projector.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_Projector.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_ShadedShape.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_ShadedShape.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_ShadingAspect.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_ShadingAspect.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_WFDeflectionRestrictedFace.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_WFDeflectionRestrictedFace.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_WFDeflectionShape.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_WFDeflectionShape.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_WFRestrictedFace.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_WFRestrictedFace.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlConverter/VrmlConverter_WFShape.cxx" )
  SOURCE_GROUP (VrmlConverter FILES "../../../src/VrmlConverter/VrmlConverter_WFShape.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlAPI/VrmlAPI.cxx" )
  SOURCE_GROUP (VrmlAPI FILES "../../../src/VrmlAPI/VrmlAPI.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlAPI/VrmlAPI_Writer.cxx" )
  SOURCE_GROUP (VrmlAPI FILES "../../../src/VrmlAPI/VrmlAPI_Writer.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_AsciiText.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_AsciiText.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Cone.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Cone.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Coordinate3.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Coordinate3.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Cube.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Cube.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Cylinder.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Cylinder.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_DirectionalLight.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_DirectionalLight.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_FontStyle.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_FontStyle.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Group.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Group.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_IndexedFaceSet.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_IndexedFaceSet.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_IndexedLineSet.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_IndexedLineSet.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Info.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Info.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Instancing.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Instancing.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_LOD.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_LOD.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Material.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Material.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_MaterialBinding.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_MaterialBinding.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_MatrixTransform.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_MatrixTransform.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Normal.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Normal.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_NormalBinding.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_NormalBinding.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_OrthographicCamera.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_OrthographicCamera.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_PerspectiveCamera.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_PerspectiveCamera.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_PointLight.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_PointLight.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_PointSet.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_PointSet.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Rotation.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Rotation.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_SFImage.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_SFImage.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_SFRotation.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_SFRotation.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Scale.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Scale.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Separator.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Separator.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_ShapeHints.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_ShapeHints.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Sphere.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Sphere.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_SpotLight.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_SpotLight.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Switch.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Switch.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Texture2.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Texture2.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Texture2Transform.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Texture2Transform.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_TextureCoordinate2.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_TextureCoordinate2.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Transform.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Transform.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_TransformSeparator.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_TransformSeparator.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_Translation.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_Translation.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_WWWAnchor.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_WWWAnchor.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/Vrml/Vrml_WWWInline.cxx" )
  SOURCE_GROUP (Vrml FILES "../../../src/Vrml/Vrml_WWWInline.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_Geometry.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_Geometry.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_Group.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_Group.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_IndexedFaceSet.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_IndexedFaceSet.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_IndexedLineSet.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_IndexedLineSet.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_Material.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_Material.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_Node.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_Node.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_Scene.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_Scene.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_ShapeConvert.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_ShapeConvert.cxx")

  list( APPEND TKVRML_USED_SRCFILES "../../../src/VrmlData/VrmlData_WorldInfo.cxx" )
  SOURCE_GROUP (VrmlData FILES "../../../src/VrmlData/VrmlData_WorldInfo.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKVRML)
 add_library( TKVRML SHARED ${TKVRML_USED_SRCFILES} )

 set_property(TARGET TKVRML PROPERTY FOLDER DataExchange)

 install( TARGETS TKVRML
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKVRML.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKVRML PROPERTIES COMPILE_FLAGS "${TKVRML_PRECOMPILED_DEFS}" )
 include_directories( ${TKVRML_COMPILER_DIRECTORIES} )
 target_link_libraries( TKVRML ${TKVRML_USED_LIBS} )
endif()
