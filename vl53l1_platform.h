/**
 * @file  vl53l1_platform.h
 * @brief Those platform functions are platform dependent and have to be implemented by the user
 */
 
#include "main.h"


#ifndef _VL53L1_PLATFORM_H_
#define _VL53L1_PLATFORM_H_

/*||||||||||| USER/PROJECT PARAMETERS |||||||||||*/

/*****************     STEP 1      *****************g
 **************** I2C communication ****************
 * set information about the I2c connection
 ***************************************************/
#define TOF_PORT	hi2c1			// that's the I2C port connected to VI53L1X
#define TOF_ADDR	0x52			// the I2C chip address


/*****************     STEP 2      *****************
 ********** VL53L1X ranging configuration **********
 * these parameters set the ranging configuration
 * on the device boot
 ***************************************************/
#define VL53L1__DISTANCE_MODE	(2)		// 1=short, 2=long
#define VL53L1__TIMING_BUDGET	(20)	// in ms, possible values: [15 (only if DISTANCE MODE is 1), 20, 33, 50, 100, 200, 500] - that's the time for a single reading
#define VL53L1__TB_IM_DELTA		(5)		// in ms, added to TB to get IM setting
#define VL53L1__INTERMEASUREMENT	(VL53L1__TIMING_BUDGET + VL53L1__TB_IM_DELTA)		// in ms, it must be > = VL53L1_TIMING_BUDGET - that's the interval (including reading time) between two readings in continuous mode


/*****************     STEP 3      *****************
 ********* VL53L1X active window parameters ********
 * these parameters are loaded on the device boot
 * Detect them using the STM calibration functions
 * available in the VL53L1X package
 ***************************************************/
#define VL53L1__WINDOW_MODE		(0)		// 0=below, 1=beyond, 2=out of window, 3=inside window
#define VL53L1__LOWER_THRESHOLD	(3000)		// (mm) lower window limit. For WINDOW_MODE = 0, 2, 3
#define VL53L1__UPPER_THRESHOLD	(3000)		// (mm) upper window limit. For WINDOW_MODE = 1, 2, 3


/*****************     STEP 4      *****************
 ********** VL53L1X calibration parameters *********
 * these parameters are loaded on the device boot
 * Detect them using the STM calibration functions
 * available in the VL53L1X package
 ***************************************************/
#define VL53L1__CALIB_OFFSET	(-25)	//It must must be detected "una tantum" using VL53L1X_CalibrateOffset()
#define VL53L1__CALIB_XTALK		(0)	 	//It must must be detected "una tantum" using VL53L1X_CalibrateXtalk()


/*****************     STEP 5     *****************
 ************* range status threeshold*************
 * set the Range_Status level accepted as a good
 * ranging.
 * (below or equal this value)
 * (used in the library ranging functions)
 * RANGE STATUS meaning (details on STM VL53L1X ULD user manual):
 * 0=no errors,
 * 1= warning: high standard deviation
 * 2= warning: low return signal level
 * 4-7 errors
 *******************************************/
#define RANGE_STATUS_THREEESH	(2)		// acceptable values: 0,1,2,4,7


/*|||||||| END OF USER/PROJECT PARAMETERS ||||||||*/



/*|||||||||||||| DEVICE PARAMETERS |||||||||||||||||*/
/* you shouldn't need to change anything here after */

// Reference Registers for VL53L1X
// allowing to validate I2C connection on boot
#define VL53L1__MODELID_INDEX	0x010F
#define VL53L1__MODELID_VALUE	0xEA
#define VL53L1__MODULETYPE_INDEX	0x0110
#define VL53L1__MODULETYPE_VALUE	0xCC
#define VL53L1__MASKREV_INDEX	0x0111
#define VL53L1__MASKREV_VALUE	0x10


#define I2C_COMM_TIMEOUT		20   	// ms timeout for the I2C communication

// error code returned by I/O interface functions
#define VL53L1__IO_ERROR			( - 13)
	/*!< error reported from IO functions */


/*|||||||||||||| PACKAGE PARAMETERS |||||||||||||||||*/
/* declarations set by STM software library          */

typedef struct {
	uint32_t dummy;
} VL53L1_Dev_t;

typedef VL53L1_Dev_t *VL53L1_DEV;


// function declarations
uint8_t  VL53L1__Xshut(uint8_t level);
uint8_t  VL53L1__Init();
uint16_t VL53L1__GetDistance(uint8_t level);



/** @brief VL53L1_WriteMulti() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WriteMulti(
		uint16_t 			dev,
		uint16_t      index,
		uint8_t      *pdata,
		uint32_t      count);
/** @brief VL53L1_ReadMulti() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_ReadMulti(
		uint16_t 			dev,
		uint16_t      index,
		uint8_t      *pdata,
		uint32_t      count);
/** @brief VL53L1_WrByte() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrByte(
		uint16_t dev,
		uint16_t      index,
		uint8_t       data);
/** @brief VL53L1_WrWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrWord(
		uint16_t dev,
		uint16_t      index,
		uint16_t      data);
/** @brief VL53L1_WrDWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_WrDWord(
		uint16_t dev,
		uint16_t      index,
		uint32_t      data);
/** @brief VL53L1_RdByte() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdByte(
		uint16_t dev,
		uint16_t      index,
		uint8_t      *pdata);
/** @brief VL53L1_RdWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdWord(
		uint16_t dev,
		uint16_t      index,
		uint16_t     *pdata);
/** @brief VL53L1_RdDWord() definition.\n
 * To be implemented by the developer
 */
int8_t VL53L1_RdDWord(
		uint16_t dev,
		uint16_t      index,
		uint32_t     *pdata);

/** @brief VL53L1_WaitMs() definition.\n
 * To be implemented by the developer
 */
/*
int8_t VL53L1_WaitMs(
		uint16_t dev,
		int32_t       wait_ms);
*/



#endif
