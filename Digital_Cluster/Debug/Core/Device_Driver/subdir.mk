################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Device_Driver/TouchController.c \
../Core/Device_Driver/fonts.c \
../Core/Device_Driver/lvgl_port_disp.c 

OBJS += \
./Core/Device_Driver/TouchController.o \
./Core/Device_Driver/fonts.o \
./Core/Device_Driver/lvgl_port_disp.o 

C_DEPS += \
./Core/Device_Driver/TouchController.d \
./Core/Device_Driver/fonts.d \
./Core/Device_Driver/lvgl_port_disp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Device_Driver/%.o Core/Device_Driver/%.su Core/Device_Driver/%.cyclo: ../Core/Device_Driver/%.c Core/Device_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Device_Driver

clean-Core-2f-Device_Driver:
	-$(RM) ./Core/Device_Driver/TouchController.cyclo ./Core/Device_Driver/TouchController.d ./Core/Device_Driver/TouchController.o ./Core/Device_Driver/TouchController.su ./Core/Device_Driver/fonts.cyclo ./Core/Device_Driver/fonts.d ./Core/Device_Driver/fonts.o ./Core/Device_Driver/fonts.su ./Core/Device_Driver/lvgl_port_disp.cyclo ./Core/Device_Driver/lvgl_port_disp.d ./Core/Device_Driver/lvgl_port_disp.o ./Core/Device_Driver/lvgl_port_disp.su

.PHONY: clean-Core-2f-Device_Driver

