################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/widgets/lv_arc.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_bar.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_btn.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_img.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_label.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_line.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_roller.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_slider.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_switch.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_table.c \
../Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_img.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_label.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_line.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_table.o \
./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_img.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_label.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_line.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_table.d \
./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/widgets/%.o Middlewares/Third_Party/lvgl/src/widgets/%.su Middlewares/Third_Party/lvgl/src/widgets/%.cyclo: ../Middlewares/Third_Party/lvgl/src/widgets/%.c Middlewares/Third_Party/lvgl/src/widgets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-widgets

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-widgets:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_arc.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_bar.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_btn.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_btnmatrix.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_canvas.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_checkbox.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_dropdown.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_img.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_img.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_img.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_img.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_label.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_label.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_label.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_label.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_line.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_line.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_line.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_line.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_objx_templ.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_roller.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_slider.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_switch.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_table.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_table.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_table.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_table.su ./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.cyclo ./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.d ./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.o ./Middlewares/Third_Party/lvgl/src/widgets/lv_textarea.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-widgets

