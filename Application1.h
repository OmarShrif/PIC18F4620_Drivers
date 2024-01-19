/* 
 * File:   Application1.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 10:46 PM
 */

#ifndef APPLICATION1_H
#define	APPLICATION1_H


/* Section : Includes */
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/button/ecu_button.h"
#include "ECU_Layer/relay/ecu_relay.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"

/* Section : Macro Declarations */
#define _XTAL_FREQ  8000000.0


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


/* Section : Functions Declarations */
void application_initialize(void);

#endif	/* APPLICATION1_H */

