################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./lvgl/src/extra/others/monkey/lv_monkey.o 

C_DEPS += \
./lvgl/src/extra/others/monkey/lv_monkey.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/extra/others/monkey/lv_monkey.o: C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Middlewares/Third_Party/lvgl/src/extra/others/monkey/lv_monkey.c lvgl/src/extra/others/monkey/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Middlewares/Third_Party/lvgl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-extra-2f-others-2f-monkey

clean-lvgl-2f-src-2f-extra-2f-others-2f-monkey:
	-$(RM) ./lvgl/src/extra/others/monkey/lv_monkey.cyclo ./lvgl/src/extra/others/monkey/lv_monkey.d ./lvgl/src/extra/others/monkey/lv_monkey.o ./lvgl/src/extra/others/monkey/lv_monkey.su

.PHONY: clean-lvgl-2f-src-2f-extra-2f-others-2f-monkey

