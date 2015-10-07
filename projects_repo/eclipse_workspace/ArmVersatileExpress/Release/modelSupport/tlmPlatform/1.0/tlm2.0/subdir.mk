################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.cpp 

OBJS += \
./modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.o 

CPP_DEPS += \
./modelSupport/tlmPlatform/1.0/tlm2.0/tlmPlatform.d 


# Each subdirectory must supply rules for building sources it contributes
modelSupport/tlmPlatform/1.0/tlm2.0/%.o: ../modelSupport/tlmPlatform/1.0/tlm2.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


