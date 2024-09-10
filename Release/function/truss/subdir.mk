################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../function/truss/Function_Truss_10_Bar.cpp \
../function/truss/Function_Truss_10_Bar_Discrete.cpp \
../function/truss/Function_Truss_25_Bar.cpp \
../function/truss/Function_Truss_25_Bar_Discrete.cpp \
../function/truss/Function_Truss_60_Bar.cpp \
../function/truss/Function_Truss_60_Bar_Discrete.cpp \
../function/truss/Function_Truss_72_Bar.cpp \
../function/truss/Function_Truss_72_Bar_Discrete.cpp \
../function/truss/Function_Truss_942_Bar.cpp \
../function/truss/Function_Truss_942_Bar_Discrete.cpp \
../function/truss/Problem.cpp \
../function/truss/Truss_Bar_Structure_Static_Problem.cpp 

OBJS += \
./function/truss/Function_Truss_10_Bar.o \
./function/truss/Function_Truss_10_Bar_Discrete.o \
./function/truss/Function_Truss_25_Bar.o \
./function/truss/Function_Truss_25_Bar_Discrete.o \
./function/truss/Function_Truss_60_Bar.o \
./function/truss/Function_Truss_60_Bar_Discrete.o \
./function/truss/Function_Truss_72_Bar.o \
./function/truss/Function_Truss_72_Bar_Discrete.o \
./function/truss/Function_Truss_942_Bar.o \
./function/truss/Function_Truss_942_Bar_Discrete.o \
./function/truss/Problem.o \
./function/truss/Truss_Bar_Structure_Static_Problem.o 

CPP_DEPS += \
./function/truss/Function_Truss_10_Bar.d \
./function/truss/Function_Truss_10_Bar_Discrete.d \
./function/truss/Function_Truss_25_Bar.d \
./function/truss/Function_Truss_25_Bar_Discrete.d \
./function/truss/Function_Truss_60_Bar.d \
./function/truss/Function_Truss_60_Bar_Discrete.d \
./function/truss/Function_Truss_72_Bar.d \
./function/truss/Function_Truss_72_Bar_Discrete.d \
./function/truss/Function_Truss_942_Bar.d \
./function/truss/Function_Truss_942_Bar_Discrete.d \
./function/truss/Problem.d \
./function/truss/Truss_Bar_Structure_Static_Problem.d 


# Each subdirectory must supply rules for building sources it contributes
function/truss/%.o: ../function/truss/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


