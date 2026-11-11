/*
 * can_task.h
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 */

#ifndef APP_CAN_TASK_H_
#define APP_CAN_TASK_H_

#include <stdio.h>
#include <stdint.h>
#include "cmsis_os.h"
#include "main.h"
#include "Handler_task.h"
#include "ui.h"
/* AUTOSAR CAN Stack Headers */
#include "../Device_Driver/CAN_TJA1050/Can/Can.h"
#include "../Device_Driver/CAN_TJA1050/CanIf/CanIf.h"



/* Các widget hiển thị trên màn hình Taplo */

void Can_Handler(void *argument);
void Cluster_CanRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

#endif /* APP_CAN_TASK_H_ */
