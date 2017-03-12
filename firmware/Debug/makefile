################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tasks/src/subdir.mk
-include src/FreeRTOS/portable/MemMang/subdir.mk
-include src/FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include src/FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ADC.elf

# Tool invocations
ADC.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/jeremy/LPCXpresso/workspace/CMSISv2p10_LPC13Uxx/Debug" -L"/home/jeremy/LPCXpresso/workspace/LPC13Uxx_DriverLib/Debug" --specs=rdimon.specs -lc -lrdimon -Xlinker -Map="ADC.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "ADC_Debug.ld" -o "ADC.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) ADC.elf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "ADC.elf" ; arm-none-eabi-objcopy -O binary "ADC.elf" "ADC.elf" ; checksum -p LPC1317 -d "ADC.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
