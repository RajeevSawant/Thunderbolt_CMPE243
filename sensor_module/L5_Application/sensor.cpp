/*
 * sensor.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: arthurnguyen
 */

#include "sensor.h"

int frontStart = 0;
int frontStop = 0;
int backStart = 0;
int backStop = 0;
int leftStart = 0;
int leftStop = 0;
int rightStart = 0;
int rightStop = 0;



int frontDistance = 0;
int backDistance = 0;
int leftDistance = 0;
int rightDistance = 0;

SemaphoreHandle_t sensor1 = 0;
SemaphoreHandle_t sensor2 = 0;
SemaphoreHandle_t sensor3 = 0;
SemaphoreHandle_t sensor4 = 0;

bool PWMtask1::Init()
{
    static GPIO *Sensor_Input = new GPIO(P0_30);
    Sensor_Input->setAsOutput();
    Sensor_Input->setHigh();
    vTaskDelay(250);
    Sensor_Input->setLow();
    delete Sensor_Input;
    return true;
}
bool PWMtask1::run(void *p)
{
    static GPIO *Sensor_Input = new GPIO(P0_30);
    printf("goodbye");
    Sensor_Input->setAsOutput();
    Sensor_Input->setHigh();
    vTaskDelay(20);
    Sensor_Input->setLow();
    vTaskDelay(2000); //testing
    printf("DISTANCE 1 and 2 **************\n"); //testing
    printf("%i\n", frontDistance);
    printf("%i\n", backDistance);
    xSemaphoreGive(sensor1);
    if(xSemaphoreTake(sensor3, portMAX_DELAY))
    {
    }
    return true;
}
bool PWMtask2::Init()
{
    static GPIO *Sensor_Input = new GPIO(P0_29);
    Sensor_Input->setAsOutput();
    Sensor_Input->setHigh();
    vTaskDelay(250);
    Sensor_Input->setLow();
    delete Sensor_Input;
    return true;
}
bool PWMtask2::run(void *p)
{
    if(xSemaphoreTake(sensor1, portMAX_DELAY))
    {
        static GPIO *Sensor_Input = new GPIO(P0_29);
        Sensor_Input->setAsOutput();
        Sensor_Input->setHigh();
        vTaskDelay(20);
        Sensor_Input->setLow();
        vTaskDelay(2000); //testing
        printf("DISTANCE 3 and 4 ===============\n"); //testing
        printf("%i\n", leftDistance); //testing don't need delay
        printf("%i\n", rightDistance); //testing don't need delay

    }
    xSemaphoreGive(sensor3);
    return true;
}

void frontstartTimer(void)
{
    frontStart = (int)sys_get_uptime_us();
}

void frontstopTimer(void)
{
   frontStop = (int)sys_get_uptime_us() - frontStart;
   frontDistance = frontStop/147;
   long yield = 0;
   //xSemaphoreGiveFromISR(sensor1, &yield);
   portYIELD_FROM_ISR(&yield);
}

void backstartTimer(void)
{
    backStart = (int)sys_get_uptime_us();
}
void backstopTimer(void)
{
    backStop = (int)sys_get_uptime_us() - backStart;
    backDistance = backStop/147;
    long yield = 0;
    //xSemaphoreGiveFromISR(sensor2, &yield);
    portYIELD_FROM_ISR(&yield);
}

void leftstartTimer(void)
{
    leftStart = (int)sys_get_uptime_us();
}
void leftstopTimer(void)
{
    leftStop = (int)sys_get_uptime_us() - leftStart;
    leftDistance = leftStop/147;
    long yield = 0;
    //xSemaphoreGiveFromISR(sensor3, &yield);
    portYIELD_FROM_ISR(&yield);
}

void rightstartTimer(void)
{
    rightStart = (int)sys_get_uptime_us();
}
void rightstopTimer(void)
{
    rightStop = (int)sys_get_uptime_us() - rightStart;
    rightDistance = rightStop/147;
    long yield = 0;
    //xSemaphoreGiveFromISR(sensor4, &yield);
    portYIELD_FROM_ISR(&yield);
}

