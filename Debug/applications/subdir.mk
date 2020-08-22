################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../applications/main.c \
../applications/syscalls.c \
../applications/sysmem.c 

OBJS += \
./applications/main.o \
./applications/syscalls.o \
./applications/sysmem.o 

C_DEPS += \
./applications/main.d \
./applications/syscalls.d \
./applications/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
applications/main.o: ../applications/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"applications/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
applications/syscalls.o: ../applications/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"applications/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
applications/sysmem.o: ../applications/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"applications/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

