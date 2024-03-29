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

Std_ReturnType ret = E_NOT_OK;
uint8 customChar1[] = {0x0E,0x0A,0x11,0x11,0x11,0x11,0x1F,0x00};
uint8 customChar2[] = {0x0E,0x0A,0x11,0x11,0x11,0x1F,0x1F,0x00};
uint8 customChar3[] = {0x0E,0x0A,0x11,0x11,0x1F,0x1F,0x1F,0x00};
uint8 customChar4[] = {0x0E,0x0A,0x11,0x1F,0x1F,0x1F,0x1F,0x00};
uint8 customChar5[] = {0x0E,0x0A,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};
uint8 customChar6[] = {0x0E,0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x00};

void welcome_message(void)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_lcd1_counter = ZERO_INIT;
    
    for(l_lcd1_counter = 1; l_lcd1_counter<=5 ; l_lcd1_counter++)
    {
        ret = lcd_4bit_send_string_pos(&lcd1,1,7,"Hello All");
        __delay_ms(500);
        ret = lcd_4bit_send_command(&lcd1,_LCD_CLEAR);
        __delay_ms(500);
    }
}

void loading_screen(void)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_lcd2_counter = ZERO_INIT;
    ret = lcd_8bit_send_string_pos(&lcd2,1,1,"Loading");
    
    for(l_lcd2_counter = 1; l_lcd2_counter<=8 ; l_lcd2_counter++)
    {
        ret = lcd_8bit_send_char_data(&lcd2,'.');
        __delay_ms(500);
    }
    ret = lcd_8bit_send_command(&lcd2,_LCD_CLEAR);
}
void battary_charging(void)
{
    uint8 l_lcd2_counter = ZERO_INIT;
    for(l_lcd2_counter = 1; l_lcd2_counter<=8 ; l_lcd2_counter++)
    {
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar1,0);__delay_ms(250);
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar2,0);__delay_ms(250);
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar3,0);__delay_ms(250);
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar4,0);__delay_ms(250);
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar5,0);__delay_ms(250);
        ret = lcd_8bit_send_custom_char_pos(&lcd2,1,20,customChar6,0);__delay_ms(250);
    }
}
void battary_charging2(void)
{
    uint8 l_lcd1_counter = ZERO_INIT;
    for(l_lcd1_counter = 1; l_lcd1_counter<=8 ; l_lcd1_counter++)
    {
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar1,0);__delay_ms(250);
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar2,0);__delay_ms(250);
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar3,0);__delay_ms(250);
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar4,0);__delay_ms(250);
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar5,0);__delay_ms(250);
        ret = lcd_4bit_send_custom_char_pos(&lcd1,1,20,customChar6,0);__delay_ms(250);
    }
}

/* Section : Functions Definition */
int main() 
{
    application_initialize();
    //welcome_message();
    //loading_screen();
    battary_charging2();
    while(1)
    {
        
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void)
{
    Std_ReturnType ret_init = E_NOT_OK;
    ret_init = ecu_layer_initialize();
}