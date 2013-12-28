project(TKStdSchema)

if (WIN32)
  list( APPEND TKStdSchema_PRECOMPILED_DEFS "-D__StdSchema_DLL" )
  list( APPEND TKStdSchema_PRECOMPILED_DEFS "-D__StdDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKStdSchema_PRECOMPILED_DEFS "${TKStdSchema_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "../../../drv/StdSchema" )
  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "../../../src/StdSchema" )
  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "../../../drv/StdDrivers" )
  list( APPEND TKStdSchema_COMPILER_DIRECTORIES "../../../src/StdDrivers" )

if (WIN32)
else()
endif()

  list( APPEND TKStdSchema_USED_LIBS TKCDF )
  list( APPEND TKStdSchema_USED_LIBS PTKernel )
  list( APPEND TKStdSchema_USED_LIBS TKPLCAF )
  list( APPEND TKStdSchema_USED_LIBS TKernel )
  list( APPEND TKStdSchema_USED_LIBS TKCAF )
  list( APPEND TKStdSchema_USED_LIBS TKShapeSchema )
  list( APPEND TKStdSchema_USED_LIBS TKLCAF )
  list( APPEND TKStdSchema_USED_LIBS TKStdLSchema )
  list( APPEND TKStdSchema_USED_LIBS TKG3d )
  list( APPEND TKStdSchema_USED_LIBS TKPShape )
  list( APPEND TKStdSchema_USED_LIBS TKMath )
  list( APPEND TKStdSchema_USED_LIBS TKG2d )
  list( APPEND TKStdSchema_USED_LIBS TKPCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_DBC_VArrayOfCharacter.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_DBC_VArrayOfCharacter.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_DBC_VArrayOfExtCharacter.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_DBC_VArrayOfExtCharacter.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PColStd_FieldOfHArray1OfInteger.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PColStd_FieldOfHArray1OfInteger.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PColStd_HArray1OfInteger.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PColStd_HArray1OfInteger.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PCollection_HAsciiString.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PCollection_HAsciiString.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PCollection_HExtendedString.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PCollection_HExtendedString.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDF_Attribute.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDF_Attribute.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDF_FieldOfHAttributeArray1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDF_FieldOfHAttributeArray1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDF_HAttributeArray1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDF_HAttributeArray1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataStd_Integer.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataStd_Integer.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataStd_Real.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataStd_Real.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Axis.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Axis.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Constraint.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Constraint.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Geometry.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Geometry.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_PatternStd.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_PatternStd.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Placement.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Placement.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Plane.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Plane.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Point.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Point.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Position.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Position.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PDataXtd_Shape.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PDataXtd_Shape.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_FieldOfHArray1OfNamedShape.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_FieldOfHArray1OfNamedShape.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_HArray1OfNamedShape.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_HArray1OfNamedShape.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Name.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Name.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Name_1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Name_1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Name_2.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Name_2.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_NamedShape.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_NamedShape.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Naming.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Naming.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Naming_1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Naming_1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PNaming_Naming_2.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PNaming_Naming_2.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PPrsStd_AISPresentation.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PPrsStd_AISPresentation.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PPrsStd_AISPresentation_1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PPrsStd_AISPresentation_1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopLoc_Datum3D.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopLoc_Datum3D.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopLoc_ItemLocation.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopLoc_ItemLocation.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopLoc_Location.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopLoc_Location.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopoDS_FieldOfHArray1OfShape1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopoDS_FieldOfHArray1OfShape1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopoDS_HArray1OfShape1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopoDS_HArray1OfShape1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopoDS_Shape1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopoDS_Shape1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_PTopoDS_TShape1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_PTopoDS_TShape1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_Standard_Persistent.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_Standard_Persistent.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_Standard_Storable.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_Standard_Storable.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Ax1.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Ax1.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Ax2.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Ax2.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Ax2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Ax2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Ax3.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Ax3.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Dir.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Dir.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Dir2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Dir2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Mat.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Mat.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Mat2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Mat2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Pnt.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Pnt.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Pnt2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Pnt2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Trsf.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Trsf.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Trsf2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Trsf2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Vec.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Vec.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_Vec2d.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_Vec2d.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_XY.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_XY.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../drv/StdSchema/StdSchema_gp_XYZ.cxx" )
  SOURCE_GROUP (StdSchema FILES "../../../drv/StdSchema/StdSchema_gp_XYZ.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../src/StdDrivers/StdDrivers.cxx" )
  SOURCE_GROUP (StdDrivers FILES "../../../src/StdDrivers/StdDrivers.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../src/StdDrivers/StdDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (StdDrivers FILES "../../../src/StdDrivers/StdDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKStdSchema_USED_SRCFILES "../../../src/StdDrivers/StdDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (StdDrivers FILES "../../../src/StdDrivers/StdDrivers_DocumentStorageDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKStdSchema)
 add_library( TKStdSchema SHARED ${TKStdSchema_USED_SRCFILES} )

 set_property(TARGET TKStdSchema PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKStdSchema
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKStdSchema.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKStdSchema PROPERTIES COMPILE_FLAGS "${TKStdSchema_PRECOMPILED_DEFS}" )
 include_directories( ${TKStdSchema_COMPILER_DIRECTORIES} )
 target_link_libraries( TKStdSchema ${TKStdSchema_USED_LIBS} )
endif()
