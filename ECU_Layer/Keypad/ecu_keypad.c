/* 
 * File:   ecu_keypad.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:12 PM
 */

/* Section : Includes */
#include "ecu_keypad.h"

 
/* Section : Global Variables Definition */
static const uint8 keypad_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                                                    {'7','8','9','/'},
                                                                    {'4','5','6','*'},
                                                                    {'1','2','3','-'},
                                                                    {'c','0','=','+'}
                                                                };

/* Section : Helper Function Declaration */


/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pins Rows to be output and columns to be input
 * @param _keypad  pointer to the keypad module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad)
{
    Std_ReturnType ret = E_OK;
    uint8 row_counter = ZERO_INIT,column_counter = ZERO_INIT;
    if(_keypad != NULL)
    {
        for(row_counter = ZERO_INIT ; row_counter<KEYPAD_ROWS ; row_counter++)
        {
            ret = gpio_pin_initialize(&(_keypad->keypad_row_pin[row_counter]));
        }
        for(column_counter = ZERO_INIT ; column_counter<KEYPAD_COLUMNS ; column_counter++)
        {
            ret = gpio_pin_direction_initialize(&(_keypad->keypad_column_pin[column_counter]));
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Get the pressed number
 * @param _keypad  pointer to the keypad module configurations
 * @param value the pressed number
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad,uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_row_counter = ZERO_INIT,l_column_counter = ZERO_INIT,l_counter = ZERO_INIT;
    logic_t column_logic = ZERO_INIT;
    if((_keypad != NULL) && (value != NULL))
    {
        for(l_row_counter = ZERO_INIT ; l_row_counter<KEYPAD_ROWS ; l_row_counter++)
        {
            for(l_counter = ZERO_INIT ; l_counter<KEYPAD_ROWS ; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad->keypad_row_pin[l_counter]),GPIO_LOGIC_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad->keypad_row_pin[l_row_counter]),GPIO_LOGIC_HIGH);
            for(l_column_counter = ZERO_INIT ; l_column_counter<KEYPAD_COLUMNS ; l_column_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad->keypad_column_pin[l_column_counter]),&column_logic);
                if(GPIO_LOGIC_HIGH == column_logic)
                {
                    *value = keypad_values[l_row_counter][l_column_counter];
                }
            }
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 
