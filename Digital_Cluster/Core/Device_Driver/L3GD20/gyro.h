/*
 * gyro.h
 *
 *  Created on: Nov 2, 2026
 *      Author: admin
 */

#ifndef DEVICE_DRIVER_L3GD20_GYRO_H_
#define DEVICE_DRIVER_L3GD20_GYRO_H_

#include <stdint.h>

/* Cấu trúc con trỏ hàm chuẩn của ST BSP */
typedef struct
{
  void      (*Init)(uint16_t);
  void      (*DeInit)(void);
  uint8_t   (*ReadID)(void);
  void      (*Reset)(void);
  void      (*LowPower)(uint16_t);
  void      (*ConfigIT)(uint16_t);
  void      (*EnableIT)(uint8_t);
  void      (*DisableIT)(uint8_t);
  uint8_t   (*ITStatus)(uint16_t, uint16_t);
  void      (*ClearIT)(uint16_t, uint16_t);
  void      (*FilterConfig)(uint8_t);
  void      (*FilterCmd)(uint8_t);
  void      (*GetXYZ)(float *);
} GYRO_DrvTypeDef;

void    GYRO_IO_Init(void);
void    GYRO_IO_DeInit(void);
void    GYRO_IO_Write(uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
void    GYRO_IO_Read(uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);

#endif /* DEVICE_DRIVER_L3GD20_GYRO_H_ */
