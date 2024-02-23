/*
 * z_vl53l1_gesture.c
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

#include <main.h>

uint8_t GestureMenu_CurrentItem=0; //stores current menu status: 0 = menu disabled, 1 to GESTUREMENU_ITEMS indicates the current active menu item

//declare the extern timer handle if there is a led for the menu status
#ifdef GESTUREMENU_ISLED
extern TIM_HandleTypeDef GESTUREMENU_LEDTIMER;
#endif // GESTUREMENU_ISLED


/**************************************
 *@brief	initialize  gesture handling
 *			Call this function before entering into main loop
 **************************************/
void VL53L1__InitGesture(){
#ifdef GESTUREMENU_ISLED
	HAL_TIM_PeriodElapsedCallback (&GESTUREMENU_LEDTIMER);	// initialize ARR
	HAL_TIM_Base_Start_IT(&GESTUREMENU_LEDTIMER);			// start timer click
#endif // GESTUREMENU_ISLED
	VL53L1__SetTimingBudget(GESTURE_DETECTION_TB,GESTURE_DETECTION_TB+VL53L1__TB_IM_DELTA);			// initialize TimingBudget for target detection
}



// if there is a led for the menu status , define the below timer callback
#ifdef GESTUREMENU_ISLED
/*****************************************
 * Peroid Elapsed Callback for the timer
 * assigned to the menu status led.
 * Timer GESTUREMENU_LEDTIMER must be set just as a counting timer.
 * Its prescaler must be set on CubeMX generating a 1ms time base
 * Refer to ".h" file for more info
 *****************************************/
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim){
	if (htim==&GESTUREMENU_LEDTIMER){
		static uint8_t FlashCounter=0;
		static uint8_t ledstatus=0;
		if (!(GestureMenu_CurrentItem==0)){
			if (ledstatus==0) {
				FlashCounter = (FlashCounter + 1) % GestureMenu_CurrentItem;
				HAL_GPIO_WritePin(MENU_LED_GPIO_Port, MENU_LED_Pin, GESTUREMENU_LEDON);
				GESTUREMENU_LEDTIMER.Instance->ARR=GESTUREMENU_LED_ON_TIME;
			} else {
				HAL_GPIO_WritePin(MENU_LED_GPIO_Port, MENU_LED_Pin, !GESTUREMENU_LEDON);
				GESTUREMENU_LEDTIMER.Instance->ARR=(FlashCounter==0 ? GESTUREMENU_LED_LPAUSE : GESTUREMENU_LED_SPAUSE);
			}
			ledstatus = !ledstatus;
		} else {
			HAL_GPIO_WritePin(MENU_LED_GPIO_Port, MENU_LED_Pin, !GESTUREMENU_LEDON);
			GESTUREMENU_LEDTIMER.Instance->ARR=GESTUREMENU_LED_SPAUSE;
		}
	}
}

#endif	//GESTUREMENU_ISLED





/********************************************************************
 *@brief	receive the distance detected and identifies gestures, if any.
 *			In case of gesture set to 1 the corresponding variable,
 *			otherqwist is 0.
 *			In case of a long click, function returns also the click
 *			value calculated in the range indicated by parameters.
 *@params	dist		(in)		distance detected via VL53L1__GetDistance()
 *			sClick		(out) 		1 if detected a single click, otherwise 0
 *			dClick		(out) 		1 if detected a double click, otherwise 0
 *			lClick		(out)	 	1 if detected a long click, otherwise 0
 *			lClickVal	(in/out) 	if long click running, it is increased/decreased
 *						/			depending of the target position and the range
 *									defined by the next parameters.
 *			lClickLower (in)		lower limit of lClickVal range
 *			lClickUpper (in)		upper limit of lClickVal range
 *@return	1	target detected into the valid gesture distance range and handled
 *			0	target outside the gesture distance range: not handled
 ********************************************************************/
uint8_t VL53L1__CheckGesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int16_t *lClickVal, const int16_t lClickLower, const int16_t lClickUpper){
	static uint8_t  clickDetected=0;	// there's a click running
	static uint32_t detectionTime=0;	// time at new click detected
	static uint8_t  dClickDetected=0;	// there's a doubleclick running
	static uint8_t  sClickWaiting=0;	// detected (and closed) a single click, waiting to see if it is a doubleclick, before reporting it
	static uint16_t initPos;			// initial gesture position on a longClick
	static uint16_t initVal;			// initial gesture position on a longClick

	static uint8_t  locLClick=0;		// longClick status (0 = no, 1 = yes, >1 waiting for stabilizing)
	static int32_t	residualDist=0;
	int32_t	lDist;
	uint8_t handled=0;

	if ((dist > GESTURE_MIN_DIST) && (dist < GESTURE_MAX_DIST)){ 	// target is in gesture area
		if (clickDetected){		// this is a click detected previously
			if ((HAL_GetTick()-detectionTime)>GESTURE_LONG_GEST_TRHSLD) { // if target detected for a long time: it is a long command
				if (locLClick) { 	// long command already (previously) detected
					if (locLClick>1) { // do not handle position until is above 1. That because after changing timingbudget, some meaningless readings have to be done
						(locLClick)--;
						if (locLClick==1) { // ok, now ranging is stable.
							initPos=dist;	// this is the starting position for lClickVal
							initVal=(*lClickVal);
						}
					} else {				// change lClickVal as per changes distance detected
/* proportional algorithm
						lDist=(int32_t)dist+residualDist;																								//add to the target position the distance previously not-considered for rounding reason
						int32_t locClickVal=((int32_t)lDist-(int32_t)initPos);																			//measure changing target position since the long-click start
						locClickVal=(locClickVal*((int32_t)lClickUpper-(int32_t)lClickLower))/((int32_t)GESTURE_MAX_DIST-(int32_t)GESTURE_MIN_DIST);	//apply the parameter ratio

						locClickVal+=(initVal);																										//add the result to the parameter value received...
						locClickVal = ((locClickVal>lClickUpper) ? lClickUpper: ((locClickVal<lClickLower) ? lClickLower : locClickVal));				//and keep it inside boundaries
						*lClickVal=locClickVal;																											//that's the result
 end of proportional algorithm */

/* incremental algorithm */
						lDist=(int32_t)dist+residualDist;																								//add to the target position the distance previously not-considered for rounding reason
						int32_t locClickVal=((int32_t)lDist-(int32_t)initPos);																			//measure changing target position since the long-click start
						locClickVal=(locClickVal*((int32_t)lClickUpper-(int32_t)lClickLower))/((int32_t)GESTURE_MAX_DIST-(int32_t)GESTURE_MIN_DIST);	//apply the parameter ratio
						locClickVal=(locClickVal*((int32_t)GESTURE_MEASUREMENT_TB+(int32_t)VL53L1__TB_IM_DELTA))/((int32_t)GESTURE_LGD_TTIME); 			//apply menu smoothness: see ".h" file
						residualDist=(locClickVal*(int32_t)GESTURE_LGD_TTIME)/((int32_t)GESTURE_MEASUREMENT_TB+(int32_t)VL53L1__TB_IM_DELTA);			//apply a reverse smoothness to the value obtained
						residualDist=(residualDist*((int32_t)GESTURE_MAX_DIST-(int32_t)GESTURE_MIN_DIST))/((int32_t)lClickUpper-(int32_t)lClickLower);	//apply a reverse parameter ratio
						residualDist=(lDist-(int32_t)initPos)-residualDist;																				//keep the difference to the original target position. This residual difference has to be added to the next detection
						locClickVal+=(*lClickVal);																										//add the result to the parameter value received...
						locClickVal = ((locClickVal>lClickUpper) ? lClickUpper: ((locClickVal<lClickLower) ? lClickLower : locClickVal));				//and keep it inside boundaries
						*lClickVal=locClickVal;																											//that's the result
/* end of incremental algorithm */
					}
				} else { 	//target detection is overriding the time threshold for a long-click: it is not a click, nor a doubleclick, it is a long-click
					locLClick=GESTURE_LONG_GEST_GRACE_NUM;	//changing TB reading must stabilize, this is the number of rangings to do before considering measured distance.
					VL53L1__SetTimingBudget(GESTURE_MEASUREMENT_TB,GESTURE_MEASUREMENT_TB+VL53L1__TB_IM_DELTA);
					dClickDetected=0;
					*sClick=0;
					*dClick=0;
				}
			}
		} else {	// it is a new detection
			uint32_t currentTime=HAL_GetTick();
			if (((currentTime-detectionTime)<GESTURE_DOUBLECLICK_TRHSLD) && ((currentTime-detectionTime)>0)){	// if previously a click detected within the double click interval: it is (probably) a double click
				dClickDetected=1;
			}
			*dClick=0;
			*sClick=0;
			clickDetected=1;
			detectionTime=HAL_GetTick();
		}
		handled=1; //distance falls inside gesture interval
	} else {							//no target into gesture interval: no clicking
		if (clickDetected){ 			// this is a first "no click" after a click series
			if (locLClick) {			// if it was a long-click. it can be closed immediately
				VL53L1__SetTimingBudget(GESTURE_DETECTION_TB,GESTURE_DETECTION_TB+VL53L1__TB_IM_DELTA);	//reset TB to the target detection timing
				locLClick=0;			// long-click ended
			} else if (dClickDetected){ //if it was a doubleclick notify it immediately
				*dClick=1;
				*sClick=0;
				dClickDetected=0;
				clickDetected=0;
				sClickWaiting=0;
				detectionTime=(HAL_GetTick()-GESTURE_DOUBLECLICK_TRHSLD); // reset doubleclick detection
			} else {	// it was a single click: wait to see if it will become a doubleclick
				sClickWaiting=1;
			}
			clickDetected=0;
		}
		if (sClickWaiting) {			//if there is a single click waiting to see if it will become a doubleclick
			if ((HAL_GetTick()-detectionTime)>GESTURE_DOUBLECLICK_TRHSLD) { // if time for a double click passed
				*dClick=0;
				*sClick=1;
				sClickWaiting=0;
			}
		}
	}
	*lClick=(!(!locLClick));			// lClick is 0/1, locLClick can be >1
	return handled;
};




/*****************************************************************
 * @brief	called by VL53L1__GestureMenu.
 * 			activates menu if GESTUREMENU_ENABLER_STARTSEQ is detected
 * 			chages menu item if GESTUREMENU_ENABLER_CHGITEM is detected
 * 			disables menu after a GESTUREMENU_ENABLER_TOUT timeout having no
 * 			any valid gesture detected
 * @param	sClick, dClick, lClick notifies to the function a
 * 			single/double/long click detectedy
 * @return	1 if menu status changed (GestureMenu_CurrentItem value changed)
 * 			-1 if gesture trapped by the function but menu status unchanged
 * 			0 uf gesture not used by the function (available)
 *****************************************************************/

int8_t VL53L1__GestureMenu_MenuEnabler(uint8_t sClick, uint8_t dClick, uint8_t lClick){
	uint8_t	MenuEnabler[]=GESTUREMENU_ENABLER_STARTSEQ;
	uint8_t	MenuChanger[]=GESTUREMENU_MENU_CHGITEMSEQ;
	uint8_t *MenuTest;
	uint8_t MenuSize;
	static uint8_t EnablerKey=0;			// current sequence position to detect
	static uint32_t EnablingStartTime=0;	// to detect Timeout within wich the Enabler Menu Sequence has to be detected
	static uint32_t MenuActiveTime;
	uint32_t CTime;
	int8_t status=0;

	CTime=HAL_GetTick();
	if ((EnablerKey) && (CTime-EnablingStartTime>GESTUREMENU_SEQ_TOUT)){ //if previously started a sequence and timout expired (uncompleted sequence)
		EnablerKey=0;														 //restart sequence
		EnablingStartTime=0;
	}

	if (!GestureMenu_CurrentItem) {  // if menu is not active proceed detecting an enabling sequence
		MenuTest=MenuEnabler;
		MenuSize=sizeof(MenuEnabler);
	} else {	// if menu is active proceed detecting a swap menu sequence
		MenuTest=MenuChanger;
		MenuSize=sizeof(MenuChanger);
	}

	if (((MenuTest[EnablerKey]==1) && sClick) || ((MenuTest[EnablerKey]==2) && dClick) || ((MenuTest[EnablerKey]==3) && lClick)) {  //if sequence step detected
		status=-1;	// enabling sequence, proceeding
		if (EnablerKey==0) //if it is the first step
			EnablingStartTime=CTime;
		EnablerKey++;	//ok, go to the next sequence step
		if (EnablerKey==MenuSize){ // if sequence completed, enable menu handling
			GestureMenu_CurrentItem=(GestureMenu_CurrentItem % GESTUREMENU_TOT_ITEMS)+1;	//global variable just for CubeMonitor

			MenuActiveTime=CTime;
			EnablerKey=0;
			status=1;	// sequence completed
		}
	}

	if (sClick || dClick || lClick) {	//if a click detected, keep alive menu
		MenuActiveTime=CTime;
	} else {	// no gesture
		if ((CTime-MenuActiveTime) > GESTUREMENU_MENU_TOUT) {  // if timeout expired, disable menu
			GestureMenu_CurrentItem=0;
			EnablerKey=0;
			EnablingStartTime=0;
		}
	}
	return status;
}




/*****************************************************************
 * @brief	gesture menu handling function:
 * 			-	if "Distance" falls into the menu ranging interval
 * 				(GESTURE_MIN_DIST to GESTURE_MAX_DIST)
 * 			-	if range status ("SStatus") reports an acceptable ranging
 * 				(below oe equal to RANGE_STATUS_THRESH)
 * 			-	detects gestures handling a gesture menu.
 * 			- 	menu handling starts after detecting a gesture activation sequence
 * 			-	moving through the menu items which number is defined by GESTUREMENU_ITEMS
 * 			-	calling VL53L1X__GestureMenu_Items() where user have to implement
 * 				the menu commands.
 * 			Function updates "GestureMenu_CurrentItem" global variable
 * 			indicating if the menu is inactive (value = 0) or which menu level is active
 * 			(from 1 to GESTUREMENU_ITEMS)
 * @param	SStatus		RangeStatus read from the sensor
 * 			Distance	ranging read from sensor
 * @return	1 if data (Distance and SStatus were used handling menu
 *****************************************************************/
uint8_t VL53L1__GestureMenu(uint8_t SStatus,uint16_t Distance){

	uint8_t 		shortClick=0,doubleClick=0,longClick=0,handled=0;
	static int16_t 	longClickVal=(TESTGESTURE_LCLICK_UPPER+TESTGESTURE_LCLICK_LOWER)/2;
	static int16_t 	longClickUpperValue=TESTGESTURE_LCLICK_UPPER;
	static int16_t 	longClickLowerValue=TESTGESTURE_LCLICK_LOWER;
	static uint8_t	firstCall=0;

	// detect a gesture, setting shortClick, doubleClick, LongClick and LongClickVal, if needed
	if (SStatus<=VL53L1__RANGE_STATUS_THRESH){
		handled=VL53L1__CheckGesture(Distance, &shortClick, &doubleClick, &longClick, &longClickVal, longClickLowerValue, longClickUpperValue);
	}
	// handle menu gesture
	if ((!GestureMenu_CurrentItem) && (shortClick || doubleClick || longClick)){ 	// menu inactive and some click detected: handle activation sequence
		if (VL53L1__GestureMenu_MenuEnabler(shortClick, doubleClick, longClick)) {;			//check if menu has to be enabled
			firstCall=1;	// on next call of VL53L1X__GestureMenu_Items(), notify that it is the first call
		}
	} else if (GestureMenu_CurrentItem) { 											// menu is active
		uint8_t status=VL53L1__GestureMenu_MenuEnabler(shortClick, doubleClick, longClick);
		if (status==1) {			//if menu changed
			firstCall=1;
		} else if (!status){	// if gesture not used by menuEnabler																		// single click or longclick
				VL53L1X__GestureMenu_Items(GestureMenu_CurrentItem, firstCall, shortClick, doubleClick, longClick, &longClickVal, &longClickLowerValue, &longClickUpperValue);
				firstCall=0;
		}
	}
	return handled; // notify that target measurement (Distance and SStatus) was used by GestureMenu
}








/*************************************************************
 * @brief	user function defining action corresponding to
 * 			the menu item enabled
 * 			first time menu item is called, parameter "firstCall" is 1
 * 			otherwise is 0
 * 			if using a longClick: longClickLowerValue and
 * 			longClickUpperValue should be set defining
 * 			the longClick valid range and, on "fistTime",
 * 			longClickVal must be set to the initial value
 *************************************************************/
__weak void VL53L1__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick, uint8_t doubleClick, uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue){

	switch (menuItem) {
	case 1:
		if (firstCall) {
		}
		break;
	}
	// etc.
}


