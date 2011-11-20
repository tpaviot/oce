#include <UnitsAPI.hxx>
#include <OSD_Environment.hxx>
#include <stdlib.h>
#include <gtest/gtest.h>

/*
 * Resource files have not yet been installed, so we have
 * to specify their location in sources.
 */
TEST(UnitsAPITestSuite, testCurrentUnits)
{
	OSD_Environment v1("CASROOT", SRC_CASROOT); v1.Build();
	OSD_Environment v2("CSF_CurrentUnitsUserDefaults", SRC_RESOURCE); v2.Build();

	UnitsAPI::SetLocalSystem(UnitsAPI_SI);
	ASSERT_TRUE(0 == strcmp(UnitsAPI::CurrentUnit("LENGTH"), "m"));
}

TEST(UnitsAPITestSuite, testMDTVCurrentUnits)
{
	OSD_Environment v1("CASROOT", SRC_CASROOT); v1.Build ();
	OSD_Environment v2("CSF_MDTVCurrentUnitsUserDefaults", SRC_RESOURCE); v2.Build();
	
	UnitsAPI::SetLocalSystem(UnitsAPI_MDTV);
	ASSERT_TRUE(0 == strcmp(UnitsAPI::CurrentUnit("LENGTH"), "mm"));
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
