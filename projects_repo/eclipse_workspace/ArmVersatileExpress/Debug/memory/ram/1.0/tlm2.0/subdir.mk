################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../memory/ram/1.0/tlm2.0/tlmMemory.cpp 

OBJS += \
./memory/ram/1.0/tlm2.0/tlmMemory.o 

CPP_DEPS += \
./memory/ram/1.0/tlm2.0/tlmMemory.d 


# Each subdirectory must supply rules for building sources it contributes
memory/ram/1.0/tlm2.0/%.o: ../memory/ram/1.0/tlm2.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/uzair/huawei_workspace/OVPsim/setup/Imperas.20150901/ImperasLib/source -I/home/uzair/huawei_workspace/OVPsim/setup/Imperas.20150901/ImpPublic/include/host -I/usr/local/systemc-2.3.1/include -O0 -g3 -Wall -c -fmessage-length=0 -m32 -Wno-long-long -DSC_INCLUDE_DYNAMIC_PROCESSES -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


