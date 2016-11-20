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
#include "sensor.hpp"



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
    // TODO : Jon : Single function to do can_init();

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


/**
 * Below are your periodic functions.
 * The argument 'count' is the number of times each periodic task is called.
 */

void period_1Hz(uint32_t count)
{
    // TODO : Jon : Single function to handle_can_bus_reset();

	//Check CAN bus
	if(CAN_is_bus_off(can1))
	{
		CAN_reset_bus(can1);
		CAN_bypass_filter_accept_all_msgs(); // TODO : Jon : Consider filtering only on messages you receive
		                                     //              It's not critical but you should get the practice of
		                                     //              being able to do this
		LE.on(1);
	}
	else
	{
		LE.off(1);
		static SENSOR_HEARTBEAT_t sensor_heartbeat;
		sensor_heartbeat.SENSOR_HEARTBEAT_UNSIGNED = 336;

		// TODO : Jon : Make a wrapper for CAN_tx() so that you only have to send the msg_hrd.mid
		//              and the msg type (&sensor_heartbeat), and the wrapper will declare a local instance
		//              of can_msg_t so that you don't have to keep declaring it everytime you want to send a message.
		//              This will avoid clutter and multiple declarations everywhere.
		can_msg_t can_msg = {0};

		// Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
		dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_HEARTBEAT(can_msg.data.bytes, &sensor_heartbeat);
		can_msg.msg_id = msg_hdr.mid;
		can_msg.frame_fields.data_len = msg_hdr.dlc;

		// TODO : Jon : nit: spacing
		if(CAN_tx(can1, &can_msg, 0))
		 {
			//printf("Send heartbeat success\n");
		 }
		 else
		 {
			printf("Send heartbeat fail!\n");
		 }

	}

}

void period_10Hz(uint32_t count)
{
    // TODO : Single functions
	  static SENSOR_SONARS_t sonar_data;
	    sonar_data.SENSOR_SONARS_LEFT_UNSIGNED = leftDistance;
	    sonar_data.SENSOR_SONARS_RIGHT_UNSIGNED = rightDistance;
	    sonar_data.SENSOR_SONARS_FRONT_UNSIGNED = frontDistance;
	    sonar_data.SENSOR_SONARS_BACK_UNSIGNED = backDistance;
	    //can_msg_t can_msg;
		can_msg_t can_msg = {0};

		// Encode the CAN message's data bytes, get its header and set the CAN message's DLC and length
		dbc_msg_hdr_t msg_hdr = dbc_encode_SENSOR_SONARS(can_msg.data.bytes, &sonar_data);
		can_msg.msg_id = msg_hdr.mid;
		can_msg.frame_fields.data_len = msg_hdr.dlc;

		// TODO : Jon : nit: spacing
		// Queue the CAN message to be sent out
		if(CAN_tx(can1, &can_msg, 0))
		 {
		   //printf("Send data success\n");
		 }
		 else
		 {
			printf("Send data fail!\n");
		 }
		if(leftDistance < 20)
		{
			LE.on(1);
		}
		else
		{
			LE.off(1);
		}
		if(frontDistance < 20)
		{
			LE.on(2);
		}
		else
		{
			LE.off(2);
		}
		if(rightDistance < 20)
		{
			LE.on(3);
		}
		else
		{
			LE.off(3);
		}
}

void period_100Hz(uint32_t count)
{
   // LE.toggle(3);
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
   // LE.toggle(4);
}
