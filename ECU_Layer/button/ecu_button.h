/* 
 * File:   ecu_button.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 15, 2024, 5:01 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum
{
    BUTTON_ACRIVE_HIGH = 0,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct
{
    pin_config_t button_pin;
    button_state_t button_status;
    button_active_t button_active;
}button_t;

/* Section : Functions Declarations */

Std_ReturnType button_initialize(const button_t *button);
Std_ReturnType button_read_status(const button_t *button,button_state_t button_status);

#endif	/* ECU_BUTTON_H */

