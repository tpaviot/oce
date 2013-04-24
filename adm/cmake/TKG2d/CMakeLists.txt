project(TKG2d)

if (WIN32)
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__Geom2d_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__LProp_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__TColGeom2d_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__Adaptor2d_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__Geom2dLProp_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__Geom2dAdaptor_DLL" )
  list( APPEND TKG2d_PRECOMPILED_DEFS "-D__GProp_DLL" )
  string( REGEX REPLACE ";" " " TKG2d_PRECOMPILED_DEFS "${TKG2d_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKG2d_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/Geom2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/Geom2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/LProp" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/LProp" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/TColGeom2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/TColGeom2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/Adaptor2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/Adaptor2d" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/Geom2dLProp" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/Geom2dLProp" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/Geom2dAdaptor" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/Geom2dAdaptor" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../drv/GProp" )
  list( APPEND TKG2d_COMPILER_DIRECTORIES "../../../src/GProp" )

if (WIN32)
else()
endif()

  list( APPEND TKG2d_USED_LIBS TKernel )
  list( APPEND TKG2d_USED_LIBS TKMath )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2d/Geom2d_UndefinedDerivative_0.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../drv/Geom2d/Geom2d_UndefinedDerivative_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2d/Geom2d_UndefinedValue_0.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../drv/Geom2d/Geom2d_UndefinedValue_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_AxisPlacement.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_AxisPlacement.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_BSplineCurve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_BSplineCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_BSplineCurve_1.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_BSplineCurve_1.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_BezierCurve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_BezierCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_BoundedCurve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_BoundedCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_CartesianPoint.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_CartesianPoint.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Circle.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Circle.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Conic.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Conic.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Curve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Curve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Direction.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Direction.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Ellipse.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Ellipse.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Geometry.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Geometry.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Hyperbola.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Hyperbola.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Line.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Line.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_OffsetCurve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_OffsetCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Parabola.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Parabola.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Point.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Point.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Transformation.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Transformation.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_TrimmedCurve.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_TrimmedCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_Vector.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_Vector.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2d/Geom2d_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (Geom2d FILES "../../../src/Geom2d/Geom2d_VectorWithMagnitude.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/LProp/LProp_BadContinuity_0.cxx" )
  SOURCE_GROUP (LProp FILES "../../../drv/LProp/LProp_BadContinuity_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/LProp/LProp_NotDefined_0.cxx" )
  SOURCE_GROUP (LProp FILES "../../../drv/LProp/LProp_NotDefined_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/LProp/LProp_SequenceNodeOfSequenceOfCIType_0.cxx" )
  SOURCE_GROUP (LProp FILES "../../../drv/LProp/LProp_SequenceNodeOfSequenceOfCIType_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/LProp/LProp_SequenceOfCIType_0.cxx" )
  SOURCE_GROUP (LProp FILES "../../../drv/LProp/LProp_SequenceOfCIType_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/LProp/LProp_AnalyticCurInf.cxx" )
  SOURCE_GROUP (LProp FILES "../../../src/LProp/LProp_AnalyticCurInf.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/LProp/LProp_CurAndInf.cxx" )
  SOURCE_GROUP (LProp FILES "../../../src/LProp/LProp_CurAndInf.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBSplineCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBezierCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfBoundedCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfGeometry_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_Array1OfGeometry_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBSplineCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBezierCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfBoundedCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfGeometry_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HArray1OfGeometry_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfGeometry_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_HSequenceOfGeometry_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfGeometry_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfGeometry_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfGeometry_0.cxx" )
  SOURCE_GROUP (TColGeom2d FILES "../../../drv/TColGeom2d/TColGeom2d_SequenceOfGeometry_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Adaptor2d/Adaptor2d_HLine2d_0.cxx" )
  SOURCE_GROUP (Adaptor2d FILES "../../../drv/Adaptor2d/Adaptor2d_HLine2d_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Adaptor2d/Adaptor2d_Curve2d.cxx" )
  SOURCE_GROUP (Adaptor2d FILES "../../../src/Adaptor2d/Adaptor2d_Curve2d.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Adaptor2d/Adaptor2d_HCurve2d.cxx" )
  SOURCE_GROUP (Adaptor2d FILES "../../../src/Adaptor2d/Adaptor2d_HCurve2d.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Adaptor2d/Adaptor2d_Line2d.cxx" )
  SOURCE_GROUP (Adaptor2d FILES "../../../src/Adaptor2d/Adaptor2d_Line2d.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2dLProp/Geom2dLProp_CLProps2d_0.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../drv/Geom2dLProp/Geom2dLProp_CLProps2d_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2dLProp/Geom2dLProp_FCurExtOfNumericCurInf2d_0.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../drv/Geom2dLProp/Geom2dLProp_FCurExtOfNumericCurInf2d_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2dLProp/Geom2dLProp_FCurNulOfNumericCurInf2d_0.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../drv/Geom2dLProp/Geom2dLProp_FCurNulOfNumericCurInf2d_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2dLProp/Geom2dLProp_NumericCurInf2d_0.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../drv/Geom2dLProp/Geom2dLProp_NumericCurInf2d_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2dLProp/Geom2dLProp_CurAndInf2d.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../src/Geom2dLProp/Geom2dLProp_CurAndInf2d.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2dLProp/Geom2dLProp_Curve2dTool.cxx" )
  SOURCE_GROUP (Geom2dLProp FILES "../../../src/Geom2dLProp/Geom2dLProp_Curve2dTool.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/Geom2dAdaptor/Geom2dAdaptor_GHCurve_0.cxx" )
  SOURCE_GROUP (Geom2dAdaptor FILES "../../../drv/Geom2dAdaptor/Geom2dAdaptor_GHCurve_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2dAdaptor/Geom2dAdaptor.cxx" )
  SOURCE_GROUP (Geom2dAdaptor FILES "../../../src/Geom2dAdaptor/Geom2dAdaptor.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2dAdaptor/Geom2dAdaptor_Curve.cxx" )
  SOURCE_GROUP (Geom2dAdaptor FILES "../../../src/Geom2dAdaptor/Geom2dAdaptor_Curve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/Geom2dAdaptor/Geom2dAdaptor_HCurve.cxx" )
  SOURCE_GROUP (Geom2dAdaptor FILES "../../../src/Geom2dAdaptor/Geom2dAdaptor_HCurve.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../drv/GProp/GProp_UndefinedAxis_0.cxx" )
  SOURCE_GROUP (GProp FILES "../../../drv/GProp/GProp_UndefinedAxis_0.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_CelGProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_CelGProps.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_GProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_GProps.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_PEquation.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_PEquation.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_PGProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_PGProps.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_PrincipalProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_PrincipalProps.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_SelGProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_SelGProps.cxx")

  list( APPEND TKG2d_USED_SRCFILES "../../../src/GProp/GProp_VelGProps.cxx" )
  SOURCE_GROUP (GProp FILES "../../../src/GProp/GProp_VelGProps.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKG2d)
 add_library( TKG2d SHARED ${TKG2d_USED_SRCFILES} )

 set_property(TARGET TKG2d PROPERTY FOLDER ModelingData)

 install( TARGETS TKG2d
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKG2d.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKG2d PROPERTIES COMPILE_FLAGS "${TKG2d_PRECOMPILED_DEFS}" )
 include_directories( ${TKG2d_COMPILER_DIRECTORIES} )
 target_link_libraries( TKG2d ${TKG2d_USED_LIBS} )
endif()
