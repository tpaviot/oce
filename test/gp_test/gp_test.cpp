#include <gp_Pnt.hxx>
#include <gtest/gtest.h>

TEST(gpTestSuite, testgp_PntConstruct)
{
    gp_Pnt P;
    ASSERT_EQ(0.0,P.X());
    ASSERT_EQ(0.0,P.Y());
    ASSERT_EQ(0.0,P.Z());
}

TEST(gpTestSuite, testgp_PntDistance)
{
    gp_Pnt P1(0.,0.,0.);
    gp_Pnt P2(0.,3.,4.);
    float D = (float)P1.Distance(P2);
    ASSERT_EQ(5.,D);
}

TEST(gpTestSuite, testBuildThousandsPoints)
{
    for (int i=1;i<10000;i++) {
        gp_Pnt(1,2,3);
    }
}

/*  This test fails with OCCT 6.5.1 and GCC 4.2 */
TEST(gpTestSuite, testGCC42gp_Trsf)
{
    gp_Trsf T;
    T.SetValues(
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0);
    ASSERT_EQ(1.0,T.Value(1,1));
    ASSERT_EQ(1.0,T.Value(2,2));
    ASSERT_EQ(1.0,T.Value(3,3));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
