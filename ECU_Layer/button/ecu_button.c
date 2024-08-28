/* 
 * File:   ecu_button.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 15, 2024, 5:01 AM
 */

/* Section : Includes */
#include "ecu_button.h"

 
/* Section : Global Variables Definition */

/* Section : Helper Function Declaration */


/* Section : Functions Definition */
/**
 * @brief Initialize the assigned pin to be input
 * @param button pointer to the button module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t *button)
{
    Std_ReturnType ret = E_OK;
    if(button != NULL)
    {
        ret = gpio_pin_direction_initialize(&(button->button_pin));
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Read the state of the button
 * @param button pointer to the button module configurations
 * @param button_status button state @ref button_state_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read_status(const button_t *button,button_state_t *button_status)
{
    Std_ReturnType ret = E_OK;
    logic_t pin_logic_status = GPIO_LOGIC_LOW;
    if((button != NULL) && (button_status))
    {
        ret = gpio_pin_read_logic(&(button->button_pin),&pin_logic_status);
        switch (button->button_connection)
        {
            case BUTTON_ACRIVE_HIGH:
                if(GPIO_LOGIC_HIGH == pin_logic_status)
                {
                    *button_status = BUTTON_PRESSED;
                }
                else
                {
                    *button_status = BUTTON_RELEASED;
                }
                ret = E_OK;
                break;
            case BUTTON_ACTIVE_LOW:
                if(GPIO_LOGIC_HIGH == pin_logic_status)
                {
                    *button_status = BUTTON_RELEASED;
                }
                else
                {
                    *button_status = BUTTON_PRESSED;
                }
                ret = E_OK;
                break;
            default:
                ret = E_NOT_OK;
                break; 
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 
