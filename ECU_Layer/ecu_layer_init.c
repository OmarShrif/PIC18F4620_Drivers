/* 
 * File:   ecu_layer_init.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:59 PM
 */

/* Section : Includes */
#include "ecu_layer_init.h"

 
/* Section : Global Variables Definition */
led_t led1 = {.led_port = GPIO_PORTD_INDEX,.led_pin = GPIO_PIN0_INDEX,.led_status = LED_OFF};

keypad_t keypad1 = {
    .keypad_row_pins[0].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0_INDEX,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[1].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1_INDEX,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[2].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2_INDEX,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[3].port = GPIO_PORTC_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3_INDEX,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOGIC_LOW,
    .keypad_column_pins[0].port = GPIO_PORTC_INDEX,
    .keypad_column_pins[0].pin = GPIO_PIN4_INDEX,
    .keypad_column_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[0].logic = GPIO_LOGIC_LOW,
    .keypad_column_pins[1].port = GPIO_PORTC_INDEX,
    .keypad_column_pins[1].pin = GPIO_PIN5_INDEX,
    .keypad_column_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[1].logic = GPIO_LOGIC_LOW,
    .keypad_column_pins[2].port = GPIO_PORTC_INDEX,
    .keypad_column_pins[2].pin = GPIO_PIN6_INDEX,
    .keypad_column_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[2].logic = GPIO_LOGIC_LOW,
    .keypad_column_pins[3].port = GPIO_PORTC_INDEX,
    .keypad_column_pins[3].pin = GPIO_PIN7_INDEX,
    .keypad_column_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pins[3].logic = GPIO_LOGIC_LOW,
};
chr_lcd_4bit_t lcd1 = 
{
    .lcd_rs.port = GPIO_PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0_INDEX,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOGIC_LOW,
    
    .lcd_en.port = GPIO_PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1_INDEX,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOGIC_LOW,
    
    .lcd_data[0].port = GPIO_PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2_INDEX,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[1].port = GPIO_PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3_INDEX,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[2].port = GPIO_PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4_INDEX,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[3].port = GPIO_PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5_INDEX,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOGIC_LOW,
};
chr_lcd_8bit_t lcd2 = 
{
    .lcd_rs.port = GPIO_PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6_INDEX,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOGIC_LOW,
    
    .lcd_en.port = GPIO_PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN7_INDEX,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOGIC_LOW,
    
    .lcd_data[0].port = GPIO_PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN0_INDEX,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[1].port = GPIO_PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN1_INDEX,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[2].port = GPIO_PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN2_INDEX,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[3].port = GPIO_PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN3_INDEX,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[4].port = GPIO_PORTD_INDEX,
    .lcd_data[4].pin = GPIO_PIN4_INDEX,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[5].port = GPIO_PORTD_INDEX,
    .lcd_data[5].pin = GPIO_PIN5_INDEX,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[6].port = GPIO_PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN6_INDEX,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOGIC_LOW,
    
    .lcd_data[7].port = GPIO_PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN7_INDEX,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOGIC_LOW,
};
/* Section : Functions Definition */
Std_ReturnType ecu_layer_initialize(void)
{
    Std_ReturnType ret_init = E_NOT_OK;
    ret_init = lcd_4bit_initialize(&lcd1);
    ret_init = lcd_8bit_initialize(&lcd2);
    return ret_init; 
}