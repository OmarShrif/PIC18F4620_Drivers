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

/* Section : Macro Declarations */
#define _XTAL_FREQ  4000000.0

#define ENABLE      1
#define DISABLE     0
#define GPIO_TEST   DISABLE
#define LED_TEST    DISABLE

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


/* Section : Functions Declarations */
void application_initialize(void);

#endif	/* APPLICATION1_H */

