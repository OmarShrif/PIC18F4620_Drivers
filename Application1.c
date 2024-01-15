/* 
 * File:   Application1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:09 PM
 */

/* Section : Includes */
#include "Application1.h"
 
/* Section : Global Variables Definition */
#if GPIO_TEST == ENABLE
pin_config_t led_1 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN0_INDEX,.direction = GPIO_DIRECTION_OUTPUT,.logic = GPIO_LOGIC_LOW};
pin_config_t led_2 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN1_INDEX,.direction = GPIO_DIRECTION_OUTPUT,.logic = GPIO_LOGIC_LOW};
pin_config_t led_3 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN2_INDEX,.direction = GPIO_DIRECTION_OUTPUT,.logic = GPIO_LOGIC_LOW};
pin_config_t btn_1 = {.port = GPIO_PORTD_INDEX,.pin = GPIO_PIN0_INDEX,.direction = GPIO_DIRECTION_INPUT,.logic = GPIO_LOGIC_LOW};
 
direction_t led_1_st;
logic_t btn_1_log;
#endif

#if LED_TEST == ENABLE
led_t  led1 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN0_INDEX,.led_status = GPIO_LOGIC_LOW};
led_t  led2 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN1_INDEX,.led_status = GPIO_LOGIC_LOW};
led_t  led3 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN2_INDEX,.led_status = GPIO_LOGIC_LOW};
led_t  led4 = {.port = GPIO_PORTC_INDEX,.pin = GPIO_PIN3_INDEX,.led_status = GPIO_LOGIC_LOW};
#endif

Std_ReturnType ret = E_NOT_OK;

/* Section : Functions Definition */
int main() 
{
    application_initialize();
    
    while(1)
    {
        #if GPIO_TEST == ENABLE
        ret = gpio_pin_read_logic(&btn_1,&btn_1_log);
        if(btn_1_log == GPIO_LOGIC_HIGH)
        {
            ret = gpio_pin_toggle_logic(&led_2);
        __delay_ms(250);
        }
        else
        {
            ret = gpio_pin_toggle_logic(&led_1);
            ret = gpio_pin_toggle_logic(&led_3);
        __delay_ms(250);
        }
        #endif

        #if LED_TEST == ENABLE
        ret = led_turn_on(&led1);
        ret = led_turn_on(&led2);
        __delay_ms(250);
        ret = led_turn_toggle(&led2);
        ret = led_turn_toggle(&led4);
        __delay_ms(250);
        ret = led_turn_toggle(&led1);
        ret = led_turn_toggle(&led3);
        __delay_ms(250);
        #endif
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    Std_ReturnType ret_init = E_NOT_OK;
    #if GPIO_TEST == ENABLE
    ret_init = gpio_pin_initialize(&btn_1);
    ret_init = gpio_pin_initialize(&led_1);
    ret_init = gpio_pin_initialize(&led_2);
    ret_init = gpio_pin_initialize(&led_3);
    #endif

    #if LED_TEST == ENABLE
    ret_init = led_initialize(&led1);
    ret_init = led_initialize(&led2);
    ret_init = led_initialize(&led3);
    ret_init = led_initialize(&led4);
    #endif
}