################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../function/bbob/benchmarks.cpp \
../function/bbob/benchmarksdeclare.cpp \
../function/bbob/benchmarkshelper.cpp \
../function/bbob/benchmarksnoisy.cpp \
../function/bbob/dirOK.cpp \
../function/bbob/fgeneric.cpp 

OBJS += \
./function/bbob/benchmarks.o \
./function/bbob/benchmarksdeclare.o \
./function/bbob/benchmarkshelper.o \
./function/bbob/benchmarksnoisy.o \
./function/bbob/dirOK.o \
./function/bbob/fgeneric.o 

CPP_DEPS += \
./function/bbob/benchmarks.d \
./function/bbob/benchmarksdeclare.d \
./function/bbob/benchmarkshelper.d \
./function/bbob/benchmarksnoisy.d \
./function/bbob/dirOK.d \
./function/bbob/fgeneric.d 


# Each subdirectory must supply rules for building sources it contributes
function/bbob/%.o: ../function/bbob/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


