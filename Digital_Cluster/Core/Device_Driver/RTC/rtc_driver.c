/**
  ******************************************************************************
  * @file    rtc_driver.c
  * @brief   Triển khai đọc RTC và cập nhật lên màn hình LVGL
  ******************************************************************************
  */

#include "rtc_driver.h"
#include "screens.h"
#include <stdio.h>

extern RTC_HandleTypeDef hrtc;
extern lv_obj_t *cluster_time_label;

static lv_timer_t *rtc_timer = NULL;

HAL_StatusTypeDef RTC_Driver_GetDateTime(rtc_datetime_t *dt)
{
    if (dt == NULL) return HAL_ERROR;

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    // 1. Đọc Time trước
    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        return HAL_ERROR;
    }

    // 2. BẮT BUỘC đọc Date ngay sau Time để mở khóa shadow register của STM32 RTC
    if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK) {
        return HAL_ERROR;
    }

    dt->hours   = sTime.Hours;
    dt->minutes = sTime.Minutes;
    dt->seconds = sTime.Seconds;
    dt->date    = sDate.Date;
    dt->month   = sDate.Month;
    dt->year    = sDate.Year;

    return HAL_OK;
}

HAL_StatusTypeDef RTC_Driver_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    RTC_TimeTypeDef sTime = {0};
    sTime.Hours = hours;
    sTime.Minutes = minutes;
    sTime.Seconds = seconds;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_SET;

    return HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
}

void RTC_Timer_Callback(lv_timer_t *timer)
{
    (void)timer;

    if (cluster_time_label == NULL) return;

    rtc_datetime_t dt;
    if (RTC_Driver_GetDateTime(&dt) == HAL_OK) {
        // Cập nhật lên widget cluster_time_label theo định dạng HH:MM
        // Dấu hai chấm nhấp nháy theo giây (dt.seconds % 2 == 0) để tạo cảm giác sống động
        if (dt.seconds % 2 == 0) {
            lv_label_set_text_fmt(cluster_time_label, "%02d:%02d", dt.hours, dt.minutes);
        } else {
            lv_label_set_text_fmt(cluster_time_label, "%02d %02d", dt.hours, dt.minutes);
        }
    }
}

void RTC_Driver_Init(uint32_t update_period_ms)
{
    if (rtc_timer == NULL) {
        // Tạo timer chạy định kỳ trong LVGL để cập nhật UI
        rtc_timer = lv_timer_create(RTC_Timer_Callback, update_period_ms, NULL);
    }
}

