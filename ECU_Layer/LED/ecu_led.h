/* 
 * File:   ecu_led.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 10:43 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_led_cfg.h"

/* Section : Macro Declarations */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    LED_OFF = 0,
    LED_ON
}led_status_t;

typedef struct
{
    uint8 led_port      :3; /* @ref port_index_t */
    uint8 led_pin       :3; /* @ref pin_index_t */
    uint8 led_status    :1; /* @ref led_status_t | logic_t*/ 
    uint8 reserved      :1; // Not used
}led_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pin to be output and turn the led off or on
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led);

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

