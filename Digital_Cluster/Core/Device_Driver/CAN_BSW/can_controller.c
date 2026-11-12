/*
 * can_controller.c
 *
 *  Created on: Nov 5, 2026
 *      Author: admin
 */

#ifndef DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_C_
#define DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_C_

/*
 * NOTE: File nay da duoc thay the bang AUTOSAR CAN Stack (Can.c, CanIf.c).
 * Giu lai duoi dang backup tham khao.
 */
#if 0

#include "main.h"
#include <stdio.h>
extern CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef TxMsg1;
CAN_TxHeaderTypeDef TxMsg2;
CAN_TxHeaderTypeDef TxMsg3;
CAN_TxHeaderTypeDef TxMsg4;
CAN_TxHeaderTypeDef TxMsg5;

CAN_RxHeaderTypeDef RxMsg;
CAN_FilterTypeDef sFilterConfig;

uint8_t Rx_Buff[8];
uint8_t Tx_Buff1[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
uint8_t Tx_Buff2[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07};
uint8_t Tx_Buff3[8] = {0x02,0x01,0x0C,0x00,0x00,0x00,0x00,0x00}; // OBD-II PID 0x0C
uint8_t Tx_Buff4[8] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};
uint8_t Tx_Buff5[8] = {0xAA,0xBB,0xCC,0xDD,0x11,0x22,0x33,0x44};


uint32_t Tx_MailBox0;
uint32_t Tx_Mailbox1;
uint32_t Tx_Mailbox2;
uint32_t Tx_Mailbox3;
uint32_t Tx_Mailbox4;
uint8_t ubuff[50] = "Send Message CAN OK\r\n";

uint8_t flag_Tx = 0;
uint8_t flag_Rx = 0;

void Config_MailBoxes(void)
{
    // Bản tin 1 – Extended ID
    TxMsg1.ExtId = 0x1ABCDE3;
    TxMsg1.IDE   = CAN_ID_EXT;
    TxMsg1.RTR   = CAN_RTR_DATA;
    TxMsg1.DLC   = 8;
    TxMsg1.TransmitGlobalTime = DISABLE;

    // Bản tin 2 – Standard ID
    TxMsg2.StdId = 0x796;
    TxMsg2.IDE   = CAN_ID_STD;
    TxMsg2.RTR   = CAN_RTR_DATA;
    TxMsg2.DLC   = 8;
    TxMsg2.TransmitGlobalTime = DISABLE;

    // Bản tin 3 – OBD-II request (0x7DF)
    TxMsg3.StdId = 0x7DF;
    TxMsg3.IDE   = CAN_ID_STD;
    TxMsg3.RTR   = CAN_RTR_DATA;
    TxMsg3.DLC   = 8;
    TxMsg3.TransmitGlobalTime = DISABLE;

    // Bản tin 4 – Standard ID khác
    TxMsg4.StdId = 0x655;
    TxMsg4.IDE   = CAN_ID_STD;
    TxMsg4.RTR   = CAN_RTR_DATA;
    TxMsg4.DLC   = 8;
    TxMsg4.TransmitGlobalTime = DISABLE;

    // Bản tin 5 – Standard ID khác
    TxMsg5.StdId = 0x321;
    TxMsg5.IDE   = CAN_ID_STD;
    TxMsg5.RTR   = CAN_RTR_DATA;
    TxMsg5.DLC   = 8;
    TxMsg5.TransmitGlobalTime = DISABLE;
}
void Fillter_Config(void)
{
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh     = (0x563 << 5);   //
	sFilterConfig.FilterIdLow      = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0x7FF << 5);   // mask for 11-bit
	sFilterConfig.FilterMaskIdLow  = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
//	sFilterConfig.SlaveStartFilterBank = 14;         // Set for CAN2

	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
	sFilterConfig.FilterBank = 1;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh     = (0x700 << 5);   //
	sFilterConfig.FilterIdLow      = 0x0000;
	sFilterConfig.FilterMaskIdHigh = (0x7F0 << 5);   // mask for 11-bit
	sFilterConfig.FilterMaskIdLow  = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);


	sFilterConfig.FilterBank = 2;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh     = (0x221 << 5);
	sFilterConfig.FilterIdLow      = (0x223 << 5);
	sFilterConfig.FilterMaskIdHigh = (0x224 << 5);
	sFilterConfig.FilterMaskIdLow  = (0x225 << 5);
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
//	sFilterConfig.SlaveStartFilterBank = 14;         // bắt buộc khi có CAN2
	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);

}

void CAN_TxPump(void)
{
	uint8_t mb;
	CAN_TxHeaderTypeDef th;
	uint8_t td[8];
	while((!txq_Empty()) &&  HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
	{
		if (!txq_pop(&th, td)) break;
		if (HAL_CAN_AddTxMessage(&hcan1, &th, td, &mb) != HAL_OK)
		{
			txq_push(&th, td);
			break;
		}
	}


}
void CAN_MainHandler(void)
{
	 if(flag_Rx == 1)
	  {
		  printf("RX StdID=0x%03lX DLC=%lu Data: ", RxMsg.StdId, (unsigned long)RxMsg.DLC);
		  for (uint8_t i = 0; i < RxMsg.DLC; i++) printf("%02X ", Rx_Buff[i]);
		  printf("\r\n");
//		  if(HAL_CAN_AddTxMessage(&hcan1, &TxMsg4, Tx_Buff5, &Tx_Mailbox3) != HAL_OK)
//		   {
//			  Error_Handler();
//		   }
		  flag_Rx = 0;
	  }
//	  CAN_TxPump();
//	   if(HAL_CAN_AddTxMessage(&hcan1, &TxMsg1, Tx_Buff1, &Tx_MailBox0) != HAL_OK)
//	   {
//		  Error_Handler();
//	   }
//	   if (HAL_CAN_AddTxMessage(&hcan1, &TxMsg2, Tx_Buff2, &Tx_Mailbox1) != HAL_OK)
//	   {
//		   Error_Handler();
//	   }
//	   if(HAL_CAN_AddTxMessage(&hcan1, &TxMsg3, Tx_Buff3, &Tx_Mailbox2) != HAL_OK)
//	   {
//		   Error_Handler();
//	   }
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance != CAN1) return;

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMsg, Rx_Buff) == HAL_OK)
    {
        if (RxMsg.IDE == CAN_ID_STD)
//        	 if (RxMsg.IDE == CAN_ID_STD && RxMsg.StdId == 0x563)
        {
            flag_Rx = 1;
            HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
        }
    }
}

#endif /* BACKUP */

#endif /* DEVICE_DRIVER_CAN_TJA1050_CAN_CONTROLLER_C_ */
