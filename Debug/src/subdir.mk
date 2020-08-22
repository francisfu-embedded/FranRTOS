################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/led.c \
../src/org_template.c \
../src/oskernel.c \
../src/task.c 

OBJS += \
./src/led.o \
./src/org_template.o \
./src/oskernel.o \
./src/task.o 

C_DEPS += \
./src/led.d \
./src/org_template.d \
./src/oskernel.d \
./src/task.d 


# Each subdirectory must supply rules for building sources it contributes
src/led.o: ../src/led.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/led.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/org_template.o: ../src/org_template.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/org_template.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/oskernel.o: ../src/oskernel.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/oskernel.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
src/task.o: ../src/task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/apple/STM32CubeIDE/workspace_1.1.0/RTOS/FranRTOS/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"src/task.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

