################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/driver/LedBar/LedBar.c 

OBJS += \
./Core/driver/LedBar/LedBar.o 

C_DEPS += \
./Core/driver/LedBar/LedBar.d 


# Each subdirectory must supply rules for building sources it contributes
Core/driver/LedBar/%.o Core/driver/LedBar/%.su Core/driver/LedBar/%.cyclo: ../Core/driver/LedBar/%.c Core/driver/LedBar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/harman/STM32Cube/wine_celler/Core/ap" -I"C:/harman/STM32Cube/wine_celler/Core/driver/Button" -I"C:/harman/STM32Cube/wine_celler/Core/driver/FND" -I"C:/harman/STM32Cube/wine_celler/Core/driver/LedBar" -I"C:/harman/STM32Cube/wine_celler/Core/ap/src" -I"C:/harman/STM32Cube/wine_celler/Core/driver/LCD" -I"C:/harman/STM32Cube/wine_celler/Core/ap/inc" -I"C:/harman/STM32Cube/wine_celler/Core/driver/buzzer" -I"C:/harman/STM32Cube/wine_celler/Core/driver/DHT11" -I"C:/harman/STM32Cube/wine_celler/Core/driver/motor" -I"C:/harman/STM32Cube/wine_celler/Core/driver/Light" -I"C:/harman/STM32Cube/wine_celler/Core/driver/hypersonic" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-driver-2f-LedBar

clean-Core-2f-driver-2f-LedBar:
	-$(RM) ./Core/driver/LedBar/LedBar.cyclo ./Core/driver/LedBar/LedBar.d ./Core/driver/LedBar/LedBar.o ./Core/driver/LedBar/LedBar.su

.PHONY: clean-Core-2f-driver-2f-LedBar

