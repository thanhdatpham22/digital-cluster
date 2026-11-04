################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.c \
../Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.o \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.d \
./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/draw/sw/%.o Middlewares/Third_Party/lvgl/src/draw/sw/%.su Middlewares/Third_Party/lvgl/src/draw/sw/%.cyclo: ../Middlewares/Third_Party/lvgl/src/draw/sw/%.c Middlewares/Third_Party/lvgl/src/draw/sw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-sw

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-sw:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_arc.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_blend.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_dither.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_gradient.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_img.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_layer.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_letter.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_line.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_polygon.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_rect.su ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.cyclo ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.d ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.o ./Middlewares/Third_Party/lvgl/src/draw/sw/lv_draw_sw_transform.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-sw

