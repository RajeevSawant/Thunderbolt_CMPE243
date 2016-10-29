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
#include <stdio.h>
#include "can.h"
#include "_can_dbc/generated_can.h"
#include "sensor.h"




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
    //CAN initialization
    CAN_init(can1, 100, 4, 4, NULL, NULL);
    CAN_reset_bus(can1);
    CAN_bypass_filter_accept_all_msgs();
    return true; // Must return true upon success
}

/// Register any telemetry variables
bool period_reg_tlm(void)
{
    // Make sure "SYS_CFG_ENABLE_TLM" is enabled at sys_config.h to use Telemetry
    return true; // Must return true upon success
}



void period_1Hz(void)
{
    //Check CAN bus
    if(CAN_is_bus_off(can1))
    {
        CAN_reset_bus(can1);
        CAN_bypass_filter_accept_all_msgs();
        LE.on(1);
    }
    else
    {
        LE.off(1);
        static SENSOR_HEARTBEAT_t sensor_heartbeat;
        sensor_heartbeat.SENSOR_HEARTBEAT_UNSIGNED = 255;
        if(dbc_encode_and_send_SENSOR_HEARTBEAT(&sensor_heartbeat))
        {
            LE.on(1);
        }
        else
        {
            LE.off(1);
        }

    }
}

void period_10Hz(void)
{
    static SENSOR_SONARS_t sonar_data;
    sonar_data.SENSOR_SONARS_LEFT_UNSIGNED = leftDistance;
    sonar_data.SENSOR_SONARS_RIGHT_UNSIGNED = rightDistance;
    sonar_data.SENSOR_SONARS_FRONT_UNSIGNED = frontDistance;
    sonar_data.SENSOR_SONARS_BACK_UNSIGNED = backDistance;
    //can_msg_t can_msg;
    if(dbc_encode_and_send_SENSOR_SONARS(&sonar_data))
    {
    	LE.on(2);
    }
    else
    {
        LE.off(2);
    }

}

void period_100Hz(void)
{
    //LE.toggle(3);
}

void period_1000Hz(void)
{
    //LE.toggle(4);
}
