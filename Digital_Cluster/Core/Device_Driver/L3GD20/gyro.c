/*
 * gyro.c
 *
 *  Created on: Nov 2, 2026
 *      Author: admin
 */

#include "l3gd20.h"
#include "main.h"
extern SPI_HandleTypeDef hspi5; // Sử dụng SPI5 đã cấu hình trên CubeMX

#define L3GD20_CS_LOW()   HAL_GPIO_WritePin(L3DG20_CS_GPIO_Port, L3DG20_CS_Pin, GPIO_PIN_RESET)
#define L3GD20_CS_HIGH()  HAL_GPIO_WritePin(L3DG20_CS_GPIO_Port, L3DG20_CS_Pin, GPIO_PIN_SET)

// Khởi tạo phần cứng cơ bản (nếu SPI5 và PC1 đã init ở CubeMX thì hàm này có thể để trống)
void GYRO_IO_Init(void) {
    L3GD20_CS_HIGH(); // Đảm bảo CS ở mức cao trước khi truyền
}

// Hàm vô hiệu hóa (không bắt buộc dùng)
void GYRO_IO_DeInit(void) {
}

void GYRO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead) {
    // Bit 7 (0x80) là lệnh Read, Bit 6 (0x40) để tự động tăng địa chỉ
    ReadAddr |= 0x80;
    if (NumByteToRead > 1) {
        ReadAddr |= 0x40;
    }

    // Khai báo mảng gộp (1 byte địa chỉ + số byte data cần đọc)
    uint8_t tx_buf[10] = {0};
    uint8_t rx_buf[10] = {0};

    tx_buf[0] = ReadAddr;

    L3GD20_CS_LOW();
    // Dùng TransmitReceive ép đồng bộ xung nhịp cả 2 chiều
    HAL_SPI_TransmitReceive(&hspi5, tx_buf, rx_buf, NumByteToRead + 1, 100);
    L3GD20_CS_HIGH();

    // Copy data thực tế (bỏ qua byte đầu tiên vì đó là lúc gửi địa chỉ)
    for(uint16_t i = 0; i < NumByteToRead; i++) {
        pBuffer[i] = rx_buf[i + 1];
    }
    for(volatile int i = 0; i < 50; i++);
}

void GYRO_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
    // Nếu ghi nhiều byte, bật cờ tự động tăng địa chỉ
    if (NumByteToWrite > 1) {
        WriteAddr |= 0x40;
    }

    uint8_t tx_buf[10] = {0};
    uint8_t rx_buf[10] = {0};

    tx_buf[0] = WriteAddr;
    for(uint16_t i = 0; i < NumByteToWrite; i++) {
        tx_buf[i + 1] = pBuffer[i];
    }

    L3GD20_CS_LOW();
    HAL_SPI_TransmitReceive(&hspi5, tx_buf, rx_buf, NumByteToWrite + 1, 100);
    L3GD20_CS_HIGH();
    for(volatile int i = 0; i < 50; i++);
}
