################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include surrogate/kdtree/subdir.mk
-include surrogate/algebra/distribution/subdir.mk
-include surrogate/algebra/subdir.mk
-include surrogate/subdir.mk
-include smde/subdir.mk
-include slsde/subdir.mk
-include operator/subdir.mk
-include hybridAOS/subdir.mk
-include function/truss/simulator/subdir.mk
-include function/truss/subdir.mk
-include function/function_f/subdir.mk
-include function/bbob/subdir.mk
-include function/subdir.mk
-include evaluate/subdir.mk
-include esmde/subdir.mk
-include base/subdir.mk
-include aos/ubcsat/subdir.mk
-include aos/osr/mab/subdir.mk
-include aos/osr/subdir.mk
-include aos/cas/subdir.mk
-include aos/subdir.mk
-include algorithm/subdir.mk
-include blde/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Opt

# Tool invocations
Opt: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -w  -o "Opt" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Opt
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
