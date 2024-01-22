/* 
 * File:   ecu_seven_seg.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 20, 2024, 4:49 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section : Includes */
#include "ecu_seven_seg_cfg.h"


/* Section : Macro Declarations */
#define SEGMENT_PIN0    0
#define SEGMENT_PIN1    1
#define SEGMENT_PIN2    2
#define SEGMENT_PIN3    3

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */
typedef enum
{
    SEGMENT_COMMON_ANODE = 0,
    SEGMENT_COMMON_CATHODE        
}segment_type_t;

typedef struct
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pins to be output
 * @param seg  pointer to the 7-segment module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg);

/**
 * @brief Write number on the 7-segment
 * @param seg  pointer to the 7-segment module configurations
 * @param number needed to be displayed
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg,uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

