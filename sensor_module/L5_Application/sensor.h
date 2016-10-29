/*
 * sensor.h
 *
 *  Created on: Oct 20, 2016
 *      Author: arthurnguyen
 */

#ifndef L5_APPLICATION_SENSOR_HPP_
#define L5_APPLICATION_SENSOR_HPP_

#include "tasks.hpp"
#include "gpio.hpp"
#include <stdio.h>

extern int leftDistance;
extern int rightDistance;
extern int frontDistance;
extern int backDistance;

//Start and stop signal
extern bool startProcess;
//Time
extern int frontStart;
extern int frontStop;
extern int backStart;
extern int backStop;
extern int leftStart;
extern int leftStop;
extern int rightStart;
extern int rightStop;

//Semaphores
extern SemaphoreHandle_t sensor1;
extern SemaphoreHandle_t sensor2;
extern SemaphoreHandle_t sensor3;
extern SemaphoreHandle_t sensor4;


class PWMtask1 : public scheduler_task
 {
 public:
 PWMtask1(uint8_t priority) :
            scheduler_task("PWM task1", 512*4, priority)
        {

        }
    bool Init();
    bool run(void *p);
};
class PWMtask2 : public scheduler_task
 {
 public:
 PWMtask2(uint8_t priority) :
            scheduler_task("PWM task2", 512*4, priority)
        {

        }
    bool Init();
    bool run(void *p);
};

void frontstartTimer(void);
void frontstopTimer(void);
void backstartTimer(void);
void backstopTimer(void);
void leftstartTimer(void);
void leftstopTimer(void);
void rightstartTimer(void);
void rightstopTimer(void);

#endif /* L5_APPLICATION_SENSOR_HPP_ */
