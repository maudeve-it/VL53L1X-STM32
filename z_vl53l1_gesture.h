/*
 * z_vl53l1_gesture.h
 *
 *  Created on: Nov 23, 2023
 *      Author: mauro
 */

#ifndef INC_Z_VL53L1_GESTURE_H_
#define INC_Z_VL53L1_GESTURE_H_



#define GESTURE_MIN_DIST			(0)		// gesture only if target detected above this distance
#define GESTURE_MAX_DIST			(400)	// gesture only if target detected below this distance
#define GESTURE_LONG_GEST_TRHSLD	(2000)	// gesture detected longer than this time starts a "long gesture"
#define GESTURE_DOUBLECLICK_TRHSLD  (1000)	// gesture is a doubleclick id 2 clicks within this time


void check_gesture(uint16_t dist, uint8_t *sClick, uint8_t *dClick, uint8_t *lClick, int8_t *lClickVal);


#endif /* INC_Z_VL53L1_GESTURE_H_ */
