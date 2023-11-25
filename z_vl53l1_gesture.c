/*
 * z_vl53l1_gesture.c
 *
 *  Created on: Nov 23, 2023
 *      Author: mauro
 */

#include <main.h>




void check_gesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int8_t *lClickVal){
	static uint8_t clickDetected=0;
	static uint32_t detectionTime=0;
	static uint16_t lDetectionPos=0;
	static uint8_t dClickDetected=0;


	if ((dist > GESTURE_MIN_DIST) && (dist < GESTURE_MAX_DIST)){ 	// target is in gesture area
		if (clickDetected){		// it is a click detected previously
			if ((HAL_GetTick()-detectionTime)>GESTURE_LONG_GEST_TRHSLD) { // if target detected for a long time: it is a long command
				if (lClick){ // long command previously detected
					*lClickVal = ((((int32_t)(dist-lDetectionPos))*100/((GESTURE_MAX_DIST-GESTURE_MIN_DIST)/2)));
					*lClickVal = ((*lClickVal>100) ? 100 : *lClickVal);
					*lClickVal = ((*lClickVal<-100) ? -100 : *lClickVal);
				} else { 	// target detection is overriding the time threshold for a long command: it is not a click, nor a doubleclick, it is a long-command
					*lClick=1;
					dClickDetected=0;
					lDetectionPos=dist;
					*lClickVal=0;
					*sClick=0;
					*dClick=0;
				}
			}
		} else {	// if it is a new detection
			if ((HAL_GetTick()-detectionTime)<GESTURE_DOUBLECLICK_TRHSLD) { // if previous target detected within the double click interval: it is (probably) a double click
				dClickDetected=1;
				*dClick=0;
			}
			*sClick=0;
			clickDetected=1;
			detectionTime=HAL_GetTick();
		}
	} else { //no target, no a running click
		if (clickDetected){ // there was a click previously?
			if (*lClick) {	// if it was a long click. It ended, it can be closed immediately
				*lClick=0;
				*lClickVal=0;
			} else { // // it was a click or a Double click: before notifying a click wait to see if it will become a doubleclick
				uint32_t a=HAL_GetTick();
				if ((HAL_GetTick()-detectionTime)<GESTURE_DOUBLECLICK_TRHSLD) { // the double click interval is over. the ended click is a single one. Notify it!
					clickDetected=0;
					if (dClickDetected){
						*dClick=1;
						*sClick=0;
					} else {
						*dClick=0;
						*sClick=1;
					}
				}
			}
		}
	}
};
