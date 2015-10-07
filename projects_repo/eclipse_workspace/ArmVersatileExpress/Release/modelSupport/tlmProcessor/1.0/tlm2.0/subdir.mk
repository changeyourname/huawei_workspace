################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.cpp 

OBJS += \
./modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.o 

CPP_DEPS += \
./modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
modelSupport/tlmProcessor/1.0/tlm2.0/%.o: ../modelSupport/tlmProcessor/1.0/tlm2.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


