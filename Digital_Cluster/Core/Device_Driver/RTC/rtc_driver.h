/**
  ******************************************************************************
  * @file    rtc_driver.h
  * @brief   Driver điều khiển và đọc thời gian RTC cho Digital Cluster
  ******************************************************************************
  */

#ifndef DEVICE_DRIVER_RTC_DRIVER_H_
#define DEVICE_DRIVER_RTC_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "lvgl.h"

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} rtc_datetime_t;

/**
 * @brief  Khởi tạo RTC Driver và kích hoạt timer cập nhật UI tự động trong LVGL
 * @param  update_period_ms: Chu kỳ cập nhật (thường 500ms hoặc 1000ms)
 */
void RTC_Driver_Init(uint32_t update_period_ms);

/**
 * @brief  Đọc ngày giờ hiện tại từ STM32 RTC
 * @param  dt: con trỏ lưu trữ ngày giờ
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef RTC_Driver_GetDateTime(rtc_datetime_t *dt);

/**
 * @brief  Cài đặt giờ mới cho RTC
 * @retval HAL_StatusTypeDef
 */
HAL_StatusTypeDef RTC_Driver_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds);

/**
 * @brief  Callback định kỳ của LVGL cập nhật lên label cluster_time_label
 */
void RTC_Timer_Callback(lv_timer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* DEVICE_DRIVER_RTC_DRIVER_H_ */

