#include "TDataXtd_PatternStd.hxx"
#include "TDF_Label.hxx"
#include "XCAFApp_Application.hxx"
#include "TDocStd_Document.hxx"
#include "TDataStd_Integer.hxx"
#include "TDataStd_Real.hxx"
#include "TDataXtd_Array1OfTrsf.hxx"
#include "TNaming_NamedShape.hxx"

#include <gtest/gtest.h>

TEST(TDataXtdTestSuite, testPattern)
{
    Handle(TDocStd_Document) document;
    Handle (XCAFApp_Application) anApp = XCAFApp_Application::GetApplication();
    anApp->NewDocument("", document);
    Handle(TNaming_NamedShape) axis1 = new TNaming_NamedShape();
    ASSERT_FALSE(axis1.IsNull());
    Handle(TNaming_NamedShape) axis2 = new TNaming_NamedShape();
    ASSERT_FALSE(axis2.IsNull());
    TDF_Label patternsLabel = document->Main();
    TDF_Label newPatternLabel = TDF_TagSource::NewChild(patternsLabel);
    // adding the pattern data as an attribute
    Handle(TDataXtd_PatternStd) pattern = TDataXtd_PatternStd::Set(newPatternLabel);
    ASSERT_FALSE(pattern.IsNull());
    pattern->Signature(3);
    TDF_Label nbInst1Lab = TDF_TagSource::NewChild(newPatternLabel);
    Handle(TDataStd_Integer) nbInst1Attr = TDataStd_Integer::Set(nbInst1Lab,5);
    ASSERT_FALSE(nbInst1Attr.IsNull());
    pattern->NbInstances1(nbInst1Attr);
    TDF_Label nbInst2Lab = TDF_TagSource::NewChild(newPatternLabel);
    Handle(TDataStd_Integer) nbInst2Attr = TDataStd_Integer::Set(nbInst2Lab,5);
    ASSERT_FALSE(nbInst2Attr.IsNull());
    pattern->NbInstances2(nbInst2Attr);
    TDF_Label value1Lab = TDF_TagSource::NewChild(newPatternLabel);
    Handle(TDataStd_Real) value1Attr = TDataStd_Real::Set(value1Lab,20);
    ASSERT_FALSE(value1Attr.IsNull());
    pattern->Value1(value1Attr);
    TDF_Label value2Lab = TDF_TagSource::NewChild(newPatternLabel);
    Handle(TDataStd_Real) value2Attr = TDataStd_Real::Set(value2Lab,20);
    ASSERT_FALSE(value2Attr.IsNull());
    pattern->Value2(value2Attr);
    pattern->Axis1(axis1);
    pattern->Axis2(axis2);
    TDataXtd_Array1OfTrsf trsfArray(0, pattern->NbTrsfs());
    pattern->ComputeTrsfs(trsfArray);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
