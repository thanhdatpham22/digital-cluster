################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Digital_Cluster/src/ui/images.c \
../Digital_Cluster/src/ui/screens.c \
../Digital_Cluster/src/ui/styles.c \
../Digital_Cluster/src/ui/ui.c 

OBJS += \
./Digital_Cluster/src/ui/images.o \
./Digital_Cluster/src/ui/screens.o \
./Digital_Cluster/src/ui/styles.o \
./Digital_Cluster/src/ui/ui.o 

C_DEPS += \
./Digital_Cluster/src/ui/images.d \
./Digital_Cluster/src/ui/screens.d \
./Digital_Cluster/src/ui/styles.d \
./Digital_Cluster/src/ui/ui.d 


# Each subdirectory must supply rules for building sources it contributes
Digital_Cluster/src/ui/%.o Digital_Cluster/src/ui/%.su Digital_Cluster/src/ui/%.cyclo: ../Digital_Cluster/src/ui/%.c Digital_Cluster/src/ui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/lvgl -I../Core/Device_Driver/CAN_TJA1050/Can -I../Core/Device_Driver/CAN_TJA1050/CanIf -I../Core/Device_Driver/CAN_TJA1050/config -I../Core/Device_Driver/CAN_TJA1050/Det -I../Core/Device_Driver/CAN_TJA1050/shared -I"E:/Personal_Documents/digital-cluster/Digital_Cluster/Digital_Cluster/src/ui" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Digital_Cluster-2f-src-2f-ui

clean-Digital_Cluster-2f-src-2f-ui:
	-$(RM) ./Digital_Cluster/src/ui/images.cyclo ./Digital_Cluster/src/ui/images.d ./Digital_Cluster/src/ui/images.o ./Digital_Cluster/src/ui/images.su ./Digital_Cluster/src/ui/screens.cyclo ./Digital_Cluster/src/ui/screens.d ./Digital_Cluster/src/ui/screens.o ./Digital_Cluster/src/ui/screens.su ./Digital_Cluster/src/ui/styles.cyclo ./Digital_Cluster/src/ui/styles.d ./Digital_Cluster/src/ui/styles.o ./Digital_Cluster/src/ui/styles.su ./Digital_Cluster/src/ui/ui.cyclo ./Digital_Cluster/src/ui/ui.d ./Digital_Cluster/src/ui/ui.o ./Digital_Cluster/src/ui/ui.su

.PHONY: clean-Digital_Cluster-2f-src-2f-ui

