################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/DLT645/src/dlt645.c \
../lib/DLT645/src/dlt645_1997.c \
../lib/DLT645/src/dlt645_2007.c \
../lib/DLT645/src/dlt645_data.c \
../lib/DLT645/src/dlt645_port.c 

OBJS += \
./lib/DLT645/src/dlt645.o \
./lib/DLT645/src/dlt645_1997.o \
./lib/DLT645/src/dlt645_2007.o \
./lib/DLT645/src/dlt645_data.o \
./lib/DLT645/src/dlt645_port.o 

C_DEPS += \
./lib/DLT645/src/dlt645.d \
./lib/DLT645/src/dlt645_1997.d \
./lib/DLT645/src/dlt645_2007.d \
./lib/DLT645/src/dlt645_data.d \
./lib/DLT645/src/dlt645_port.d 


# Each subdirectory must supply rules for building sources it contributes
lib/DLT645/src/%.o: ../lib/DLT645/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/work/workspace/eclipse/MT7688_x86/lib/DLT645/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


