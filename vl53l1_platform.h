/**
 * @file  vl53l1_platform.h
 * @brief Those platform functions are platform dependent and have to be implemented by the user
 */
 
#ifndef _VL53L1_PLATFORM_H_
#define _VL53L1_PLATFORM_H_


#define TOF_PORT	hi2c1			// here using I2C1 port
#define TOF_ADDR	0x52			// the I2C chip address

#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

#define I2C_COMM_TIMEOUT		20   			// ms timeout for the I2C communication (consider

// Reference Registers for VL53L1
// allowing to validate I2C connection on boot
#define VL53L1_MODELID_INDEX	0x010F
#define VL53L1_MODELID_VALUE	0xEA
#define VL53L1_MODULETYPE_INDEX	0x0110
#define VL53L1_MODULETYPE_VALUE	0xCC
#define VL53L1_MASKREV_INDEX	0x0111
#define VL53L1_MASKREV_VALUE	0x10

// initialization parameters
#define VL53L1_CALIB_OFFSET		(-24)			//It must must be detected "una tantum" using VL53L1X_CalibrateOffset() available in the VL53L1X package provided by ST
#define VL53L1_DISTANCE_MODE	(2)				// 1=short, 2=long
#define VL53L1_TIMING_BUDGET	(100)			// in ms, possible values [20, 50, 100, 200, 500]
#define VL53L1_INTERMEASUREMENT	(150)			// in ms, IM must be > = Timing_Budget


typedef struct {
	uint32_t dummy;
} VL53L1_Dev_t;

typedef VL53L1_Dev_t *VL53L1_DEV;


uint8_t VL53L1_Xshut(uint8_t level);
uint8_t VL53L1_Init();


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
int8_t VL53L1_WaitMs(
		uint16_t dev,
		int32_t       wait_ms);


#endif
