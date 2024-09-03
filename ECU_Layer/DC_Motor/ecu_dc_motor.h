/* 
 * File:   ecu_dc_motor.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 19, 2024, 2:47 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/* Section : Includes */
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef enum
{
    DC_MOTOR_PIN1 = 0,
    DC_MOTOR_PIN2    
}dc_motor_pins_t;

typedef enum
{
    DC_MOTOR_OFF = 0,
    DC_MOTOR_ON    
}dc_motor_state_t;

typedef struct
{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pins to be output
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);

/**
 * @brief Move the DC motor to the right
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);

/**
 * @brief Move the DC motor to the left
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);

/**
 * @brief Stop the DC motor
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);


#endif	/* ECU_DC_MOTOR_H */

