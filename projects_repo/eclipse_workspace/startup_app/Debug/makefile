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
startup_app.hex \

SECONDARY_SIZE += \
startup_app.siz \


# All Target
all: startup_app.elf secondary-outputs

# Tool invocations
startup_app.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-linux-gnueabi-gcc -mcpu=cortex-a9 -marm -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -Xlinker --gc-sections -Wl,-Map,"startup_app.map" -o "startup_app.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

startup_app.hex: startup_app.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-linux-gnueabi-objcopy -O ihex "startup_app.elf"  "startup_app.hex"
	@echo 'Finished building: $@'
	@echo ' '

startup_app.siz: startup_app.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-linux-gnueabi-size --format=berkeley "startup_app.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) startup_app.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
