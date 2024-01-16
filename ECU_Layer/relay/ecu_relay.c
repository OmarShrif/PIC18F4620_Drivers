/* 
 * File:   ecu_relay.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 16, 2024, 10:08 AM
 */

/* Section : Includes */
#include "ecu_relay.h"

 
/* Section : Global Variables Definition */

/* Section : Helper Function Declaration */


/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pin to be output and turn the relay off or on
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay != NULL)
    {
        pin_config_t pin = {.port = relay->relay_port ,.pin = relay->relay_pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_state};
        ret = gpio_pin_initialize(&pin);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Turn the relay on
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay != NULL)
    {
        pin_config_t pin = {.port = relay->relay_port ,.pin = relay->relay_pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_state};
        ret = gpio_pin_write_logic(&pin,GPIO_LOGIC_HIGH);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Turn the relay off
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay)
{
    Std_ReturnType ret = E_OK;
    if(relay != NULL)
    {
        pin_config_t pin = {.port = relay->relay_port ,.pin = relay->relay_pin , 
                            .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_state};
        ret = gpio_pin_write_logic(&pin,GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 

