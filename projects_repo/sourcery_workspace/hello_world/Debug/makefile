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
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
hello_world \


# All Target
all: hello_world secondary-outputs

# Tool invocations
hello_world: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Sourcery CodeBench C++ Linker'
	arm-none-linux-gnueabi-g++ -pthread -Xlinker -Map="hello_world.map" -mcpu=cortex-a9 -o "hello_world" "@objs.rsp" "@user_objs.rsp" "@libs.rsp"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS)
	-$(RM) "/home/uzair/huawei_workspace/projects_repo/sourcery_workspace/hello_world/Debug/main.o"  hello_world hello_world
post-build:
	-arm-none-linux-gnueabi-size "hello_world"
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
