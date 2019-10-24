################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/work/workspace/eclipse/MT7688_x86/lib/DLT645/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Sample/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/TinyFrame/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Upacker/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/DeviceDriver/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


