#include "pch.h"
#include <gtest/gtest.h>

struct PCU
{
	int CurrentVelocity = 0;
	double CurrentSteeringAngle = 0;
	bool leadTruckselected = false;
	bool intruder_detected = false;
	int front_truck_latitude = 0;
	int front_truck_longitude = 0;
	int measuredDistanceGap = 0;
	bool detectedStatus = false;


	PCU()
	{
	}

	void PCU::updateCoordinates(double latitude, double longitude)
	{
		front_truck_latitude = latitude;
		front_truck_longitude = longitude;
	}

	void PCU::updateGap(int16_t gap)
	{
		measuredDistanceGap = gap;
	}

	void PCU::updateIntruder(bool detected_status)
	{
		if (detected_status == true)
		{
			intruder_detected = true;
		}
		else
		{
			intruder_detected = false;
		}
	}


	void PCU::truckSelect(bool truckSelect)
	{
		if (truckSelect == true)
			leadTruckselected = true;
		else
			leadTruckselected = false;
	}

};


TEST(InitialValueTest, PCUsetup)
{
	PCU initialSetup;

	EXPECT_FALSE(initialSetup.leadTruckselected);
	EXPECT_FALSE(initialSetup.intruder_detected);
	EXPECT_EQ(0, initialSetup.front_truck_latitude);
	EXPECT_EQ(0, initialSetup.front_truck_longitude);
	EXPECT_EQ(0, initialSetup.measuredDistanceGap);

}

TEST(updateCoordinatesTest, PCUtest)
{
	PCU setCoord;
	setCoord.updateCoordinates(10, 20);
	EXPECT_EQ(10, setCoord.front_truck_latitude);
	EXPECT_EQ(20, setCoord.front_truck_longitude);

}

TEST(truckSelection, PCUtest)
{
	PCU selectTruck;

	selectTruck.truckSelect(true);
	EXPECT_TRUE(selectTruck.leadTruckselected);
	selectTruck.truckSelect(false);
	EXPECT_FALSE(selectTruck.leadTruckselected);
}

TEST(detectIntruderTest, PCUtest)
{
	PCU detectIntruder;
	detectIntruder.updateIntruder(true);
	EXPECT_TRUE(detectIntruder.intruder_detected);
	detectIntruder.updateIntruder(false);
	EXPECT_FALSE(detectIntruder.intruder_detected);

}


TEST(gapUpdateTest, PCUtest)
{
	PCU gapUpdater;
	gapUpdater.updateGap(20);
	EXPECT_EQ(20, gapUpdater.measuredDistanceGap);
}
	



int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
