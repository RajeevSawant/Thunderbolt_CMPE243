/// DBC file: ../../243.dbc    Self node: 'COM_BRIDGE'  (ALL = 0)
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

static const dbc_msg_hdr_t GPS_CURRENT_LOCATION_HDR =             {  162, 8 };
static const dbc_msg_hdr_t COM_BRIDGE_CHECK_POINT_HDR =           {  148, 8 };
static const dbc_msg_hdr_t COM_BRIDGE_CLICKED_START_HDR =         {   84, 2 };
// static const dbc_msg_hdr_t MASTER_DRIVING_CAR_HDR =               {  209, 8 };
// static const dbc_msg_hdr_t SENSOR_SONARS_HDR =                    {  144, 5 };
// static const dbc_msg_hdr_t MOTOR_HEARTBEAT_HDR =                  {  339, 2 };
// static const dbc_msg_hdr_t MOTOR_CAR_SPEED_HDR =                  {  147, 8 };
static const dbc_msg_hdr_t COM_BRIDGE_STOPALL_HDR =               {    4, 1 };
// static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR =                 {  336, 2 };
// static const dbc_msg_hdr_t GPS_HEARTBEAT_HDR =                    {  338, 2 };
static const dbc_msg_hdr_t COM_BRIDGE_HEARTBEAT_HDR =             {  340, 2 };
// static const dbc_msg_hdr_t MASTER_ACKNOWLEDGEMENT_HDR =           {  281, 1 };
static const dbc_msg_hdr_t GPS_ACKNOWLEDGEMENT_HDR =              {  290, 1 };
// static const dbc_msg_hdr_t GPS_MASTER_DATA_HDR =                  {  146, 6 };




/// Message: GPS_CURRENT_LOCATION from 'GPS', DLC: 8 byte(s), MID: 162
typedef struct {
    float GPS_LATTITUDE_SIGNED;               ///< B29:0  Min: -90 Max: 90   Destination: COM_BRIDGE
    float GPS_LONGITUDE_SIGNED;               ///< B59:30  Min: -180 Max: 180   Destination: COM_BRIDGE

    dbc_mia_info_t mia_info;
} GPS_CURRENT_LOCATION_t;

/// @{ MUX'd message: COM_BRIDGE_CHECK_POINT

/// Struct for MUX: m0 (used for transmitting)
typedef struct {
    uint8_t COM_BRIDGE_TOTAL_COUNT_UNSIGNED;  ///< B9:2   Destination: GPS
    uint8_t COM_BRIDGE_CURRENT_COUNT_UNSIGNED; ///< B17:10   Destination: GPS
    float COM_BRIDGE_LATTITUDE_SIGNED;        ///< B57:18  Min: -90 Max: 90   Destination: GPS

    // No dbc_mia_info_t for a message that we will send
} COM_BRIDGE_CHECK_POINT_m0_t;

/// Struct for MUX: m1 (used for transmitting)
typedef struct {
    uint8_t COM_BRIDGE_TOTAL_COUNT_UNSIGNED;  ///< B9:2   Destination: GPS
    uint8_t COM_BRIDGE_CURRENT_COUNT_UNSIGNED; ///< B17:10   Destination: GPS
    float COM_BRIDGE_LONGITUDE_SIGNED;        ///< B57:18  Min: -180 Max: 180   Destination: GPS

    // No dbc_mia_info_t for a message that we will send
} COM_BRIDGE_CHECK_POINT_m1_t;

/// Struct with all the child MUX'd signals (Used for receiving)
typedef struct {
    COM_BRIDGE_CHECK_POINT_m0_t m0; ///< MUX'd structure
    COM_BRIDGE_CHECK_POINT_m1_t m1; ///< MUX'd structure
} COM_BRIDGE_CHECK_POINT_t;
/// @} MUX'd message


/// Message: COM_BRIDGE_CLICKED_START from 'COM_BRIDGE', DLC: 2 byte(s), MID: 84
typedef struct {
    uint8_t COM_BRIDGE_CLICKED_START_UNSIGNED; ///< B7:0   Destination: MASTER,GPS

    // No dbc_mia_info_t for a message that we will send
} COM_BRIDGE_CLICKED_START_t;


/// Message: COM_BRIDGE_STOPALL from 'COM_BRIDGE', DLC: 1 byte(s), MID: 4
typedef struct {
    uint8_t COM_BRIDGE_STOPALL_UNSIGNED;      ///< B7:0   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} COM_BRIDGE_STOPALL_t;


/// Message: COM_BRIDGE_HEARTBEAT from 'COM_BRIDGE', DLC: 2 byte(s), MID: 340
typedef struct {
    uint16_t COM_BRIDGE_HEARTBEAT_UNSIGNED;   ///< B10:0   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} COM_BRIDGE_HEARTBEAT_t;


/// Message: GPS_ACKNOWLEDGEMENT from 'GPS', DLC: 1 byte(s), MID: 290
typedef struct {
    uint8_t GPS_ACKNOWLEDGEMENT_UNSIGNED;     ///< B7:0   Destination: COM_BRIDGE

    dbc_mia_info_t mia_info;
} GPS_ACKNOWLEDGEMENT_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             GPS_CURRENT_LOCATION__MIA_MS;
extern const GPS_CURRENT_LOCATION_t               GPS_CURRENT_LOCATION__MIA_MSG;
extern const uint32_t                             GPS_ACKNOWLEDGEMENT__MIA_MS;
extern const GPS_ACKNOWLEDGEMENT_t                GPS_ACKNOWLEDGEMENT__MIA_MSG;
/// @}


/// Not generating code for dbc_encode_GPS_CURRENT_LOCATION() since the sender is GPS and we are COM_BRIDGE

/// Encode COM_BRIDGE's 'COM_BRIDGE_CHECK_POINT' MUX(m0) message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_COM_BRIDGE_CHECK_POINT_m0(uint8_t bytes[8], COM_BRIDGE_CHECK_POINT_m0_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    // Set the MUX index value
    raw = ((uint32_t)(((0)))) & 0x03;
    bytes[0] |= (((uint8_t)(raw) & 0x03)); ///< 2 bit(s) starting from B0

    // Set non MUX'd signals that need to go out with this MUX'd message
    raw = ((uint32_t)(((from->COM_BRIDGE_TOTAL_COUNT_UNSIGNED)))) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B2
    bytes[1] |= (((uint8_t)(raw >> 6) & 0x03)); ///< 2 bit(s) starting from B8
    raw = ((uint32_t)(((from->COM_BRIDGE_CURRENT_COUNT_UNSIGNED)))) & 0xff;
    bytes[1] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B10
    bytes[2] |= (((uint8_t)(raw >> 6) & 0x03)); ///< 2 bit(s) starting from B16

    // Set the rest of the signals within this MUX (m0)
    if(from->COM_BRIDGE_LATTITUDE_SIGNED < -90) { from->COM_BRIDGE_LATTITUDE_SIGNED = -90; } // Min value: -90
    if(from->COM_BRIDGE_LATTITUDE_SIGNED > 90) { from->COM_BRIDGE_LATTITUDE_SIGNED = 90; } // Max value: 90
    raw = ((uint32_t)(((from->COM_BRIDGE_LATTITUDE_SIGNED - (-90)) / 1e-06) + 0.5)) & 0xffffffffff;
    bytes[2] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B18
    bytes[3] |= (((uint8_t)(raw >> 6) & 0xff)); ///< 8 bit(s) starting from B24
    bytes[4] |= (((uint8_t)(raw >> 14) & 0xff)); ///< 8 bit(s) starting from B32
    bytes[5] |= (((uint8_t)(raw >> 22) & 0xff)); ///< 8 bit(s) starting from B40
    bytes[6] |= (((uint8_t)(raw >> 30) & 0xff)); ///< 8 bit(s) starting from B48
    bytes[7] |= (((uint8_t)(raw >> 38) & 0x03)); ///< 2 bit(s) starting from B56

    return COM_BRIDGE_CHECK_POINT_HDR;
}

/// Encode and send for dbc_encode_COM_BRIDGE_CHECK_POINT_m0() message
static inline bool dbc_encode_and_send_COM_BRIDGE_CHECK_POINT_m0(COM_BRIDGE_CHECK_POINT_m0_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_COM_BRIDGE_CHECK_POINT_m0(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}


/// Encode COM_BRIDGE's 'COM_BRIDGE_CHECK_POINT' MUX(m1) message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_COM_BRIDGE_CHECK_POINT_m1(uint8_t bytes[8], COM_BRIDGE_CHECK_POINT_m1_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    // Set the MUX index value
    raw = ((uint32_t)(((1)))) & 0x03;
    bytes[0] |= (((uint8_t)(raw) & 0x03)); ///< 2 bit(s) starting from B0

    // Set non MUX'd signals that need to go out with this MUX'd message
    raw = ((uint32_t)(((from->COM_BRIDGE_TOTAL_COUNT_UNSIGNED)))) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B2
    bytes[1] |= (((uint8_t)(raw >> 6) & 0x03)); ///< 2 bit(s) starting from B8
    raw = ((uint32_t)(((from->COM_BRIDGE_CURRENT_COUNT_UNSIGNED)))) & 0xff;
    bytes[1] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B10
    bytes[2] |= (((uint8_t)(raw >> 6) & 0x03)); ///< 2 bit(s) starting from B16

    // Set the rest of the signals within this MUX (m1)
    if(from->COM_BRIDGE_LONGITUDE_SIGNED < -180) { from->COM_BRIDGE_LONGITUDE_SIGNED = -180; } // Min value: -180
    if(from->COM_BRIDGE_LONGITUDE_SIGNED > 180) { from->COM_BRIDGE_LONGITUDE_SIGNED = 180; } // Max value: 180
    raw = ((uint32_t)(((from->COM_BRIDGE_LONGITUDE_SIGNED - (-180)) / 1e-06) + 0.5)) & 0xffffffffff;
    bytes[2] |= (((uint8_t)(raw) & 0x3f) << 2); ///< 6 bit(s) starting from B18
    bytes[3] |= (((uint8_t)(raw >> 6) & 0xff)); ///< 8 bit(s) starting from B24
    bytes[4] |= (((uint8_t)(raw >> 14) & 0xff)); ///< 8 bit(s) starting from B32
    bytes[5] |= (((uint8_t)(raw >> 22) & 0xff)); ///< 8 bit(s) starting from B40
    bytes[6] |= (((uint8_t)(raw >> 30) & 0xff)); ///< 8 bit(s) starting from B48
    bytes[7] |= (((uint8_t)(raw >> 38) & 0x03)); ///< 2 bit(s) starting from B56

    return COM_BRIDGE_CHECK_POINT_HDR;
}

/// Encode and send for dbc_encode_COM_BRIDGE_CHECK_POINT_m1() message
static inline bool dbc_encode_and_send_COM_BRIDGE_CHECK_POINT_m1(COM_BRIDGE_CHECK_POINT_m1_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_COM_BRIDGE_CHECK_POINT_m1(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Encode COM_BRIDGE's 'COM_BRIDGE_CLICKED_START' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_COM_BRIDGE_CLICKED_START(uint8_t bytes[8], COM_BRIDGE_CLICKED_START_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->COM_BRIDGE_CLICKED_START_UNSIGNED)))) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0

    return COM_BRIDGE_CLICKED_START_HDR;
}

/// Encode and send for dbc_encode_COM_BRIDGE_CLICKED_START() message
static inline bool dbc_encode_and_send_COM_BRIDGE_CLICKED_START(COM_BRIDGE_CLICKED_START_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_COM_BRIDGE_CLICKED_START(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_MASTER_DRIVING_CAR() since the sender is MASTER and we are COM_BRIDGE

/// Not generating code for dbc_encode_SENSOR_SONARS() since the sender is SENSOR and we are COM_BRIDGE

/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are COM_BRIDGE

/// Not generating code for dbc_encode_MOTOR_CAR_SPEED() since the sender is MOTOR and we are COM_BRIDGE

/// Encode COM_BRIDGE's 'COM_BRIDGE_STOPALL' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_COM_BRIDGE_STOPALL(uint8_t bytes[8], COM_BRIDGE_STOPALL_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->COM_BRIDGE_STOPALL_UNSIGNED)))) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0

    return COM_BRIDGE_STOPALL_HDR;
}

/// Encode and send for dbc_encode_COM_BRIDGE_STOPALL() message
static inline bool dbc_encode_and_send_COM_BRIDGE_STOPALL(COM_BRIDGE_STOPALL_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_COM_BRIDGE_STOPALL(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_SENSOR_HEARTBEAT() since the sender is SENSOR and we are COM_BRIDGE

/// Not generating code for dbc_encode_GPS_HEARTBEAT() since the sender is GPS and we are COM_BRIDGE

/// Encode COM_BRIDGE's 'COM_BRIDGE_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_COM_BRIDGE_HEARTBEAT(uint8_t bytes[8], COM_BRIDGE_HEARTBEAT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->COM_BRIDGE_HEARTBEAT_UNSIGNED)))) & 0x7ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x07)); ///< 3 bit(s) starting from B8

    return COM_BRIDGE_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_COM_BRIDGE_HEARTBEAT() message
static inline bool dbc_encode_and_send_COM_BRIDGE_HEARTBEAT(COM_BRIDGE_HEARTBEAT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_COM_BRIDGE_HEARTBEAT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_MASTER_ACKNOWLEDGEMENT() since the sender is MASTER and we are COM_BRIDGE

/// Not generating code for dbc_encode_GPS_ACKNOWLEDGEMENT() since the sender is GPS and we are COM_BRIDGE

/// Not generating code for dbc_encode_GPS_MASTER_DATA() since the sender is GPS and we are COM_BRIDGE

/// Decode GPS's 'GPS_CURRENT_LOCATION' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GPS_CURRENT_LOCATION(GPS_CURRENT_LOCATION_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != GPS_CURRENT_LOCATION_HDR.dlc || hdr->mid != GPS_CURRENT_LOCATION_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]))) << 8; ///< 8 bit(s) from B8
    raw |= ((uint32_t)((bytes[2]))) << 16; ///< 8 bit(s) from B16
    raw |= ((uint32_t)((bytes[3]) & 0x3f)) << 24; ///< 6 bit(s) from B24
    to->GPS_LATTITUDE_SIGNED = ((raw * 1e-06) + (-90));
    raw  = ((uint32_t)((bytes[3] >> 6) & 0x03)); ///< 2 bit(s) from B30
    raw |= ((uint32_t)((bytes[4]))) << 2; ///< 8 bit(s) from B32
    raw |= ((uint32_t)((bytes[5]))) << 10; ///< 8 bit(s) from B40
    raw |= ((uint32_t)((bytes[6]))) << 18; ///< 8 bit(s) from B48
    raw |= ((uint32_t)((bytes[7]) & 0x0f)) << 26; ///< 4 bit(s) from B56
    to->GPS_LONGITUDE_SIGNED = ((raw * 1e-06) + (-180));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_COM_BRIDGE_CHECK_POINT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_CLICKED_START() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MASTER_DRIVING_CAR() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_SONARS() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_HEARTBEAT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_CAR_SPEED() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_STOPALL() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_HEARTBEAT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_HEARTBEAT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_HEARTBEAT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MASTER_ACKNOWLEDGEMENT() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Decode GPS's 'GPS_ACKNOWLEDGEMENT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_GPS_ACKNOWLEDGEMENT(GPS_ACKNOWLEDGEMENT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != GPS_ACKNOWLEDGEMENT_HDR.dlc || hdr->mid != GPS_ACKNOWLEDGEMENT_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    to->GPS_ACKNOWLEDGEMENT_UNSIGNED = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_GPS_MASTER_DATA() since 'COM_BRIDGE' is not the recipient of any of the signals

/// Handle the MIA for GPS's GPS_CURRENT_LOCATION message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GPS_CURRENT_LOCATION(GPS_CURRENT_LOCATION_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GPS_CURRENT_LOCATION__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = GPS_CURRENT_LOCATION__MIA_MSG;
        msg->mia_info.mia_counter_ms = GPS_CURRENT_LOCATION__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for GPS's GPS_ACKNOWLEDGEMENT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_GPS_ACKNOWLEDGEMENT(GPS_ACKNOWLEDGEMENT_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= GPS_ACKNOWLEDGEMENT__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = GPS_ACKNOWLEDGEMENT__MIA_MSG;
        msg->mia_info.mia_counter_ms = GPS_ACKNOWLEDGEMENT__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

#endif
