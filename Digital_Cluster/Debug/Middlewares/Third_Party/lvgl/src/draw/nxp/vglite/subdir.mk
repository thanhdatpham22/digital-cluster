################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.c \
../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.o \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.d \
./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/%.o Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/%.su Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/%.cyclo: ../Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/%.c Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_buf.su ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.cyclo ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.d ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.o ./Middlewares/Third_Party/lvgl/src/draw/nxp/vglite/lv_vglite_utils.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-vglite

