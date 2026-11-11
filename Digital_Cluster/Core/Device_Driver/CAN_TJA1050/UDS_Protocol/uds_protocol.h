/*
 * uds_protocol.h
 *
 *  Created on: Nov 10, 2026
 *      Author: admin
 */

#ifndef DEVICE_DRIVER_CAN_TJA1050_UDS_PROTOCOL_UDS_PROTOCOL_H_
#define DEVICE_DRIVER_CAN_TJA1050_UDS_PROTOCOL_UDS_PROTOCOL_H_
#include "stdint.h"
#include "../Device_Driver/CAN_TJA1050/CanIf/CanIf.h"
/* Khai báo kiểu con trỏ hàm giải mã PDU */
typedef void (*PduRxDecoderFunc_t)(const uint8_t *data, uint8_t dlc);

/* Struct định nghĩa từng phần tử trong bảng định tuyến PDU */
typedef struct {
    PduIdType           pdu_id;
    PduRxDecoderFunc_t  decoder;
}PduRxRoute_t;

/* Cấu trúc dữ liệu trạng thái xe cập nhật cho taplo */
typedef struct {
    uint16_t speed_kmh;      // 0 - 260 km/h
    uint16_t engine_rpm;     // 0 - 8000 RPM
    char     gear;           // 'P', 'R', 'N', 'D', 'S'
    uint8_t  fuel_percent;   // 0 - 100 %
    int8_t   coolant_temp;   // -40 đến 125 °C
    uint8_t  warning_flags;  // Cờ báo hiệu / xi nhan
} VehicleData_t;
extern VehicleData_t g_VehicleData;
void Decode_SpeedRpm(const uint8_t *data, uint8_t dlc);
void Decode_BodyStatus(const uint8_t *data, uint8_t dlc);
#endif /* DEVICE_DRIVER_CAN_TJA1050_UDS_PROTOCOL_UDS_PROTOCOL_H_ */
