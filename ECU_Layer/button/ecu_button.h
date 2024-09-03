/* 
 * File:   ecu_button.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 15, 2024, 5:01 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_button_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
}button_state_t;

typedef enum
{
    BUTTON_ACTIVE_LOW = 0,
    BUTTON_ACRIVE_HIGH
}button_active_t;

typedef struct
{
    pin_config_t button_pin;
    button_state_t button_status;
    button_active_t button_connection;
}button_t;

/* Section : Functions Declarations */

/* Section : Functions Definition */
/**
 * @brief Initialize the assigned pin to be input
 * @param button pointer to the button module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t *button);

/**
 * @brief Read the state of the button
 * @param button pointer to the button module configurations
 * @param button_status button state @ref button_state_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read_status(const button_t *button,button_state_t *button_status);

#endif	/* ECU_BUTTON_H */

