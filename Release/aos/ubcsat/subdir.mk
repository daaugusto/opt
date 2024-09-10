################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../aos/ubcsat/mt19937ar.cpp 

OBJS += \
./aos/ubcsat/mt19937ar.o 

CPP_DEPS += \
./aos/ubcsat/mt19937ar.d 


# Each subdirectory must supply rules for building sources it contributes
aos/ubcsat/%.o: ../aos/ubcsat/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


