################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../aos/osr/mab/AUCOption.cpp \
../aos/osr/mab/Option.cpp 

OBJS += \
./aos/osr/mab/AUCOption.o \
./aos/osr/mab/Option.o 

CPP_DEPS += \
./aos/osr/mab/AUCOption.d \
./aos/osr/mab/Option.d 


# Each subdirectory must supply rules for building sources it contributes
aos/osr/mab/%.o: ../aos/osr/mab/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


