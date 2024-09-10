################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../algorithm/Algorithm.cpp \
../algorithm/Algorithm_DE.cpp \
../algorithm/Algorithm_GA.cpp 

OBJS += \
./algorithm/Algorithm.o \
./algorithm/Algorithm_DE.o \
./algorithm/Algorithm_GA.o 

CPP_DEPS += \
./algorithm/Algorithm.d \
./algorithm/Algorithm_DE.d \
./algorithm/Algorithm_GA.d 


# Each subdirectory must supply rules for building sources it contributes
algorithm/%.o: ../algorithm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


