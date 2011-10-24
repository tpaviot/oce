#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <BRep_Builder.hxx>
#include <Geom_Surface.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <TopLoc_Location.hxx>
#include <Poly_Triangulation.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepBuilderAPI_NurbsConvert.hxx>

#include <gtest/gtest.h>

TEST(BRepMeshTestSuite, testMeshBox)
{
    BRepPrimAPI_MakeBox box(10.,10.,10.);
    box.Build();
    ASSERT_TRUE(box.IsDone());
    // compute mesh
    BRepMesh_IncrementalMesh m(box.Shape(), 7E-3, true);
	m.Perform();
    ASSERT_TRUE(m.IsDone());
}

TEST(BRepMeshTestSuite, testMeshSphere)
{
    BRepPrimAPI_MakeSphere sphere(50.);
    sphere.Build();
    ASSERT_TRUE(sphere.IsDone());
    // compute mesh
    BRepMesh_IncrementalMesh m(sphere.Shape(), 7E-3, true);
	m.Perform();
    ASSERT_TRUE(m.IsDone());
}

int nbTriangle(const TopoDS_Face & s)
{
	BRepMesh_IncrementalMesh m(s, 7E-3, true);
	m.Perform();
	TopLoc_Location l;
	const Handle(Poly_Triangulation) & pt = BRep_Tool::Triangulation(s, l);
	return pt.IsNull() ? 0 : pt->NbTriangles();
}

TEST(BRepMeshTestSuite, testMeshTorus)
{
    for(int radius = 1; radius < 20; radius++) {
        BRepPrimAPI_MakeTorus torus(radius,1.);
        torus.Build();
        ASSERT_TRUE(torus.IsDone());
	    TopExp_Explorer ex(torus.Shape(), TopAbs_FACE);
	    const TopoDS_Face & primTorus = (const TopoDS_Face &)ex.Current();
        ASSERT_NE(nbTriangle(primTorus),0);
   	    BRepBuilderAPI_NurbsConvert converter;
	    converter.Perform(primTorus);
        ASSERT_TRUE(converter.IsDone());
	    const TopoDS_Face & nurbsTorus = (const TopoDS_Face &)converter.ModifiedShape(primTorus);
	    ASSERT_NE(nbTriangle(nurbsTorus),0);
   	}
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
