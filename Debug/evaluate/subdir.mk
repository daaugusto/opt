################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../evaluate/Evaluate.cpp \
../evaluate/Evaluate_APM.cpp \
../evaluate/Evaluate_APM_Damping.cpp \
../evaluate/Evaluate_APM_Monotonic.cpp \
../evaluate/Evaluate_Deb.cpp 

OBJS += \
./evaluate/Evaluate.o \
./evaluate/Evaluate_APM.o \
./evaluate/Evaluate_APM_Damping.o \
./evaluate/Evaluate_APM_Monotonic.o \
./evaluate/Evaluate_Deb.o 

CPP_DEPS += \
./evaluate/Evaluate.d \
./evaluate/Evaluate_APM.d \
./evaluate/Evaluate_APM_Damping.d \
./evaluate/Evaluate_APM_Monotonic.d \
./evaluate/Evaluate_Deb.d 


# Each subdirectory must supply rules for building sources it contributes
evaluate/%.o: ../evaluate/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


