################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../adctest.c \
../cr_startup_lpc13u.c 

OBJS += \
./adc.o \
./adctest.o \
./cr_startup_lpc13u.o 

C_DEPS += \
./adc.d \
./adctest.d \
./cr_startup_lpc13u.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p10_LPC13Uxx -DDEBUG -D__CODE_RED -D__NEWLIB__ -I"/home/jeremy/LPCXpresso/workspace/ADC" -I/home/jeremy/LPCXpresso/workspace/ADC/tasks/inc -I/home/jeremy/LPCXpresso/workspace/ADC/src/FreeRTOS/include -I/home/jeremy/LPCXpresso/workspace/ADC/src/FreeRTOS/portable/GCC/ARM_CM3 -I"/home/jeremy/LPCXpresso/workspace/CMSISv2p10_LPC13Uxx/inc" -I"/home/jeremy/LPCXpresso/workspace/LPC13Uxx_DriverLib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


