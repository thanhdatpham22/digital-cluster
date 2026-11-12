################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Device_Driver/CAN_BSW/Det/Det.c 

OBJS += \
./Core/Device_Driver/CAN_BSW/Det/Det.o 

C_DEPS += \
./Core/Device_Driver/CAN_BSW/Det/Det.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Device_Driver/CAN_BSW/Det/%.o Core/Device_Driver/CAN_BSW/Det/%.su Core/Device_Driver/CAN_BSW/Det/%.cyclo: ../Core/Device_Driver/CAN_BSW/Det/%.c Core/Device_Driver/CAN_BSW/Det/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Device_Driver-2f-CAN_BSW-2f-Det

clean-Core-2f-Device_Driver-2f-CAN_BSW-2f-Det:
	-$(RM) ./Core/Device_Driver/CAN_BSW/Det/Det.cyclo ./Core/Device_Driver/CAN_BSW/Det/Det.d ./Core/Device_Driver/CAN_BSW/Det/Det.o ./Core/Device_Driver/CAN_BSW/Det/Det.su

.PHONY: clean-Core-2f-Device_Driver-2f-CAN_BSW-2f-Det

