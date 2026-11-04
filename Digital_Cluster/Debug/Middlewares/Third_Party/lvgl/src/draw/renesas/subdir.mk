################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.c \
../Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.o \
./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.d \
./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/draw/renesas/%.o Middlewares/Third_Party/lvgl/src/draw/renesas/%.su Middlewares/Third_Party/lvgl/src/draw/renesas/%.cyclo: ../Middlewares/Third_Party/lvgl/src/draw/renesas/%.c Middlewares/Third_Party/lvgl/src/draw/renesas/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-renesas

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-renesas:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.cyclo ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.d ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.o ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_draw_label.su ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.cyclo ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.d ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.o ./Middlewares/Third_Party/lvgl/src/draw/renesas/lv_gpu_d2_ra6m3.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-renesas

