#include <Arduino.h>
#include "PCU.h"
#include "wifi.h"

int CurrentVelocity;
double CurrentSteeringAngle;
bool leadTruckselected;
bool intruder_detected;
char sendingData[10] = {'v','e','l','a','n','g','p','o','s','\0'};
char receivedData[10];
double front_truck_latitude;
double front_truck_longitude;
int16_t measuredDistanceGap;

#define DESIRED_DISTANCE_GAP 100  /*10 meters*/


wifi wifiobj = wifi();

pcu::pcu()
{

}

void pcu::pcu_setup()
{
	leadTruckselected = false;
	intruder_detected = false;

	front_truck_latitude = 0;
	front_truck_longitude = 0;

	measuredDistanceGap = 0;

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

	wifiobj.updateTxFrame(sendingData);
}


void pcu::serializeData()
{

}

void pcu::deserializeData()
{


}

void pcu::dataProcesssing()
{
	if(measuredDistanceGap < DESIRED_DISTANCE_GAP)
	{
		Serial.print("Decreasing Speed : Measured_Distance = ");
		Serial.println(measuredDistanceGap);
	}
	else
	{
		Serial.print("Increasing Speed : Measured_Distance = ");
		Serial.println(measuredDistanceGap);
	}

	

	if(intruder_detected == true)
	{
		Serial.println("Intruder detected Decreasing Speed");
	}
	else
	{
		Serial.println("Maintaining Speed");
	}

	// Serial.println("DataProcessing");
}

void pcu::updateCoordinates(double latitude, double longitude)
{
	 Serial.print("Front truck latitude before updating: ");
	 Serial.println(front_truck_latitude);
	 Serial.print("Front truck longitude before updating: ");
	 Serial.println(front_truck_longitude);
	 front_truck_latitude = latitude;
	 front_truck_longitude = longitude;
	 Serial.print("Front truck latitude after updating: ");
	 Serial.println(front_truck_latitude);
	 Serial.print("Front truck longitude after updating: ");
	 Serial.println(front_truck_longitude);
}

void pcu::updateGap(int16_t gap)
{
	measuredDistanceGap = gap;
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
	char* temp = receivedData;
	temp = frame;
	Serial.println("Wifi data is updated");
}

