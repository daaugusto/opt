################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../aos/cas/AUCCredit.cpp \
../aos/cas/CreditAssignment.cpp \
../aos/cas/RankingCredit.cpp \
../aos/cas/SUMCredit.cpp 

OBJS += \
./aos/cas/AUCCredit.o \
./aos/cas/CreditAssignment.o \
./aos/cas/RankingCredit.o \
./aos/cas/SUMCredit.o 

CPP_DEPS += \
./aos/cas/AUCCredit.d \
./aos/cas/CreditAssignment.d \
./aos/cas/RankingCredit.d \
./aos/cas/SUMCredit.d 


# Each subdirectory must supply rules for building sources it contributes
aos/cas/%.o: ../aos/cas/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


