################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/MemMang/heap_1.c \
../FreeRTOS/Source/portable/MemMang/heap_2.c \
../FreeRTOS/Source/portable/MemMang/heap_3.c \
../FreeRTOS/Source/portable/MemMang/heap_4.c \
../FreeRTOS/Source/portable/MemMang/heap_5.c 

OBJS += \
./FreeRTOS/Source/portable/MemMang/heap_1.o \
./FreeRTOS/Source/portable/MemMang/heap_2.o \
./FreeRTOS/Source/portable/MemMang/heap_3.o \
./FreeRTOS/Source/portable/MemMang/heap_4.o \
./FreeRTOS/Source/portable/MemMang/heap_5.o 

C_DEPS += \
./FreeRTOS/Source/portable/MemMang/heap_1.d \
./FreeRTOS/Source/portable/MemMang/heap_2.d \
./FreeRTOS/Source/portable/MemMang/heap_3.d \
./FreeRTOS/Source/portable/MemMang/heap_4.d \
./FreeRTOS/Source/portable/MemMang/heap_5.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/MemMang/%.o: ../FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS=CMSISv2p10_LPC13Uxx -DDEBUG -D__CODE_RED -I"/home/jeremy/LPCXpresso/workspace/ADC" -I/home/jeremy/LPCXpresso/workspace/ADC/FreeRTOS/Source/include -I/home/jeremy/LPCXpresso/workspace/ADC/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"/home/jeremy/LPCXpresso/workspace/CMSISv2p10_LPC13Uxx/inc" -I"/home/jeremy/LPCXpresso/workspace/LPC13Uxx_DriverLib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


