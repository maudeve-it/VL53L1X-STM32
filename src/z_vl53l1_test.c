/*
 * z_vl53l1_test.c
 * rel. 2.00
 *
 *  Created on: Nov 23, 2023
 *      Author: mauro
 *
 *  licensing: https://github.com/maudeve-it/VL53L1X-STM32/blob/main/LICENSE
 *
 *	To install and use this library follow instruction on: https://www.youtube.com/playlist?list=PL6Fwy7aR3zSlArL6TJnSjWSbKmxM5BHnb
 *
 */

#include "main.h"
#include <math.h>


/*
 **** VL53L1__test() ***
 * the above function feeds the following global variables 
 * for STM32CubeMonitor running TestRanging_VL53L1X.json script
 *
 */

uint16_t 	Distance;							// data read from VL53L1
uint8_t 	RangeStatus;						// data read from VL53L1
uint16_t 	SignalRate;							// data read from VL53L1
uint16_t 	AmbientRate;						// data read from VL53L1
uint16_t 	SignalPerSpad;						// data read from VL53L1
uint16_t 	AmbientPerSpad;						// data read from VL53L1
uint16_t 	TimingBudget=VL53L1__TIMING_BUDGET;	// TimeBudget requested on (written by) STM32CubeMonitor
int16_t 	CalibOffset=VL53L1__CALIB_OFFSET;	// CalibrationOffset requested on (written by) STM32CubeMonitor
uint16_t 	DistanceMode=VL53L1__DISTANCE_MODE;	// DistanceMode requested on (written by) STM32CubeMonitor
uint8_t 	ErrorPerc=0;						// percentage of distance readings returning error
uint32_t 	numerrors=0;						//
uint32_t 	readCounter=0;						//
float 		avgDist;
float		StdDev;


/*
 **** VL53L1__testGesture() ****
 * the above function feeds the following global variables 
 * for STM32CubeMonitor running TestRanging_VL53L1X.json script
 */
uint8_t 	shortClick=0;
uint8_t 	doubleClick=0;
uint8_t 	longClick=0;
int16_t 	longClickVal=(TESTGESTURE_LCLICK_UPPER+TESTGESTURE_LCLICK_LOWER)/2;
int16_t		lowerlimit_V = TESTGESTURE_LCLICK_LOWER;
int16_t		upperlimit_V = TESTGESTURE_LCLICK_UPPER;
int16_t		lowerlimit_H = GESTURE_MIN_DIST;
int16_t		upperlimit_H = GESTURE_MAX_DIST;

uint16_t	currentIM;


uint8_t SStatus;


/*
 **** VL53L1X__GestureMenu_Items() ****
 * the above function feeds the following global variables 
 * for STM32CubeMonitor running TestRanging_VL53L1X.json script
 *
 */

uint8_t		option1,option2;
int16_t 	glevel1=150,gll1=100,gul1=200;
int16_t 	glevel2=500,gll2=0,gul2=1000;




/*************************************************************
 * @brief: 	performing one "good" ranging,
 * 			saving results on global variables for
 * 			STM32CubeMonitor
 ************************************************************/
void VL53L1__testRanging(){
	static uint16_t curTB=VL53L1__TIMING_BUDGET;
	static uint16_t curDM=VL53L1__DISTANCE_MODE;
	static float DistArray[TESTGESTURE_DIM_ARR];	// storing last DIM_ARR values of "Distance" to compute avg value and std dev.
	static uint16_t posArr=0;			// position in DistArray to store next "Distance" value
	static uint16_t	sampleNum=0;
	float sumArr=0, sumSqArr=0;
	static uint32_t	ReadingTime=0;
	uint32_t testingTime=HAL_GetTick();
	uint8_t status=0;

	//before starting rangings update sensor, if user changed ranging parameters through CubeMonitor
	if (TimingBudget!=curTB) {		// update TimingBudget if changed in repTB (by CubeMonitor)
		status |= VL53L1X_StopRanging(VL53L1__ADDR);
		status |= VL53L1X_SetTimingBudgetInMs(VL53L1__ADDR, TimingBudget);
		status |= VL53L1X_SetInterMeasurementInMs(VL53L1__ADDR, (TimingBudget+VL53L1__TB_IM_DELTA));
		curTB = TimingBudget;
		status |= VL53L1X_StartRanging(VL53L1__ADDR);
		readCounter=0;
		numerrors=0;
		ErrorPerc=0;
		posArr=0;
		sampleNum=0;
	}

	if (DistanceMode!=curDM) {		// update Distance Mode if changed by CubeMonitor
		status |= VL53L1X_StopRanging(VL53L1__ADDR);
		status |= VL53L1X_SetDistanceMode(VL53L1__ADDR, DistanceMode);
		curDM = DistanceMode;
		status |= VL53L1X_StartRanging(VL53L1__ADDR);
		readCounter=0;
		numerrors=0;
		ErrorPerc=0;
		posArr=0;
		sampleNum=0;
	}

// check data availability waiting for the intermeasurement time
// test can be done in two modes depending if using interrupt or polling mode

#ifdef	VL53L1__USING_GPIO
	while ((!HAL_GPIO_ReadPin(TOF_GPIO_GPIO_Port, TOF_GPIO_Pin)) && ((HAL_GetTick()-testingTime)<=VL53L1__INTERMEASUREMENT)) {};
	if (HAL_GPIO_ReadPin(TOF_GPIO_GPIO_Port, TOF_GPIO_Pin)) {
#else
	uint8_t dataReady=0;
	while ((dataReady == 0) && ((HAL_GetTick()-testingTime)<VL53L1__INTERMEASUREMENT) && (!status))
		status |= VL53L1X_CheckForDataReady(VL53L1__ADDR, &dataReady);
	if (dataReady && (!status)) {
#endif
		// a new ranging data set is available
		readCounter++;
		ReadingTime=HAL_GetTick();

		status |= VL53L1X_GetRangeStatus(VL53L1__ADDR, &RangeStatus);
		if (RangeStatus>VL53L1__RANGE_STATUS_THRESH){	//non acceptable range status
			numerrors++;
			status |= VL53L1X_ClearInterrupt(VL53L1__ADDR); // reset for a new ranging notification
		} else {					//here is available a "no error" reading. Proceed getting all values
			status |= VL53L1X_GetDistance(VL53L1__ADDR, &Distance);
			status |= VL53L1X_GetSignalRate(VL53L1__ADDR, &SignalRate);
			status |= VL53L1X_GetAmbientRate(VL53L1__ADDR, &AmbientRate);
			status |= VL53L1X_ClearInterrupt(VL53L1__ADDR); // Everything read. Restart interrupt

			// Calculate distance average value and standard deviation over last TESTGESTURE_DIM_ARR readings
			DistArray[posArr]=Distance;		//store Distance into array to compute avg value and std dev.
			if ((posArr+1) > sampleNum)
				sampleNum = (posArr+1); 	//that's the number of samples available in DistArray
			posArr = (posArr+1) % TESTGESTURE_DIM_ARR;
			for (uint16_t k=0; k<sampleNum; k++){
				sumArr+=DistArray[k];
				sumSqArr+=(DistArray[k]*DistArray[k]);
			}
			avgDist=sumArr/((float)sampleNum);									// that's average value
			StdDev=sqrt(sampleNum*sumSqArr - sumArr*sumArr)/((float)sampleNum); // that's the standard deviation
			// end of "Calculate distance average value and ...
		}
		uint8_t currperc =((numerrors*100)+readCounter-1)/readCounter;
		ErrorPerc=currperc;
	} else {
		if ((HAL_GetTick()-ReadingTime)>(TimingBudget+VL53L1__TB_IM_DELTA)) 	// if data is not available
			RangeStatus=255;										// mark RangeStatus
	}

	// setting RangeStatus variable if I2C communication went wrong
	if (status) {
		RangeStatus=99;
		HAL_Delay(1000);
	}
}



/*************************************************************
 * @brief: 	test function performing one  gesture detection,
 * 			saving results on (above) global variables for
 * 			STM32CubeMonitor
 ************************************************************/
void VL53L1__testGesture(){
	static uint32_t clickTime=0;

	lowerlimit_V = TESTGESTURE_LCLICK_LOWER;
	upperlimit_V = TESTGESTURE_LCLICK_UPPER;
	lowerlimit_H = GESTURE_MIN_DIST;
	upperlimit_H = GESTURE_MAX_DIST;

	if (shortClick || doubleClick) {
		if (clickTime==0)
			clickTime=HAL_GetTick();
		if ((HAL_GetTick()-clickTime) > TESTGESTURE_CLICK_DURATION) {
			clickTime=0;
			shortClick=0;
			doubleClick=0;
		}
	}

/*	uint16_t locIM;
	VL53L1X_GetInterMeasurementInMs(VL53L1__ADDR, &locIM);
	currentIM=locIM;
*/
	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)
		VL53L1__CheckGesture(Distance, &shortClick, &doubleClick, &longClick, &longClickVal, TESTGESTURE_LCLICK_LOWER, TESTGESTURE_LCLICK_UPPER);

}




/*************************************************************
 * @brief: 	test function performing gesture detection,
 * 			and menu handling
 ************************************************************/
void VL53L1__testMenu(){
//	static uint32_t clickTime=0;


	SStatus=VL53L1__GetDistance(&Distance);
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH)
		VL53L1__GestureMenu(SStatus, Distance);
}





/*************************************************************
 * @brief: 	function performing the test menu handling,
 * 			feeding (above) global variables for
 * 			STM32CubeMonitor
 ************************************************************/
void VL53L1X__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick, uint8_t doubleClick, uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue){

	switch (menuItem) {
	case 1: // menu level 1
		if (shortClick){
			option1=!option1;			//global variable just for CubeMonitor
		}
		break;
	case 2: // menu level 2
		if (firstCall) {
			*longClickLowerValue=100;
			*longClickUpperValue=200;
			gll1=*longClickLowerValue;  //global variable just for CubeMonitor
			gul1=*longClickUpperValue;	//global variable just for CubeMonitor
			*longClickVal=glevel1;
		}
		glevel1=*longClickVal;			//global variable just for CubeMonitor

		break;
	case 3: // menu level 3
		if (shortClick) {
			option2=(++option2 % 4);	//global variable just for CubeMonitor
		}

		if (firstCall) {
			*longClickLowerValue=0;
			*longClickUpperValue=1000;
			gll2=*longClickLowerValue;  //global variable just for CubeMonitor
			gul2=*longClickUpperValue;  //global variable just for CubeMonitor
			*longClickVal=glevel2;
		}
		glevel2=*longClickVal;			//global variable just for CubeMonitor
		break;
	}
}











