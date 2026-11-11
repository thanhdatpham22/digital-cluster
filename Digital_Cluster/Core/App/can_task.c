/*
 * can_tas.c
 *
 *  AUTOSAR CAN Stack Interface & Task for Digital Cluster
 *  Created on: Nov 6, 2026
 *      Author: admin
 */
#include "can_task.h"
#include "../Device_Driver/CAN_TJA1050/UDS_Protocol/uds_protocol.h"
/* Biến toàn cục lưu trữ trạng thái xe (sau này có thể cập nhật qua Queue) */

/* Bảng con trỏ hàm trực tiếp theo Index của RxPduId */
static const PduRxDecoderFunc_t g_PduDecoderTable[] = {
    [CANIF_RX_PDU_SPEED_RPM]   = Decode_SpeedRpm,
    [CANIF_RX_PDU_BODY_STATUS] = Decode_BodyStatus,
    /* Khi mở rộng, chỉ cần thêm dòng ở đây:
    [CANIF_RX_PDU_TPMS]        = Decode_Tpms,
    [CANIF_RX_PDU_ADAS]        = Decode_Adas,
    */
};

#define PDU_DECODER_TABLE_SIZE (sizeof(g_PduDecoderTable) / sizeof(g_PduDecoderTable[0]))


static void Init_CanAutosar(void);
/**
 * @brief Task xử lý CAN của FreeRTOS
 */
void Can_Handler(void *argument)
{
    /* Khởi tạo toàn bộ AUTOSAR CAN Stack */
	osThreadFlagsWait(INIT_FLAG_START, osFlagsWaitAny, osWaitForever);
    Init_CanAutosar();
    printf("AUTOSAR CAN Stack Initialized & Started!\r\n");

    /* Kích hoạt Common Task tiếp tục sau khi CAN đã sẵn sàng */
    osThreadFlagsSet(commontaskHandle, INIT_FLAG_START);

    for(;;)
    {
        /* Thực hiện các chu kỳ MainFunction của AUTOSAR Can */
        Can_MainFunction_Read();
        Can_MainFunction_Write();
        Can_MainFunction_BusOff();

        /* In log an toàn từ Task context thay vì từ ISR */

        osDelay(10);
    }
}

/**
 * @brief Khởi tạo AUTOSAR Can Driver và Can Interface
 */
static void Init_CanAutosar(void)
{
    /* 1. Khởi tạo MCAL Can Driver theo cấu hình CanConfigData */
    Can_Init(&CanConfigData);

    /* 2. Khởi tạo ECU Abstraction CanIf theo cấu hình CanIf_Config */
    CanIf_Init(&CanIf_Config);

    /* 3. Đưa Can Controller sang trạng thái CAN_CS_STARTED (Start phần cứng & bật IRQ) */
    Can_SetControllerMode(CAN_CTRL_1, CAN_CS_STARTED);

    /* 4. Đưa CanIf Controller và PDU Mode sang ONLINE để cho phép nhận/phát PDU */
    CanIf_SetControllerMode(CAN_CTRL_1, CAN_CS_STARTED);
    CanIf_SetPduMode(CAN_CTRL_1, CANIF_ONLINE);
}
/**
 * @brief Hàm Callback được tầng CanIf gọi đến khi nhận đúng PDU đã cấu hình
 * @note Chạy trong ngữ cảnh ngắt (ISR) -> TUYỆT ĐỐI KHÔNG DÙNG printf ở đây!
 */
void Cluster_CanRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    if (PduInfoPtr == NULL || PduInfoPtr->SduDataPtr == NULL) return;

    if(RxPduId < PDU_DECODER_TABLE_SIZE && g_PduDecoderTable[RxPduId]!= NULL)
    {
    	g_PduDecoderTable[RxPduId](PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    }


    /* 
     * GHI CHÚ CHO BƯỚC TIẾP THEO KHI TẠO QUEUE TRONG .IOC:
     * Sau khi bạn tạo Message Queue (vd: vehicleQueueHandle) trong file .ioc:
     * BaseType_t xHigherPriorityTaskWoken = pdFALSE;
     * xQueueSendFromISR(vehicleQueueHandle, &g_VehicleData, &xHigherPriorityTaskWoken);
     * portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
     */
}
