#include <BRepPrimAPI_MakeBox.hxx>
#include <gtest/gtest.h>

TEST(BRepPrimAPITestSuite, testCreateBox)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeBox my_box(10,20.5,30.);
    my_box.Build();
    ASSERT_TRUE(my_box.IsDone());
}

TEST(BRepPrimAPITestSuite, testCreateFlatBox)
{
    // one of the length is equal to 0.
    // OCE must raise Standard_DomainError
    ASSERT_THROW(BRepPrimAPI_MakeBox my_box(0,30.,30),Standard_DomainError);
    ASSERT_THROW(BRepPrimAPI_MakeBox my_box(30.,0.,30),Standard_DomainError);
    ASSERT_THROW(BRepPrimAPI_MakeBox my_box(30.,30.,0.),Standard_DomainError);
}

TEST(BRepPrimAPITestSuite, testCreateSmallestBox)
{
    // all the lengths are equal to Precision::Confusion()
    // should not raise any exception
    Standard_Real smallest_length = Precision::Confusion() + 1e-14;
    BRepPrimAPI_MakeBox my_box(smallest_length,smallest_length,smallest_length);
    my_box.Build();
    ASSERT_TRUE(my_box.IsDone());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
