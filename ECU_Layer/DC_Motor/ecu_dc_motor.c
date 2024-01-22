/* 
 * File:   ecu_dc_motor.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 19, 2024, 2:47 PM
 */


/* Section : Includes */
#include "ecu_dc_motor.h"

 
/* Section : Global Variables Definition */

/* Section : Helper Function Declaration */


/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pins to be output
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(_dc_motor != NULL)
    {
        
        ret = gpio_pin_initialize(&_dc_motor->dc_motor[DC_MOTOR_PIN1]);
        ret = gpio_pin_initialize(&_dc_motor->dc_motor[DC_MOTOR_PIN2]);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Move the DC motor to the right
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(_dc_motor != NULL)
    {
        
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN1],GPIO_LOGIC_HIGH);
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN2],GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Move the DC motor to the left
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(_dc_motor != NULL)
    {
        
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN1],GPIO_LOGIC_LOW);
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN2],GPIO_LOGIC_HIGH);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Stop the DC motor
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    if(_dc_motor != NULL)
    {
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN1],GPIO_LOGIC_LOW);
        ret = gpio_pin_write_logic(&_dc_motor->dc_motor[DC_MOTOR_PIN2],GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 


