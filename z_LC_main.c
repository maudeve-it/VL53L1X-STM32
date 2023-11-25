/*
 * z_LC_main.c
 *
 *  Created on: Nov 2, 2023
 *      Author: mauro
 */


#include "main.h"

uint16_t SetFullScaleLimit(){
	const uint16_t repetitions=3000;
	uint32_t fsl=0;
	uint16_t k;

	for (k=0;k<repetitions;k++){
		fsl+=VL53L1__GetDistance(0);
	};
	fsl=(fsl+repetitions/2)/repetitions;
	return (uint16_t)fsl;
}


uint8_t IsDoubleTouch(){
	return 0;
}
