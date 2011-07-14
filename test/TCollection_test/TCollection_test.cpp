#include <gp_Pnt.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <gtest/gtest.h>

TEST(TCollectionTestSuite, testSequenceOfPnt)
{
    int n=500000;
    gp_Pnt res;
    TColgp_SequenceOfPnt pnt_seq;
    // test Append method
    for (int i=0;i<n;i++) {
        pnt_seq.Append(gp_Pnt(i,i,i));
    }
    // test Length method
    ASSERT_EQ(pnt_seq.Length(),n);
    // test Value method
    for (int i=1;i<n;i++) {
        res = pnt_seq.Value(i);
        ASSERT_EQ(res.X(),i-1);
        ASSERT_EQ(res.Y(),i-1);
        ASSERT_EQ(res.Z(),i-1);
    }
    // test First() method
    res = pnt_seq.First();
    ASSERT_EQ(res.X(),0.);
    ASSERT_EQ(res.Y(),0.);
    ASSERT_EQ(res.Z(),0.);
    // test Last() method
    res = pnt_seq.Last();
    ASSERT_EQ(res.X(),n-1);
    ASSERT_EQ(res.Y(),n-1);
    ASSERT_EQ(res.Z(),n-1);
    // test Exchange() method
    pnt_seq.Exchange(50,120);
    res = pnt_seq.Value(50);
    ASSERT_EQ(res.X(),119);
    ASSERT_EQ(res.Y(),119);
    ASSERT_EQ(res.Z(),119);
    res = pnt_seq.Value(120);
    ASSERT_EQ(res.X(),49);
    ASSERT_EQ(res.Y(),49);
    ASSERT_EQ(res.Z(),49);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
