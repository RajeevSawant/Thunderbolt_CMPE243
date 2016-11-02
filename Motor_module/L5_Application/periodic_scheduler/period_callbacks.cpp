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
 *          p r e et . w i k i @ g m a il . c o m
 */

/**
 * @file
 * This contains the period callback functions for the periodic scheduler
 *
 * @warning
 * These callbacks should be used for hard real-time system, and the priority of these
 * tasks are above everything else in the system (above the PRIORITY_CRITICAL).
 * The period functions SHOULD NEVER block and SHOULD NEVER run over their time slot.
 * For example, the 1000Hz take slot runs periodically every 1ms, and whatever you
 * do must be completed within 1ms.  Running over the time slot will reset the system.
 */

#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "_can_dbc/generated_can.h"
#include "can.h"
#include "lpc_pwm.hpp"
#include <stdio.h>


MOTOR_HEARTBEAT_t motor_heartbeat = {0};
can_msg_t msg={ 0 };
dbc_msg_hdr_t msg_hdr;
 static int initVal=0;
const uint32_t      MASTER_DRIVING_CAR__MIA_MS = 3000;
const MASTER_DRIVING_CAR_t    MASTER_DRIVING_CAR__MIA_MSG = {STOP,CENTER,LOW};

MASTER_DRIVING_CAR_t rcv_car;
bool status;



/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);

/**
 * This is the stack size of the dispatcher task that triggers the period tasks to run.
 * Minimum 1500 bytes are needed in order to write a debug file if the period tasks overrun.
 * This stack size is also used while calling the period_init() and period_reg_tlm(), and if you use
 * printf inside these functions, you need about 1500 bytes minimum
 */
const uint32_t PERIOD_DISPATCHER_TASK_STACK_SIZE_BYTES = (512 * 3);

/// Called once before the RTOS is started, this is a good place to initialize things once
bool period_init(void)
{
    CAN_init(can1,100,10,10,NULL, NULL);
    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(can1);

    rcv_car.MASTER_DRIVE_ENUM =STOP;
    rcv_car.MASTER_SPEED_ENUM =LOW;
    rcv_car.MASTER_STEER_ENUM =CENTER;

    //   static PWM motor(PWM::pwm2, 50);
    //   static PWM servo(PWM::pwm1, 50);
    return true; // Must return true upon success

}

/// Register any telemetry variables
bool period_reg_tlm(void)
{
    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
    return true; // Must return true upon success
}


/**
 * Below are your periodic functions.
 * The argument 'count' is the number of times each periodic task is called.
 */

void period_1Hz(uint32_t count)
{

    if(CAN_is_bus_off(can1))
    {
        CAN_reset_bus(can1);
    }

    msg_hdr = dbc_encode_MOTOR_HEARTBEAT(msg.data.bytes,&motor_heartbeat);
    msg.msg_id = msg_hdr.mid;
    msg.frame_fields.data_len = msg_hdr.dlc;
    msg.data.qword = msg_hdr.mid;
    CAN_tx(can1, &msg, 0);

}

void period_10Hz(uint32_t count)
{
    if(CAN_rx(can1,&msg,0))
    {
        // status=CAN_rx(can1,&msg,0);
        dbc_msg_hdr_t msg_header;
        msg_header.mid=msg.msg_id;
        msg_header.dlc=msg.frame_fields.data_len;
        if(msg_header.mid == MASTER_DRIVING_CAR_HDR.mid)
        {
            dbc_decode_MASTER_DRIVING_CAR(&rcv_car,msg.data.bytes,&msg_header);
        }
    }

    printf("\n %d %d",rcv_car.MASTER_DRIVE_ENUM,rcv_car.MASTER_STEER_ENUM);
    dbc_handle_mia_MASTER_DRIVING_CAR(&rcv_car,100);
    static PWM motor(PWM::pwm2, 50);
    static PWM servo(PWM::pwm1, 50);
   if(initVal==0)
   {
       servo.set(7.2);
       motor.set(7.5);

   }
    switch(rcv_car.MASTER_STEER_ENUM)
    {
    case FAR_RIGHT:
        servo.set(10);
        break;
    case RIGHT:
        servo.set(6.1);
        break;
    case CENTER:
        servo.set(7.2);
        break;
    case LEFT:
        servo.set(8.6);
        break;
    case FAR_LEFT:
        servo.set(5.1);
        break;
    }

    switch(rcv_car.MASTER_SPEED_ENUM)
    {
    case LOW:
        motor.set(7.9);
        break;
    case MEDIUM:
        motor.set(8.1);
        break;
    case HIGH:
        motor.set(8.3);
        break;
    }

    switch(rcv_car.MASTER_DRIVE_ENUM)
    {
    case REVERSE:
        motor.set(7.1);
        break;
    case STOP:
        motor.set(7.5);
        break;
    case DRIVE:
        motor.set(7.9);
        break;
    }
    // LE.toggle(2);
}

void period_100Hz(uint32_t count)
{
    //LE.toggle(3);
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
    LE.toggle(4);
}
