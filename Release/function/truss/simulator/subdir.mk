################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../function/truss/simulator/Truss_Bar_Structure_Static_Simulator.cpp 

OBJS += \
./function/truss/simulator/Truss_Bar_Structure_Static_Simulator.o 

CPP_DEPS += \
./function/truss/simulator/Truss_Bar_Structure_Static_Simulator.d 


# Each subdirectory must supply rules for building sources it contributes
function/truss/simulator/%.o: ../function/truss/simulator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


