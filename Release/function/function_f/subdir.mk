################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../function/function_f/functions_code.cpp 

OBJS += \
./function/function_f/functions_code.o 

CPP_DEPS += \
./function/function_f/functions_code.d 


# Each subdirectory must supply rules for building sources it contributes
function/function_f/%.o: ../function/function_f/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


