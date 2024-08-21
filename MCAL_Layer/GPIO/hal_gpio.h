/* 
 * File:   hal_gpio.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:41 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */
#include "../mcal_std_types.h"
#include "pic18f4620.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/* Section : Macro Declarations */
#define BIT_MASK        (uint8)0x01
#define PORT_MASK       (uint8)0xFF
#define PORT_PIN_MAX_NUMBER     8
#define PORT_MAX_NUMBER         5

/* Section : Macro Functions Declarations */
#define HWREG8(_X)      (*((volatile uint8 *)0x))

#define SET_BIT(REG , BIT_POSN)         (REG |=  (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG , BIT_POSN)       (REG &=~ (BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG , BIT_POSN)      (REG ^=  (BIT_MASK << BIT_POSN))
#define READ_BIT(REG , BIT_POSN)        ((REG >> BIT_POSN) & 1)

/* Section : Data Type Declarations */
typedef enum
{
    GPIO_PORTA_INDEX = 0,
    GPIO_PORTB_INDEX,
    GPIO_PORTC_INDEX,
    GPIO_PORTD_INDEX,
    GPIO_PORTE_INDEX,
}port_index_t;

typedef enum
{
    GPIO_PIN0_INDEX = 0,
    GPIO_PIN1_INDEX,
    GPIO_PIN2_INDEX,
    GPIO_PIN3_INDEX,
    GPIO_PIN4_INDEX,
    GPIO_PIN5_INDEX,
    GPIO_PIN6_INDEX,
    GPIO_PIN7_INDEX,
}pin_index_t;

typedef enum
{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum
{
    GPIO_LOGIC_LOW = 0,
    GPIO_LOGIC_HIGH
}logic_t;

typedef struct 
{
    uint8 port      :3 ; /* @ref port_index_t */
    uint8 pin       :3 ; /* @ref pin_index_t */
    uint8 direction :1 ; /* @ref direction_t */
    uint8 logic     :1 ; /* @ref logic_t */
    
}pin_config_t;

/* Section : Functions Declarations (APIs) */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config ,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config , logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);


Std_ReturnType gpio_port_direction_initialize(port_index_t port , uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */
