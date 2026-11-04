/*
 * TouchController.c
 *
 *  Ported for XPT2046 Touch Controller with LVGL
 */

/*********************
 *      INCLUDES
 *********************/
#include "../Device_Driver/TouchController.h"

#include "lvgl.h"
#include "main.h"
#include <stdio.h>
#include "ST7789/ST7789_STM32_Driver.h"
#include "XPT2046/xpt2046.h"

/**********************
 *  EXTERNAL VARIABLES
 **********************/
extern SPI_HandleTypeDef hspi3;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    /* 1. Khởi tạo phần cứng Touchpad */
    touchpad_init();

    /* 2. Đăng ký driver touchpad với LVGL */
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Khởi tạo cấu hình cho XPT2046 */
static void touchpad_init(void)
{
    // Gán cổng SPI3 vào driver
    xpt2046_spi(&hspi3);

    // Đặt kích thước màn hình theo ST7789
    xpt2046_set_size(240, 320);

    // Đặt hướng cảm ứng khớp với hướng hiển thị của LCD
    // (Đổi thành XPT2046_ORIENTATION_PORTRAIT / LANDSCAPE tùy cách hiển thị của bạn)
    xpt2046_orientation(XPT2046_ORIENTATION_LANDSCAPE);

    // Khởi tạo chip XPT2046
    xpt2046_init();
}

/* Callback được LVGL gọi định kỳ (lv_task_handler / lv_timer_handler) để quét vị trí chạm */
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
    uint16_t touch_x = 0;
    uint16_t touch_y = 0;

    // Đọc vị trí từ tầng driver xpt2046
    xpt2046_read_position(&touch_x, &touch_y);

    // Nếu màn hình đang được nhấn (tọa độ khác 0)
    if (touch_x != 0 || touch_y != 0)
    {
        last_x = (lv_coord_t)touch_x;
//        last_y = (lv_coord_t)touch_y;
        // Đảo ngược trục Y theo chiều cao màn hình: Y_new = Height - Y_old
		// (Thay 320 bằng đúng chiều cao hiện tại của màn hình hiển thị trong LVGL)
		last_y = (lv_coord_t)(320 - 1 - touch_y);
        data->state = LV_INDEV_STATE_PR; // Trạng thái: Pressed (Đang nhấn)

        // Debug qua UART khi chạm (nếu cần)
         printf("LVGL Touch -> X: %d, Y: %d\r\n", last_x, last_y);
    }
    else
    {
        data->state = LV_INDEV_STATE_REL; // Trạng thái: Released (Đã nhả tay)
    }

    // Luôn gửi tọa độ cuối cùng cho LVGL (kể cả khi vừa nhả tay)
    data->point.x = last_x;
    data->point.y = last_y;
}
