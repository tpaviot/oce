#include <TopoDS_Shape.hxx>
#include <IGESControl_Reader.hxx>

#include <gtest/gtest.h>

#include "IGESImport_test_config.h"

TEST(IGESImportTestSuite, testImportIGES_1)
{
    Standard_CString aFileName = (Standard_CString) iges_file_1;
    IGESControl_Reader Reader;
    int status = Reader.ReadFile(aFileName);
    ASSERT_EQ(status,IFSelect_RetDone);
    TopoDS_Shape tdsshape;
    if ( status == IFSelect_RetDone )
    {
        Reader.TransferRoots();
        tdsshape = Reader.OneShape();
    }
    ASSERT_FALSE(tdsshape.IsNull());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
