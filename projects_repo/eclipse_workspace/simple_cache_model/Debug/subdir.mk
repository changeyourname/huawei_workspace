################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cache.cpp \
../cache_controller.cpp \
../main.cpp 

OBJS += \
./cache.o \
./cache_controller.o \
./main.o 

CPP_DEPS += \
./cache.d \
./cache_controller.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.1/include -O0 -g3 -Wall -c -fmessage-length=0 -m32 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


