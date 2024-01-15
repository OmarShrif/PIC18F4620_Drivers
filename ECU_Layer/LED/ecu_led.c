/* 
 * File:   ecu_led.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 10:43 PM
 */

/* Section : Includes */
#include "ecu_led.h"

 
/* Section : Global Variables Definition */

/* Reference to the Data Direction Control Registers */

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pin to be output and turn the led off
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led != NULL)
    {
        pin_config_t pin = {.port = led->port ,.pin = led->pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        ret = gpio_pin_initialize(&pin);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Turn the led on
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led != NULL)
    {
        pin_config_t pin = {.port = led->port ,.pin = led->pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        ret = gpio_pin_write_logic(&pin,GPIO_LOGIC_HIGH);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Turn the led off
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led != NULL)
    {
        pin_config_t pin = {.port = led->port ,.pin = led->pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        ret = gpio_pin_write_logic(&pin,GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Toggle the led
 * @param led : pointer to the led module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    if(led != NULL)
    {
        pin_config_t pin = {.port = led->port ,.pin = led->pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = led->led_status};
        ret = gpio_pin_toggle_logic(&pin);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 