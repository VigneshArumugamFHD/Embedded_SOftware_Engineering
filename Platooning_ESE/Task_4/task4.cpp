#include<iostream>

using namespace std;


class Truck{
private:
	double sensor = 0;
	double gps = 0;
	double speed = 0;
public:
	void setSensor(double s){
		sensor = s;
	}
	void setGps(double g){
		gps = g;
	}
	void setSpeed(double sp){
		speed = sp;
	}	
	
	double getSensor(){
		return sensor; 
	}
	double getGps(){
		return gps;
	}
	double getSpeed(){
		return speed;
	}
};

bool Parsing(double x, double y, double z){
	if(x == 0 || y == 0 || z == 0 ){
		return true;
	}
	return false;
}

int checkDistanceChanged(double d1, double d2){
	
	if(d1-d2 == 10){
		return 0;
	}else if(d1-d2 > 10){
		return 1;
	}	
	return 2;
}

void increaseSpeed(Truck &t){
	t.setSpeed(t.getSpeed() + 1);
}

void decreaseSpeed(Truck &t){
	//cout << t.getSpeed();
	t.setSpeed(t.getSpeed() - 1);
	//cout << t.getSpeed();
	
}

int main() {
	Truck leading_truck;
	leading_truck.setGps(1);
	leading_truck.setSensor(2);
	leading_truck.setSpeed(3);
	double lsensor = leading_truck.getSensor();
	double lGps = leading_truck.getGps();
	double lSpeed = leading_truck.getSpeed();
	
	Truck truck1;
	truck1.setGps(40);
	truck1.setSensor(2);
	truck1.setSpeed(3);
	double sensor1 = truck1.getSensor();
	double gps1 = truck1.getGps();
	double speed1 = truck1.getSpeed();
	
	
	
	Truck truck2;
	truck2.setGps(31);
	truck2.setSensor(2);
	truck2.setSpeed(3);
	double sensor2 = truck2.getSensor();
	double gps2 = truck2.getGps();
	double speed2 = truck2.getSpeed();
	
	Truck truck3;
	truck3.setGps(20);
	truck3.setSensor(2);
	truck3.setSpeed(3);
	double sensor3 = truck3.getSensor();
	double gps3 = truck3.getGps();
	double speed3 = truck3.getSpeed();
	
	bool P1 = Parsing(lsensor, lGps, lSpeed);
	bool P2 = Parsing(sensor1, gps1, speed1);
	bool P3 = Parsing(sensor2, gps2, speed2);
	bool P4 = Parsing(sensor3, gps3, speed3);
	
	if(P1 || P2 || P3 || P4){
		cout << "Final State" << endl;
		return 0;
	}
	
	if(!checkDistanceChanged(gps2,gps3)){
		cout << "Final State" << endl; 
		return 0;
	}
	if(checkDistanceChanged(gps2,gps3) == 1){
		decreaseSpeed(truck3);
		cout<< "Speed of truck 3 increased to" << truck3.getSpeed() << endl;
	}
	if(checkDistanceChanged(gps1,gps2) == 2){
		increaseSpeed(truck1);
		cout<< "Speed of truck 3 increased to" << truck1.getSpeed() << endl;
	}
	
	cout << "Final State" << endl;
	return 0;
	
	
}


