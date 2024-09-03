/* 
 * File:   Application1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:09 PM
 */

/* Section : Includes */
#include "Application1.h"

/* Section : Functions Definition */

void RB4_APP_ISR(void);
void RB5_APP_ISR(void);
void RB6_APP_ISR(void);
void RB7_APP_ISR(void);

/* Section : Global Variables Definition */

Std_ReturnType ret = E_OK;

ext_interrupt_RBx_t rb4_obj = 
{
    .ext_interrupt_RBx_high_handler = RB4_APP_ISR,
    .ext_interrupt_RBx_low_handler = RB4_APP_ISR,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .RBx_pin.port = GPIO_PORTB,
    .RBx_pin.pin = GPIO_PIN4,
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    .RBx_pin.direction = GPIO_DIRECTION_INPUT
    #endif
};
ext_interrupt_RBx_t rb5_obj = 
{
    .ext_interrupt_RBx_high_handler = RB5_APP_ISR,
    .ext_interrupt_RBx_low_handler = RB5_APP_ISR,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .RBx_pin.port = GPIO_PORTB,
    .RBx_pin.pin = GPIO_PIN5,
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    .RBx_pin.direction = GPIO_DIRECTION_INPUT
    #endif
};
ext_interrupt_RBx_t rb6_obj = 
{
    .ext_interrupt_RBx_high_handler = RB6_APP_ISR,
    .ext_interrupt_RBx_low_handler = RB6_APP_ISR,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .RBx_pin.port = GPIO_PORTB,
    .RBx_pin.pin = GPIO_PIN6,
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    .RBx_pin.direction = GPIO_DIRECTION_INPUT
    #endif
};
ext_interrupt_RBx_t rb7_obj = 
{
    .ext_interrupt_RBx_high_handler = RB7_APP_ISR,
    .ext_interrupt_RBx_low_handler = RB7_APP_ISR,
    .priority = INTERRUPT_PRIORITY_HIGH,
    .RBx_pin.port = GPIO_PORTB,
    .RBx_pin.pin = GPIO_PIN7,
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    .RBx_pin.direction = GPIO_DIRECTION_INPUT
    #endif
};

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
    ret_init = ext_interrupt_RBx_Init(&rb4_obj);
    ret_init = ext_interrupt_RBx_Init(&rb5_obj);
    ret_init = ext_interrupt_RBx_Init(&rb6_obj);
    ret_init = ext_interrupt_RBx_Init(&rb7_obj);
}

void RB4_APP_ISR(void)
{
    led_turn_toggle(&led1);
}
void RB5_APP_ISR(void)
{
    led_turn_toggle(&led2);
}
void RB6_APP_ISR(void)
{
    led_turn_toggle(&led3);
}
void RB7_APP_ISR(void)
{
    led_turn_toggle(&led4);
}