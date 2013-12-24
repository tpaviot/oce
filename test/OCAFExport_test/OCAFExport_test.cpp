#include <AppStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Application.hxx>
#include <OSD_File.hxx>
#include <OSD_Path.hxx>
#include <TCollection_ExtendedString.hxx>
#include <LDOM_OSStream.hxx>
#include <iostream>
#include <gtest/gtest.h>

Handle(TDocStd_Application) app = new AppStd_Application();

TEST(OCAFExportTestSuite, testExportAscii)
{
    const char * filename = "ascii.cbf";
    Handle(TDocStd_Document) doc;
    app->NewDocument("BinOcaf", doc);
    app->SaveAs(doc, filename);
    app->Close(doc);

    OSD_Path path(filename);
    OSD_File file(path);
    ASSERT_TRUE(file.Exists());
    file.Remove();
    ASSERT_FALSE(file.Failed());
}

TEST(OCAFExportTestSuite, testExportNonAscii)
{
    // Use codepoints and not characters to avoid encoding problems
    TCollection_ExtendedString extName("XX.cbf");
    extName.SetValue(1, 0x439);
    extName.SetValue(2, 0x446);
    char* filename = new char[extName.LengthOfCString()+1];
    extName.ToUTF8CString(filename);

    Handle(TDocStd_Document) doc;
    app->NewDocument("BinOcaf", doc);
    app->SaveAs(doc, filename);
    app->Close(doc);

    OSD_Path path(filename);
    OSD_File file(path);
    ASSERT_TRUE(file.Exists());
    file.Remove();
    ASSERT_FALSE(file.Failed());
    delete[] filename;
}

TEST(OCAFExportTestSuite, testOverflow)
{
    // See https://github.com/tpaviot/oce/pull/441
    LDOM_OSStream oss(128);
    oss << "line 1" << std::endl;
    oss << "line 2" << std::endl;
    ASSERT_TRUE(strlen(oss.str()) == 14);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
