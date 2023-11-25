/*
 * z_LC_main.h
 *
 *  Created on: Nov 2, 2023
 *      Author: mauro
 */

#ifndef INC_Z_LC_MAIN_H_
#define INC_Z_LC_MAIN_H_


// project parameters
#define LC_FULL_SCALE_LIMIT 	2000 	//soffitto di casa //mm defined via SetFullScaleLimit() function
#define LC_ENABLE_COMMAND_LIMIT 400		//upper limit enabling "command mode" with a double touch
#define	LC_DOUBLE_TOUCH_TIMING	100


uint16_t SetFullScaleLimit();


#endif /* INC_Z_LC_MAIN_H_ */
