################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
basic_mem_write_read_with_timing.hex \

SECONDARY_SIZE += \
basic_mem_write_read_with_timing.siz \


# All Target
all: basic_mem_write_read_with_timing.elf secondary-outputs

# Tool invocations
basic_mem_write_read_with_timing.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-linux-gnueabi-gcc -mcpu=cortex-a9 -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Xlinker --gc-sections -Wl,-Map,"basic_mem_write_read_with_timing.map" -o "basic_mem_write_read_with_timing.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

basic_mem_write_read_with_timing.hex: basic_mem_write_read_with_timing.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-linux-gnueabi-objcopy -O ihex "basic_mem_write_read_with_timing.elf"  "basic_mem_write_read_with_timing.hex"
	@echo 'Finished building: $@'
	@echo ' '

basic_mem_write_read_with_timing.siz: basic_mem_write_read_with_timing.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-linux-gnueabi-size --format=berkeley "basic_mem_write_read_with_timing.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) basic_mem_write_read_with_timing.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
