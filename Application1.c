/* 
 * File:   Application1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:09 PM
 */

/* Section : Includes */
#include "Application1.h"

/* Section : Functions Declarations */

/* Section : Global Variables Definition */

Std_ReturnType ret = E_OK;

/* Section : Functions Definition */

int main() 
{
    application_initialize();
    while(1)
    {
        
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    Std_ReturnType ret_init = E_OK;
    ret_init = ecu_layer_initialize();
}
