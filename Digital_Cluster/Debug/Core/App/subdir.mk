################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/App/can_task.c \
../Core/App/common_task.c \
../Core/App/display_task.c \
../Core/App/log_task.c 

OBJS += \
./Core/App/can_task.o \
./Core/App/common_task.o \
./Core/App/display_task.o \
./Core/App/log_task.o 

C_DEPS += \
./Core/App/can_task.d \
./Core/App/common_task.d \
./Core/App/display_task.d \
./Core/App/log_task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/App/%.o Core/App/%.su Core/App/%.cyclo: ../Core/App/%.c Core/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-App

clean-Core-2f-App:
	-$(RM) ./Core/App/can_task.cyclo ./Core/App/can_task.d ./Core/App/can_task.o ./Core/App/can_task.su ./Core/App/common_task.cyclo ./Core/App/common_task.d ./Core/App/common_task.o ./Core/App/common_task.su ./Core/App/display_task.cyclo ./Core/App/display_task.d ./Core/App/display_task.o ./Core/App/display_task.su ./Core/App/log_task.cyclo ./Core/App/log_task.d ./Core/App/log_task.o ./Core/App/log_task.su

.PHONY: clean-Core-2f-App

