################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/main.c \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/stm32f4xx_hal_msp.c \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/stm32f4xx_it.c \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/syscalls.c \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/vl53l1_platform.c 

OBJS += \
./Application/User/main.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_it.o \
./Application/User/syscalls.o \
./Application/User/vl53l1_platform.o 

C_DEPS += \
./Application/User/main.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_it.d \
./Application/User/syscalls.d \
./Application/User/vl53l1_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/main.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/syscalls.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/syscalls.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/vl53l1_platform.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Src/vl53l1_platform.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


