################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.c \
../Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.c 

OBJS += \
./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.o \
./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.o 

C_DEPS += \
./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.d \
./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/%.o Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/%.su Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/%.cyclo: ../Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/%.c Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I"C:/Users/admin/STM32CubeIDE/workspace_1.16.0/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-libs-2f-sjpg

clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-libs-2f-sjpg:
	-$(RM) ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.cyclo ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.d ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.o ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/lv_sjpg.su ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.cyclo ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.d ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.o ./Middlewares/Third_Party/lvgl/src/extra/libs/sjpg/tjpgd.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lvgl-2f-src-2f-extra-2f-libs-2f-sjpg

