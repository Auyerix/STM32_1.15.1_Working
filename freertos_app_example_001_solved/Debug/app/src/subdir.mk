################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/src/app.c \
../app/src/logger.c \
../app/src/task_a.c \
../app/src/task_b.c \
../app/src/task_test.c 

OBJS += \
./app/src/app.o \
./app/src/logger.o \
./app/src/task_a.o \
./app/src/task_b.o \
./app/src/task_test.o 

C_DEPS += \
./app/src/app.d \
./app/src/logger.d \
./app/src/task_a.d \
./app/src/task_b.d \
./app/src/task_test.d 


# Each subdirectory must supply rules for building sources it contributes
app/src/%.o app/src/%.su app/src/%.cyclo: ../app/src/%.c app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../app/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app-2f-src

clean-app-2f-src:
	-$(RM) ./app/src/app.cyclo ./app/src/app.d ./app/src/app.o ./app/src/app.su ./app/src/logger.cyclo ./app/src/logger.d ./app/src/logger.o ./app/src/logger.su ./app/src/task_a.cyclo ./app/src/task_a.d ./app/src/task_a.o ./app/src/task_a.su ./app/src/task_b.cyclo ./app/src/task_b.d ./app/src/task_b.o ./app/src/task_b.su ./app/src/task_test.cyclo ./app/src/task_test.d ./app/src/task_test.o ./app/src/task_test.su

.PHONY: clean-app-2f-src

