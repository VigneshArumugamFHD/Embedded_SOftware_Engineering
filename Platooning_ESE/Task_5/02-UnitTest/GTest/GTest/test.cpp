#include "pch.h"
#include <gtest/gtest.h>




struct PCU
{
	int CurrentVelocity;
	double CurrentSteeringAngle;
	bool leadTruckselected = false;
	bool intruder_detected = false;
	char* sendingData, * receivedData;
	int front_truck_latitude = 0;
	int front_truck_longitude = 0;
	int16_t measuredDistanceGap;
	bool detectedStatus;

	PCU()
	{
	}

	void updateGap(int16_t gap)
	{
		measuredDistanceGap = gap;
	}

	void updateCoordinates(double latitude, double longitude)
	{
		front_truck_latitude = latitude;
		front_truck_longitude = longitude;
	}

};

TEST(SetupTest, PCUsetup)
{
	PCU setup;
	EXPECT_EQ(false, setup.leadTruckselected);
	EXPECT_EQ(false, setup.intruder_detected);
	EXPECT_EQ(0, setup.front_truck_latitude);
	EXPECT_EQ(0, setup.front_truck_longitude);

	//EXPECT_TRUE(true,setup.leadTruckselected);

	//ASSERT_EQ(1,setup.leadTruckselected);


}

struct changeSettings : testing::Test
{
	PCU* newSetup;



	void updateGap(int16_t gap)
	{
		newSetup->measuredDistanceGap = gap;
	}

	void updateIntruder(bool detected_status)
	{
		if (detected_status == true)
		{
			newSetup->intruder_detected = true;
		}
		else
		{
			newSetup->intruder_detected = false;
		}
	}

};


TEST_F(changeSettings, settingsChanged)
{
	newSetup->updateGap(10);
	EXPECT_EQ(1, newSetup->measuredDistanceGap);

}


/*
struct setup : testing::Test {
	bool leadTrucksSelected;
	bool setupTesting()
	{
		leadtrucks = false;
	}

};
*/





/*
TEST(SetupTest, SelectedVehiclesFalse) {
	EQQ
}
*/

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
