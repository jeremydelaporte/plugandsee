################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM3/%.o: ../FreeRTOS/Source/portable/GCC/ARM_CM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS=CMSISv2p10_LPC13Uxx -DDEBUG -D__CODE_RED -I"/home/jeremy/LPCXpresso/workspace/ADC" -I/home/jeremy/LPCXpresso/workspace/ADC/FreeRTOS/Source/include -I/home/jeremy/LPCXpresso/workspace/ADC/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"/home/jeremy/LPCXpresso/workspace/CMSISv2p10_LPC13Uxx/inc" -I"/home/jeremy/LPCXpresso/workspace/LPC13Uxx_DriverLib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


