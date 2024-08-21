/* 
 * File:   Application1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:09 PM
 */

/* Section : Includes */
#include "Application1.h"
 
/* Section : Global Variables Definition */

Std_ReturnType ret = E_OK;

/* Section : Functions Definition */

int main() 
{
    application_initialize();
    TRISA = 0b00000000;
    LATA = 0b11111111;
    
    TRISB = 0b00000000;
    LATB = 0b11111111;
    
    TRISC = 0b00000000;
    LATC = 0b11111111;
    
    TRISD = 0b00000000;
    LATD = 0b11111111;
    
    TRISE = 0b00000000;
    LATE = 0b11111111;
    
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