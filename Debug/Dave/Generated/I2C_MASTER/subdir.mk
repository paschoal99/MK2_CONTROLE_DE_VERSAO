################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/I2C_MASTER/i2c_master.c \
../Dave/Generated/I2C_MASTER/i2c_master_conf.c 

OBJS += \
./Dave/Generated/I2C_MASTER/i2c_master.o \
./Dave/Generated/I2C_MASTER/i2c_master_conf.o 

C_DEPS += \
./Dave/Generated/I2C_MASTER/i2c_master.d \
./Dave/Generated/I2C_MASTER/i2c_master_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/I2C_MASTER/%.o: ../Dave/Generated/I2C_MASTER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1402_F064x0200 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1400_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

