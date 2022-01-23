#include <Arduino.h>
#include "pcu.h"

using namespace std;

static int CurrentVelocity;
static double CurrentSteeringAngle;
static bool leadTruckselected;
static bool intruder_detected;
static char * sendingData,*receivedData;

pcu::pcu()
{

}

void static pcu_setup()
{
	leadTruckselected = false;
	intruder_detected = false;

	leadTruckselected = false;//getLeadTruckSelected();
}


void static pcu_loop()
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

	updateTxFrame(sendingData);
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

	if(d1-d2 == 10){
			return 0;
		}else if(d1-d2 > 10){
			return 1;
		}
		return 2;


}

void updateCoordinates(double latitude, double longitude)
{
	front_truck_latitude = latitude;
	front_truck_longitude = longitude;
}

void updateGap(int gap)
{
	distance_gap = gap;
}


void updateIntruder(bool detected_status)
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

void updateRxFrame(char* frame)
{
	receivedData = frame;
}

// void increaseSpeed(Truck &t)
// {
// 	t.setSpeed(t.getSpeed() + 1);
// }

// void decreaseSpeed(Truck &t)
// {
// 	//cout << t.getSpeed();
// 	t.setSpeed(t.getSpeed() - 1);
// 	//cout << t.getSpeed();
	
// }

//int main() {
//	Truck leading_truck;
//	leading_truck.setGps(1);
//	leading_truck.setSensor(2);
//	leading_truck.setSpeed(3);
//	double lsensor = leading_truck.getSensor();
//	double lGps = leading_truck.getGps();
//	double lSpeed = leading_truck.getSpeed();
//
//	Truck truck1;
//	truck1.setGps(40);
//	truck1.setSensor(2);
//	truck1.setSpeed(3);
//	double sensor1 = truck1.getSensor();
//	double gps1 = truck1.getGps();
//	double speed1 = truck1.getSpeed();
//
//
//
//	Truck truck2;
//	truck2.setGps(31);
//	truck2.setSensor(2);
//	truck2.setSpeed(3);
//	double sensor2 = truck2.getSensor();
//	double gps2 = truck2.getGps();
//	double speed2 = truck2.getSpeed();
//
//	Truck truck3;
//	truck3.setGps(20);
//	truck3.setSensor(2);
//	truck3.setSpeed(3);
//	double sensor3 = truck3.getSensor();
//	double gps3 = truck3.getGps();
//	double speed3 = truck3.getSpeed();
//
//	bool P1 = Parsing(lsensor, lGps, lSpeed);
//	bool P2 = Parsing(sensor1, gps1, speed1);
//	bool P3 = Parsing(sensor2, gps2, speed2);
//	bool P4 = Parsing(sensor3, gps3, speed3);
//
//	if(P1 || P2 || P3 || P4){
//		cout << "Final State" << endl;
//		return 0;
//	}
//
//	if(!checkDistanceChanged(gps2,gps3)){
//		cout << "Final State" << endl;
//		return 0;
//	}
//	if(checkDistanceChanged(gps2,gps3) == 1){
//		decreaseSpeed(truck3);
//		cout<< "Speed of truck 3 increased to" << truck3.getSpeed() << endl;
//	}
//	if(checkDistanceChanged(gps1,gps2) == 2){
//		increaseSpeed(truck1);
//		cout<< "Speed of truck 3 increased to" << truck1.getSpeed() << endl;
//	}
//
//	cout << "Final State" << endl;
//	return 0;
//
//
//}


