################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld/VL53L1X_api.c \
C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld/VL53L1X_calibration.c 

OBJS += \
./Drivers/BSP/vl53l1_uld/VL53L1X_api.o \
./Drivers/BSP/vl53l1_uld/VL53L1X_calibration.o 

C_DEPS += \
./Drivers/BSP/vl53l1_uld/VL53L1X_api.d \
./Drivers/BSP/vl53l1_uld/VL53L1X_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/vl53l1_uld/VL53L1X_api.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld/VL53L1X_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/BSP/vl53l1_uld/VL53L1X_calibration.o: C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld/VL53L1X_calibration.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/Components/vl53l1x_uld" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/SVN_Approj_VL53L1X/trunk/software/STSW-IMG009/Example/Drivers/BSP/X-NUCLEO-53L1A1"  -Og -g3 -Wall -fmessage-length=0 -fno-builtin-fputc -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


