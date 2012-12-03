#include <TCollection_CompareOfInteger.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <SortTools_QuickSortOfInteger.hxx>

#include <gtest/gtest.h>


class MyCompare : public TCollection_CompareOfInteger
{

    public:
        Standard_Boolean IsLower(
            const Standard_Integer &Left, const Standard_Integer &Right) const
        {
            return Left <= Right;
        }
};

TEST(SortToolsTestSuite, testQuickSortOfInteger)
{
    MyCompare comp;
    TColStd_Array1OfInteger arr(1, 3);
    arr.SetValue(1, 0);
    arr.SetValue(2, 0);
    arr.SetValue(3, 0);
    SortTools_QuickSortOfInteger::Sort(arr, comp);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
