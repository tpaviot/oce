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
    float D = P1.Distance(P2);
    ASSERT_EQ(5.,D);
}

TEST(gpTestSuite, testBuildThousandsPoints)
{
    for (int i=1;i<10000;i++) {
        gp_Pnt(1,2,3);
    }
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
