/**
  @page Description of X-NUCLEO-53L1A1 Expansion Board example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  ST/Imaging
  * @version V1.0.0
  * @date    January/11/2018
  * @brief   Description of the VL53L1X Expansion Board example.
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par VL53L1X Expansion Board example Description

This directory contains reference project that demonstrates the functionalities of
STMicroelectronics X-NUCLEO-53L1A1 Expansion Board. The demo
application runs on STM32F4xx-Nucleo and STM32L4xx-Nucleo boards.

@par Directory contents 

  - Src/main.c                  Main program 
  - Src/stm32f4xx_hal_msp.c     HAL MSP module for STM32F4xx
  - Src/stm32f4xx_it.c          Interrupt handlers for STM32F4xx 
  - Inc/stm32f4xx_hal_conf.h    HAL Configuration file for STM32F4xx
  - Inc/stm32f4xx_it.h          Interrupt handlers header file for STM32F4xx
  - Src/stm32l4xx_hal_msp.c     HAL MSP module for STM32L4xx
  - Src/stm32l4xx_it.c          Interrupt handlers for STM32L4xx 
  - Inc/stm32l4xx_hal_conf.h    HAL Configuration file for STM32L4xx
  - Inc/stm32l4xx_it.h          Interrupt handlers header file for STM32L4xx  
  - Inc/stm32xxx_hal.h          Generic HAL selector

@par Hardware and Software environment
    
  - This example has been tested with STMicroelectronics STM32F401RE and STM32L476RG Nucleo boards

  - This example requires a X-NUCLEO-53L1A1 expansion board

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain (IAR, Keil, STM32Workbench)
 - Rebuild all files and load your image into target memory
 - Open an Tera Term session
 - Select the right COM port
 - Reset Nucleo board
 - Observe the distance measured on the Tera Term.
 - Full description in Documentation directory

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
