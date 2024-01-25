/* 
 * File:   ecu_layer_init.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:59 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "Seven_Seg/ecu_seven_seg.h"
#include "Keypad/ecu_keypad.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
extern keypad_t keypad1;
extern led_t led1;

/* Section : Functions Declarations */
Std_ReturnType ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

