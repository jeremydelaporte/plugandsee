################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Serial.c \
../src/clkconfig.c \
../src/cr_startup_lpc13u.c \
../src/gpio.c \
../src/nmi.c \
../src/timer16.c \
../src/timer32.c \
../src/uart.c 

OBJS += \
./src/Serial.o \
./src/clkconfig.o \
./src/cr_startup_lpc13u.o \
./src/gpio.o \
./src/nmi.o \
./src/timer16.o \
./src/timer32.o \
./src/uart.o 

C_DEPS += \
./src/Serial.d \
./src/clkconfig.d \
./src/cr_startup_lpc13u.d \
./src/gpio.d \
./src/nmi.d \
./src/timer16.d \
./src/timer32.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPC13Uxx_DriverLib -I"/home/jeremy/LPCXpresso/workspace/LPC13Uxx_DriverLib/inc" -I"/home/jeremy/LPCXpresso/workspace/CMSISv2p10_LPC13Uxx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


