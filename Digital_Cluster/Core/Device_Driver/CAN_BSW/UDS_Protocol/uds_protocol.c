/*
 * uds_protocol.c
 *
 *  Created on: Nov 10, 2026
 *      Author: admin
 */


#include "../../CAN_BSW/UDS_Protocol/uds_protocol.h"


VehicleData_t g_VehicleData = {
    .speed_kmh = 0,
    .engine_rpm = 0,
    .gear = 'P',
    .fuel_percent = 100,
    .coolant_temp = 85,
    .warning_flags = 0
};
/* Giải mã bản tin CANID 0x120: Tốc độ, Vòng tua, Vị trí số */
void Decode_SpeedRpm(const uint8_t *data, uint8_t dlc)
{
    if (dlc < 5) return;

    g_VehicleData.speed_kmh  = (uint16_t)((data[0] << 8) | data[1]);
    g_VehicleData.engine_rpm = (uint16_t)((data[2] << 8) | data[3]);

    static const char gear_map[] = {'P', 'R', 'N', 'D', 'S'};
    if (data[4] < sizeof(gear_map)) {
        g_VehicleData.gear = gear_map[data[4]];
    } else {
        g_VehicleData.gear = (char)data[4];
    }

    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);

}

/* Giải mã bản tin CANID 0x220: Trạng thái thân xe */
void Decode_BodyStatus(const uint8_t *data, uint8_t dlc)
{
    if (dlc < 3) return;

    g_VehicleData.fuel_percent  = data[0];
    g_VehicleData.coolant_temp  = (int8_t)data[1];
    g_VehicleData.warning_flags = data[2];

    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);

}
