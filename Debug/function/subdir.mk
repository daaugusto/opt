################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../function/Function.cpp \
../function/Function_BBOB.cpp \
../function/Function_F.cpp \
../function/Function_G.cpp \
../function/Function_Mechanic.cpp \
../function/Function_Truss.cpp \
../function/Function_Unconstrained.cpp 

OBJS += \
./function/Function.o \
./function/Function_BBOB.o \
./function/Function_F.o \
./function/Function_G.o \
./function/Function_Mechanic.o \
./function/Function_Truss.o \
./function/Function_Unconstrained.o 

CPP_DEPS += \
./function/Function.d \
./function/Function_BBOB.d \
./function/Function_F.d \
./function/Function_G.d \
./function/Function_Mechanic.d \
./function/Function_Truss.d \
./function/Function_Unconstrained.d 


# Each subdirectory must supply rules for building sources it contributes
function/%.o: ../function/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


