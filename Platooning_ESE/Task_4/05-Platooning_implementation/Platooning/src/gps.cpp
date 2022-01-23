#include <Arduino.h>
#include "gps.h"
#include "PCU.h"

pcu gps_pcuobj = pcu();

double longitude;
double latitude;

gps::gps()
{

}

void gps::gps_setup()
{
    longitude = 0;
    latitude = 0;
}

void gps::gps_loop()
{
    captureCoordinates();
    gps_pcuobj.updateCoordinates(latitude, longitude);
}

void gps::captureCoordinates()
{
    longitude = 100;//getlongitude();
    latitude = 200;//getlatitude();
}