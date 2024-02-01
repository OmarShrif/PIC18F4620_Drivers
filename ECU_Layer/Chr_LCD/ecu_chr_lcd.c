/* 
 * File:   ecu_chr_lcd.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 28, 2024, 2:10 AM
 */

/* Section : Includes */
#include "ecu_chr_lcd.h"
 
/* Section : Global Variables Definition */

/* Reference to the Data Direction Control Registers */

/* Section : Helper Function Declaration */

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);

/* Section : Functions Definition */

/**
 * @brief Initialize the assigned pin to be output.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pins_counter = ZERO_INIT;
    if(lcd != NULL)
    {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_pins_counter = ZERO_INIT ; l_pins_counter<4 ; l_pins_counter++)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_pins_counter]));
        }
        /* Delay after power on*/
        __delay_ms(20);
        /* Selecting the mode of operation*/
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        
        /* Clear the LCD*/
        ret = lcd_4bit_send_command(lcd,_LCD_CLEAR);
        /* Return the cursor to home*/
        ret = lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        /* Entry mode selection*/
        ret = lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        /* Display mode selection*/
        ret = lcd_4bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        /* Selecting the mode of operation*/
        ret = lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        /* Return the cursor to home location*/
        ret = lcd_4bit_send_command(lcd,0x80);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Send command to the LCD.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param command : the command wanted to be send to the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        /* R/W is connected to ground by HardWare */
        /* RS set to low to choose Instruction Register*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOGIC_LOW);
        /* Send the high nipple form command*/
        ret = lcd_send_4bits(lcd,command >> 4);
        /* Send Enable signal*/
        ret = lcd_4bit_send_enable_signal(lcd);
        /* Send the low nipple form command*/
        ret = lcd_send_4bits(lcd,command);
        /* Send Enable signal*/
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a character on the lcd.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        /* R/W is connected to ground by HardWare */
        /* RS set to low to choose Instruction Register*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOGIC_HIGH);
        /* Send the high nipple form command*/
        ret = lcd_send_4bits(lcd,data >> 4);
        /* Send Enable signal*/
        ret = lcd_4bit_send_enable_signal(lcd);
        /* Send the low nipple form command*/
        ret = lcd_send_4bits(lcd,data);
        /* Send Enable signal*/
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a character on the lcd at (row,column) position.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = lcd_4bit_set_cursor(lcd,row,column);
        ret = lcd_4bit_send_char_data(lcd,data);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a String on the lcd.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((lcd != NULL) && (str != NULL))
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a string on the lcd at (row,column) position.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((lcd != NULL) && (str != NULL))
    {
        ret = lcd_4bit_set_cursor(lcd,row,column);
        ret = lcd_4bit_send_string(lcd,str);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a custom character on the lcd at (row,column) position.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param _char : the custom character array wanted to be displayed on the lcd
 * @param mem_pos : the character position on the CGRAM
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
                                              const uint8 _char[],uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(lcd != NULL)
    {
        ret = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = ZERO_INIT ; lcd_counter<=7 ; lcd_counter++)
        {
            ret = lcd_4bit_send_char_data(lcd,_char[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}


/**
 * @brief Initialize the assigned pin to be output.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pins_counter = ZERO_INIT;
    if(lcd != NULL)
    {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_pins_counter = ZERO_INIT ; l_pins_counter<8 ; l_pins_counter++)
        {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_pins_counter]));
        }
        /* Delay after power on*/
        __delay_ms(20);
        /* Selecting the mode of operation*/
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        /* Clear the LCD*/
        ret = lcd_8bit_send_command(lcd,_LCD_CLEAR);
        /* Return the cursor to home*/
        ret = lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        /* Entry mode selection*/
        ret = lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
        /* Display mode selection*/
        ret = lcd_8bit_send_command(lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        /* Selecting the mode of operation*/
        ret = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        /* Return the cursor to home location*/
        ret = lcd_8bit_send_command(lcd,0x80);
        
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Send command to the LCD.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param command : the command wanted to be send to the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pins_counter = ZERO_INIT ;
    if(lcd != NULL)
    {
        /* R/W is connected to ground by HardWare */
        /* RS set to low to choose Instruction Register*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOGIC_LOW);
        /* Send the command*/
        for(l_pins_counter = ZERO_INIT ; l_pins_counter<8 ; l_pins_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),(command >> l_pins_counter) & (uint8)0x01);
        }
        /* Send Enable signal*/
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a character on the lcd.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pins_counter = ZERO_INIT ;
    if(lcd != NULL)
    {
        /* R/W is connected to ground by HardWare */
        /* RS set to low to choose Instruction Register*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs),GPIO_LOGIC_HIGH);
        /* Send the command*/
        for(l_pins_counter = ZERO_INIT ; l_pins_counter<8 ; l_pins_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),(data >> l_pins_counter) & (uint8)0x01);
        }
        /* Send Enable signal*/
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a character on the lcd at (row,column) position.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = lcd_8bit_set_cursor(lcd,row,column);
        ret = lcd_8bit_send_char_data(lcd,data);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a String on the lcd.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((lcd != NULL) && (str != NULL))
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd,*str++);
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a string on the lcd at (row,column) position.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if((lcd != NULL) && (str != NULL))
    {
        ret = lcd_8bit_set_cursor(lcd,row,column);
        ret = lcd_8bit_send_string(lcd,str);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief Display a custom character on the lcd at (row,column) position.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param row : the row position on the lcd
 * @param column : the column position on the lcd
 * @param _char : the custom character array wanted to be displayed on the lcd
 * @param mem_pos : the character position on the CGRAM
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,
                                              const uint8 _char[],uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(lcd != NULL)
    {
        ret = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = ZERO_INIT ; lcd_counter<=7 ; lcd_counter++)
        {
            ret = lcd_8bit_send_char_data(lcd,_char[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd,row,column,mem_pos);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief convert 1-byte data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str != NULL)
    {
        memset((char *)str,'\0',4);
        sprintf((char *)str,"%i",value);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief convert 2-byte(short) data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str != NULL)
    {
        memset((char *)str,'\0',6);
        sprintf((char *)str,"%i",value);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * @brief convert 4-byte(int) data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str)
{
    Std_ReturnType ret = E_OK;
    if(str != NULL)
    {
        memset((char *)str,'\0',11);
        sprintf((char *)str,"%i",value);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}
/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd,uint8 _data_command)
{
    Std_ReturnType ret = E_OK;
    uint8 l_pins_counter = ZERO_INIT;
    if(lcd != NULL)
    {
        for(l_pins_counter = ZERO_INIT ; l_pins_counter<4 ; l_pins_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pins_counter]),(_data_command >> l_pins_counter) & (uint8)0x01);
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOGIC_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOGIC_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en),GPIO_LOGIC_LOW);
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        column--;
        switch (row)
        {
            case ROW1 : ret = lcd_4bit_send_command(lcd,(0x80 + column)); break ;
            case ROW2 : ret = lcd_4bit_send_command(lcd,(0xc0 + column)); break ;
            case ROW3 : ret = lcd_4bit_send_command(lcd,(0x94 + column)); break ;
            case ROW4 : ret = lcd_4bit_send_command(lcd,(0xd4 + column)); break ;
            default : break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column)
{
    Std_ReturnType ret = E_OK;
    if(lcd != NULL)
    {
        column--;
        switch (row)
        {
            case ROW1 : ret = lcd_8bit_send_command(lcd,(0x80 + column)); break ;
            case ROW2 : ret = lcd_8bit_send_command(lcd,(0xc0 + column)); break ;
            case ROW3 : ret = lcd_8bit_send_command(lcd,(0x94 + column)); break ;
            case ROW4 : ret = lcd_8bit_send_command(lcd,(0xd4 + column)); break ;
            default : break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}