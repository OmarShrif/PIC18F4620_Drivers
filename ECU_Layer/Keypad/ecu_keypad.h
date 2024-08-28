/* 
 * File:   ecu_keypad.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:12 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"


/* Section : Macro Declarations */
#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef struct
{
    pin_config_t keypad_row_pin[KEYPAD_ROWS];
    pin_config_t keypad_column_pin[KEYPAD_COLUMNS];
    
}keypad_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pins Rows to be output and columns to be input
 * @param _keypad  pointer to the keypad module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad);

/**
 * @brief Get the pressed number
 * @param _keypad  pointer to the keypad module configurations
 * @param value the pressed number
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad,uint8 *value);


#endif	/* ECU_KEYPAD_H */

