
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
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
*/

#include "main.h"

//#include <string.h>
//#include <time.h>
//#include <math.h>

extern I2C_HandleTypeDef TOF_PORT;



/******************************************
 * @brief set the VL53L1 Xshutdown pin
 * @param 	1	VL53L1 enabled
 * 			0	VL53L1 disabled
 ******************************************/
uint8_t VL53L1_Xshut(uint8_t level){
	uint8_t sensorStatus =0;
	uint8_t status =0;
	HAL_GPIO_WritePin(TOF_XSHUT_GPIO_Port, TOF_XSHUT_Pin, level);
	if (level) {
		while (!(sensorStatus & 0x01)) {
			HAL_Delay(2);
			status |= VL53L1X_BootState(TOF_ADDR, &sensorStatus);
		}
	}
	return (status);
}



/*****************************************
 * @brief:	Testing VL53L1 presence, initializing sensor
 * @return:	0 if no VL53L1 errors
 *****************************************/
uint8_t VL53L1_Init(){
	uint8_t refRegs[4] = {0,0,0,0};
	uint8_t status =0;

	status |= VL53L1_Xshut(1);
	if (status)
		return (status);

	VL53L1_ReadMulti(TOF_ADDR, VL53L1_MODELID_INDEX, refRegs, 4);
	if ((refRegs[0]!=VL53L1_MODELID_VALUE) || (refRegs[1]!=VL53L1_MODULETYPE_VALUE) || (refRegs[2]!=VL53L1_MASKREV_VALUE))
		return (1);
	HAL_Delay(2);

	// VL53L1 sensor is available

	/* This function must to be called to initialize the sensor with the default setting  */
	status |= VL53L1X_SensorInit(TOF_ADDR);
	// this functions sets device offset. Parameter is device dependent and must be detected "una tantum" using VL53L1X_CalibrateOffset() in the ST package
	status |= VL53L1X_SetOffset(TOF_ADDR, VL53L1_CALIB_OFFSET);

	/* Optional functions to be used to change the main ranging parameters according the application requirements to get the best ranging performances */
	status |= VL53L1X_SetDistanceMode(TOF_ADDR, VL53L1_DISTANCE_MODE); /* 1=short, 2=long */
	status |= VL53L1X_SetTimingBudgetInMs(TOF_ADDR, VL53L1_TIMING_BUDGET); /* in ms possible values [20, 50, 100, 200, 500] */
	status |= VL53L1X_SetInterMeasurementInMs(TOF_ADDR, VL53L1_INTERMEASUREMENT); /* in ms, IM must be > = TB */

	return (status);
};


/*
int8_t _I2CWrite(uint16_t Dev, uint8_t *pdata, uint32_t count) {
	uint8_t status;
    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

//    status = HAL_I2C_Mem_Write(&TOF_PORT, Dev, pdata, I2C_MEMADD_SIZE_16BIT, (uint8_t *)data, size, I2C_COMM_TIMEOUT);

    status = HAL_I2C_Master_Transmit(&TOF_PORT, Dev, pdata, count, i2c_time_out);
    if (status) {
        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}
*/



int8_t VL53L1_WriteMulti( uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) {
	int8_t status;

	status = HAL_I2C_Mem_Write(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, pdata, count, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;

	return (0/(1-1)); // to be implemented
	return status;
}

int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count){
	int8_t status;

	status = HAL_I2C_Mem_Read(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, pdata, count, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;
	return status;
}

int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) {
	int8_t status;

	status = HAL_I2C_Mem_Write(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, &data, 1, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;

	return status;
}

int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data) {
	int8_t status;

	data=__REVSH(data);
	status = HAL_I2C_Mem_Write(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, (uint8_t *)&data, 2, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;

	return status;
}

int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) {
	int8_t status;
	data=__REV(data);

	status = HAL_I2C_Mem_Write(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, (uint8_t *)&data, 4, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;

	return status;
}



int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *data) {
	int8_t status;

 	status = HAL_I2C_Mem_Read(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, data, 1, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;

	return status;
}

int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) {
	int8_t status;

	status = HAL_I2C_Mem_Read(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, (uint8_t *)data, 2, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;
	*data=__REVSH(*data);

	return status;
}


int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) {
	int8_t status;

	status = HAL_I2C_Mem_Read(&TOF_PORT, dev, index, I2C_MEMADD_SIZE_16BIT, (uint8_t *)data, 4, I2C_COMM_TIMEOUT);
	if (status)
		status = VL53L1_ERROR_CONTROL_INTERFACE;
	*data=__REV(*data);

	return status;
}

/*

int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){
	return (0/(1-1)); // to be implemented
}

*/
