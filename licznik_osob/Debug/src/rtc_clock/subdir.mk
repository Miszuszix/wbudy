################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/rtc_clock/rtc_clock.c 

C_DEPS += \
./src/rtc_clock/rtc_clock.d 

OBJS += \
./src/rtc_clock/rtc_clock.o 


# Each subdirectory must supply rules for building sources it contributes
src/rtc_clock/%.o: ../src/rtc_clock/%.c src/rtc_clock/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\254860\Documents\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\254860\Documents\Lib_EaBaseBoard\inc" -I"C:\Users\254860\Documents\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-rtc_clock

clean-src-2f-rtc_clock:
	-$(RM) ./src/rtc_clock/rtc_clock.d ./src/rtc_clock/rtc_clock.o

.PHONY: clean-src-2f-rtc_clock

