#include <Arduino.h>
#include "gps.h"
#include "lidar.h"
#include "camera.h"
#include "pcu.h"
#include "wifi.h"
//#include "componentTest.h"


void gps_task( void * parameter);
void lidar_task( void * parameter);
void camera_task( void * parameter);
void pcu_task( void * parameter);
void wifi_task( void * parameter);

gps gps_obj =  gps();
lidar lidar_obj =  lidar();
camera camera_obj =  camera();
pcu pcu_obj =  pcu();
wifi wifi_obj =  wifi();
//componentTest cmp = componentTest();

#define LED_BOARD 2

void setup(){

  pinMode(LED_BOARD, OUTPUT);
  Serial.begin(9600);

  gps_obj.gps_setup();
  lidar_obj.lidar_setup();
  camera_obj.camera_setup();
  pcu_obj.pcu_setup();
  wifi_obj.wifi_setup();


  

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
    for(;;)
    {
        gps_obj.gps_loop();
        vTaskDelay(0 / portTICK_PERIOD_MS);
    }
    
}


void lidar_task( void * parameter )
{
   //cmp.testLidar(); 
   for(;;)
   {
       lidar_obj.lidar_loop();
       
       vTaskDelay(30 / portTICK_PERIOD_MS);
   }
}


void camera_task( void * parameter )
{
    for(;;)
    {
        camera_obj.camera_loop();
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
    
}


void pcu_task( void * parameter )
{
    for(;;)
    {
        
        pcu_obj.pcu_loop();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void wifi_task( void * parameter )
{
    for(;;)
    {
        wifi_obj.wifi_loop();
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
