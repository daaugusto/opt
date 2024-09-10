################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../aos/osr/AUCBandit.cpp \
../aos/osr/AdaptPursuit.cpp \
../aos/osr/BanditAlone.cpp \
../aos/osr/BanditRestart.cpp \
../aos/osr/OperatorSelection.cpp \
../aos/osr/ProbMatching.cpp \
../aos/osr/Uniform.cpp 

OBJS += \
./aos/osr/AUCBandit.o \
./aos/osr/AdaptPursuit.o \
./aos/osr/BanditAlone.o \
./aos/osr/BanditRestart.o \
./aos/osr/OperatorSelection.o \
./aos/osr/ProbMatching.o \
./aos/osr/Uniform.o 

CPP_DEPS += \
./aos/osr/AUCBandit.d \
./aos/osr/AdaptPursuit.d \
./aos/osr/BanditAlone.d \
./aos/osr/BanditRestart.d \
./aos/osr/OperatorSelection.d \
./aos/osr/ProbMatching.d \
./aos/osr/Uniform.d 


# Each subdirectory must supply rules for building sources it contributes
aos/osr/%.o: ../aos/osr/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


