################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../hybridAOS/Algorithm_DE_AOS.cpp \
../hybridAOS/Algorithm_GA_AOS.cpp \
../hybridAOS/Algorithm_HybridOp_AOS.cpp \
../hybridAOS/Algorithm_Hybrid_AOS.cpp 

OBJS += \
./hybridAOS/Algorithm_DE_AOS.o \
./hybridAOS/Algorithm_GA_AOS.o \
./hybridAOS/Algorithm_HybridOp_AOS.o \
./hybridAOS/Algorithm_Hybrid_AOS.o 

CPP_DEPS += \
./hybridAOS/Algorithm_DE_AOS.d \
./hybridAOS/Algorithm_GA_AOS.d \
./hybridAOS/Algorithm_HybridOp_AOS.d \
./hybridAOS/Algorithm_Hybrid_AOS.d 


# Each subdirectory must supply rules for building sources it contributes
hybridAOS/%.o: ../hybridAOS/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


