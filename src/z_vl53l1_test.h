/*
 * z_vl53l1_test.h
 *
 *  Created on: Nov 23, 2023
 *      Author: mauro
 *	rel. 2.00
 *
 *
 * How to use test functions:
 *
 * follow configutarion as indicated on
 * vl53l1_platform.h
 * and on
 * z_vl53l1_gesture.h
 *
 * then, the below functions feed global variables for the corresponding CubeMonitor scripts:
 *
 * TestRanging_VL53L1X.json
 * TestGesture_VL53L1X.json
 * TestMenu_VL53L1X.json
 *
 * these scripts were used on the CubeMonitor in videos shown on
 * https://www.youtube.com/playlist?list=PL6Fwy7aR3zSlArL6TJnSjWSbKmxM5BHnb
 *
 */
 
#ifndef _Z_VL53L1_TEST_H_
#define _Z_VL53L1_TEST_H_


#define TESTGESTURE_LCLICK_UPPER	1000
#define TESTGESTURE_LCLICK_LOWER	0

//number of sample for average and std deviation calculation
#define TESTGESTURE_DIM_ARR 		100
// time (ms) a click keeps active (to ,correctly show it in CubeMonitor)
#define TESTGESTURE_CLICK_DURATION	1000




void VL53L1__testRanging();
void VL53L1__testGesture();
void VL53L1__testMenu();
void VL53L1X__GestureMenu_Items(uint8_t menuItem, uint8_t firstCall, uint8_t shortClick, uint8_t doubleClick, uint8_t longClick,int16_t *longClickVal,int16_t *longClickLowerValue,int16_t *longClickUpperValue);

#endif
