################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/minIni/src/subdir.mk
-include lib/libmodbus/src/subdir.mk
-include lib/cJSON/src/subdir.mk
-include lib/Upacker/src/subdir.mk
-include lib/TinyFrame/src/subdir.mk
-include lib/Sample/src/subdir.mk
-include lib/Protobuf/src/subdir.mk
-include lib/Mongoose/src/subdir.mk
-include lib/LSSDP/src/subdir.mk
-include lib/DeviceDriver/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MT7688_x86

# Tool invocations
MT7688_x86: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "MT7688_x86" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MT7688_x86
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
