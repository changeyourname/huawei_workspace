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
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
helloWorld_C \


# All Target
all: helloWorld_C secondary-outputs

# Tool invocations
helloWorld_C: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Sourcery CodeBench C Linker'
	arm-none-linux-gnueabi-gcc -Xlinker -Map="helloWorld_C.map" -mcpu=cortex-a9 -o "helloWorld_C" "@objs.rsp" "@user_objs.rsp" "@libs.rsp"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C_DEPS)$(EXECUTABLES)
	-$(RM) "/home/uzair/huawei_workspace/projects_repo/sourcery_workspace/helloWorld_C/Debug/main.o"  helloWorld_C helloWorld_C
post-build:
	-arm-none-linux-gnueabi-size "helloWorld_C"
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
