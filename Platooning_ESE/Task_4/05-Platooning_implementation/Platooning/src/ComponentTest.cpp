#include <Arduino.h>
#include "gps.h"
#include "lidar.h"
#include "camera.h"
#include "pcu.h"
#include "wifi.h"
#include "componentTest.h"



// gps gps_obj =  gps();
// lidar lidar_obj =  lidar();
// camera camera_obj =  camera();
pcu pcu_obj_test =  pcu();
// wifi wifi_obj =  wifi();

componentTest::componentTest()
{

}


// void setup(){


//     gps_obj.gps_setup();
//     lidar_obj.lidar_setup();
//     camera_obj.camera_setup();
//     pcu_obj.pcu_setup();
//     wifi_obj.wifi_setup();
// }

void componentTest::testLidar(){
    int16_t test_value = 150;
    pcu_obj_test.updateGap(test_value);
    pcu_obj_test.dataProcesssing();

    // char* test_output = "Decreasing Speed ";
}

void componentTest::testGPS(){
    pcu_obj_test.updateCoordinates(12,15);
}

void componentTest::testWifi(){
    pcu_obj_test.updateRxFrame("Update Wifi");
}

void componentTest::testCamera(){
    bool intruder = true;
    pcu_obj_test.updateIntruder(intruder);
}


