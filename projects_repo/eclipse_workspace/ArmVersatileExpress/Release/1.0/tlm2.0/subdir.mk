################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../1.0/tlm2.0/tlmMemory.cpp 

OBJS += \
./1.0/tlm2.0/tlmMemory.o 

CPP_DEPS += \
./1.0/tlm2.0/tlmMemory.d 


# Each subdirectory must supply rules for building sources it contributes
1.0/tlm2.0/%.o: ../1.0/tlm2.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


