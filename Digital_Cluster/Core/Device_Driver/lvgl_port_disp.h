/*
 * lvgl_port_disp.h
 *
 *  Created on: Oct 30, 2026
 *      Author: admin
 */

#ifndef DEVICE_DRIVER_LVGL_PORT_DISP_H_
#define DEVICE_DRIVER_LVGL_PORT_DISP_H_

#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 320
#define BUFFER_LINES 20 // Buffer 20 dòng để tiết kiệm RAM (~9.6 KB)
void lv_port_disp_init(void);

#endif /* DEVICE_DRIVER_LVGL_PORT_DISP_H_ */
