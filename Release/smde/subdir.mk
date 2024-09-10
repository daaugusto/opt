################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../smde/Algorithm_SMDE.cpp \
../smde/Algorithm_SMDE_aKnn.cpp 

OBJS += \
./smde/Algorithm_SMDE.o \
./smde/Algorithm_SMDE_aKnn.o 

CPP_DEPS += \
./smde/Algorithm_SMDE.d \
./smde/Algorithm_SMDE_aKnn.d 


# Each subdirectory must supply rules for building sources it contributes
smde/%.o: ../smde/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


