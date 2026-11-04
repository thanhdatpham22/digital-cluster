/**
 ******************************************************************************
 * @file    ST7789_STM32_Driver.c
 * @brief   ST7789 2.4 inch TFT LCD SPI Driver implementation for STM32F429ZIT
 ******************************************************************************
 */
#include "../Device_Driver/ST7789/ST7789_STM32_Driver.h"

volatile uint16_t ST7789_LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
volatile uint16_t ST7789_LCD_WIDTH = ST7789_SCREEN_WIDTH;
volatile uint16_t ST7789_X_Start = 0;
volatile uint16_t ST7789_Y_Start = 0;
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
  /* Prevent unused argument warning.
   * NOTE: Do NOT pull LCD_CS HIGH here! CS is controlled by the drawing functions
   * so multi-chunk transfers and bursts remain active on ST7789.
   */
  UNUSED(hspi);
}

static void ST7789_WaitSpiReady(void) {
  while (HAL_SPI_GetState(HSPI_INSTANCE) != HAL_SPI_STATE_READY) {
    /* spin */
  }
}

static void ST7789_SPI_Tx(uint8_t data) {
  /* Single-byte commands/data should use fast blocking SPI.
   * Setting up DMA for 1 byte has high overhead and risks deadlock.
   */
  HAL_SPI_Transmit(HSPI_INSTANCE, &data, 1, 100);
}

void ST7789_SPI_TxBuffer(uint8_t *buffer, uint16_t len)
{
  if (len <= 8)
  {
    /* Small packets (coordinates, 1 pixel) are much faster via polling */
    HAL_SPI_Transmit(HSPI_INSTANCE, buffer, len, 100);
  } else {
    /* Large buffers (images, fill bursts) use DMA */
    ST7789_WaitSpiReady();
    if (HAL_SPI_Transmit_DMA(HSPI_INSTANCE, buffer, len) == HAL_OK) {
      ST7789_WaitSpiReady();
    } else {
      /* Fallback to polling if DMA is busy or returns error */
      HAL_SPI_Transmit(HSPI_INSTANCE, buffer, len, 1000);
    }
  }
}

void ST7789_Select(void) {
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}

void ST7789_Unselect(void) {
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void ST7789_WriteCommand(uint8_t cmd) {
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET); // Command mode
  ST7789_Select();
  ST7789_SPI_Tx(cmd);
  ST7789_Unselect();
}

void ST7789_WriteData(uint8_t data) {
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET); // Data mode
  ST7789_Select();
  ST7789_SPI_Tx(data);
  ST7789_Unselect();
}

void ST7789_WriteBuffer(uint8_t *buffer, uint16_t len) {
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET); // Data mode
  ST7789_Select();
  ST7789_SPI_TxBuffer(buffer, len);
  ST7789_Unselect();
}

void ST7789_Reset(void) {
  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
  HAL_Delay(120);
}

void ST7789_Enable(void) {
  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

/**
 * @brief Initialize ST7789 LCD Controller according to official datasheet
 */
void ST7789_Init(void) {
  ST7789_Enable();
  ST7789_Reset();

  // 1. Software Reset (SWRESET 01h)
  ST7789_WriteCommand(0x01);
  HAL_Delay(150);

  // 2. Sleep Out (SLPOUT 11h)
  ST7789_WriteCommand(0x11);
  HAL_Delay(120); // Required delay for internal power booster stabilization

  // 3. Pixel Format (COLMOD 3Ah)
  // 0x55 = 16-bit/pixel (RGB565) for both RGB and MCU interfaces
  ST7789_WriteCommand(0x3A);
  ST7789_WriteData(0x55);

  // 4. Memory Data Access Control (MADCTL 36h)
  ST7789_SetRotation(SCREEN_VERTICAL_1);

  // 5. Porch Control (PORCTRL B2h)
  // BPA=0x0C, FPA=0x0C, PSEN=0x00, BPB/FPB=0x33, BPC/FPC=0x33
  ST7789_WriteCommand(0xB2);
  ST7789_WriteData(0x0C);
  ST7789_WriteData(0x0C);
  ST7789_WriteData(0x00);
  ST7789_WriteData(0x33);
  ST7789_WriteData(0x33);

  // 6. Gate Control (GCTRL B7h)
  // 0x35: VGH = 13.26V, VGL = -10.43V
  ST7789_WriteCommand(0xB7);
  ST7789_WriteData(0x35);

  // 7. VCOM Setting (VCOMS BBh)
  // 0x19: 0.725V (Standard value for flicker-free ST7789)
  ST7789_WriteCommand(0xBB);
  ST7789_WriteData(0x19);

  // 8. LCM Control (LCMCTRL C0h)
  // 0x2C: Default LCM control with no XOR inversion overrides
  ST7789_WriteCommand(0xC0);
  ST7789_WriteData(0x2C);

  // 9. VDV and VRH Command Enable (VDVVRHEN C2h)
  // 0x01: CMDEN=1 (register values controlled by commands)
  ST7789_WriteCommand(0xC2);
  ST7789_WriteData(0x01);

  // 10. VRH Set (VRHS C3h)
  // 0x12: 4.45V
  ST7789_WriteCommand(0xC3);
  ST7789_WriteData(0x12);

  // 11. VDV Set (VDVS C4h)
  // 0x20: 0V
  ST7789_WriteCommand(0xC4);
  ST7789_WriteData(0x20);

  // 12. Frame Rate Control in Normal Mode (FRCTRL2 C6h)
  // 0x0F: 60Hz
  ST7789_WriteCommand(0xC6);
  ST7789_WriteData(0x0F);

  // 13. Power Control 1 (PWCTRL1 D0h)
  // 0xA4, 0xA1: AVDD=6.8V, AVCL=-4.8V, VDS=2.3V
  ST7789_WriteCommand(0xD0);
  ST7789_WriteData(0xA4);
  ST7789_WriteData(0xA1);

  // 14. Positive Voltage Gamma Control (PVGAMCTRL E0h)
  ST7789_WriteCommand(0xE0);
  ST7789_WriteData(0xD0);
  ST7789_WriteData(0x04);
  ST7789_WriteData(0x0D);
  ST7789_WriteData(0x11);
  ST7789_WriteData(0x13);
  ST7789_WriteData(0x2B);
  ST7789_WriteData(0x3F);
  ST7789_WriteData(0x54);
  ST7789_WriteData(0x4C);
  ST7789_WriteData(0x18);
  ST7789_WriteData(0x0D);
  ST7789_WriteData(0x0B);
  ST7789_WriteData(0x1F);
  ST7789_WriteData(0x23);

  // 15. Negative Voltage Gamma Control (NVGAMCTRL E1h)
  ST7789_WriteCommand(0xE1);
  ST7789_WriteData(0xD0);
  ST7789_WriteData(0x04);
  ST7789_WriteData(0x0C);
  ST7789_WriteData(0x11);
  ST7789_WriteData(0x13);
  ST7789_WriteData(0x2C);
  ST7789_WriteData(0x3F);
  ST7789_WriteData(0x44);
  ST7789_WriteData(0x51);
  ST7789_WriteData(0x2F);
  ST7789_WriteData(0x1F);
  ST7789_WriteData(0x1F);
  ST7789_WriteData(0x20);
  ST7789_WriteData(0x23);

  // 16. Display Inversion On (INVON 21h)
  // ST7789 IPS displays require inversion ON. Without this, colors are
  // inverted!
  ST7789_WriteCommand(0x20);

  // 17. Display On (DISPON 29h)
  ST7789_WriteCommand(0x29);
  HAL_Delay(50);
}

/**
 * @brief Configure screen rotation and coordinate mapping
 */
void ST7789_SetRotation(uint8_t rotation) {
  ST7789_WriteCommand(0x36); // MADCTL
  HAL_Delay(1);

  switch (rotation) {
  case SCREEN_VERTICAL_1: // Portrait 0 deg
    ST7789_WriteData(0x00 | ST7789_COLOR_ORDER);
    ST7789_LCD_WIDTH = ST7789_TFTWIDTH;
    ST7789_LCD_HEIGHT = ST7789_TFTHEIGHT;
#if (ST7789_TFTHEIGHT == 240 && ST7789_TFTWIDTH == 240)
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#else
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#endif
    break;

  case SCREEN_HORIZONTAL_1: // Landscape 90 deg
    ST7789_WriteData(ST7789_MADCTL_MX | ST7789_MADCTL_MV |
                     ST7789_COLOR_ORDER); // 0x60
    ST7789_LCD_WIDTH = ST7789_TFTHEIGHT;
    ST7789_LCD_HEIGHT = ST7789_TFTWIDTH;
#if (ST7789_TFTHEIGHT == 240 && ST7789_TFTWIDTH == 240)
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#else
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#endif
    break;

  case SCREEN_VERTICAL_2: // Portrait 180 deg (Inverted)
    ST7789_WriteData(ST7789_MADCTL_MX | ST7789_MADCTL_MY |
                     ST7789_COLOR_ORDER); // 0xC0
    ST7789_LCD_WIDTH = ST7789_TFTWIDTH;
    ST7789_LCD_HEIGHT = ST7789_TFTHEIGHT;
#if (ST7789_TFTHEIGHT == 240 && ST7789_TFTWIDTH == 240)
    ST7789_X_Start = 0;
    ST7789_Y_Start = 80;
#else
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#endif
    break;

  case SCREEN_HORIZONTAL_2: // Landscape 270 deg (Inverted)
    ST7789_WriteData(ST7789_MADCTL_MY | ST7789_MADCTL_MV |
                     ST7789_COLOR_ORDER); // 0xA0
    ST7789_LCD_WIDTH = ST7789_TFTHEIGHT;
    ST7789_LCD_HEIGHT = ST7789_TFTWIDTH;
#if (ST7789_TFTHEIGHT == 240 && ST7789_TFTWIDTH == 240)
    ST7789_X_Start = 80;
    ST7789_Y_Start = 0;
#else
    ST7789_X_Start = 0;
    ST7789_Y_Start = 0;
#endif
    break;

  default:
    break;
  }
}

/**
 * @brief Set the active drawing window
 * @param x1 Start Column (inclusive)
 * @param y1 Start Row (inclusive)
 * @param x2 End Column (inclusive)
 * @param y2 End Row (inclusive)
 */
void ST7789_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  uint8_t buffer[4];

  x1 += ST7789_X_Start;
  x2 += ST7789_X_Start;
  y1 += ST7789_Y_Start;
  y2 += ST7789_Y_Start;

  // Column Address Set (CASET 2Ah)
  buffer[0] = (uint8_t)(x1 >> 8);
  buffer[1] = (uint8_t)(x1 & 0xFF);
  buffer[2] = (uint8_t)(x2 >> 8);
  buffer[3] = (uint8_t)(x2 & 0xFF);
  ST7789_WriteCommand(0x2A);
  ST7789_WriteBuffer(buffer, 4);

  // Row Address Set (RASET 2Bh)
  buffer[0] = (uint8_t)(y1 >> 8);
  buffer[1] = (uint8_t)(y1 & 0xFF);
  buffer[2] = (uint8_t)(y2 >> 8);
  buffer[3] = (uint8_t)(y2 & 0xFF);
  ST7789_WriteCommand(0x2B);
  ST7789_WriteBuffer(buffer, 4);

  // Memory Write (RAMWR 2Ch)
  ST7789_WriteCommand(0x2C);
}

void ST7789_DrawColor(uint16_t color) {
  uint8_t buffer[2] = {(uint8_t)(color >> 8), (uint8_t)(color & 0xFF)};
  ST7789_WriteBuffer(buffer, sizeof(buffer));
}

void ST7789_DrawColorBurst(uint16_t color, uint32_t size_pixels) {
  const uint32_t totalBytes = size_pixels * 2U;
  uint32_t chunk =
      (totalBytes < ST7789_BURST_MAX_SIZE) ? totalBytes : ST7789_BURST_MAX_SIZE;
  chunk &= ~1U; // Ensure even number of bytes for 16-bit color

  static uint8_t BurstBuffer[ST7789_BURST_MAX_SIZE];
  uint8_t hi = (uint8_t)(color >> 8);
  uint8_t lo = (uint8_t)(color & 0xFF);

  for (uint32_t j = 0; j < chunk; j += 2) {
    BurstBuffer[j] = hi;
    BurstBuffer[j + 1] = lo;
  }

  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  ST7789_Select();

  uint32_t remain = totalBytes;
  while (remain > 0) {
    uint16_t n = (remain > chunk) ? (uint16_t)chunk : (uint16_t)remain;
    ST7789_SPI_TxBuffer(BurstBuffer, n);
    remain -= n;
  }

  ST7789_Unselect();
}

void ST7789_FillScreen(uint16_t color) {
  ST7789_SetAddress(0, 0, ST7789_LCD_WIDTH - 1, ST7789_LCD_HEIGHT - 1);
  ST7789_DrawColorBurst(color, (uint32_t)ST7789_LCD_WIDTH * ST7789_LCD_HEIGHT);
}

void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
  if ((x >= ST7789_LCD_WIDTH) || (y >= ST7789_LCD_HEIGHT))
    return;

  ST7789_SetAddress(x, y, x, y);
  uint8_t bufferC[2] = {(uint8_t)(color >> 8), (uint8_t)(color & 0xFF)};
  ST7789_WriteBuffer(bufferC, sizeof(bufferC));
}

void ST7789_DrawRectangle(uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height, uint16_t color) {
  if ((x >= ST7789_LCD_WIDTH) || (y >= ST7789_LCD_HEIGHT))
    return;

  if ((x + width) > ST7789_LCD_WIDTH) {
    width = ST7789_LCD_WIDTH - x;
  }

  if ((y + height) > ST7789_LCD_HEIGHT) {
    height = ST7789_LCD_HEIGHT - y;
  }

  if (width == 0 || height == 0)
    return;

  ST7789_SetAddress(x, y, x + width - 1, y + height - 1);
  ST7789_DrawColorBurst(color, (uint32_t)height * width);
}

void ST7789_DrawHLine(uint16_t x, uint16_t y, uint16_t width, uint16_t color) {
  if ((x >= ST7789_LCD_WIDTH) || (y >= ST7789_LCD_HEIGHT))
    return;

  if ((x + width) > ST7789_LCD_WIDTH) {
    width = ST7789_LCD_WIDTH - x;
  }

  if (width == 0)
    return;

  ST7789_SetAddress(x, y, x + width - 1, y);
  ST7789_DrawColorBurst(color, width);
}

void ST7789_DrawVLine(uint16_t x, uint16_t y, uint16_t height, uint16_t color) {
  if ((x >= ST7789_LCD_WIDTH) || (y >= ST7789_LCD_HEIGHT))
    return;

  if ((y + height) > ST7789_LCD_HEIGHT) {
    height = ST7789_LCD_HEIGHT - y;
  }

  if (height == 0)
    return;

  ST7789_SetAddress(x, y, x, y + height - 1);
  ST7789_DrawColorBurst(color, height);
}

void ST7789_InvertColors(uint8_t invert) {
  if (invert) {
    ST7789_WriteCommand(0x21); // INVON: Display Inversion On
  } else {
    ST7789_WriteCommand(0x20); // INVOFF: Display Inversion Off
  }
}
