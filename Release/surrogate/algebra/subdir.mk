################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../surrogate/algebra/Algebra.cpp 

OBJS += \
./surrogate/algebra/Algebra.o 

CPP_DEPS += \
./surrogate/algebra/Algebra.d 


# Each subdirectory must supply rules for building sources it contributes
surrogate/algebra/%.o: ../surrogate/algebra/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


