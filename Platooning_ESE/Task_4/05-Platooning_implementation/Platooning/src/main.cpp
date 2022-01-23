#include <Arduino.h>
#include "pcu.h"


void gps_task( void * parameter);
void lidar_task( void * parameter);
void camera_task( void * parameter);
void pcu_task( void * parameter);
void wifi_task( void * parameter);

pcu pcu_obj =  pcu();

#define LED_BOARD 2

void setup(){

  pinMode(LED_BOARD, OUTPUT);
  Serial.begin(9600);

  pcu_obj.pcu_setup();
  
  delay(1000);

  xTaskCreate(
                    gps_task,          /* Task function. */
                    "gps_task",        /* String with name of task. */
                    2048,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

  xTaskCreate(
                    lidar_task,          /* Task function. */
                    "lidar_task",        /* String with name of task. */
                    2048,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    2,                /* Priority of the task. */
                    NULL);            /* Task handle. */

   xTaskCreate(
                    camera_task,          /* Task function. */
                    "camera_task",        /* String with name of task. */
                    2048,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    2,                /* Priority of the task. */
                    NULL);            /* Task handle. */

  xTaskCreate(
                    pcu_task,          /* Task function. */
                    "pcu_task",        /* String with name of task. */
                    2048,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

  xTaskCreate(
                    wifi_task,          /* Task function. */
                    "wifi_task",        /* String with name of task. */
                    2048,              /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

}

void loop(){
delay(1000);
}

void gps_task( void * parameter )
{
    
}


void lidar_task( void * parameter )
{
   
}


void camera_task( void * parameter )
{
    
}


void pcu_task( void * parameter )
{
    for(;;)
    {
        
    }
}

void wifi_task( void * parameter )
{
    
}
