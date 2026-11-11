/*
 * common_task.c
 *
 *  Created on: Nov 6, 2026
 *      Author: admin
 */

#include "common_task.h"

extern lv_obj_t * cluster_temp_label;

static void temp_meter_update_cb(lv_timer_t * timer)
{
    if (cluster_temp_label == NULL ) return;

    uint8_t temp_raw;
    // �?�?c 1 byte từ thanh ghi OUT_TEMP (0x26)[cite: 35, 41]
    GYRO_IO_Read(&temp_raw, 0x26, 1);

    // Ép kiểu v�? số nguyên có dấu 8-bit[cite: 41]
    int8_t temp_c = (int8_t)temp_raw;
//    printf("temp_c: 0%X02\r\n",temp_raw);
    // Cộng thêm offset (giả sử khoảng 40 để v�? nhiệt độ phòng chuẩn)
    int32_t display_temp = temp_c;
    // Cập nhật giá trị kim lên giao diện
    lv_label_set_text_fmt(cluster_temp_label, "%ld °C", (long)display_temp);
}
void Common_Task(void *argument)
{
	osThreadFlagsWait(INIT_FLAG_START, osFlagsWaitAny, osWaitForever);

	printf("Common task is begin\r\n");
	L3GD20_RebootCmd();
	osDelay(50);
	L3GD20_Init(L3GD20_MODE_ACTIVE | L3GD20_OUTPUT_DATARATE_1 | L3GD20_AXES_ENABLE);
	// Kiểm tra WHO_AM_I
	uint8_t who_am_i = 0;
	GYRO_IO_Read(&who_am_i, L3GD20_WHO_AM_I_ADDR, 1);
	printf("L3GD20 WHO_AM_I = 0x%02X\r\n", who_am_i);
	// Bật hoạt động L3GD20 (ghi 0x0F vào CTRL_REG1)
	uint8_t ctrl1 = 0x0F;
	GYRO_IO_Write(&ctrl1, L3GD20_CTRL_REG1_ADDR, 1);
	// �?�?c lại kiểm tra xem đã ghi thành công vào CTRL_REG1 chưa
	uint8_t check_ctrl1 = 0;
	GYRO_IO_Read(&check_ctrl1, L3GD20_CTRL_REG1_ADDR, 1);
	printf("CTRL_REG1 = 0x%02X (phai la 0x0F)\r\n", check_ctrl1);
	lv_timer_create(temp_meter_update_cb, 500, NULL);
	RTC_Driver_Init(500);

	osThreadFlagsSet(logtaskHandle, INIT_FLAG_START);
	for(;;)
	{

		osDelay(1);
	}
}
