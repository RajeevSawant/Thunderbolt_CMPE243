/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 *                      FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 *                      @see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include "tasks.hpp"
#include <stdio.h>
#include "examples/examples.hpp"
#include "periodic_scheduler/periodic_callback.h"
#include "eint.h"
#include "FreeRTOS.h"
#include "io.hpp"
#include "gpio.hpp"
#include "uart2.hpp"
#include "uart3.hpp"
#include <string>
#include "adc0.h"
#include <iostream>
#include "lpc_sys.h"
#include "soft_timer.hpp"
#include <inttypes.h>
using namespace std;


/**
 * The main() creates tasks or "threads".  See the documentation of scheduler_task class at scheduler_task.hpp
 * for details.  There is a very simple example towards the beginning of this class's declaration.
 *
 * @warning SPI #1 bus usage notes (interfaced to SD & Flash):
 *      - You can read/write files from multiple tasks because it automatically goes through SPI semaphore.
 *      - If you are going to use the SPI Bus in a FreeRTOS task, you need to use the API at L4_IO/fat/spi_sem.h
 *
 * @warning SPI #0 usage notes (Nordic wireless)
 *      - This bus is more tricky to use because if FreeRTOS is not running, the RIT interrupt may use the bus.
 *      - If FreeRTOS is running, then wireless task may use it.
 *        In either case, you should avoid using this bus or interfacing to external components because
 *        there is no semaphore configured for this bus and it should be used exclusively by nordic wireless.
 */

int startTime;
int stopTime;
int testCount;
SemaphoreHandle_t startCount = NULL;

 class PWMtask : public scheduler_task
  {
  public:
  PWMtask(uint8_t priority) :
             scheduler_task("PWM task", 512*4, priority)
         {

         }

     bool run(void *p)
     {
         vTaskDelay(1000); 																										//testing
         static GPIO *Sensor_Input = new GPIO(P0_30);
         Sensor_Input->setAsOutput();
         Sensor_Input->setHigh();
         vTaskDelay(30);
         Sensor_Input->setLow();
         vTaskDelay(30);
         printf("%i\n", stopTime);
         return true;
     }
 };


void startTimer(void);
void stopTimer(void);

int main(void)
{

    //Testing
    scheduler_add_task(new PWMtask(PRIORITY_HIGH));
    eint3_enable_port2(0, eint_rising_edge, startTimer);
    eint3_enable_port2(0, eint_falling_edge, stopTimer);

    scheduler_start(); ///< This shouldn't return
    return -1;
}
void startTimer(void)
{
     startTime = (int)sys_get_uptime_us();
     testCount ++;
}

void stopTimer(void)
{
    stopTime = ((int)sys_get_uptime_us() - startTime)/147;
    testCount++;
}
