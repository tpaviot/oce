#include <TopoDS_Shape.hxx>
#include <STEPControl_Reader.hxx>

#include <gtest/gtest.h>

#include "STEPImport_test_config.h"

TEST(STEPImportTestSuite, testImportAP203_1)
{
    Standard_CString aFileName = (Standard_CString) step_file_ap203_1;
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    int nb_root = aReader.NbRootsForTransfer();
    int nb_shapes = 0;
    for ( Standard_Integer n = 1; n <= nb_root; n++ ) {
        Standard_Boolean result = aReader.TransferRoot( n );
        ASSERT_EQ(Standard_True,result);
        nb_shapes = aReader.NbShapes();
        if ( nb_shapes > 0 ) {
            TopoDS_Shape shape = aReader.Shape( n );
            ASSERT_EQ(Standard_False,shape.IsNull());
            }
        }
}

TEST(STEPImportTestSuite, testImportAP203_2)
{
    Standard_CString aFileName = (Standard_CString) step_file_ap203_2;
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    int nb_root = aReader.NbRootsForTransfer();
    int nb_shapes = 0;
    for ( Standard_Integer n = 1; n <= nb_root; n++ ) {
        Standard_Boolean result = aReader.TransferRoot( n );
        ASSERT_EQ(Standard_True,result);
        nb_shapes = aReader.NbShapes();
        if ( nb_shapes > 0 ) {
            TopoDS_Shape shape = aReader.Shape( n );
            ASSERT_EQ(Standard_False,shape.IsNull());
            }
        }
}

TEST(STEPImportTestSuite, testImportAP214_1)
{
    Standard_CString aFileName = (Standard_CString) step_file_ap214_1;
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    int nb_root = aReader.NbRootsForTransfer();
    int nb_shapes = 0;
    for ( Standard_Integer n = 1; n <= nb_root; n++ ) {
        Standard_Boolean result = aReader.TransferRoot( n );
        ASSERT_EQ(Standard_True,result);
        nb_shapes = aReader.NbShapes();
        if ( nb_shapes > 0 ) {
            TopoDS_Shape shape = aReader.Shape( n );
            ASSERT_EQ(Standard_False,shape.IsNull());
            }
        }
}

TEST(STEPImportTestSuite, testImportAP214_2)
{
    Standard_CString aFileName = (Standard_CString) step_file_ap214_2;
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    int nb_root = aReader.NbRootsForTransfer();
    int nb_shapes = 0;
    for ( Standard_Integer n = 1; n <= nb_root; n++ ) {
        Standard_Boolean result = aReader.TransferRoot( n );
        ASSERT_EQ(Standard_True,result);
        nb_shapes = aReader.NbShapes();
        if ( nb_shapes > 0 ) {
            TopoDS_Shape shape = aReader.Shape( n );
            ASSERT_EQ(Standard_False,shape.IsNull());
            }
        }
}

TEST(STEPImportTestSuite, testImportAP214_3)
{
    Standard_CString aFileName = (Standard_CString) step_file_ap214_3;
    STEPControl_Reader aReader;
    IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    int nb_root = aReader.NbRootsForTransfer();
    int nb_shapes = 0;
    for ( Standard_Integer n = 1; n <= nb_root; n++ ) {
        Standard_Boolean result = aReader.TransferRoot( n );
        ASSERT_EQ(Standard_True,result);
        nb_shapes = aReader.NbShapes();
        if ( nb_shapes > 0 ) {
            TopoDS_Shape shape = aReader.Shape( n );
            ASSERT_EQ(Standard_False,shape.IsNull());
            }
        }
}

//------------------------------------------------------------------------------
// Test for importing a surface of linear extrusion with a null swept curve.
// Success if no exceptions (C++ exceptions and Windows SEH exceptions) raised.
//------------------------------------------------------------------------------
TEST(STEPImportTestSuite, testImportNullSweptCurve) {
  Standard_CString aFileName = (Standard_CString) step_file_null_swept_curve;
  STEPControl_Reader aReader;

  IFSelect_ReturnStatus status = aReader.ReadFile (aFileName);
  if (status != IFSelect_RetDone) {
    return ;
  }

  int nb_root   = aReader.NbRootsForTransfer ();
  int nb_shapes = 0;

  for (Standard_Integer n = 1; n <= nb_root; ++n) {
    Standard_Boolean result = aReader.TransferRoot (n);
    if (! result) {
      continue;
    }

    nb_shapes = aReader.NbShapes ();
    if (nb_shapes > 0) {
      TopoDS_Shape shape = aReader.Shape (n);
      if (shape.IsNull ()) {
        continue;
      }
    }
  }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
