################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/PIN_INTERRUPT/pin_interrupt.c \
../Dave/Generated/PIN_INTERRUPT/pin_interrupt_conf.c 

OBJS += \
./Dave/Generated/PIN_INTERRUPT/pin_interrupt.o \
./Dave/Generated/PIN_INTERRUPT/pin_interrupt_conf.o 

C_DEPS += \
./Dave/Generated/PIN_INTERRUPT/pin_interrupt.d \
./Dave/Generated/PIN_INTERRUPT/pin_interrupt_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/PIN_INTERRUPT/%.o: ../Dave/Generated/PIN_INTERRUPT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1402_F064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

