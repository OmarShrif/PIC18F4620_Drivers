/* 
 * File:   ecu_relay.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 16, 2024, 10:08 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON
            
}relay_state_t;

typedef struct
{
    uint8 relay_port    :3; /* @ref port_index_t */
    uint8 relay_pin     :3; /* @ref pin_index_t */
    uint8 relay_state   :1; /* @ref relay_state_t | logic_t*/ 
    uint8 reserved      :1; /* Not used */
    
}relay_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pin to be output and turn the relay off or on
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_initialize(const relay_t *relay);

/**
 * @brief Turn the relay on
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay);

/**
 * @brief Turn the relay off
 * @param relay pointer to the relay module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay);


#endif	/* ECU_RELAY_H */

