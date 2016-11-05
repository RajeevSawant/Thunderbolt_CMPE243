/*
8   *     SocialLedge.com - Copyright (C) 2013
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
#include "uart2.hpp"
#include<stdio.h>
#include <cmath>
#include <string>
#include <stdlib.h>
#include<math.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "can.h"
#include "_can_dbc/generated_can.h"
using namespace std;
#define EARTH_RADIUS 6384000
#define PI 3.14159
#define MIN_PER_DEGREE 60.0
#define SEC_PER_MINUTE 60.0
GPS_CURRENT_LOCATION_t com_data = {0};
GPS_ACKNOWLEDGEMENT_t ackToComBridge ={0};
GPS_MASTER_DATA_t master_data = {0};
double finalDestinationDistance ;
double turn_angle ;
double distanceToNextCheckpoint;
static int TotalCountReceived=0;
static int sentData=0;
bool isCheckpointReceived = false;
double latitude_array[18]={37.336057, 37.336151, 37.336151, 37.336262,37.336330,37.336373,37.336450,37.336484,37.336586,37.336612,37.336671,37.336740,37.336842,37.336885,37.336970,37.337132,37.337243,37.337354};
double longitude_array [18]={-121.885627,-121.885456,-121.88537,-121.885198,-121.88508,-121.884962,-121.884823,-121.884694,-121.884554,-121.884426,-121.884297,-121.8842,-121.883986,-121.883814,-121.883718,-121.8};
//double longitude_array [256];
//double latitude_array [256];
bool AcknowlegmentSent=false;
int TotalCheckpointCount = 0 ;
const uint32_t COM_BRIDGE_CHECK_POINT_m0__MIA_MS = 3000;
const uint32_t COM_BRIDGE_CHECK_POINT_m1__MIA_MS = 3000;
const COM_BRIDGE_CHECK_POINT_m0_t COM_BRIDGE_CHECK_POINT_m0__MIA_MSG = { 0 };
const COM_BRIDGE_CHECK_POINT_m1_t COM_BRIDGE_CHECK_POINT_m1__MIA_MSG = { 0 };
COM_BRIDGE_CHECK_POINT_t checkpoint_can_msg = { 0 };
struct checkPoint
{
	double longitude;
	double lattitude;
	bool isLattitudeAdded;
	bool isLongitudeAdded;
	int TotalCount;

};

double toRadian( double degree )
{
	const double halfC = PI / 180;
	return (degree * halfC);
}

double toDegree( double radian)
{
	const double halfR = 180/PI;
	return (radian * halfR);
}

double toDecimaldegrees ( string lat1, string lon1)
{
	double  latitude_dcm,
			longitude_dcm;
	string deg, min, sec;
	string c1, c2;
	int deg1, min1, sec1;

//Converting Latitude
	if (lat1.length() > 8)
	{
		c1  = lat1.substr(0,1);
		deg = lat1.substr(1,2);
		min = lat1.substr(3,4);
		sec = lat1.substr(6,8);
	}
	else
	{
		deg = lat1.substr(0,2);
		min = lat1.substr(2,3);
		sec = lat1.substr(5,7);
	}

	   istringstream(deg) >> deg1;
	   istringstream(min) >> min1;
	   istringstream(sec) >> sec1;
	   latitude_dcm = deg1 + (min1 + sec1 / SEC_PER_MINUTE) / MIN_PER_DEGREE;
	   if (c1=="-")
	   {
		   latitude_dcm = -1 * latitude_dcm;
	   }
//Converting Longitude
		if (lon1.length() > 9)
		{
			c2  = lon1.substr(0,1);
			deg = lon1.substr(1,3);
			min = lon1.substr(4,2);
			sec = lon1.substr(7,8);
		}
		else
		{
			deg = lon1.substr(0,3);
			min = lon1.substr(3,5);
			sec = lon1.substr(6,8);
		}

		   istringstream(deg) >> deg1;
		   istringstream(min) >> min1;
		   istringstream(sec) >> sec1;
		   longitude_dcm = deg1 + (min1 + sec1 / SEC_PER_MINUTE) / MIN_PER_DEGREE;
		   if (c1=="-")
		   {
			   longitude_dcm = -1 * longitude_dcm;
		   }

	   return latitude_dcm, longitude_dcm;
}


double distanceCalculation(double lat1,double lat2,double long1,double long2)
{
	double a,C;
	double Lat1 = toRadian(lat1);
	double Lat2 = toRadian(lat2);
	double Long1 = toRadian(long1);
	double Long2 = toRadian(long2);
	double dLat = Lat1 - Lat2 ;
	double dLong = Long1 - Long2;
	a = pow((sin(dLat)/2),2) + (cos (Lat1) * cos (Lat2) * pow((sin(dLong)/2),2));
	C = 2 * atan2(sqrt(a),sqrt(1-a));
	double distance = EARTH_RADIUS *C;
	return(distance);
}

double bearing(double Lat1,double Lat2,double Long1,double Long2)
{
	double dLong = Long2 -Long1;
	double arg1 = sin (Long2) * cos (Lat2);
	double arg2 = ((cos (Lat1) *  sin(Lat2)) - ( sin (Lat1) * cos(Lat2) * cos(dLong)));
	double turn_angle1 = atan2(arg1 , arg2);
	//double turn_angle = compass_reading_function_call - turn_angle1;
	return (turn_angle1);

}

/// This is the stack size used for each of the period tasks (1Hz, 10Hz, 100Hz, and 1000Hz)
const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
Uart2& u2 = Uart2::getInstance();
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
	CAN_init(can1,100,5,5,NULL,NULL);
	CAN_bypass_filter_accept_all_msgs();
	CAN_reset_bus(can1);
	u2.init(115200,1000,1000);
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
	GPS_HEARTBEAT_t heartbeat = { 0 };
	heartbeat.GPS_HEARTBEAT_UNSIGNED = GPS_HEARTBEAT_HDR.mid;
	can_msg_t can_msg = { 0 };
	dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_HEARTBEAT(can_msg.data.bytes, &heartbeat);
	can_msg.msg_id = msg_hdr.mid;
	can_msg.frame_fields.data_len = msg_hdr.dlc;
	if (CAN_tx(can1, &can_msg, 0))
	{
		printf("heartbeat sent\n");
	}

	if(CAN_is_bus_off(can1))
	{
		CAN_reset_bus(can1);
	}

	//LE.toggle(1);
}

void period_10Hz(uint32_t count)
{

	com_data.GPS_LATTITUDE_SIGNED = 37.336057;
	com_data.GPS_LONGITUDE_SIGNED = -121.885627;
	can_msg_t can_msg = { 0 };
	dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_CURRENT_LOCATION(can_msg.data.bytes, &com_data);
	can_msg.msg_id = msg_hdr.mid;
	can_msg.frame_fields.data_len = msg_hdr.dlc;
	CAN_tx(can1, &can_msg, 0);
	dbc_msg_hdr_t can_msg_hdr;
	can_msg_t msg;
	while (CAN_rx(can1, &msg, 0))
	{

		can_msg_hdr.dlc = msg.frame_fields.data_len;
		can_msg_hdr.mid = msg.msg_id;
		dbc_decode_COM_BRIDGE_CHECK_POINT(&checkpoint_can_msg ,msg.data.bytes, &can_msg_hdr);
		if(can_msg_hdr.mid == COM_BRIDGE_CHECK_POINT_HDR.mid && TotalCountReceived == 0)
		{
			TotalCheckpointCount = 2 *checkpoint_can_msg.m0.COM_BRIDGE_CURRENT_COUNT_UNSIGNED;
			isCheckpointReceived = true;

		}
	}

	if(TotalCountReceived == TotalCheckpointCount && isCheckpointReceived)
	{
		ackToComBridge.GPS_ACKNOWLEDGEMENT_UNSIGNED = GPS_ACKNOWLEDGEMENT_HDR.mid;

		can_msg_t can_msg = { 0 };
		dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_ACKNOWLEDGEMENT(can_msg.data.bytes, &ackToComBridge);
		can_msg.msg_id = msg_hdr.mid;
		can_msg.frame_fields.data_len = msg_hdr.dlc;
		CAN_tx(can1, &can_msg, 0);
		isCheckpointReceived = false;
		TotalCountReceived=0;
		AcknowlegmentSent=true;

	}
	if(AcknowlegmentSent)
	{
			if(sentData==18)
			{
				sentData=0;
			}
			else
			{
				master_data.GEO_DATA_TURNANGLE_SIGNED = bearing(latitude_array[sentData] ,latitude_array[sentData+1],longitude_array[sentData],longitude_array[sentData+1]);
				master_data.GEO_DATA_DISTANCE_TO_FINAL_DESTINATION_SIGNED = distanceCalculation(latitude_array[sentData] ,latitude_array[17],longitude_array[sentData],longitude_array[17]);
				master_data.GEO_DATA_DISTANCE_TO_NEXT_CHECKPOINT_SIGNED = distanceCalculation(latitude_array[sentData] ,latitude_array[sentData+1],longitude_array[sentData],longitude_array[sentData+1]);


				dbc_msg_hdr_t msg_hdr = dbc_encode_GPS_MASTER_DATA(can_msg.data.bytes, &master_data);
				can_msg.msg_id = msg_hdr.mid;
				can_msg.frame_fields.data_len = msg_hdr.dlc;
				if(CAN_tx(can1, &can_msg, 0))
				{
					finalDestinationDistance = master_data.GEO_DATA_DISTANCE_TO_FINAL_DESTINATION_SIGNED;
					turn_angle = master_data.GEO_DATA_TURNANGLE_SIGNED;
					distanceToNextCheckpoint= master_data.GEO_DATA_DISTANCE_TO_NEXT_CHECKPOINT_SIGNED;
					printf("Distance to final destination is %f \n Distance to next checkpoint is %f\n destination turn angle is %f\n",finalDestinationDistance,distanceToNextCheckpoint,turn_angle);
					sentData++;
				}

			}
	}
}

void period_100Hz(uint32_t count)
{
	LE.toggle(3);
}

// 1Khz (1ms) is only run if Periodic Dispatcher was configured to run it at main():
// scheduler_add_task(new periodicSchedulerTask(run_1Khz = true));
void period_1000Hz(uint32_t count)
{
	LE.toggle(4);
}
