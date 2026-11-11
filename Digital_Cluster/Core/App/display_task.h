/*
 * display_task.h
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 *
 * ==============================================================================
 *                      ĐẶC TẢ HƯỚNG & TỌA ĐỘ MÀN HÌNH (PORTRAIT 240x320)
 * ==============================================================================
 *
 *  1. TỌA ĐỘ PHẦN CỨNG THỰC TẾ (CẢM ỨNG XPT2046 ĐỌC ĐƯỢC KHI ĐỂ ĐỨNG):
 *
 *     (X=0, Y=320)  ┌──────────────────────────────────┐  (X=240, Y=320)
 *                   │  ▲                               │
 *                   │  │ TRÊN CÙNG (TOP)               │
 *                   │                                  │
 *                   │                                  │
 *                   │                                  │
 *                   │       MÀN HÌNH ĐỨNG              │
 *                   │     PORTRAIT 240 x 320           │
 *                   │                                  │
 *                   │                                  │
 *                   │                                  │
 *                   │  │ DƯỚI CÙNG (BOTTOM)            │
 *                   │  ▼                               │
 *       (X=0, Y=0)  └──────────────────────────────────┘  (X=240, Y=0)
 *                   ◄────────────── X (240) ───────────►
 *
 *  2. ÁNH XẠ SANG HỆ TỌA ĐỘ ĐỒ HỌA LVGL:
 *     Trong LVGL, gốc tọa độ (0, 0) chuẩn nằm ở GÓC TRÊN CÙNG BÊN TRÁI.
 *     Do đó trục Y cần được đảo ngược:
 *         X_lvgl = touch_x;
 *         Y_lvgl = (320 - 1 - touch_y);
 *
 *     - Chạm (0, 320)   [Trên - Trái] -> LVGL (0, 0)
 *     - Chạm (240, 320) [Trên - Phải] -> LVGL (239, 0)
 *     - Chạm (0, 0)     [Dưới - Trái] -> LVGL (0, 319)
 *     - Chạm (240, 0)   [Dưới - Phải] -> LVGL (239, 319)
 * ==============================================================================
 */

#ifndef APP_DISPLAY_TASK_H_
#define APP_DISPLAY_TASK_H_

#include <stdio.h>
#include "cmsis_os.h"
#include "lvgl.h"
#include "ui.h"
#include "Handler_task.h"
#include "../Device_Driver/lvgl_port_disp.h"
#include "../Device_Driver/TouchController.h"
#include "../Device_Driver/ST7789/ST7789_GFX.h"
#include "../Device_Driver/ST7789/ST7789_STM32_Driver.h"

void Display_Handler(void *argument);

extern lv_obj_t *cluster_speed_label;
extern lv_obj_t *cluster_rpm_label;
extern lv_obj_t *cluster_gear_label;
extern lv_obj_t *cluster_fuel_label;
extern lv_obj_t *cluster_temp_label;
extern lv_obj_t *cluster_fuel_bar;
extern lv_obj_t *cluster_rpm_arc;

#endif /* APP_DISPLAY_TASK_H_ */
