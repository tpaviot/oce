#include <UnitsAPI.hxx>

#include <stdlib.h>
#include <gtest/gtest.h>

/*
 * Resource files have not yet been installed, so we have
 * to specify their location in sources.
 */
TEST(UnitsAPITestSuite, testCurrentUnits)
{
	setenv("CASROOT", SRC_CASROOT, 1);
	setenv("CSF_CurrentUnitsUserDefaults", SRC_RESOURCE, 1);
	UnitsAPI u;
	u.SetLocalSystem(UnitsAPI_SI);
	ASSERT_TRUE(0 == strcmp(u.CurrentUnit("LENGTH"), "m"));
}

TEST(UnitsAPITestSuite, testMDTVCurrentUnits)
{
	setenv("CASROOT", SRC_CASROOT, 1);
	setenv("CSF_MDTVCurrentUnitsUserDefaults", SRC_RESOURCE, 1);
	UnitsAPI u;
	u.SetLocalSystem(UnitsAPI_MDTV);
	ASSERT_TRUE(0 == strcmp(u.CurrentUnit("LENGTH"), "mm"));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
