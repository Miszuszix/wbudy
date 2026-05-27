################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/startup/cr_startup_lpc17.c 

C_DEPS += \
./src/startup/cr_startup_lpc17.d 

OBJS += \
./src/startup/cr_startup_lpc17.o 


# Each subdirectory must supply rules for building sources it contributes
src/startup/%.o: ../src/startup/%.c src/startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\254860\Documents\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\254860\Documents\Lib_EaBaseBoard\inc" -I"C:\Users\254860\Documents\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-startup

clean-src-2f-startup:
	-$(RM) ./src/startup/cr_startup_lpc17.d ./src/startup/cr_startup_lpc17.o

.PHONY: clean-src-2f-startup

