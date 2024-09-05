/* 
 * File:   ecu_layer_init.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:59 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "Led/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "Seven_Seg/ecu_seven_seg.h"
#include "Keypad/ecu_keypad.h"
#include "LCD/ecu_lcd.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */

extern led_t led1;
extern led_t led2;
extern button_t btn1;
extern relay_t relay1;
extern dc_motor_t motor1;
extern segment_t segment1;
extern keypad_t keypad1;
extern lcd_4bit_t lcd1;
extern lcd_8bit_t lcd2;

/* Section : Functions Declarations */
Std_ReturnType ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

