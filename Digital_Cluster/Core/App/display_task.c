/*
 * display_task.c
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 */
#include "display_task.h"
#include "../Device_Driver/CAN_TJA1050/UDS_Protocol/uds_protocol.h"
#include "screens.h"
#include "../Device_Driver/RTC/rtc_driver.h"

/**
 * @brief Cập nhật dữ liệu xe từ CAN Stack lên các widget LVGL
 * @note Chạy an toàn trực tiếp trong ngữ cảnh Task Display (LVGL thread)
 */
static void Update_Cluster_From_CAN(void)
{
//    if (!g_VehicleDataUpdated) return;
//    g_VehicleDataUpdated = 0;

    static uint16_t last_speed = 0xFFFF;
    static uint16_t last_rpm   = 0xFFFF;
    static char     last_gear  = 0;
    static uint8_t  last_fuel  = 0xFF;
    static int8_t   last_temp  = 0x7F;

    /* 1. Cập nhật tốc độ (km/h) */
    if (g_VehicleData.speed_kmh != last_speed) {
        last_speed = g_VehicleData.speed_kmh;
        if (cluster_speed_label != NULL) {
            lv_label_set_text_fmt(cluster_speed_label, "%03u", (unsigned int)last_speed);
        }
    }

    /* 2. Cập nhật vòng tua máy (RPM) - An toàn tuyệt đối không dùng float */
    if (g_VehicleData.engine_rpm != last_rpm) {
        last_rpm = g_VehicleData.engine_rpm;
        if (cluster_rpm_label != NULL) {
            unsigned int rpm_int = last_rpm / 1000;
            unsigned int rpm_dec = (last_rpm % 1000) / 100;
            lv_label_set_text_fmt(cluster_rpm_label, "%u.%u", rpm_int, rpm_dec);
        }
        if (cluster_rpm_arc != NULL) {
            int16_t arc_val = (last_rpm > 8000) ? 8000 : (int16_t)last_rpm;
            lv_arc_set_value(cluster_rpm_arc, arc_val);
        }
    }

    /* 3. Cập nhật cấp số (P, R, N, D, S) */
    if (g_VehicleData.gear != last_gear) {
        last_gear = g_VehicleData.gear;
        if (cluster_gear_label != NULL) {
            char gear_str[2] = {last_gear, '\0'};
            lv_label_set_text(cluster_gear_label, gear_str);
        }
    }

    /* 4. Cập nhật lượng nhiên liệu (%) */
    if (g_VehicleData.fuel_percent != last_fuel) {
        last_fuel = g_VehicleData.fuel_percent;
        if (cluster_fuel_label != NULL) {
            lv_label_set_text_fmt(cluster_fuel_label, "%u%%", (unsigned int)last_fuel);
        }
        if (cluster_fuel_bar != NULL) {
            lv_bar_set_value(cluster_fuel_bar, (int32_t)last_fuel, LV_ANIM_OFF);
        }
    }

    /* 5. Cập nhật nhiệt độ nước làm mát (°C) */
    if (g_VehicleData.coolant_temp != last_temp) {
        last_temp = g_VehicleData.coolant_temp;
        if (cluster_temp_label != NULL) {
            lv_label_set_text_fmt(cluster_temp_label, "%d C", (int)last_temp);
        }
    }
}

void Display_Handler(void *argument)
{
    printf("Display_Handler: Starting hardware init...\r\n");

    ST7789_Init(); // Init driver of Display
    ST7789_SetRotation(SCREEN_VERTICAL_1); // Chế độ màn hình đứng Portrait (240x320)

    lv_init(); // Init lvgl Library
    lv_port_disp_init();  // Init Connection lvgl with ST7789 driver
    lv_port_indev_init(); // Init Touch controller
    ui_init(); // Khởi tạo giao diện đồ họa
    RTC_Driver_Init(500); // Khởi tạo timer RTC an toàn trong LVGL thread
    printf("Task Display is Raise! Screens generated successfully.\r\n");

    /* Kích hoạt CAN Task chạy sau khi UI đã sẵn sàng */
    osThreadFlagsSet(cantaskHandle, INIT_FLAG_START);
    for(;;)
    {
        Update_Cluster_From_CAN(); // Đọc dữ liệu CAN cập nhật lên widget
        lv_timer_handler();        // Xử lý render và timer đồ họa LVGL
        ui_tick();                 // Xử lý event nội tại EEZ Studio
        osDelay(10);
    }
}
