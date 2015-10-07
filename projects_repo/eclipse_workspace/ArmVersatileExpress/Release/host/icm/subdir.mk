################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../host/icm/icmCpuManager.cpp 

OBJS += \
./host/icm/icmCpuManager.o 

CPP_DEPS += \
./host/icm/icmCpuManager.d 


# Each subdirectory must supply rules for building sources it contributes
host/icm/%.o: ../host/icm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


