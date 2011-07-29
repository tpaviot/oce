#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepAlgoAPI_Cut.hxx>

#include <gtest/gtest.h>

TEST(BRepAlgoAPITestSuite, testCutBox)
{
    // create the first shape: a cube, a corner at the origin
    TopoDS_Solid box1 = BRepPrimAPI_MakeBox(10.,10.,10.);
    ASSERT_FALSE(box1.IsNull());
    // the second shape: a smaller cube, a corner at the origin
    TopoDS_Solid box2 = BRepPrimAPI_MakeBox(5.,5.,5.);
    ASSERT_FALSE(box2.IsNull());
    // boolean cut
    TopoDS_Shape shp_result = BRepAlgoAPI_Cut(box1,box2);
    ASSERT_FALSE(shp_result.IsNull());
    TopoDS_Shape shp_result2 = BRepAlgoAPI_Cut(box2,box1);
    ASSERT_FALSE(shp_result2.IsNull());
}

TEST(BRepAlgoAPITestSuite, testCutCylSphere)
{
    // create the first shape: a sphere, centered at the origin
    TopoDS_Solid sphere = BRepPrimAPI_MakeSphere(10.);
    ASSERT_FALSE(sphere.IsNull());
    // the second shape: a cylinder cube, a corner at the origin
    TopoDS_Solid cylinder = BRepPrimAPI_MakeCylinder(5.,15.);
    ASSERT_FALSE(cylinder.IsNull());
    // boolean cut
    TopoDS_Shape shp_result = BRepAlgoAPI_Cut(sphere,cylinder);
    ASSERT_FALSE(shp_result.IsNull());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
