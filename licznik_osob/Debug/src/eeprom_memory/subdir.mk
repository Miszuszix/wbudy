################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/eeprom_memory/eeprom_memory.c 

C_DEPS += \
./src/eeprom_memory/eeprom_memory.d 

OBJS += \
./src/eeprom_memory/eeprom_memory.o 


# Each subdirectory must supply rules for building sources it contributes
src/eeprom_memory/%.o: ../src/eeprom_memory/%.c src/eeprom_memory/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\254860\Documents\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\254860\Documents\Lib_EaBaseBoard\inc" -I"C:\Users\254860\Documents\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-eeprom_memory

clean-src-2f-eeprom_memory:
	-$(RM) ./src/eeprom_memory/eeprom_memory.d ./src/eeprom_memory/eeprom_memory.o

.PHONY: clean-src-2f-eeprom_memory

