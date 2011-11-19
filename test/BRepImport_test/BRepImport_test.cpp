#include <TopoDS_Shape.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <gtest/gtest.h>

#include "BRepImport_test_config.h"

TEST(BRepImportTestSuite, testImportBRep1)
{
    Standard_CString aFileName = (Standard_CString) brep_file_1;
    BRep_Builder aBuilder;
    TopoDS_Shape aShape;
	Standard_Boolean result = BRepTools::Read(aShape,aFileName,aBuilder);
    ASSERT_TRUE(result);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(BRepImportTestSuite, testImportBRep2)
{
    Standard_CString aFileName = (Standard_CString) brep_file_2;
    BRep_Builder aBuilder;
    TopoDS_Shape aShape;
	Standard_Boolean result = BRepTools::Read(aShape,aFileName,aBuilder);
    ASSERT_TRUE(result);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(BRepImportTestSuite, testImportBRep3)
{
    Standard_CString aFileName = (Standard_CString) brep_file_3;
    BRep_Builder aBuilder;
    TopoDS_Shape aShape;
	Standard_Boolean result = BRepTools::Read(aShape,aFileName,aBuilder);
    ASSERT_TRUE(result);
    ASSERT_FALSE(aShape.IsNull());
}

TEST(BRepImportTestSuite, testImportBRep4)
{
    Standard_CString aFileName = (Standard_CString) brep_file_4;
    BRep_Builder aBuilder;
    TopoDS_Shape aShape;
	Standard_Boolean result = BRepTools::Read(aShape,aFileName,aBuilder);
    ASSERT_TRUE(result);
    ASSERT_FALSE(aShape.IsNull());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
