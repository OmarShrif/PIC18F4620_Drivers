/* 
 * File:   ecu_layer_init.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 25, 2024, 8:59 PM
 */

/* Section : Includes */
#include "ecu_layer_init.h"


/* Section : Global Variables Definition */

led_t led1 = 
{
    .led_port = GPIO_PORTC,
    .led_pin = GPIO_PIN0,
    .led_status = GPIO_LOGIC_LOW
};

button_t btn1 = 
{
    .button_pin.port = GPIO_PORTD,
    .button_pin.pin = GPIO_PIN1,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOGIC_LOW,
    .button_connection = BUTTON_ACRIVE_HIGH,
    .button_status = BUTTON_RELEASED
};

relay_t relay1 = 
{
    .relay_port = GPIO_PORTA,
    .relay_pin = GPIO_PIN0,
    .relay_state = GPIO_LOGIC_LOW
};

dc_motor_t motor1 = 
{
    .dc_motor_pin[DC_MOTOR_PIN1].port = GPIO_PORTC,
    .dc_motor_pin[DC_MOTOR_PIN1].pin = GPIO_PIN0,
    .dc_motor_pin[DC_MOTOR_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[DC_MOTOR_PIN1].logic = GPIO_LOGIC_LOW,

    .dc_motor_pin[DC_MOTOR_PIN2].port = GPIO_PORTC,
    .dc_motor_pin[DC_MOTOR_PIN2].pin = GPIO_PIN1,
    .dc_motor_pin[DC_MOTOR_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[DC_MOTOR_PIN2].logic = GPIO_LOGIC_LOW
};

segment_t segment1 = 
{
    .segment_pin[SEGMENT_PIN0].port = GPIO_PORTC,
    .segment_pin[SEGMENT_PIN0].pin = GPIO_PIN0,
    .segment_pin[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[SEGMENT_PIN0].logic = GPIO_LOGIC_LOW,

    .segment_pin[SEGMENT_PIN1].port = GPIO_PORTC,
    .segment_pin[SEGMENT_PIN1].pin = GPIO_PIN1,
    .segment_pin[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[SEGMENT_PIN1].logic = GPIO_LOGIC_LOW,

    .segment_pin[SEGMENT_PIN2].port = GPIO_PORTC,
    .segment_pin[SEGMENT_PIN2].pin = GPIO_PIN2,
    .segment_pin[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[SEGMENT_PIN2].logic = GPIO_LOGIC_LOW,

    .segment_pin[SEGMENT_PIN3].port = GPIO_PORTC,
    .segment_pin[SEGMENT_PIN3].pin = GPIO_PIN3,
    .segment_pin[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[SEGMENT_PIN3].logic = GPIO_LOGIC_LOW,

    .segment_type = SEGMENT_COMMON_CATHODE
};

keypad_t keypad1 = 
{
    .keypad_row_pin[0].port = GPIO_PORTC,
    .keypad_row_pin[0].pin = GPIO_PIN0,
    .keypad_row_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pin[0].logic = GPIO_LOGIC_LOW,

    .keypad_row_pin[1].port = GPIO_PORTC,
    .keypad_row_pin[1].pin = GPIO_PIN1,
    .keypad_row_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pin[1].logic = GPIO_LOGIC_LOW,

    .keypad_row_pin[2].port = GPIO_PORTC,
    .keypad_row_pin[2].pin = GPIO_PIN2,
    .keypad_row_pin[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pin[2].logic = GPIO_LOGIC_LOW,

    .keypad_row_pin[3].port = GPIO_PORTC,
    .keypad_row_pin[3].pin = GPIO_PIN3,
    .keypad_row_pin[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pin[3].logic = GPIO_LOGIC_LOW,

    .keypad_column_pin[0].port = GPIO_PORTC,
    .keypad_column_pin[0].pin = GPIO_PIN4,
    .keypad_column_pin[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pin[0].logic = GPIO_LOGIC_LOW,

    .keypad_column_pin[1].port = GPIO_PORTC,
    .keypad_column_pin[1].pin = GPIO_PIN5,
    .keypad_column_pin[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pin[1].logic = GPIO_LOGIC_LOW,

    .keypad_column_pin[2].port = GPIO_PORTC,
    .keypad_column_pin[2].pin = GPIO_PIN6,
    .keypad_column_pin[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pin[2].logic = GPIO_LOGIC_LOW,

    .keypad_column_pin[3].port = GPIO_PORTC,
    .keypad_column_pin[3].pin = GPIO_PIN7,
    .keypad_column_pin[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_column_pin[3].logic = GPIO_LOGIC_LOW,
};

lcd_4bit_t lcd1 = 
{
    .lcd_rs.port = GPIO_PORTC,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOGIC_LOW,

    .lcd_en.port = GPIO_PORTC,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOGIC_LOW,

    .lcd_data[0].port = GPIO_PORTC,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOGIC_LOW,

    .lcd_data[1].port = GPIO_PORTC,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOGIC_LOW,

    .lcd_data[2].port = GPIO_PORTC,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOGIC_LOW,

    .lcd_data[3].port = GPIO_PORTC,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOGIC_LOW,
};

lcd_8bit_t lcd2 = 
{
    .lcd_rs.port = GPIO_PORTC,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOGIC_LOW,

    .lcd_en.port = GPIO_PORTC,
    .lcd_en.pin = GPIO_PIN7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOGIC_LOW,

    .lcd_data[0].port = GPIO_PORTD,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOGIC_LOW,

    .lcd_data[1].port = GPIO_PORTD,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOGIC_LOW,

    .lcd_data[2].port = GPIO_PORTD,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOGIC_LOW,

    .lcd_data[3].port = GPIO_PORTD,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOGIC_LOW,

    .lcd_data[4].port = GPIO_PORTD,
    .lcd_data[4].pin = GPIO_PIN4,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOGIC_LOW,

    .lcd_data[5].port = GPIO_PORTD,
    .lcd_data[5].pin = GPIO_PIN5,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOGIC_LOW,

    .lcd_data[6].port = GPIO_PORTD,
    .lcd_data[6].pin = GPIO_PIN6,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOGIC_LOW,

    .lcd_data[7].port = GPIO_PORTD,
    .lcd_data[7].pin = GPIO_PIN7,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOGIC_LOW,
};

/* Section : Functions Definition */

/**
 * @brief
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ecu_layer_initialize(void)
{
    Std_ReturnType ret_init = E_NOT_OK; 
    
    ret_init = led_initialize(&led1);
    
    return ret_init;
}