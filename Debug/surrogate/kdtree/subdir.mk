################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../surrogate/kdtree/KDTree.cpp 

OBJS += \
./surrogate/kdtree/KDTree.o 

CPP_DEPS += \
./surrogate/kdtree/KDTree.d 


# Each subdirectory must supply rules for building sources it contributes
surrogate/kdtree/%.o: ../surrogate/kdtree/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


