################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/Sample/src/Ini_sample.c \
../lib/Sample/src/TF_Sample.c \
../lib/Sample/src/cJSON_Sample.c \
../lib/Sample/src/lssdp_sample.c \
../lib/Sample/src/mongoose_Sample.c \
../lib/Sample/src/protobuf_Sample.c \
../lib/Sample/src/upack_sample.c 

OBJS += \
./lib/Sample/src/Ini_sample.o \
./lib/Sample/src/TF_Sample.o \
./lib/Sample/src/cJSON_Sample.o \
./lib/Sample/src/lssdp_sample.o \
./lib/Sample/src/mongoose_Sample.o \
./lib/Sample/src/protobuf_Sample.o \
./lib/Sample/src/upack_sample.o 

C_DEPS += \
./lib/Sample/src/Ini_sample.d \
./lib/Sample/src/TF_Sample.d \
./lib/Sample/src/cJSON_Sample.d \
./lib/Sample/src/lssdp_sample.d \
./lib/Sample/src/mongoose_Sample.d \
./lib/Sample/src/protobuf_Sample.d \
./lib/Sample/src/upack_sample.d 


# Each subdirectory must supply rules for building sources it contributes
lib/Sample/src/%.o: ../lib/Sample/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/work/workspace/eclipse/MT7688_x86/lib/RTT_Port/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/picoc/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/libmodbus/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/LSSDP/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/cJSON/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Protobuf/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/minIni/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Mongoose/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Sample/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/TinyFrame/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/Upacker/inc" -I"/home/work/workspace/eclipse/MT7688_x86/lib/DeviceDriver/inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu99 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


