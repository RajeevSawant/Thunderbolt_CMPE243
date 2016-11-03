/// DBC file: ../../243.dbc    Self node: 'GPS'  (ALL = 0)
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
// static const dbc_msg_hdr_t COM_BRIDGE_STOPALL_HDR =               {    4, 2 };
// static const dbc_msg_hdr_t SENSOR_HEARTBEAT_HDR =                 {  336, 2 };
static const dbc_msg_hdr_t GPS_HEARTBEAT_HDR =                    {  338, 2 };
// static const dbc_msg_hdr_t COM_BRIDGE_HEARTBEAT_HDR =             {  340, 2 };
static const dbc_msg_hdr_t MASTER_ACKNOWLEDGEMENT_HDR =           {  281, 2 };
static const dbc_msg_hdr_t GPS_ACKNOWLEDGEMENT_HDR =              {  290, 2 };
static const dbc_msg_hdr_t GPS_MASTER_DATA_HDR =                  {  146, 6 };




/// Message: GPS_CURRENT_LOCATION from 'GPS', DLC: 8 byte(s), MID: 162
typedef struct {
    float GPS_LATTITUDE_SIGNED;               ///< B29:0  Min: -90 Max: 90   Destination: COM_BRIDGE
    float GPS_LONGITUDE_SIGNED;               ///< B59:30  Min: -180 Max: 180   Destination: COM_BRIDGE

    // No dbc_mia_info_t for a message that we will send
} GPS_CURRENT_LOCATION_t;

/// @{ MUX'd message: COM_BRIDGE_CHECK_POINT

/// Struct for MUX: m0 (used for transmitting)
typedef struct {
    uint8_t COM_BRIDGE_TOTAL_COUNT_UNSIGNED;  ///< B9:2   Destination: GPS
    uint8_t COM_BRIDGE_CURRENT_COUNT_UNSIGNED; ///< B17:10   Destination: GPS
    float COM_BRIDGE_LATTITUDE_SIGNED;        ///< B57:18  Min: -90 Max: 90   Destination: GPS

    dbc_mia_info_t mia_info;
} COM_BRIDGE_CHECK_POINT_m0_t;

/// Struct for MUX: m1 (used for transmitting)
typedef struct {
    uint8_t COM_BRIDGE_TOTAL_COUNT_UNSIGNED;  ///< B9:2   Destination: GPS
    uint8_t COM_BRIDGE_CURRENT_COUNT_UNSIGNED; ///< B17:10   Destination: GPS
    float COM_BRIDGE_LONGITUDE_SIGNED;        ///< B57:18  Min: -180 Max: 180   Destination: GPS

    dbc_mia_info_t mia_info;
} COM_BRIDGE_CHECK_POINT_m1_t;

/// Struct with all the child MUX'd signals (Used for receiving)
typedef struct {
    COM_BRIDGE_CHECK_POINT_m0_t m0; ///< MUX'd structure
    COM_BRIDGE_CHECK_POINT_m1_t m1; ///< MUX'd structure
} COM_BRIDGE_CHECK_POINT_t;
/// @} MUX'd message


/// Message: COM_BRIDGE_CLICKED_START from 'COM_BRIDGE', DLC: 2 byte(s), MID: 84
typedef struct {
    uint16_t COM_BRIDGE_CLICKED_START_UNSIGNED; ///< B10:0   Destination: MASTER,GPS

    dbc_mia_info_t mia_info;
} COM_BRIDGE_CLICKED_START_t;


/// Message: GPS_HEARTBEAT from 'GPS', DLC: 2 byte(s), MID: 338
typedef struct {
    uint16_t GPS_HEARTBEAT_UNSIGNED;          ///< B10:0   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} GPS_HEARTBEAT_t;


/// Message: MASTER_ACKNOWLEDGEMENT from 'MASTER', DLC: 2 byte(s), MID: 281
typedef struct {
    uint16_t ACKNOWLEDGEMENT_DATA_REACHED_UNSIGNED; ///< B10:0   Destination: GPS

    dbc_mia_info_t mia_info;
} MASTER_ACKNOWLEDGEMENT_t;


/// Message: GPS_ACKNOWLEDGEMENT from 'GPS', DLC: 2 byte(s), MID: 290
typedef struct {
    uint16_t GPS_ACKNOWLEDGEMENT_UNSIGNED;    ///< B10:0   Destination: COM_BRIDGE

    // No dbc_mia_info_t for a message that we will send
} GPS_ACKNOWLEDGEMENT_t;


/// Message: GPS_MASTER_DATA from 'GPS', DLC: 6 byte(s), MID: 146
typedef struct {
    float GEO_DATA_TURNANGLE_SIGNED;          ///< B7:0   Destination: MASTER
    uint8_t GEO_DATA_ISFINAL_SIGNED : 1;      ///< B15:15   Destination: MASTER
    float GEO_DATA_DISTANCE_TO_FINAL_DESTINATION_SIGNED; ///< B31:16   Destination: MASTER
    float GEO_DATA_DISTANCE_TO_NEXT_CHECKPOINT_SIGNED; ///< B47:32   Destination: MASTER

    // No dbc_mia_info_t for a message that we will send
} GPS_MASTER_DATA_t;


/// @{ These 'externs' need to be defined in a source file of your project
extern const uint32_t                             COM_BRIDGE_CHECK_POINT_m0__MIA_MS;
extern const COM_BRIDGE_CHECK_POINT_m0_t          COM_BRIDGE_CHECK_POINT_m0__MIA_MSG;
extern const uint32_t                             COM_BRIDGE_CHECK_POINT_m1__MIA_MS;
extern const COM_BRIDGE_CHECK_POINT_m1_t          COM_BRIDGE_CHECK_POINT_m1__MIA_MSG;
extern const uint32_t                             COM_BRIDGE_CLICKED_START__MIA_MS;
extern const COM_BRIDGE_CLICKED_START_t           COM_BRIDGE_CLICKED_START__MIA_MSG;
extern const uint32_t                             MASTER_ACKNOWLEDGEMENT__MIA_MS;
extern const MASTER_ACKNOWLEDGEMENT_t             MASTER_ACKNOWLEDGEMENT__MIA_MSG;
/// @}


/// Encode GPS's 'GPS_CURRENT_LOCATION' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_GPS_CURRENT_LOCATION(uint8_t bytes[8], GPS_CURRENT_LOCATION_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    if(from->GPS_LATTITUDE_SIGNED < -90) { from->GPS_LATTITUDE_SIGNED = -90; } // Min value: -90
    if(from->GPS_LATTITUDE_SIGNED > 90) { from->GPS_LATTITUDE_SIGNED = 90; } // Max value: 90
    raw = ((uint32_t)(((from->GPS_LATTITUDE_SIGNED - (-90)) / 1e-06) + 0.5)) & 0x3fffffff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0xff)); ///< 8 bit(s) starting from B8
    bytes[2] |= (((uint8_t)(raw >> 16) & 0xff)); ///< 8 bit(s) starting from B16
    bytes[3] |= (((uint8_t)(raw >> 24) & 0x3f)); ///< 6 bit(s) starting from B24

    if(from->GPS_LONGITUDE_SIGNED < -180) { from->GPS_LONGITUDE_SIGNED = -180; } // Min value: -180
    if(from->GPS_LONGITUDE_SIGNED > 180) { from->GPS_LONGITUDE_SIGNED = 180; } // Max value: 180
    raw = ((uint32_t)(((from->GPS_LONGITUDE_SIGNED - (-180)) / 1e-06) + 0.5)) & 0x3fffffff;
    bytes[3] |= (((uint8_t)(raw) & 0x03) << 6); ///< 2 bit(s) starting from B30
    bytes[4] |= (((uint8_t)(raw >> 2) & 0xff)); ///< 8 bit(s) starting from B32
    bytes[5] |= (((uint8_t)(raw >> 10) & 0xff)); ///< 8 bit(s) starting from B40
    bytes[6] |= (((uint8_t)(raw >> 18) & 0xff)); ///< 8 bit(s) starting from B48
    bytes[7] |= (((uint8_t)(raw >> 26) & 0x0f)); ///< 4 bit(s) starting from B56

    return GPS_CURRENT_LOCATION_HDR;
}

/// Encode and send for dbc_encode_GPS_CURRENT_LOCATION() message
static inline bool dbc_encode_and_send_GPS_CURRENT_LOCATION(GPS_CURRENT_LOCATION_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_GPS_CURRENT_LOCATION(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_COM_BRIDGE_CHECK_POINT() since the sender is COM_BRIDGE and we are GPS

/// Not generating code for dbc_encode_COM_BRIDGE_CLICKED_START() since the sender is COM_BRIDGE and we are GPS

/// Not generating code for dbc_encode_MASTER_DRIVING_CAR() since the sender is MASTER and we are GPS

/// Not generating code for dbc_encode_SENSOR_SONARS() since the sender is SENSOR and we are GPS

/// Not generating code for dbc_encode_MOTOR_HEARTBEAT() since the sender is MOTOR and we are GPS

/// Not generating code for dbc_encode_MOTOR_CAR_SPEED() since the sender is MOTOR and we are GPS

/// Not generating code for dbc_encode_COM_BRIDGE_STOPALL() since the sender is COM_BRIDGE and we are GPS

/// Not generating code for dbc_encode_SENSOR_HEARTBEAT() since the sender is SENSOR and we are GPS

/// Encode GPS's 'GPS_HEARTBEAT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_GPS_HEARTBEAT(uint8_t bytes[8], GPS_HEARTBEAT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->GPS_HEARTBEAT_UNSIGNED)))) & 0x7ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x07)); ///< 3 bit(s) starting from B8

    return GPS_HEARTBEAT_HDR;
}

/// Encode and send for dbc_encode_GPS_HEARTBEAT() message
static inline bool dbc_encode_and_send_GPS_HEARTBEAT(GPS_HEARTBEAT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_GPS_HEARTBEAT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_encode_COM_BRIDGE_HEARTBEAT() since the sender is COM_BRIDGE and we are GPS

/// Not generating code for dbc_encode_MASTER_ACKNOWLEDGEMENT() since the sender is MASTER and we are GPS

/// Encode GPS's 'GPS_ACKNOWLEDGEMENT' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_GPS_ACKNOWLEDGEMENT(uint8_t bytes[8], GPS_ACKNOWLEDGEMENT_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->GPS_ACKNOWLEDGEMENT_UNSIGNED)))) & 0x7ff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0
    bytes[1] |= (((uint8_t)(raw >> 8) & 0x07)); ///< 3 bit(s) starting from B8

    return GPS_ACKNOWLEDGEMENT_HDR;
}

/// Encode and send for dbc_encode_GPS_ACKNOWLEDGEMENT() message
static inline bool dbc_encode_and_send_GPS_ACKNOWLEDGEMENT(GPS_ACKNOWLEDGEMENT_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_GPS_ACKNOWLEDGEMENT(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Encode GPS's 'GPS_MASTER_DATA' message
/// @returns the message header of this message
static inline dbc_msg_hdr_t dbc_encode_GPS_MASTER_DATA(uint8_t bytes[8], GPS_MASTER_DATA_t *from)
{
    uint32_t raw;
    bytes[0]=bytes[1]=bytes[2]=bytes[3]=bytes[4]=bytes[5]=bytes[6]=bytes[7]=0;

    raw = ((uint32_t)(((from->GEO_DATA_TURNANGLE_SIGNED) / 1e-06) + 0.5)) & 0xff;
    bytes[0] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B0

    raw = ((uint32_t)(((from->GEO_DATA_ISFINAL_SIGNED)))) & 0x01;
    bytes[1] |= (((uint8_t)(raw) & 0x01) << 7); ///< 1 bit(s) starting from B15

    raw = ((uint32_t)(((from->GEO_DATA_DISTANCE_TO_FINAL_DESTINATION_SIGNED) / 1e-06) + 0.5)) & 0xffff;
    bytes[2] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B16
    bytes[3] |= (((uint8_t)(raw >> 8) & 0xff)); ///< 8 bit(s) starting from B24

    raw = ((uint32_t)(((from->GEO_DATA_DISTANCE_TO_NEXT_CHECKPOINT_SIGNED) / 1e-06) + 0.5)) & 0xffff;
    bytes[4] |= (((uint8_t)(raw) & 0xff)); ///< 8 bit(s) starting from B32
    bytes[5] |= (((uint8_t)(raw >> 8) & 0xff)); ///< 8 bit(s) starting from B40

    return GPS_MASTER_DATA_HDR;
}

/// Encode and send for dbc_encode_GPS_MASTER_DATA() message
static inline bool dbc_encode_and_send_GPS_MASTER_DATA(GPS_MASTER_DATA_t *from)
{
    uint8_t bytes[8];
    const dbc_msg_hdr_t hdr = dbc_encode_GPS_MASTER_DATA(bytes, from);
    return dbc_app_send_can_msg(hdr.mid, hdr.dlc, bytes);
}



/// Not generating code for dbc_decode_GPS_CURRENT_LOCATION() since 'GPS' is not the recipient of any of the signals

/// Decode COM_BRIDGE's 'COM_BRIDGE_CHECK_POINT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_COM_BRIDGE_CHECK_POINT(COM_BRIDGE_CHECK_POINT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != COM_BRIDGE_CHECK_POINT_HDR.dlc || hdr->mid != COM_BRIDGE_CHECK_POINT_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    // Decode the MUX
    raw  = ((uint32_t)((bytes[0]) & 0x03)); ///< 2 bit(s) from B0
    const uint8_t MUX = ((raw));

    if (0 == MUX) {
        // Non Muxed signals (part of all MUX'd structures)
        raw  = ((uint32_t)((bytes[0] >> 2) & 0x3f)); ///< 6 bit(s) from B2
        raw |= ((uint32_t)((bytes[1]) & 0x03)) << 6; ///< 2 bit(s) from B8
        to->m0.COM_BRIDGE_TOTAL_COUNT_UNSIGNED = ((raw));
        raw  = ((uint32_t)((bytes[1] >> 2) & 0x3f)); ///< 6 bit(s) from B10
        raw |= ((uint32_t)((bytes[2]) & 0x03)) << 6; ///< 2 bit(s) from B16
        to->m0.COM_BRIDGE_CURRENT_COUNT_UNSIGNED = ((raw));

        raw  = ((uint32_t)((bytes[2] >> 2) & 0x3f)); ///< 6 bit(s) from B18
        raw |= ((uint32_t)((bytes[3]))) << 6; ///< 8 bit(s) from B24
        raw |= ((uint32_t)((bytes[4]))) << 14; ///< 8 bit(s) from B32
        raw |= ((uint32_t)((bytes[5]))) << 22; ///< 8 bit(s) from B40
        raw |= ((uint32_t)((bytes[6]))) << 30; ///< 8 bit(s) from B48
        raw |= ((uint32_t)((bytes[7]) & 0x03)) << 38; ///< 2 bit(s) from B56
        to->m0.COM_BRIDGE_LATTITUDE_SIGNED = ((raw * 1e-06) + (-90));

        to->m0.mia_info.mia_counter_ms = 0; ///< Reset the MIA counter
    }
    else if (1 == MUX) {
        // Non Muxed signals (part of all MUX'd structures)
        raw  = ((uint32_t)((bytes[0] >> 2) & 0x3f)); ///< 6 bit(s) from B2
        raw |= ((uint32_t)((bytes[1]) & 0x03)) << 6; ///< 2 bit(s) from B8
        to->m1.COM_BRIDGE_TOTAL_COUNT_UNSIGNED = ((raw));
        raw  = ((uint32_t)((bytes[1] >> 2) & 0x3f)); ///< 6 bit(s) from B10
        raw |= ((uint32_t)((bytes[2]) & 0x03)) << 6; ///< 2 bit(s) from B16
        to->m1.COM_BRIDGE_CURRENT_COUNT_UNSIGNED = ((raw));

        raw  = ((uint32_t)((bytes[2] >> 2) & 0x3f)); ///< 6 bit(s) from B18
        raw |= ((uint32_t)((bytes[3]))) << 6; ///< 8 bit(s) from B24
        raw |= ((uint32_t)((bytes[4]))) << 14; ///< 8 bit(s) from B32
        raw |= ((uint32_t)((bytes[5]))) << 22; ///< 8 bit(s) from B40
        raw |= ((uint32_t)((bytes[6]))) << 30; ///< 8 bit(s) from B48
        raw |= ((uint32_t)((bytes[7]) & 0x03)) << 38; ///< 2 bit(s) from B56
        to->m1.COM_BRIDGE_LONGITUDE_SIGNED = ((raw * 1e-06) + (-180));

        to->m1.mia_info.mia_counter_ms = 0; ///< Reset the MIA counter
    }
    else {
        return !success;
    }

    return success;
}


/// Decode COM_BRIDGE's 'COM_BRIDGE_CLICKED_START' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_COM_BRIDGE_CLICKED_START(COM_BRIDGE_CLICKED_START_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != COM_BRIDGE_CLICKED_START_HDR.dlc || hdr->mid != COM_BRIDGE_CLICKED_START_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]) & 0x07)) << 8; ///< 3 bit(s) from B8
    to->COM_BRIDGE_CLICKED_START_UNSIGNED = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_MASTER_DRIVING_CAR() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_SONARS() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_HEARTBEAT() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_MOTOR_CAR_SPEED() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_STOPALL() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_SENSOR_HEARTBEAT() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_HEARTBEAT() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_COM_BRIDGE_HEARTBEAT() since 'GPS' is not the recipient of any of the signals

/// Decode MASTER's 'MASTER_ACKNOWLEDGEMENT' message
/// @param hdr  The header of the message to validate its DLC and MID; this can be NULL to skip this check
static inline bool dbc_decode_MASTER_ACKNOWLEDGEMENT(MASTER_ACKNOWLEDGEMENT_t *to, const uint8_t bytes[8], const dbc_msg_hdr_t *hdr)
{
    const bool success = true;
    // If msg header is provided, check if the DLC and the MID match
    if (NULL != hdr && (hdr->dlc != MASTER_ACKNOWLEDGEMENT_HDR.dlc || hdr->mid != MASTER_ACKNOWLEDGEMENT_HDR.mid)) {
        return !success;
    }

    uint32_t raw;
    raw  = ((uint32_t)((bytes[0]))); ///< 8 bit(s) from B0
    raw |= ((uint32_t)((bytes[1]) & 0x07)) << 8; ///< 3 bit(s) from B8
    to->ACKNOWLEDGEMENT_DATA_REACHED_UNSIGNED = ((raw));

    to->mia_info.mia_counter_ms = 0; ///< Reset the MIA counter

    return success;
}


/// Not generating code for dbc_decode_GPS_ACKNOWLEDGEMENT() since 'GPS' is not the recipient of any of the signals

/// Not generating code for dbc_decode_GPS_MASTER_DATA() since 'GPS' is not the recipient of any of the signals

/// Handle the MIA for COM_BRIDGE's COM_BRIDGE_CHECK_POINT for MUX "m0" message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_COM_BRIDGE_CHECK_POINT_m0(COM_BRIDGE_CHECK_POINT_m0_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= COM_BRIDGE_CHECK_POINT_m0__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = COM_BRIDGE_CHECK_POINT_m0__MIA_MSG;
        msg->mia_info.mia_counter_ms = COM_BRIDGE_CHECK_POINT_m0__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for COM_BRIDGE's COM_BRIDGE_CHECK_POINT for MUX "m1" message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_COM_BRIDGE_CHECK_POINT_m1(COM_BRIDGE_CHECK_POINT_m1_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= COM_BRIDGE_CHECK_POINT_m1__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = COM_BRIDGE_CHECK_POINT_m1__MIA_MSG;
        msg->mia_info.mia_counter_ms = COM_BRIDGE_CHECK_POINT_m1__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for COM_BRIDGE's COM_BRIDGE_CLICKED_START message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_COM_BRIDGE_CLICKED_START(COM_BRIDGE_CLICKED_START_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= COM_BRIDGE_CLICKED_START__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = COM_BRIDGE_CLICKED_START__MIA_MSG;
        msg->mia_info.mia_counter_ms = COM_BRIDGE_CLICKED_START__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

/// Handle the MIA for MASTER's MASTER_ACKNOWLEDGEMENT message
/// @param   time_incr_ms  The time to increment the MIA counter with
/// @returns true if the MIA just occurred
/// @post    If the MIA counter reaches the MIA threshold, MIA struct will be copied to *msg
static inline bool dbc_handle_mia_MASTER_ACKNOWLEDGEMENT(MASTER_ACKNOWLEDGEMENT_t *msg, uint32_t time_incr_ms)
{
    bool mia_occurred = false;
    const dbc_mia_info_t old_mia = msg->mia_info;
    msg->mia_info.is_mia = (msg->mia_info.mia_counter_ms >= MASTER_ACKNOWLEDGEMENT__MIA_MS);

    if (!msg->mia_info.is_mia) { // Not MIA yet, so keep incrementing the MIA counter
        msg->mia_info.mia_counter_ms += time_incr_ms;
    }
    else if(!old_mia.is_mia)   { // Previously not MIA, but it is MIA now
        // Copy MIA struct, then re-write the MIA counter and is_mia that is overwriten
        *msg = MASTER_ACKNOWLEDGEMENT__MIA_MSG;
        msg->mia_info.mia_counter_ms = MASTER_ACKNOWLEDGEMENT__MIA_MS;
        msg->mia_info.is_mia = true;
        mia_occurred = true;
    }

    return mia_occurred;
}

#endif
