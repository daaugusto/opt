################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../surrogate/Evaluate_Surrogate.cpp \
../surrogate/Evaluate_Surrogate_LLR.cpp \
../surrogate/Evaluate_Surrogate_LWR.cpp \
../surrogate/Evaluate_Surrogate_NN.cpp \
../surrogate/Evaluate_Surrogate_RBF.cpp \
../surrogate/Manager_Surrogate.cpp 

OBJS += \
./surrogate/Evaluate_Surrogate.o \
./surrogate/Evaluate_Surrogate_LLR.o \
./surrogate/Evaluate_Surrogate_LWR.o \
./surrogate/Evaluate_Surrogate_NN.o \
./surrogate/Evaluate_Surrogate_RBF.o \
./surrogate/Manager_Surrogate.o 

CPP_DEPS += \
./surrogate/Evaluate_Surrogate.d \
./surrogate/Evaluate_Surrogate_LLR.d \
./surrogate/Evaluate_Surrogate_LWR.d \
./surrogate/Evaluate_Surrogate_NN.d \
./surrogate/Evaluate_Surrogate_RBF.d \
./surrogate/Manager_Surrogate.d 


# Each subdirectory must supply rules for building sources it contributes
surrogate/%.o: ../surrogate/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


