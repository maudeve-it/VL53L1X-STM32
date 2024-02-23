/*
 * z_vl53l1_gesture.h
 *
 *  Created on: Nov 23, 2023
 *      Author: mauro
 *	rel. 2.00
 *
 * How to use it:
 * Set the below configuration step 1 for gesture detection,
 * followed by step 2 configuration, if using gesture menu features.
 * Set step 3 configuration if using a menu led.
 *
 * Then,
 * add in main.c:
 *
 * VL53L1__Init()
 * VL53L1__InitGesture();
 *
 * (if you are here I suppose you are using gestures and/or gesture menus features).
 *
 * Finally add:
 *
 * VL53L1X_StartRanging(VL53L1__ADDR);
 *
 * enabling ranging before entering into main loop
 *
 * more info on https://www.youtube.com/playlist?list=PL6Fwy7aR3zSlArL6TJnSjWSbKmxM5BHnb
 *
 */

#ifndef INC_Z_VL53L1_GESTURE_H_
#define INC_Z_VL53L1_GESTURE_H_

/*||||||||||| USER/PROJECT PARAMETERS |||||||||||*/

/*****************     STEP 1      *****************
 ************* GESTURE DETECTION SETUP *************
 * parameters defining gesture detection behavior
 ***************************************************/
#define GESTURE_MIN_DIST			(0)				// gesture detected only if above this distance
#define GESTURE_MAX_DIST			(400)			// gesture detected only if below this distance
#define GESTURE_DOUBLECLICK_TRHSLD  (500)			// gesture is a doubleclick if 2 clicks within this time
#define GESTURE_LONG_GEST_TRHSLD	(1000)			// gesture detected longer than this time starts a "long click" measurement
#define GESTURE_DETECTION_TB		(20)			// time budget when not in long_click measurement
#define GESTURE_MEASUREMENT_TB		(200)			// time budget for a long_click position measurement
#define GESTURE_LONG_GEST_GRACE_NUM	(20)			// after long click TB change, wait this number of ranging cycles before measuring (stabilizing detection after TB changing)
#define GESTURE_LGD_TTIME			(5000)			// Differential Smoothness: a larger value makes a "smoother" hand response in a long click measuring (this is the time to go a long click from min to max value)

/*****************     STEP 2      *****************
 ************** GESTURE MENU HANDLING **************
 * parameters defining Gesture Menu behavior
 ***************************************************/
#define GESTUREMENU_TOT_ITEMS			(3)				// number of items in the menu
#define GESTUREMENU_ENABLER_STARTSEQ	{2,2}			// sequence enabling menu (2=doubleclick, 1=singleclick), empty array = menu always active
#define GESTUREMENU_SEQ_TOUT			(2000)			// timeout within which the enabling menu sequence must be executed
#define GESTUREMENU_MENU_CHGITEMSEQ		{2}				// command changing menu item (2=doubleclick, 1=singleclick)
#define GESTUREMENU_MENU_TOUT			(10000)			// timeout after which the menu exits - 0 =  never expires

/*****************     STEP 3      *****************
 ************ GESTURE MENU LED HANDLING **************
 * If there is a led (a GPIO pin called MENU_LED and
 * a timer) for the gesture menu status, uncomment
 * the below define and set the next parameters
 ***********************************************/
#define	GESTUREMENU_ISLED						// Is there a led for the gesture menu status? uncomment this line. Not needing a led, leave it commented
#ifdef GESTUREMENU_ISLED						// if YES
#define GESTUREMENU_LEDON		GPIO_PIN_SET	// pin level setting on the led
#define GESTUREMENU_LEDTIMER	htim3			// timer used by the menu led
#define GESTUREMENU_LED_ON_TIME	(50)			// time having led on
#define GESTUREMENU_LED_SPAUSE	(250)			// time having led off within the menu sequence
#define GESTUREMENU_LED_LPAUSE	(1000)			// time having led off between two sequences
#endif // GESTUREMENU_ISLED

/*|||||||| EBD OF USER/PROJECT PARAMETERS |||||||||*/

void VL53L1__InitGesture();
uint8_t VL53L1__CheckGesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int16_t *lClickVal, const int16_t lClickLower, const int16_t lClickUpper);
uint8_t VL53L1__GestureMenu(uint8_t SStatus,uint16_t Distance);
__weak void VL53L1X__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick,  uint8_t doubleClick, uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue);

#endif /* INC_Z_VL53L1_GESTURE_H_ */
