#include <Arduino.h>
#include "PCU.h"
#include "wifi.h"

int CurrentVelocity;
double CurrentSteeringAngle;
bool leadTruckselected;
bool intruder_detected;
char * sendingData,*receivedData;

wifi wifiobj = wifi();

pcu::pcu()
{

}

void pcu::pcu_setup()
{
	leadTruckselected = false;
	intruder_detected = false;

	leadTruckselected = false;//getLeadTruckSelected();
}


void pcu::pcu_loop()
{
	CurrentVelocity = 100;//getVelocity();
	CurrentSteeringAngle = 100;//getSteeringAngle();

	if(leadTruckselected == true)
	{
		serializeData();
	}
	else
	{
		deserializeData();
		dataProcesssing();
		serializeData();
	}

	wifiobj.updateTxFrame();
}


void serializeData()
{
	sendingData = "leadTruck velocity+steering_angle+location";
}

void deserializeData()
{


}

void dataProcesssing()
{
	// if(d1-d2 == 10){
	// 		return 0;
	// 	}else if(d1-d2 > 10){
	// 		return 1;
	// 	}
	// 	return 2;
}

void pcu::updateCoordinates(double latitude, double longitude)
{
	// front_truck_latitude = latitude;
	// front_truck_longitude = longitude;
}

void pcu::updateGap(int gap)
{
	// distance_gap = gap;
}

void pcu::updateIntruder(bool detected_status)
{
	if(detected_status == true)
	{
		intruder_detected = true;
	}
	else
	{
		intruder_detected = false;
	}
}

void pcu::updateRxFrame(char* frame)
{
	receivedData = frame;
}

