/**
  ******************************************************************************
  * @file    ST7789_STM32_Driver.h
  * @brief   ST7789 2.4 inch TFT LCD SPI Driver for STM32F429ZIT
  ******************************************************************************
  */
#ifndef ST7789_STM32_DRIVER_H
#define ST7789_STM32_DRIVER_H

#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

/* Native panel resolution (ST7789 Frame Buffer is 240x320) */
#define ST7789_TFTWIDTH         240
#define ST7789_TFTHEIGHT        320

#define ST7789_SCREEN_WIDTH     240
#define ST7789_SCREEN_HEIGHT    320

/* Dynamic dimensions managed by ST7789_SetRotation() */
extern volatile uint16_t ST7789_LCD_HEIGHT;
extern volatile uint16_t ST7789_LCD_WIDTH;
extern volatile uint16_t ST7789_X_Start;
extern volatile uint16_t ST7789_Y_Start;

/* PIN Configuration */
#define HSPI_INSTANCE           &hspi1
#define LCD_CS_PORT             GPIOB
#define LCD_CS_PIN              GPIO_PIN_10
#define LCD_DC_PORT             GPIOB
#define LCD_DC_PIN              GPIO_PIN_0
#define LCD_RST_PORT            GPIOB
#define LCD_RST_PIN             GPIO_PIN_1

#define ST7789_BURST_MAX_SIZE   512
#ifndef BURST_MAX_SIZE
#define BURST_MAX_SIZE          ST7789_BURST_MAX_SIZE
#endif

/* Color Definitions (16-bit 565 RGB) */
#ifndef BLACK
#define BLACK                   0x0000
#define NAVY                    0x000F
#define DARKGREEN               0x03E0
#define DARKCYAN                0x03EF
#define MAROON                  0x7800
#define PURPLE                  0x780F
#define OLIVE                   0x7BE0
#define LIGHTGREY               0xC618
#define DARKGREY                0x7BEF
#define BLUE                    0x001F
#define GREEN                   0x07E0
#define CYAN                    0x07FF
#define RED                     0xF800
#define MAGENTA                 0xF81F
#define YELLOW                  0xFFE0
#define WHITE                   0xFFFF
#define ORANGE                  0xFD20
#define GREENYELLOW             0xAFE5
#define PINK                    0xF81F
#endif

/* Screen Rotation IDs */
#ifndef SCREEN_VERTICAL_1
#define SCREEN_VERTICAL_1       0
#define SCREEN_HORIZONTAL_1     1
#define SCREEN_VERTICAL_2       2
#define SCREEN_HORIZONTAL_2     3
#endif

/* ST7789 MADCTL Bits (Section 9.1.28 of ST7789VI Datasheet) */
#define ST7789_MADCTL_MY        0x80    /* Bottom to top page order */
#define ST7789_MADCTL_MX        0x40    /* Right to left column order */
#define ST7789_MADCTL_MV        0x20    /* Row/Column exchange (Landscape) */
#define ST7789_MADCTL_ML        0x10    /* LCD refresh bottom to top */
#define ST7789_MADCTL_BGR       0x08    /* BGR color filter */
#define ST7789_MADCTL_RGB       0x00    /* RGB color filter */

/* Color filter mode:
 * Set to ST7789_MADCTL_RGB (0x00) for standard ST7789 panels.
 * If Red and Blue are swapped on your screen, change this to ST7789_MADCTL_BGR (0x08).
 */
#define ST7789_COLOR_ORDER      ST7789_MADCTL_RGB

/* Function Prototypes */
void ST7789_Select(void);
void ST7789_Unselect(void);
void ST7789_WriteCommand(uint8_t cmd);
void ST7789_WriteData(uint8_t data);
void ST7789_WriteBuffer(uint8_t *buffer, uint16_t len);
void ST7789_SPI_TxBuffer(uint8_t *buffer, uint16_t len);
void ST7789_Reset(void);
void ST7789_Enable(void);
void ST7789_Init(void);
void ST7789_SetRotation(uint8_t rotation);
void ST7789_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ST7789_DrawColor(uint16_t color);
void ST7789_DrawColorBurst(uint16_t color, uint32_t size_pixels);
void ST7789_FillScreen(uint16_t color);
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void ST7789_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color);
void ST7789_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color);
void ST7789_InvertColors(uint8_t invert);

#endif /* ST7789_STM32_DRIVER_H */
