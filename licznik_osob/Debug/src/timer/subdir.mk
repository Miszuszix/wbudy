################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/timer/timer_utils.c 

C_DEPS += \
./src/timer/timer_utils.d 

OBJS += \
./src/timer/timer_utils.o 


# Each subdirectory must supply rules for building sources it contributes
src/timer/%.o: ../src/timer/%.c src/timer/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\254860\Documents\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\254860\Documents\Lib_EaBaseBoard\inc" -I"C:\Users\254860\Documents\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-timer

clean-src-2f-timer:
	-$(RM) ./src/timer/timer_utils.d ./src/timer/timer_utils.o

.PHONY: clean-src-2f-timer

