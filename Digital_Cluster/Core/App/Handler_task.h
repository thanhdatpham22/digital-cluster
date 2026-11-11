/*
 * Handler_task.h
 *
 *  Created on: Nov 9, 2026
 *      Author: admin
 */

#ifndef APP_HANDLER_TASK_H_
#define APP_HANDLER_TASK_H_
#include "cmsis_os.h"

extern osThreadId_t defaultTaskHandle;;
extern osThreadId_t cantaskHandle;
extern osThreadId_t displaytaskHandle;
extern osThreadId_t logtaskHandle;
extern osThreadId_t commontaskHandle;

#define INIT_FLAG_START  0x01

#endif /* APP_HANDLER_TASK_H_ */
