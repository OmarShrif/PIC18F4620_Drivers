/* 
 * File:   Application1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:09 PM
 */

/* Section : Includes */
#include "Application1.h"
#include "ECU_Layer/relay/ecu_relay.h"
 
/* Section : Global Variables Definition */

relay_t relay1 = {
    .relay_port = GPIO_PORTA_INDEX,
    .relay_pin = GPIO_PIN0_INDEX,
    .relay_state = RELAY_OFF
};

Std_ReturnType ret = E_NOT_OK;

/* Section : Functions Definition */
int main() 
{
    application_initialize();
    
    while(1)
    {
        ret = relay_turn_on(&relay1);
        __delay_ms(1000);
        ret = relay_turn_off(&relay1);
        __delay_ms(1000);
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    Std_ReturnType ret_init = E_NOT_OK;
    ret_init = relay_initialize(&relay1);
}