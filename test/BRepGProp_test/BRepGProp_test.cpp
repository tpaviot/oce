#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <gtest/gtest.h>
#include <Precision.hxx>

TEST(BRepGPropTestSuite, testComputeBoxVolume)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeBox my_box(10.,10.,10.);
    my_box.Build();
    ASSERT_TRUE(my_box.IsDone());
    // compute shape properties
    GProp_GProps prop;
    // a 10*10*10 cube should have a volume of 1000
    BRepGProp::VolumeProperties(my_box.Shape(), prop);
    ASSERT_GT(prop.Mass(),1000.-Precision::Confusion());
    ASSERT_LT(prop.Mass(),1001.+Precision::Confusion());
}

TEST(BRepGPropTestSuite, testComputeBoxSurface)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeBox my_box(10.,10.,10.);
    my_box.Build();
    ASSERT_TRUE(my_box.IsDone());
    // compute shape properties
    GProp_GProps prop;
    // the surface should be 6 faces*10*10=600
    BRepGProp::SurfaceProperties(my_box.Shape(), prop);
    ASSERT_GT(prop.Mass(),600.-Precision::Confusion());
    ASSERT_LT(prop.Mass(),600.+Precision::Confusion());
}

TEST(BRepGPropTestSuite, testComputeSphereVolume)
{
    // create a box, mixing integers and floats
    BRepPrimAPI_MakeSphere sphere(20.);
    sphere.Build();
    ASSERT_TRUE(sphere.IsDone());
    // compute shape properties
    GProp_GProps prop;
    // a sphere with a radius of 20 should have a volume of 
    // V = 4/3*pi*20*20*20 = 33510.321638291127
    BRepGProp::VolumeProperties(sphere.Shape(), prop);
    ASSERT_GT(prop.Mass(),33510.321638291127-Precision::Confusion());
    ASSERT_LT(prop.Mass(),33510.321638291127+Precision::Confusion());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
