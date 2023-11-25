
#include "main.h"
#include <math.h>

// global variables available
// for STM32CubeMonitor,
// running the .json VI53L1X test

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

//number of sample for average and std deviation calculation
#define DIM_ARR 100

/*************************************************************
 * @brief: 	performing one "good" ranging,
 * 			saving results on (above) global variables for
 * 			STM32CubeMonitor
 ************************************************************/
void VL53L1__test(){
	static uint16_t curTB=VL53L1__TIMING_BUDGET;
	static uint16_t curDM=VL53L1__DISTANCE_MODE;
	//	uint8_t dataReady=0;
	uint8_t status=0;
	static float DistArray[DIM_ARR];	// storing last DIM_ARR values of "Distance" to compute avg value and std dev.
	static uint16_t posArr=0;			// position in DistArray to store next "Distance" value
	static uint16_t	sampleNum;
	float sumArr=0, sumSqArr=0;


	//	while ((!goodRanging) && (!status)) {
	//keep reading until get readings without error or I2C error

	//before starting rangings update sensor, if user changed ranging parameters
	if (TimingBudget!=curTB) {					// update TimingBudget if changed in repTB (from CubeMonitor)
		status |= VL53L1X_StopRanging(TOF_ADDR);
		status |= VL53L1X_SetTimingBudgetInMs(TOF_ADDR, TimingBudget);
		status |= VL53L1X_SetInterMeasurementInMs(TOF_ADDR, (TimingBudget+VL53L1__TB_IM_DELTA));
		curTB = TimingBudget;
		status |= VL53L1X_StartRanging(TOF_ADDR);
		readCounter=0;
		numerrors=0;
		ErrorPerc=0;
		posArr=0;
		sampleNum=0;
	}

	if (DistanceMode!=curDM) {					// update Distance Mode)
		status |= VL53L1X_StopRanging(TOF_ADDR);
		status |= VL53L1X_SetDistanceMode(TOF_ADDR, DistanceMode);
		curDM = DistanceMode;
		status |= VL53L1X_StartRanging(TOF_ADDR);
		readCounter=0;
		numerrors=0;
		ErrorPerc=0;
		posArr=0;
		sampleNum=0;
	}

	// is there a new ranging available? //polling via I2C
	//	status |= VL53L1X_CheckForDataReady(TOF_ADDR, &dataReady);
	//	if (dataReady and !status){

	// is there a new ranging available? //polling via INT pin
	if (HAL_GPIO_ReadPin(TOF_INT_GPIO_Port, TOF_INT_Pin)){
		readCounter++;

		status |= VL53L1X_GetRangeStatus(TOF_ADDR, &RangeStatus);
		if (RangeStatus>RANGE_STATUS_THREEESH){			//non acceptable range status
			numerrors++;
			status |= VL53L1X_ClearInterrupt(TOF_ADDR); // reset for a new ranging notification
		} else {										//here is available a "no error" reading. Proceed getting all values
			status |= VL53L1X_GetDistance(TOF_ADDR, &Distance);
			status |= VL53L1X_GetSignalRate(TOF_ADDR, &SignalRate);
			status |= VL53L1X_GetAmbientRate(TOF_ADDR, &AmbientRate);
			status |= VL53L1X_ClearInterrupt(TOF_ADDR); // Everything read. Restart interrupt

			// AVG and STDDEV on last DIM_ARR rangings
			DistArray[posArr]=Distance;		//store Distance into array to compute avg value and std dev.
			if ((posArr+1) > sampleNum)
				sampleNum = (posArr+1); 	//that's the number of samples available in DistArray
			posArr = (posArr+1) % DIM_ARR;
			for (uint16_t k=0; k<sampleNum; k++){
				sumArr+=DistArray[k];
				sumSqArr+=(DistArray[k]*DistArray[k]);
			}
			avgDist=sumArr/((float)sampleNum);
			StdDev=sqrt(sampleNum*sumSqArr - sumArr*sumArr)/((float)sampleNum);
			// end of AVG and STDDEV
		}
		uint8_t currperc =((numerrors*100)+readCounter-1)/readCounter;
		ErrorPerc=currperc;
	}

	// setting RangeStatus variable if I2C communication went wrong
	if (status) {
		RangeStatus=99;
		HAL_Delay(1000);
	}
}


/*  con rilevazione tempo via timer

void VL53L1__test(){
	static uint32_t prevtime=0;
	static uint16_t curTB=VL53L1__TIMING_BUDGET;
	static int16_t curCO=VL53L1__CALIB_OFFSET;
	static uint16_t curDM=VL53L1__DISTANCE_MODE;
	uint8_t dataReady=0;
	uint8_t status=0;
	uint8_t currperc;
	uint8_t goodRanging=0;
	uint32_t timing[11] = {0};

	while (!goodRanging) {
		//keep reading until get readings without error

		TIM3->EGR = 1;
		HAL_Delay(1);
		timing[0]=TIM3->CNT;
		timing[10]=TIM3->CNT;

		//before starting rangings update sensor, if user changed ranging parameters
		if (TimingBudget!=curTB) {					// update TimingBudget if changed in repTB (from CubeMonitor)
			status |= VL53L1X_StopRanging(TOF_ADDR);
			status |= VL53L1X_SetTimingBudgetInMs(TOF_ADDR, TimingBudget);
			status |= VL53L1X_SetInterMeasurementInMs(TOF_ADDR, (TimingBudget+VL53L1__TB_IM_DELTA));
			curTB = TimingBudget;
			status |= VL53L1X_StartRanging(TOF_ADDR);
			readCounter=0;
			numerrors=0;
			ErrorPerc=0;
		}
		if (CalibOffset!=curCO) {					// update Calibration)
			status |= VL53L1X_StopRanging(TOF_ADDR);
			status |= VL53L1X_SetOffset(TOF_ADDR, CalibOffset);
			curCO = CalibOffset;
			status |= VL53L1X_StartRanging(TOF_ADDR);
			readCounter=0;
			numerrors=0;
			ErrorPerc=0;
		}
		if (DistanceMode!=curDM) {					// update Distance Mode)
			status |= VL53L1X_StopRanging(TOF_ADDR);
			status |= VL53L1X_SetDistanceMode(TOF_ADDR, DistanceMode);
			curDM = DistanceMode;
			status |= VL53L1X_StartRanging(TOF_ADDR);
			readCounter=0;
			numerrors=0;
			ErrorPerc=0;
		}

		timing[0]=TIM3->CNT-timing[0];
		//distance reading
		timing[1]=TIM3->CNT;
		readCounter++;
		while (dataReady == 0){
			status |= VL53L1X_CheckForDataReady(TOF_ADDR, &dataReady);
		}
		timing[1]=TIM3->CNT-timing[1];
		timing[2]=TIM3->CNT;
		status |= VL53L1X_GetRangeStatus(TOF_ADDR, &RangeStatus);
		timing[2]=TIM3->CNT-timing[2];
		if (RangeStatus>RANGE_STATUS_THREEESH){
			numerrors++;
			timing[3]=TIM3->CNT;
			status |= VL53L1X_ClearInterrupt(TOF_ADDR);  				// restart readings only in case of errors. If no errors it will be restarted later
			timing[3]=TIM3->CNT-timing[3];
			timing[10]=TIM3->CNT-timing[10];
			__NOP();
		} else {
			goodRanging=1;	// exit reading loop
			timing[3]=999999;
		}
		currperc =((numerrors*100)+readCounter-1)/readCounter;
		ErrorPerc=currperc;
	}

	//here is available a "no error" reading. Proceed getting all values

	timing[4]=TIM3->CNT;
	status |= VL53L1X_GetDistance(TOF_ADDR, &Distance);
	timing[4]-=TIM3->CNT-timing[4];
	ReadingTime=HAL_GetTick()-prevtime;									// time interval since previous reading
	prevtime+=ReadingTime;												// current time

	timing[5]=TIM3->CNT;
	status |= VL53L1X_GetSignalRate(TOF_ADDR, &SignalRate);
	timing[5]=TIM3->CNT-timing[5];
	timing[6]=TIM3->CNT;
	status |= VL53L1X_GetAmbientRate(TOF_ADDR, &AmbientRate);
	timing[6]=TIM3->CNT-timing[6];
	timing[7]=TIM3->CNT;
//	status |= VL53L1X_GetSignalPerSpad(TOF_ADDR, &SignalPerSpad);
	timing[7]=TIM3->CNT-timing[7];
	timing[8]=TIM3->CNT;
//	status |= VL53L1X_GetAmbientPerSpad(TOF_ADDR, &AmbientPerSpad);
	timing[8]=TIM3->CNT-timing[8];
	timing[9]=TIM3->CNT;
	status |= VL53L1X_ClearInterrupt(TOF_ADDR); 						// Everything read. Restart readings
	timing[9]=TIM3->CNT-timing[9];

	timing[10]=TIM3->CNT-timing[10];

	// setting RangeStatus variable if I2C communication went wrong
	if (status) {
		RangeStatus=99;
		HAL_Delay(1000);
	}
}

*/

