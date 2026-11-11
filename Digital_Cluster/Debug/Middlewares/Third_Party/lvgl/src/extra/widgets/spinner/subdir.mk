################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/%.o Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/%.su Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/%.cyclo: ../Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/%.c Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-spinner

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-spinner:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.cyclo ./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.d ./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.o ./Middlewares/Third_Party/lvgl/src/extra/widgets/spinner/lv_spinner.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-widgets-2f-spinner

