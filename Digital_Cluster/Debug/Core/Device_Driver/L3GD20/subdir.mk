################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Device_Driver/L3GD20/gyro.c \
../Core/Device_Driver/L3GD20/l3gd20.c 

OBJS += \
./Core/Device_Driver/L3GD20/gyro.o \
./Core/Device_Driver/L3GD20/l3gd20.o 

C_DEPS += \
./Core/Device_Driver/L3GD20/gyro.d \
./Core/Device_Driver/L3GD20/l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Device_Driver/L3GD20/%.o Core/Device_Driver/L3GD20/%.su Core/Device_Driver/L3GD20/%.cyclo: ../Core/Device_Driver/L3GD20/%.c Core/Device_Driver/L3GD20/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Device_Driver-2f-L3GD20

clean-Core-2f-Device_Driver-2f-L3GD20:
	-$(RM) ./Core/Device_Driver/L3GD20/gyro.cyclo ./Core/Device_Driver/L3GD20/gyro.d ./Core/Device_Driver/L3GD20/gyro.o ./Core/Device_Driver/L3GD20/gyro.su ./Core/Device_Driver/L3GD20/l3gd20.cyclo ./Core/Device_Driver/L3GD20/l3gd20.d ./Core/Device_Driver/L3GD20/l3gd20.o ./Core/Device_Driver/L3GD20/l3gd20.su

.PHONY: clean-Core-2f-Device_Driver-2f-L3GD20

