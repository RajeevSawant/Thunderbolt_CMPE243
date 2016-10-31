/// DBC file: ../_can_dbc/243.dbc    Self node: 'SENSOR'  (ALL = 0)
/// This file can be included by a source file, for example: #include "generated.h"
#ifndef __GENEARTED_DBC_PARSER
#define __GENERATED_DBC_PARSER
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/// Extern function needed for dbc_encode_and_send()
extern bool dbc_app_send_can_msg(uint32_t mid, uint8_t dlc, uint8_t bytes[8]);

/// Missing in Action structure
typedef struct {
    uint32_t is_mia : 1;          ///< Missing in action flag
    uint32_t mia_counter_ms : 31; ///< Missing in action counter
} dbc_mia_info_t;

/// CAN message header structure
typedef struct { 
    uint32_t mid; ///< Message ID of the message
    uint8_t  dlc; ///< Data length of the message
} dbc_msg_hdr_t; 

// static const dbc_msg_hdr_t GPS_CURRENT_LOCATION_HDR =             {  162, 8 };
// static const dbc_msg_hdr_t COM_BRIDGE_CHECK_POINT_HDR =           {  148, 8 };
// static const dbc_msg_hdr_t COM_BRIDGE_CLICKED_START_HDR =         {   84, 2 };
// static const dbc_msg_hdr_t MASTER_DRIVING_CAR_HDR =               {  209, 8 };
static const dbc_msg_hdr_t SENSOR_SONARS_HDR =                    {  144, 5 };
// static const dbc_msg_hdr_t MOTOR_HEARTBEAT_HDR =                  {  339, 2 };
// static const dbc_msg_hdr_t MOTOR_CAR_SPEED_HDR =                  {  147, 8 };
// static const dbc_msg_hdr_t COM_BRIDGE_STOPALL_HDR =               {    4, 1 };
static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR =                 {  336, 2 };
// static const dbc_msg_hdr_t GPS_HEARTBEAT_HDR =                    {  338, 2 };
// static const dbc_msg_hdr_t COM_BRIDGE_HEARTBEAT_HDR =             {  340, 2 };
// static const dbc_msg_hdr_t MASTER_ACKNOWLEDGEMENT_HDR =           {  281, 1 };
// static const dbc_msg_hdr_t GPS_ACKNOWLEDGEMENT_HDR =              {  290, 1 };
// static const dbc_msg_hdr_t GPS_MASTER_DATA_HDR =                  {  146, 6 };




/// Message: SENSOR_SONARS from 'SENSOR', DLC: 5 byte(s), MID: 144
typedef struct {
    uint16_t SENSOR_SONARS_LEFT_UNSIGNED;     ///< B9:0   Destination: MASTER
    uint16_t SENSOR_SONARS_RIGHT_UNSIGNED;    ///< B19:10   Destination: MASTER
    uint16_t SENSOR_SONARS_FRONT_UNSIGNED;    ///< B29:20   Destination: MASTER
    uint16_t SENSOR_SONARS_BACK_UNSIGNED;     ///< B39:30   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} SENSOR_SONARS_t;


/// Message: SENSOR_HEARTBEAT from 'SENSOR', DLC: 2 byte(s), MID: 336
typedef struct {
    uint16_t SENSOR_HEARTBEAT_UNSIGNED;       ///< B10:0   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} SENSOR_HEARTBEAT_t;


/// @{ These 'externs' need to be defined in a source file of your project
/// @}


/// Not generating code for dbc_encode_GPS_CURRENT_LOCATION() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_COM_BRIDGE_CHECK_POINT() since the sender is COM_BRIDGE and we are SENSOR

/// Not generating code for dbc_encode_COM_BRIDGE_CLICKED_START() since the sender is COM_BRIDGE and we are SENSOR

/// Not generating code for dbc_encode_MASTER_DRIVING_CAR() since the sender is MASTER and we are SENSOR

/// Encode SENSOR's 'SENSOR_SONARS' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_SENSOR_SONARS(uint8_t bytes[8], SENSOR_SONARS_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->SENSOR_SONARS_LEFT_UNSIGNED)))) & 0x3ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x03)); ///< 2 bit(s) starting from B8

    raw = ((uint32_t)(((from->SENSOR_SONARS_RIGHT_UNSIGNED)))) & 0x3ff;
    bytes[1] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B10
    bytes[2] |= (((uint8_t)(raw >> 6) & 0x0f)); ///< 4 bit(s) starting from B16

    raw = ((uint32_t)(((from->SENSOR_SONARS_FRONT_UNSIGNED)))) & 0x3ff;
    bytes[2] |= (((uint8_t)(raw) & 0x0f) << 4); ///< 4 bit(s) starting from B20
    bytes[3] |= (((uint8_t)(raw >> 4) & 0x3f)); ///< 6 bit(s) starting from B24

    raw = ((uint32_t)(((from->SENSOR_SONARS_BACK_UNSIGNED)))) & 0x3ff;
    bytes[3] |= (((uint8_t)(raw) & 0x03) << 6); ///< 2 bit(s) starting from B30
    bytes[4] |= (((uint8_t)(raw >> 2) & 0xff)); ///< 8 bit(s) starting from B32

    return SENSOR_SONARS_HDR;
}

/// Encode and send for dbc_encode_SENSOR_SONARS() message
static inline bool dbc_encode_and_send_SENSOR_SONARS(SENSOR_SONARS_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_SENSOR_SONARS(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are SENSOR

/// Not generating code for dbc_encode_MOTOR_CAR_SPEED() since the sender is MOTOR and we are SENSOR

/// Not generating code for dbc_encode_COM_BRIDGE_STOPALL() since the sender is COM_BRIDGE and we are SENSOR

/// Encode SENSOR's 'SENSOR_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_SENSOR_HEARTBEAT(uint8_t bytes[8], SENSOR_HEARTBEAT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->SENSOR_HEARTBEAT_UNSIGNED)))) & 0x7ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x07)); ///< 3 bit(s) starting from B8

    return SENSOR_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_SENSOR_HEARTBEAT() message
static inline bool dbc_encode_and_send_SENSOR_HEARTBEAT(SENSOR_HEARTBEAT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_SENSOR_HEARTBEAT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_GPS_HEARTBEAT() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_COM_BRIDGE_HEARTBEAT() since the sender is COM_BRIDGE and we are SENSOR

/// Not generating code for dbc_encode_MASTER_ACKNOWLEDGEMENT() since the sender is MASTER and we are SENSOR

/// Not generating code for dbc_encode_GPS_ACKNOWLEDGEMENT() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_encode_GPS_MASTER_DATA() since the sender is GPS and we are SENSOR

/// Not generating code for dbc_decode_GPS_CURRENT_LOCATION() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_CHECK_POINT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_CLICKED_START() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MASTER_DRIVING_CAR() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_SONARS() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_CAR_SPEED() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_STOPALL() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_HEARTBEAT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MASTER_ACKNOWLEDGEMENT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_ACKNOWLEDGEMENT() since 'SENSOR' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_MASTER_DATA() since 'SENSOR' is not the recipient of any of the signals

#endif
