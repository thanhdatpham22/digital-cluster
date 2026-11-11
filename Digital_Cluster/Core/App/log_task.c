/*
 * log_task.c
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 */
#include "log_task.h"

void Log_Handler(void *argument)
{
	osThreadFlagsWait(INIT_FLAG_START, osFlagsWaitAny, osWaitForever);
	printf("Log Task is began\r\n");
	osThreadFlagsSet(defaultTaskHandle, INIT_FLAG_START);
	for(;;)
	{
		osDelay(1);
	}
}

