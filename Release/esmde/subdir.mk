################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../esmde/Algorithm_ESMDE.cpp 

OBJS += \
./esmde/Algorithm_ESMDE.o 

CPP_DEPS += \
./esmde/Algorithm_ESMDE.d 


# Each subdirectory must supply rules for building sources it contributes
esmde/%.o: ../esmde/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


