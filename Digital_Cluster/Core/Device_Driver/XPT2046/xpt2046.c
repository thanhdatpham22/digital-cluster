#include "../Device_Driver/XPT2046/xpt2046.h"

/**
 * Init the moduel
 */
SPI_HandleTypeDef* spiPort;
TouchScreen_CoordinatesRaw ts_CoordinatesRaw;
TouchScreen_Coordinates ts_Coordinates;
TouchScreen_OrientationTypeDef ts_Orientation;
TouchScreen_Size ts_Size;
TouchScreen_ControlByte ts_ControlByte;
GPIO_TypeDef* ts_Cs_Port;
GPIO_TypeDef* ts_Penirq_Port;
uint16_t ts_Cs_Pin;
uint16_t ts_Penirq_Pin;
uint8_t command;
void xpt2046_init()
{
	ts_ControlByte.bitMode = XPT2046_12BIT_MODE;
	ts_ControlByte.powerMode = XPT2046_POWER_DOWN;
	ts_ControlByte.reference = XPT2046_DFR_MODE;
	ts_ControlByte.channel = XPT2046_DFR_X; //by default
	ts_ControlByte.startBit = XPT2046_START;
	ts_Orientation = XPT2046_ORIENTATION_LANDSCAPE;
	ts_Size.width = XPT2046_WIDTH;
	ts_Size.height = XPT2046_HEIGHT;
	ts_Cs_Pin = XPT2046_CS_Pin;
	ts_Cs_Port = XPT2046_CS_Port;
	ts_Penirq_Pin = XPT2046_PENIRQ_Pin;
	ts_Penirq_Port = XPT2046_PENIRQ_Port;
	command = ts_ControlByte.bitMode |  ts_ControlByte.powerMode |ts_ControlByte.reference |ts_ControlByte.channel |ts_ControlByte.startBit;
	xpt2046_unselect();
}


void xpt2046_orientation(TouchScreen_OrientationTypeDef orientation_)
{
	ts_Orientation = orientation_;
}

void xpt2046_bit_mode(uint8_t b)
{
	ts_ControlByte.bitMode = b;
}
void xpt2046_set_size(uint16_t w, uint16_t h)
{
	ts_Size.width = w;
	ts_Size.height = h;
}

void xpt2046_cs(GPIO_TypeDef* cs_port, uint16_t cs_pin)
{
	ts_Cs_Port = cs_port;
	ts_Cs_Pin = cs_pin;
}

void xpt2046_penirq(GPIO_TypeDef* penirq_port, uint16_t penirq_pin)
{
	ts_Penirq_Port = penirq_port;
	ts_Penirq_Pin = penirq_pin;
}

uint16_t xpt2046_zthreshold()
{
	if(ts_ControlByte.bitMode == XPT2046_8BIT_MODE)
	{
		return Z_THRESHOLD_08BIT;
	}else
	{
		return Z_THRESHOLD_12BIT;
	}
}
void xpt2046_select()
{
	HAL_GPIO_WritePin(ts_Cs_Port,ts_Cs_Pin,GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(XPT2046_CS_Port,XPT2046_CS_Pin,GPIO_PIN_RESET);
}

void xpt2046_unselect()
{
	HAL_GPIO_WritePin(ts_Cs_Port,ts_Cs_Pin,GPIO_PIN_SET);
	//HAL_GPIO_WritePin(XPT2046_CS_Port,XPT2046_CS_Pin,GPIO_PIN_SET);
}

uint8_t xpt2046_interrupt()
{
	return HAL_GPIO_ReadPin(ts_Penirq_Port,ts_Penirq_Pin) == GPIO_PIN_RESET; //Means touchScreen was pressed
}

uint8_t xpt2046_pressed()
{
	if(xpt2046_interruptions_activated())
	{
		return xpt2046_interrupt();
	}else
	{
		uint16_t zt =  xpt2046_zthreshold();
		return (ts_CoordinatesRaw.z1 > zt );
	}
}

uint8_t xpt2046_interruptions_activated()
{
	return (ts_ControlByte.powerMode == XPT2046_POWER_DOWN || ts_ControlByte.powerMode == XPT2046_REFERENCE_ON_ADC_OFF);
}
/**
 * Generate control byte
 */
void xpt2046_control_byte_update()
{
	command =  ts_ControlByte.startBit |  ts_ControlByte.channel | ts_ControlByte.bitMode | ts_ControlByte.reference | ts_ControlByte.powerMode  ;
}

static uint16_t xpt2046_read_channel(uint8_t cmd)
{
    uint8_t tx[3] = {cmd, 0x00, 0x00};
    uint8_t rx[3] = {0x00, 0x00, 0x00};

    // 1. Kéo CS xuống LOW để bắt đầu giao tiếp
    xpt2046_select();

    // 2. Truyền 1 byte lệnh + phát clock nhận 2 byte dữ liệu liên tục
    HAL_SPI_TransmitReceive(spiPort, tx, rx, 3, 100);

    // 3. Kéo CS lên HIGH ngay lập tức để reset chu kỳ SAR ADC của chip
    xpt2046_unselect();

    // 4. Ghép 12-bit dữ liệu (nằm từ bit 14 xuống bit 3 của 2 byte nhận về sau lệnh)
    uint16_t raw = ((uint16_t)rx[1] << 8) | rx[2];
    raw >>= 3;
    return (raw & 0x0FFF);
}
/**
 * Return max value depending on bit mode.
 */
uint16_t xpt2046_max_measurement(){
	if(ts_ControlByte.bitMode == XPT2046_8BIT_MODE)
	{
		return 120; //This must be calibrated
	}else
	{
		return 1900; // this value must be calibrated on your on touch screen
	}
}
static int32_t map_val(int32_t val, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
    if (in_max == in_min) return out_min;
    int32_t result = (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

    // Giới hạn không cho vượt ra ngoài khung màn hình
    if (out_min < out_max) {
        if (result < out_min) result = out_min;
        if (result > out_max) result = out_max;
    } else {
        if (result < out_max) result = out_max;
        if (result > out_min) result = out_min;
    }
    return result;
}
/**
 * Comapre Coordinates using integers and TouchScreen_Coordinates
 */
uint8_t xpt2046_compare_cords(uint16_t x, uint16_t y , uint16_t z, TouchScreen_Coordinates tsc)
{
	return 0;
}

/**
 * Comapre two TouchScreen_Coordinates
 */
uint8_t xtp_compare_tsc(TouchScreen_Coordinates c, TouchScreen_Coordinates tcs)
{
	return 0;
}
/**
 *  Set internal SPI to user defined SPI port
 */
void xpt2046_spi(SPI_HandleTypeDef* spi)
{
	spiPort =  spi;
}


/**
 * Set Size of Touch screen
 */

void xtp2046_set_size(uint16_t w, uint16_t h)
{
	ts_Size.width = w;
	ts_Size.height = h;
}


/**
 * Update X,Y,Z values of touchScreen
 */
void xpt2046_update(void)
{
    // Kiểm tra ngắt cảm ứng nếu được kích hoạt
    if (xpt2046_interruptions_activated())
    {
        if (!xpt2046_interrupt())
        {
            return;
        }
    }

    uint32_t x_avg = 0, y_avg = 0, z1_avg = 0, z2_avg = 0;

    // Đọc bỏ 1 mẫu đầu tiên để ổn định điện áp trên màng cảm ứng
    xpt2046_read_channel(XPT2046_START | XPT2046_DFR_X | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);
    xpt2046_read_channel(XPT2046_START | XPT2046_DFR_Y | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);

    for (int i = 0; i < AVERAGE_POINTS; i++)
    {
        // Đọc trục X (0xD0)
        x_avg += xpt2046_read_channel(XPT2046_START | XPT2046_DFR_X | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);

        // Đọc trục Y (0x90)
        y_avg += xpt2046_read_channel(XPT2046_START | XPT2046_DFR_Y | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);

        // Đọc Z1 (0xB0) và Z2 (0xC0) để kiểm tra áp lực chạm
        z1_avg += xpt2046_read_channel(XPT2046_START | XPT2046_DFR_Z1 | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);
        z2_avg += xpt2046_read_channel(XPT2046_START | XPT2046_DFR_Z2 | XPT2046_12BIT_MODE | XPT2046_DFR_MODE | XPT2046_REFERENCE_OFF_ADC_ON);
    }

    ts_CoordinatesRaw.x  = x_avg / AVERAGE_POINTS;
    ts_CoordinatesRaw.y  = y_avg / AVERAGE_POINTS;
    ts_CoordinatesRaw.z1 = z1_avg / AVERAGE_POINTS;
    ts_CoordinatesRaw.z2 = z2_avg / AVERAGE_POINTS;

    uint16_t max = xpt2046_max_measurement();
    if (max == 0) max = 4095; // Bảo vệ chống chia cho 0

    int32_t cal_x = 0;
	int32_t cal_y = 0;
    // Tính toán tọa độ tùy theo hướng hiển thị
    switch (ts_Orientation)
    {
    case XPT2046_ORIENTATION_PORTRAIT:
		cal_x = map_val(ts_CoordinatesRaw.x, TOUCH_MIN_RAW_X, TOUCH_MAX_RAW_X, 0, ts_Size.width);
		cal_y = map_val(ts_CoordinatesRaw.y, TOUCH_MIN_RAW_Y, TOUCH_MAX_RAW_Y, 0, ts_Size.height);
		break;

	case XPT2046_ORIENTATION_LANDSCAPE:
		// Với Landscape: X lấy theo Y_raw và Y lấy theo X_raw
		cal_x = map_val(ts_CoordinatesRaw.y, TOUCH_MIN_RAW_Y, TOUCH_MAX_RAW_Y, 0, ts_Size.width);
		cal_y = map_val(ts_CoordinatesRaw.x, TOUCH_MAX_RAW_X, TOUCH_MIN_RAW_X, 0, ts_Size.height);
		break;

	case XPT2046_ORIENTATION_PORTRAIT_MIRROR:
		cal_x = map_val(ts_CoordinatesRaw.x, TOUCH_MAX_RAW_X, TOUCH_MIN_RAW_X, 0, ts_Size.width);
		cal_y = map_val(ts_CoordinatesRaw.y, TOUCH_MAX_RAW_Y, TOUCH_MIN_RAW_Y, 0, ts_Size.height);
		break;

	case XPT2046_ORIENTATION_LANDSCAPE_MIRROR:
		cal_x = map_val(ts_CoordinatesRaw.y, TOUCH_MAX_RAW_Y, TOUCH_MIN_RAW_Y, 0, ts_Size.width);
		cal_y = map_val(ts_CoordinatesRaw.x, TOUCH_MIN_RAW_X, TOUCH_MAX_RAW_X, 0, ts_Size.height);
		break;
	default:
		break;
    }
    ts_Coordinates.x = (uint16_t)cal_x;
	ts_Coordinates.y = (uint16_t)cal_y;
	ts_Coordinates.z = ts_CoordinatesRaw.z1;
}
//void xpt2046_update(){
//	xpt2046_select();
//
//	if(xpt2046_interruptions_activated())
//	{
//		/* this means Interrupt pin was enabled*/
//		if(!xpt2046_interrupt())
//		{
//			return;
//		}
//
//
//	}
//
//	uint8_t zeros[2] = { 0x00,0x00};
//	uint32_t x_avg = 0, y_avg = 0,z1_avg=0,z2_avg=0;
//
//	for(int i = 0; i < AVERAGE_POINTS; i++)
//	{
//		ts_ControlByte.channel = XPT2046_DFR_X;
//		xpt2046_control_byte_update();
//
//		uint8_t receiveByteX[2] = {0x00,0x00};
//
//		HAL_SPI_Transmit(spiPort,&command,sizeof(command),HAL_MAX_DELAY);
//		HAL_SPI_TransmitReceive(spiPort,(uint8_t*)zeros,receiveByteX,sizeof(receiveByteX),HAL_MAX_DELAY);
//
//
//		ts_ControlByte.channel = XPT2046_DFR_Y;
//		xpt2046_control_byte_update();
//
//		uint8_t receiveByteY[2] = {0x00,0x00};
//		HAL_SPI_Transmit(spiPort,&command,sizeof(command),HAL_MAX_DELAY);
//		HAL_SPI_TransmitReceive(spiPort,(uint8_t*)zeros,receiveByteY,sizeof(receiveByteY),HAL_MAX_DELAY);
//		for (volatile int i = 0; i < 50; i++);
//
//		ts_ControlByte.channel = XPT2046_DFR_Z1;
//		xpt2046_control_byte_update();
//		uint8_t receiveByteZ1[2] = {0x00,0x00};
//
//		HAL_SPI_Transmit(spiPort,&command,sizeof(command),HAL_MAX_DELAY);
//		HAL_SPI_TransmitReceive(spiPort,(uint8_t*)zeros,receiveByteZ1,sizeof(receiveByteZ1),HAL_MAX_DELAY);
//		for (volatile int i = 0; i < 50; i++);
//
//		ts_ControlByte.channel = XPT2046_DFR_Z2;
//		xpt2046_control_byte_update();
//		uint8_t receiveByteZ2[2] = {0x00,0x00};
//
//		HAL_SPI_Transmit(spiPort,&command,sizeof(command),HAL_MAX_DELAY);
//		HAL_SPI_TransmitReceive(spiPort,(uint8_t*)zeros,receiveByteZ2,sizeof(receiveByteZ2),HAL_MAX_DELAY);
//		for (volatile int i = 0; i < 50; i++);
//		if(ts_ControlByte.bitMode == XPT2046_12BIT_MODE)
//		{
//			x_avg+= 	(receiveByteX[1] 	<< 4) | (receiveByteX[0] 	>> 4);
//			y_avg+= 	(receiveByteY[1] 	<< 4) | (receiveByteY[0] 	>> 4);
//			z1_avg+= 	(receiveByteZ1[1] 	<< 4) | (receiveByteZ1[0] 	>> 4);
//			z2_avg+= 	(receiveByteZ2[1] 	<< 4) | (receiveByteZ2[0] 	>> 4);
//		}else
//		{
//			x_avg+= 	(receiveByteX[1]);
//			y_avg+= 	(receiveByteY[1]) ;
//			z1_avg+= 	(receiveByteZ1[1]);
//			z2_avg+= 	(receiveByteZ2[1]);
//		}
//
//	}
//
//	ts_CoordinatesRaw.x = x_avg/AVERAGE_POINTS;
//	ts_CoordinatesRaw.y = y_avg/AVERAGE_POINTS;
//	ts_CoordinatesRaw.z1 = z1_avg/AVERAGE_POINTS;
//	ts_CoordinatesRaw.z2 = z2_avg/AVERAGE_POINTS;
//	uint16_t max = xpt2046_max_measurement();
//	/* Consider (0,0) as the top left point of the screen */
//	switch(ts_Orientation)
//	{
//		case XPT2046_ORIENTATION_PORTRAIT:
//		{
//			ts_Coordinates.x = (ts_Size.width * (max - ts_CoordinatesRaw.x))/max - XPT2046_X_OFFSET;
//			ts_Coordinates.y = (ts_Size.height * (ts_CoordinatesRaw.y))/max - XPT2046_Y_OFFSET;
//			ts_Coordinates.z = ts_CoordinatesRaw.z1;
//			break;
//		}
//		case XPT2046_ORIENTATION_LANDSCAPE:
//		{
//			ts_Coordinates.x = (ts_Size.width * (max - ts_CoordinatesRaw.y))/max - XPT2046_Y_OFFSET;
//			ts_Coordinates.y = (ts_Size.height * (ts_CoordinatesRaw.x))/max - XPT2046_X_OFFSET;
//			ts_Coordinates.z = ts_CoordinatesRaw.z1;
//			break;
//		}
//		case XPT2046_ORIENTATION_PORTRAIT_MIRROR:
//		{
//			ts_Coordinates.x = (ts_Size.width * (ts_CoordinatesRaw.x))/max - XPT2046_X_OFFSET;
//			ts_Coordinates.y = (ts_Size.height * (max - ts_CoordinatesRaw.y))/max - XPT2046_Y_OFFSET;
//			ts_Coordinates.z = ts_CoordinatesRaw.z1;
//			break;
//		}
//		case XPT2046_ORIENTATION_LANDSCAPE_MIRROR:
//		{
//			ts_Coordinates.x = (ts_Size.width *  (ts_CoordinatesRaw.y))/max - XPT2046_Y_OFFSET;
//			ts_Coordinates.y = (ts_Size.height * (max- ts_CoordinatesRaw.x))/max - XPT2046_X_OFFSET;
//			ts_Coordinates.z = ts_CoordinatesRaw.z1;
//			break;
//		}
//		default:
//		{
//			break;
//		}
//	}
//
//
//	xpt2046_unselect();
//}

/* by default return 0,0 if the screen isn't pressed*/
void xpt2046_read_position(uint16_t* x, uint16_t* y)
{
	xpt2046_update();
	if(xpt2046_pressed())
	{
		*x = ts_Coordinates.x;
		*y = ts_Coordinates.y;
	}else
	{
		*x = 0;
		*y = 0;
	}
}
