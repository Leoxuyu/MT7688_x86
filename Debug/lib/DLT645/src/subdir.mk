################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/DLT645/src/dlt645.c \
../lib/DLT645/src/dlt645_1997.c \
../lib/DLT645/src/dlt645_2007.c \
../lib/DLT645/src/dlt645_data.c \
../lib/DLT645/src/dlt645_port_linux.c 

OBJS += \
./lib/DLT645/src/dlt645.o \
./lib/DLT645/src/dlt645_1997.o \
./lib/DLT645/src/dlt645_2007.o \
./lib/DLT645/src/dlt645_data.o \
./lib/DLT645/src/dlt645_port_linux.o 

C_DEPS += \
./lib/DLT645/src/dlt645.d \
./lib/DLT645/src/dlt645_1997.d \
./lib/DLT645/src/dlt645_2007.d \
./lib/DLT645/src/dlt645_data.d \
./lib/DLT645/src/dlt645_port_linux.d 


# Each subdirectory must supply rules for building sources it contributes
lib/DLT645/src/%.o: ../lib/DLT645/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/work/workspace/eclipse/MT7688_x86/lib/DLT645/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/cJSON/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Protobuf/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/minIni/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Mongoose/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Sample/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/TinyFrame/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Upacker/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/DeviceDriver/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


