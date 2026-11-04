/**
  ******************************************************************************
  * @file    ST7789_GFX.c
  * @brief   Graphics library for ST7789 LCD
  ******************************************************************************
  */
#include "../Device_Driver/ST7789/ST7789_STM32_Driver.h"
#include "../Device_Driver/ST7789/ST7789_GFX.h"


/* Imprecise small delay */
__STATIC_INLINE void DelayUs(volatile uint32_t us)
{
	us *= (SystemCoreClock / 1000000);
	while (us--);
}

void ST7789_DrawHollowCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color)
{
	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int err = dx - (radius << 1);

	while (x >= y)
	{
		ST7789_DrawPixel(X + x, Y + y, color);
		ST7789_DrawPixel(X + y, Y + x, color);
		ST7789_DrawPixel(X - y, Y + x, color);
		ST7789_DrawPixel(X - x, Y + y, color);
		ST7789_DrawPixel(X - x, Y - y, color);
		ST7789_DrawPixel(X - y, Y - x, color);
		ST7789_DrawPixel(X + y, Y - x, color);
		ST7789_DrawPixel(X + x, Y - y, color);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}

		if (err > 0)
		{
			x--;
			dx += 2;
			err += (-radius << 1) + dx;
		}
	}
}

void ST7789_DrawFilledCircle(uint16_t X, uint16_t Y, uint16_t radius, uint16_t color)
{
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;

	while (x >= y)
	{
		for (int i = X - x; i <= X + x; i++)
		{
			ST7789_DrawPixel(i, Y + y, color);
			ST7789_DrawPixel(i, Y - y, color);
		}

		for (int i = X - y; i <= X + y; i++)
		{
			ST7789_DrawPixel(i, Y + x, color);
			ST7789_DrawPixel(i, Y - x, color);
		}

		y++;
		radiusError += yChange;
		yChange += 2;

		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void ST7789_DrawHollowRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color)
{
	uint16_t x = (X0 < X1) ? X0 : X1;
	uint16_t y = (Y0 < Y1) ? Y0 : Y1;
	uint16_t w = (X0 < X1) ? (X1 - X0 + 1) : (X0 - X1 + 1);
	uint16_t h = (Y0 < Y1) ? (Y1 - Y0 + 1) : (Y0 - Y1 + 1);

	ST7789_DrawHLine(x, y, w, color);
	ST7789_DrawHLine(x, y + h - 1, w, color);
	ST7789_DrawVLine(x, y, h, color);
	ST7789_DrawVLine(x + w - 1, y, h, color);
}

void ST7789_DrawFilledRectangleCoord(uint16_t X0, uint16_t Y0, uint16_t X1, uint16_t Y1, uint16_t color)
{
	uint16_t x = (X0 < X1) ? X0 : X1;
	uint16_t y = (Y0 < Y1) ? Y0 : Y1;
	uint16_t w = (X0 < X1) ? (X1 - X0 + 1) : (X0 - X1 + 1);
	uint16_t h = (Y0 < Y1) ? (Y1 - Y0 + 1) : (Y0 - Y1 + 1);

	ST7789_DrawRectangle(x, y, w, h, color);
}

void ST7789_DrawChar(char ch, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	if ((ch < 31) || (ch > 127)) return;

	uint8_t fOffset, fWidth, fHeight, fBPL;
	uint8_t *tempChar;

	fOffset = font[0];
	fWidth  = font[1];
	fHeight = font[2];
	fBPL    = font[3];

	tempChar = (uint8_t*)&font[((ch - 0x20) * fOffset) + 4];

	/* Clear character background cell */
	ST7789_DrawRectangle(X, Y, fWidth, fHeight, bgcolor);

	for (int j = 0; j < fHeight; j++)
	{
		for (int i = 0; i < fWidth; i++)
		{
			uint8_t z = tempChar[fBPL * i + ((j & 0xF8) >> 3) + 1];
			uint8_t b = 1 << (j & 0x07);
			if ((z & b) != 0x00)
			{
				ST7789_DrawPixel(X + i, Y + j, color);
			}
		}
	}
}

void ST7789_DrawText(const char* str, const uint8_t font[], uint16_t X, uint16_t Y, uint16_t color, uint16_t bgcolor)
{
	uint8_t charWidth;
	uint8_t fOffset = font[0];
	uint8_t fWidth  = font[1];

	while (*str)
	{
		ST7789_DrawChar(*str, font, X, Y, color, bgcolor);

		uint8_t *tempChar = (uint8_t*)&font[((*str - 0x20) * fOffset) + 4];
		charWidth = tempChar[0];

		if (charWidth + 2 < fWidth)
		{
			X += (charWidth + 2);
		}
		else
		{
			X += fWidth;
		}

		str++;
	}
}

void ST7789_DrawImage(const uint8_t* image, uint8_t orientation)
{
	ST7789_SetRotation(orientation);
	ST7789_SetAddress(0, 0, ST7789_LCD_WIDTH - 1, ST7789_LCD_HEIGHT - 1);

	uint32_t totalBytes = (uint32_t)ST7789_LCD_WIDTH * ST7789_LCD_HEIGHT * 2U;
	uint32_t offset = 0;

	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	ST7789_Select();

	while (offset < totalBytes)
	{
		uint16_t chunkSize = (totalBytes - offset > ST7789_BURST_MAX_SIZE) ? ST7789_BURST_MAX_SIZE : (uint16_t)(totalBytes - offset);
		ST7789_SPI_TxBuffer((uint8_t*)(image + offset), chunkSize);
		offset += chunkSize;
	}

	ST7789_Unselect();
}
