#include <Standard_StdAllocator.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(Standard_StdAllocatorTestSuite, testTraits)
{
    //type definitions
    typedef Handle_Standard_Transient elem_type;
    typedef Standard_StdAllocator<elem_type> allocator_type;

    ASSERT_EQ(sizeof (allocator_type::value_type),sizeof (elem_type));
    ASSERT_EQ(sizeof (allocator_type::pointer),sizeof (void*));
    ASSERT_EQ(sizeof (allocator_type::const_pointer),sizeof (void*));

    ASSERT_EQ(sizeof (allocator_type::size_type),sizeof (size_t));
    ASSERT_EQ(sizeof (allocator_type::difference_type),sizeof (ptrdiff_t));

    typedef int other_elem_type;
    ASSERT_EQ(sizeof (allocator_type::rebind<other_elem_type>::other::value_type), sizeof (other_elem_type));
}

TEST(Standard_StdAllocatorTestSuite, testContainers)
{
    //typed allocator
    std::list<TopoDS_Shape, Standard_StdAllocator<TopoDS_Shape> > aL;
    TopoDS_Solid aSolid = BRepPrimAPI_MakeBox (10., 20., 30.);
    aL.push_back (aSolid);
    ASSERT_EQ(aL.size(), size_t (1));

    //type cast
    Standard_StdAllocator<char> aCAlloc;
    std::vector<int, Standard_StdAllocator<int> > aV (aCAlloc);
    aV.push_back(1);
    ASSERT_EQ(aV.size(), size_t (1));

    //using void-specialization allocator
    std::vector<int, Standard_StdAllocator<void> > aV2;
    aV2.resize(10);
    aV2.push_back(-1);
    ASSERT_EQ(aV2.size(), size_t (11));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
