#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>

#include <gtest/gtest.h>

/* @TODO: in the following tests, minimal distances between two shapes.
It's not obvious anyway to figure out the relationship between the deflection passed to
BRepExtrema_DistSS (related to the mesh quality) and the precision of the output.
This has to be investigated further.
*/

TEST(BRepExtremaTestSuite, testDistSphereSphere)
{
    // the distance d between sphere1, centered at origin and radius r1, and
    // sphere 2, centered at (a,0,0) and radius r2
    // should be d = a-(r1+r2)
    Standard_Real r1 = 10.0;
    BRepPrimAPI_MakeSphere sphere1(r1);
    TopoDS_Shape sphere1_shp = sphere1.Shape();
     
    Standard_Real a = 100.0;
    Standard_Real r2 = 20.0;
    gp_Pnt center2(a,0,0);
    BRepPrimAPI_MakeSphere sphere2(center2,r2);
    TopoDS_Shape sphere2_shp = sphere2.Shape();
    
    BRepExtrema_DistShapeShape distSS;
    distSS.LoadS1(sphere1_shp);
    distSS.LoadS2(sphere2_shp);
    distSS.Perform();
    
    // should only be one minimal value
    ASSERT_EQ(distSS.NbSolution(),1);
    // this value should be
    Standard_Real expected_result = a-(r1+r2);
    Standard_Real min_dist = distSS.Value();
    // @TODO: should compare with a precision
    float abs_error = 0.001;
    ASSERT_NEAR(expected_result,min_dist,abs_error);
}

TEST(BRepExtremaTestSuite, testDistSphereVertex)
{
    // the distance d between sphere1, centered at origin and radius r1, and
    // vertex, a point of coordinates (a,b,c)
    // should be d = sqrt(a^2+b^2+c^2)-r1
    Standard_Real r1 = 10.0;
    BRepPrimAPI_MakeSphere sphere1(r1);
    TopoDS_Shape sphere1_shp = sphere1.Shape();
     
    Standard_Real a = 100.0;
    Standard_Real b = 50.0;
    Standard_Real c = 20.0;
    
    gp_Pnt point(a,b,c);
    TopoDS_Vertex V=BRepBuilderAPI_MakeVertex(point).Vertex();
    BRepExtrema_DistShapeShape distSS;
    distSS.LoadS1(sphere1_shp);
    distSS.LoadS2(V);
    distSS.SetDeflection(0.001);
    distSS.Perform();
    
    // should only be one minimal value
    ASSERT_EQ(distSS.NbSolution(),1);
    // this value should be
    gp_Vec v(a,b,c);
    Standard_Real expected_result = v.Magnitude()-r1;
    Standard_Real min_dist = distSS.Value();
    
    float abs_error = 0.001;
    ASSERT_NEAR(expected_result,min_dist,abs_error);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
