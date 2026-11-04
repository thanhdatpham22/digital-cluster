/*
 * lvgl_port_disp.c
 *
 *  Created on: Oct 30, 2026
 *      Author: admin
 */
#include "../Device_Driver/lvgl_port_disp.h"

#include "lvgl.h"

#include "ST7789/ST7789_STM32_Driver.h"

static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf_1[MY_DISP_HOR_RES * BUFFER_LINES];

/* Hàm bắn dữ liệu từ LVGL buffer xuống màn hình ST7789 */
static void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t width = (area->x2 - area->x1 + 1);
  uint32_t height = (area->y2 - area->y1 + 1);
  uint32_t total_pixels = width * height;
  uint32_t total_bytes = total_pixels * 2; // RGB565 = 2 bytes/pixel
  // 1. Set vùng vẽ tương ứng trên ST7789
  ST7789_SetAddress(area->x1, area->y1, area->x2, area->y2);
  // 2. Chuyển sang chế độ Data và kích hoạt CS
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  ST7789_Select();
  // 3. Gửi buffer qua hàm SPI/DMA sẵn có
  uint32_t offset = 0;
  uint8_t *data_ptr = (uint8_t *)color_p;
  while (offset < total_bytes) {
    uint16_t chunk = (total_bytes - offset > ST7789_BURST_MAX_SIZE)
                         ? ST7789_BURST_MAX_SIZE
                         : (uint16_t)(total_bytes - offset);
    ST7789_SPI_TxBuffer(data_ptr + offset, chunk);
    offset += chunk;
  }
  ST7789_Unselect();
  // 4. Báo cho LVGL biết đã vẽ xong vùng này
  lv_disp_flush_ready(drv);
}

void lv_port_disp_init(void)
{
  // Khởi tạo buffer vẽ
  lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, MY_DISP_HOR_RES * BUFFER_LINES);
  // Đăng ký display driver với LVGL
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = MY_DISP_HOR_RES;
  disp_drv.ver_res = MY_DISP_VER_RES;
  disp_drv.flush_cb = disp_flush;
  disp_drv.draw_buf = &disp_buf;
  lv_disp_drv_register(&disp_drv);
}
