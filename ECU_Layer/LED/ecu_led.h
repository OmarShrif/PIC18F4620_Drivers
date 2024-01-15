/* 
 * File:   ecu_led.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 10:43 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct
{
    uint8 port          :3; /* @ref port_index_t */
    uint8 pin           :3; /* @ref pin_index_t */
    uint8 led_status    :1; /* @ref led_status_t | logic_t*/ 
    uint8 reserved      :1; // Not used
}led_t;

/* Section : Functions Declarations */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

