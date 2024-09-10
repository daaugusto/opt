################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../base/Exception.cpp \
../base/Individual.cpp \
../base/Input.cpp \
../base/Tools.cpp 

OBJS += \
./base/Exception.o \
./base/Individual.o \
./base/Input.o \
./base/Tools.o 

CPP_DEPS += \
./base/Exception.d \
./base/Individual.d \
./base/Input.d \
./base/Tools.d 


# Each subdirectory must supply rules for building sources it contributes
base/%.o: ../base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


