# Makefile.am for Open Cascade toolkit TKVRML
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/VrmlConverter : @top_srcdir@/src/VrmlConverter: \
@top_srcdir@/drv/VrmlAPI : @top_srcdir@/src/VrmlAPI: \
@top_srcdir@/drv/Vrml : @top_srcdir@/src/Vrml: \
@top_srcdir@/drv/VrmlData : @top_srcdir@/src/VrmlData


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/VrmlConverter -I@top_srcdir@/src/VrmlConverter \
-I@top_srcdir@/drv/VrmlAPI -I@top_srcdir@/src/VrmlAPI \
-I@top_srcdir@/drv/Vrml -I@top_srcdir@/src/Vrml \
-I@top_srcdir@/drv/VrmlData -I@top_srcdir@/src/VrmlData


lib_LTLIBRARIES=libTKVRML.la

libTKVRML_la_LIBADD = \
../TKernel/libTKernel.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKMesh/libTKMesh.la \
../TKG2d/libTKG2d.la \
../TKHLR/libTKHLR.la \
../TKGeomBase/libTKGeomBase.la \
../TKPrim/libTKPrim.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKService/libTKService.la \
../TKV3d/libTKV3d.la \
$(STLPort_LIB) 

libTKVRML_la_SOURCES = \
@top_srcdir@/src/Vrml/Vrml.cxx \
@top_srcdir@/src/Vrml/Vrml_AsciiText.cxx \
@top_srcdir@/src/Vrml/Vrml_Cone.cxx \
@top_srcdir@/src/Vrml/Vrml_Coordinate3.cxx \
@top_srcdir@/src/Vrml/Vrml_Cube.cxx \
@top_srcdir@/src/Vrml/Vrml_Cylinder.cxx \
@top_srcdir@/src/Vrml/Vrml_DirectionalLight.cxx \
@top_srcdir@/src/Vrml/Vrml_FontStyle.cxx \
@top_srcdir@/src/Vrml/Vrml_Group.cxx \
@top_srcdir@/src/Vrml/Vrml_IndexedFaceSet.cxx \
@top_srcdir@/src/Vrml/Vrml_IndexedLineSet.cxx \
@top_srcdir@/src/Vrml/Vrml_Info.cxx \
@top_srcdir@/src/Vrml/Vrml_Instancing.cxx \
@top_srcdir@/src/Vrml/Vrml_LOD.cxx \
@top_srcdir@/src/Vrml/Vrml_Material.cxx \
@top_srcdir@/src/Vrml/Vrml_MaterialBinding.cxx \
@top_srcdir@/src/Vrml/Vrml_MatrixTransform.cxx \
@top_srcdir@/src/Vrml/Vrml_Normal.cxx \
@top_srcdir@/src/Vrml/Vrml_NormalBinding.cxx \
@top_srcdir@/src/Vrml/Vrml_OrthographicCamera.cxx \
@top_srcdir@/src/Vrml/Vrml_PerspectiveCamera.cxx \
@top_srcdir@/src/Vrml/Vrml_PointLight.cxx \
@top_srcdir@/src/Vrml/Vrml_PointSet.cxx \
@top_srcdir@/src/Vrml/Vrml_Rotation.cxx \
@top_srcdir@/src/Vrml/Vrml_SFImage.cxx \
@top_srcdir@/src/Vrml/Vrml_SFRotation.cxx \
@top_srcdir@/src/Vrml/Vrml_Scale.cxx \
@top_srcdir@/src/Vrml/Vrml_Separator.cxx \
@top_srcdir@/src/Vrml/Vrml_ShapeHints.cxx \
@top_srcdir@/src/Vrml/Vrml_Sphere.cxx \
@top_srcdir@/src/Vrml/Vrml_SpotLight.cxx \
@top_srcdir@/src/Vrml/Vrml_Switch.cxx \
@top_srcdir@/src/Vrml/Vrml_Texture2.cxx \
@top_srcdir@/src/Vrml/Vrml_Texture2Transform.cxx \
@top_srcdir@/src/Vrml/Vrml_TextureCoordinate2.cxx \
@top_srcdir@/src/Vrml/Vrml_Transform.cxx \
@top_srcdir@/src/Vrml/Vrml_TransformSeparator.cxx \
@top_srcdir@/src/Vrml/Vrml_Translation.cxx \
@top_srcdir@/src/Vrml/Vrml_WWWAnchor.cxx \
@top_srcdir@/src/Vrml/Vrml_WWWInline.cxx \
@top_srcdir@/src/VrmlAPI/VrmlAPI.cxx \
@top_srcdir@/src/VrmlAPI/VrmlAPI_Writer.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_Curve.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_DeflectionCurve.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_Drawer.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_HLRShape.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_IsoAspect.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_LineAspect.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_PointAspect.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_Projector.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_ShadedShape.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_ShadingAspect.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_WFDeflectionRestrictedFace.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_WFDeflectionShape.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_WFRestrictedFace.cxx \
@top_srcdir@/src/VrmlConverter/VrmlConverter_WFShape.cxx \
@top_srcdir@/src/VrmlData/VrmlData_Geometry.cxx \
@top_srcdir@/src/VrmlData/VrmlData_Group.cxx \
@top_srcdir@/src/VrmlData/VrmlData_IndexedFaceSet.cxx \
@top_srcdir@/src/VrmlData/VrmlData_IndexedLineSet.cxx \
@top_srcdir@/src/VrmlData/VrmlData_Material.cxx \
@top_srcdir@/src/VrmlData/VrmlData_Node.cxx \
@top_srcdir@/src/VrmlData/VrmlData_Scene.cxx \
@top_srcdir@/src/VrmlData/VrmlData_ShapeConvert.cxx \
@top_srcdir@/src/VrmlData/VrmlData_WorldInfo.cxx

libTKVRML_laLDFLAGS = -version-info @oce_version_info@

