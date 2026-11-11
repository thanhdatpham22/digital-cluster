/*
 * can_controller.h
 *
 *  Created on: Nov 5, 2026
 *      Author: admin
 */

#ifndef DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_H_
#define DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_H_


void Config_MailBoxes(void);
void Fillter_Config(void);
void CAN_TxPump(void);
void CAN_MainHandler(void);
#endif /* DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_H_ */
