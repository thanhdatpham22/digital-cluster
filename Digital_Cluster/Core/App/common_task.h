/*
 * common_task.h
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 */

#ifndef APP_COMMON_TASK_H_
#define APP_COMMON_TASK_H_
#include <stdio.h>
#include "cmsis_os.h"
#include "lvgl.h"
#include "Handler_task.h"
#include "../Device_Driver/L3GD20/l3gd20.h"
#include "../Device_Driver/RTC/rtc_driver.h"

void Common_Task(void *argument);

#endif /* APP_COMMON_TASK_H_ */
