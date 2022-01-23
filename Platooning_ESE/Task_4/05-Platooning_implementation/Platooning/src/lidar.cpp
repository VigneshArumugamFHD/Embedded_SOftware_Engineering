#include <Arduino.h>
#include <OPT3101.h>
#include <Wire.h>
#include "lidar.h"
#include "PCU.h"

pcu lidar_pcuobj = pcu();

int16_t DistanceGap;

const uint8_t lidar_dataReadyPin = 2;

OPT3101 lidar_sensor; /* create an object of the lidar_sensor class */

int16_t lidar_distances[3]; /* array where we'll store the values of each lidar_sensor pair (Tx-Rx LED) */
volatile bool lidar_dataReady = false; /* to determine when the data is ready to be read */

void lidar_setDataReadyFlag()
{
  lidar_dataReady = true;
}

lidar::lidar()
{

}

void lidar::lidar_setup()
{
    DistanceGap = 0;

    /* Wire.begin takes two arguments, first being SDA and second being SCL (Wire.begin(SDA,SCL)) */
  Wire.begin(27,26);


  Serial.println("starting");

  /* Wait for the serial port to be opened before printing */
  /* messages (only applies to boards with native USB) */
  while (!Serial) {}

  lidar_sensor.init();
  if (lidar_sensor.getLastError()) /* case it is not possible to connect to the lidar_sensor */
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(lidar_sensor.getLastError());
    while (1) {} /* stay */
  }
  lidar_sensor.setContinuousMode();
  lidar_sensor.enableDataReadyOutput(1);
  lidar_sensor.setFrameTiming(32); /* to average the specified number of samples taken before returning a value */
  lidar_sensor.setChannel(OPT3101ChannelAutoSwitch); /* to automatically cycle through all channels */
  lidar_sensor.setBrightness(OPT3101Brightness::Adaptive); /* Adaptive mode automatically uses low or high brightness 
  depending on how much reflected light */
 
  attachInterrupt(digitalPinToInterrupt(lidar_dataReadyPin), lidar_setDataReadyFlag, RISING); /* set given pin as an interuption pin */
  lidar_sensor.enableTimingGenerator();

}

void lidar::lidar_loop()
{
    captureGap();
    lidar_pcuobj.updateGap(DistanceGap);
}

void lidar::captureGap()
{
     static int16_t arr[3];
  lidar_dataReady = true;
  if (lidar_dataReady) /* when we have data to read */
  {
    lidar_sensor.readOutputRegs();

    lidar_distances[lidar_sensor.channelUsed] = lidar_sensor.distanceMillimeters;

    if (lidar_sensor.channelUsed == 2) /* iterate only when we have read the 3 channels */
    {
      for (int16_t i = 0; i < 3; i++)
      {
        arr[i] = lidar_distances[i];
      }
    }
  }
  
  DistanceGap = arr[1];    
}

