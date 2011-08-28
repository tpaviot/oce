#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepOffsetAPI_MakeEvolved.hxx>
#include <gp_Pnt.hxx>
#include <GeomAbs_JoinType.hxx>
#include <gtest/gtest.h>

TEST(BRepOffsetAPITestSuite, testEvolvedShape)
{
    // create a box, mixing integers and floats
    BRepBuilderAPI_MakePolygon P;
    P.Add(gp_Pnt(0.,0.,0.));
    P.Add(gp_Pnt(200.,0.,0.));
    P.Add(gp_Pnt(200.,200.,0.));
    P.Add(gp_Pnt(0.,200.,0.));
    P.Add(gp_Pnt(0.,0.,0.));
    BRepBuilderAPI_MakePolygon wprof(gp_Pnt(0.,0.,0.),gp_Pnt(-60.,-60.,-200.));
    BRepOffsetAPI_MakeEvolved S(P.Wire(),wprof.Wire(),GeomAbs_Arc,Standard_True,Standard_False,Standard_True,0.0001);
    S.Build();
    ASSERT_TRUE(S.IsDone());
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
