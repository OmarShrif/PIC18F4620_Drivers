/* 
 * File:   ecu_chr_lcd.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 28, 2024, 2:10 AM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/mcal_gpio.h"
#include "ecu_lcd_cfg.h"

/* Section : Macro Declarations */

#define _LCD_CLEAR                                  0X01
#define _LCD_RETURN_HOME                            0x02

#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF               0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON                0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF               0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON                0x07

#define _LCD_DISPLAY_OFF_CURSOR_OFF                 0x08

#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF    0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON     0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF     0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON      0x0F

#define _LCD_CURSOR_MOVE_LEFT                       0x10
#define _LCD_CURSOR_MOVE_RIGHT                      0x14

#define _LCD_DISPLAY_SHIFT_LEFT                     0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                    0x1C

#define _LCD_4BIT_MODE_2_LINE                       0x28
#define _LCD_8BIT_MODE_2_LINE                       0x38

#define _LCD_CGRAM_START                            0x40
#define _LCD_DDRAM_START                            0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */

typedef struct
{
  pin_config_t lcd_rs;
  pin_config_t lcd_en;
  pin_config_t lcd_data[4];
}lcd_4bit_t;

typedef struct
{
  pin_config_t lcd_rs;
  pin_config_t lcd_en;
  pin_config_t lcd_data[8];
}lcd_8bit_t;

/* Section : Functions Declarations */

/**
 * @brief Initialize the assigned pin to be output.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd);

/**
 * @brief Send command to the LCD.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param command : the command wanted to be send to the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd,uint8 command);

/**
 * @brief Display a character on the lcd.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd,uint8 data);

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
Std_ReturnType lcd_4bit_send_char_data_at_pos(const lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data);

/**
 * @brief Display a String on the lcd.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd,uint8 *str);

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
Std_ReturnType lcd_4bit_send_string_at_pos(const lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str);

/**
 * @brief Display a custom character on the lcd.
 * @param lcd : pointer to the 4-bit lcd module configurations
 * @param _char : the custom character array wanted to be displayed on the lcd
 * @param mem_pos : the character position on the CGRAM
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd,const uint8 _char[],uint8 mem_pos);

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
Std_ReturnType lcd_4bit_send_custom_char_at_pos(const lcd_4bit_t *lcd,uint8 row,uint8 column,
                                              const uint8 _char[],uint8 mem_pos);

/**
 * @brief Initialize the assigned pin to be output.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd);

/**
 * @brief Send command to the LCD.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param command : the command wanted to be send to the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd,uint8 command);

/**
 * @brief Display a character on the lcd.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param data : the data wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd,uint8 data);

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
Std_ReturnType lcd_8bit_send_char_data_at_pos(const lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data);

/**
 * @brief Display a String on the lcd.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param str : the string wanted to be displayed on the lcd
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd,uint8 *str);

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
Std_ReturnType lcd_8bit_send_string_at_pos(const lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str);

/**
 * @brief Display a custom character on the lcd.
 * @param lcd : pointer to the 8-bit lcd module configurations
 * @param _char : the custom character array wanted to be displayed on the lcd
 * @param mem_pos : the character position on the CGRAM
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd,const uint8 _char[],uint8 mem_pos);

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
Std_ReturnType lcd_8bit_send_custom_char_at_pos(const lcd_8bit_t *lcd,uint8 row,uint8 column,
                                              const uint8 _char[],uint8 mem_pos);

/**
 * @brief convert 1-byte data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_byte_to_string(uint8 value,uint8 *str);

/**
 * @brief convert 2-byte(short) data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_short_to_string(uint16 value,uint8 *str);

/**
 * @brief convert 4-byte(int) data to string
 * @param value : value needed to be converted
 * @param str : array where the string will be after converting
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType convert_int_to_string(uint32 value,uint8 *str);

#endif	/* ECU_LCD_H */

