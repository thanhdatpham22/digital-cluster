/*
 * fmc_driver.c
 *
 *  Created on: Nov 12, 2026
 *      Author: admin
 */
#include "fmc_driver.h"

void FMC_Config(void)
{
	FMC_SDRAM_CommandTypeDef Command;
	HAL_StatusTypeDef status;
	__IO uint32_t tmpmrd =0;
   /* Step 1:  Configure a clock configuration enable Command */
   Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
   Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
   Command.AutoRefreshNumber = 1;
   Command.ModeRegisterDefinition = 0;

   /* Send the Command */
   status = HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 2: Insert 100 us minimum delay */
   /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
   HAL_Delay(1);

   /* Step 3: Configure a PALL (precharge all) Command */
   Command.CommandMode = FMC_SDRAM_CMD_PALL;
   Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
   Command.AutoRefreshNumber = 1;
   Command.ModeRegisterDefinition = 0;

   /* Send the Command */
   status = HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 4 : Configure a Auto-Refresh Command */
   Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
   Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
   Command.AutoRefreshNumber = 8;
   Command.ModeRegisterDefinition = 0;

   /* Send the Command */
   status = HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 5: Program the external memory mode register */
   tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
					 SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
					 SDRAM_MODEREG_CAS_LATENCY_2           |
					 SDRAM_MODEREG_OPERATING_MODE_STANDARD |
					 SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

   Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
   Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
   Command.AutoRefreshNumber = 1;
   Command.ModeRegisterDefinition = tmpmrd;

   /* Send the Command */
   status = HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 6: Set the refresh rate counter - refer to section SDRAM refresh timer register in RM0455 */
	/* Set the device refresh rate
	* COUNT = [(SDRAM self refresh time / number of row) x  SDRAM CLK] – 20
			= [(64ms/4096) * 90MHz] - 20 = 1406.25 - 20 ~ 1386 = 0x56A */
//   hsdram1.Instance->SDRTR |= ((uint32_t)((1292)<< 1));
   status =  HAL_SDRAM_ProgramRefreshRate(&hsdram1, 0x56A);
}
