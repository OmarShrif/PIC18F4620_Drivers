/* 
 * File:   ecu_seven_seg.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 20, 2024, 4:49 PM
 */

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg.h"
 
/* Section : Global Variables Definition */

/* Reference to the Data Direction Control Registers */

/* Section : Helper Function Declaration */


/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pins to be output
 * @param seg  pointer to the 7-segment module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg)
{
    Std_ReturnType ret = E_OK;
    if(seg != NULL)
    {
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Write number on the 7-segment
 * @param seg  pointer to the 7-segment module configurations
 * @param number needed to be displayed
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number)
{
    Std_ReturnType ret = E_OK;
    if((seg != NULL) && (number<10))
    {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]),READ_BIT(number,0));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]),READ_BIT(number,1));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]),READ_BIT(number,2));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]),READ_BIT(number,3));
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 