#include <Arduino.h>
#include <OPT3101.h>
#include <Wire.h>
#include "camera.h"
#include "pcu.h"    

pcu camera_pcuobj = pcu();

bool intruderDetected;

const uint8_t dataReadyPin = 2;


OPT3101 sensor; /* create an object of the sensor class */


int16_t distances[3]; /* array where we'll store the values of each sensor pair (Tx-Rx LED) */
volatile bool dataReady = false; /* to determine when the data is ready to be read */

void setDataReadyFlag()
{
  dataReady = true;
}

camera::camera()
{

}

void camera::camera_setup()
{
    intruderDetected = false;

    /* Wire.begin takes two arguments, first being SDA and second being SCL (Wire.begin(SDA,SCL)) */
  Wire.begin(27,26);


  Serial.println("starting");

  /* Wait for the serial port to be opened before printing */
  /* messages (only applies to boards with native USB) */
  while (!Serial) {}

  sensor.init();
  if (sensor.getLastError()) /* case it is not possible to connect to the sensor */
  {
    Serial.print(F("Failed to initialize OPT3101: error "));
    Serial.println(sensor.getLastError());
    while (1) {} /* stay */
  }
  sensor.setContinuousMode();
  sensor.enableDataReadyOutput(1);
  sensor.setFrameTiming(32); /* to average the specified number of samples taken before returning a value */
  sensor.setChannel(OPT3101ChannelAutoSwitch); /* to automatically cycle through all channels */
  sensor.setBrightness(OPT3101Brightness::Adaptive); /* Adaptive mode automatically uses low or high brightness 
  depending on how much reflected light */
 
  attachInterrupt(digitalPinToInterrupt(dataReadyPin), setDataReadyFlag, RISING); /* set given pin as an interuption pin */
  sensor.enableTimingGenerator();
}

void camera::camera_loop()
{
    captureIntruder();
    camera_pcuobj.updateIntruder(intruderDetected);

}

void camera::captureIntruder()
{
    

      static int16_t arr[3];
  dataReady = true;
  if (dataReady) /* when we have data to read */
  {
    sensor.readOutputRegs();

    distances[sensor.channelUsed] = sensor.distanceMillimeters;

    if (sensor.channelUsed == 2) /* iterate only when we have read the 3 channels */
    {
      for (int16_t i = 0; i < 3; i++)
      {
        arr[i] = distances[i];
      }
    }
  }
  
  if(arr[1]<150)
  {
      intruderDetected = true;
  }
  else
  {
      intruderDetected = false;
  }


  dataReady = false;  /* put low to restart the sampling */
  delay(100);
}