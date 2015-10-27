################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cache.cpp \
../cache_controller.cpp \
../platform.cpp 

OBJS += \
./cache.o \
./cache_controller.o \
./platform.o 

CPP_DEPS += \
./cache.d \
./cache_controller.d \
./platform.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/uzair/huawei_workspace/OVPsim/setup/Imperas.20150901/ImperasLib/source -I"/home/uzair/huawei_workspace/projects_repo/eclipse_workspace/ArmVersatileExpress" -I/home/uzair/huawei_workspace/OVPsim/setup/Imperas.20150901/ImpPublic/include/host -I/usr/local/systemc-2.3.1/include -O0 -g3 -Wall -c -fmessage-length=0 -m32 -Wno-long-long -DSC_INCLUDE_DYNAMIC_PROCESSES -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


