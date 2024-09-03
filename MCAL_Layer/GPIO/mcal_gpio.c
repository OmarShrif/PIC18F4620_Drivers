/* 
 * File:   mcal_gpio.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on January 1, 2024, 9:41 PM
 */

/* Section : Includes */
#include "mcal_gpio.h"

 
/* Section : Global Variables Definition */

/* Reference to the Data Direction Control Registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to the Data Latch Registers (Read and Write to Data Latch) */
volatile uint8 *lat_registers[]  = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to the Port Status Registers */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* Section : Helper Function Declaration */


/* Section : Functions Definition */

#if GPIO_PORT_PIN_CONFIGURATIONS == GPIO_FEATURE_ENABLE
/**
 * @brief Initialize the direction of the specific pin @ref direction_t
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {
        switch(_pin_config->direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param direction_status
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config ,direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (direction_status != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {
        *direction_status = READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param logic
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config , logic_t logic)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {
        if(_pin_config->direction == GPIO_DIRECTION_OUTPUT)
        {
            switch(logic)
            {
                case GPIO_LOGIC_LOW:
                    CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
                    break;
                case GPIO_LOGIC_HIGH:
                    SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);      
                    break;
                default : ret = E_NOT_OK;
            }
        }
        else{ret = E_NOT_OK;}
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param logic
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config , logic_t *logic)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (logic != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {
        *logic = READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {
        TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    if((_pin_config != NULL) && (_pin_config->port <= PORT_MAX_NUMBER-1) && (_pin_config->pin <= PORT_PIN_MAX_NUMBER-1))
    {   
        ret = gpio_pin_direction_initialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    else{ret = E_NOT_OK;}
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATIONS == GPIO_FEATURE_ENABLE
/**
 * 
 * @param port
 * @param direction
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_direction_initialize(port_index_t port , uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if((port >= GPIO_PORTA) && (port <= PORT_MAX_NUMBER-1))
    {
        *tris_registers[port] = direction; 
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param port
 * @param direction_status
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port , uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    if((direction_status != NULL) && (port >= GPIO_PORTA) && (port <= PORT_MAX_NUMBER-1))
    {
        *direction_status = *tris_registers[port];
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_write_logic(port_index_t port , uint8 logic)
{
    Std_ReturnType ret = E_OK; 
    if((port >= GPIO_PORTA) && (port <= PORT_MAX_NUMBER-1))
    {
        *lat_registers[port] = logic;
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_read_logic(port_index_t port , uint8 *logic)
{
    Std_ReturnType ret = E_OK;
    if((logic != NULL) && (port >= GPIO_PORTA) && (port <= PORT_MAX_NUMBER-1))
    {
        *logic = *lat_registers[port];
    }
    else{ret = E_NOT_OK;}
    return ret;
}

/**
 * 
 * @param port
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if((port >= GPIO_PORTA) && (port <= PORT_MAX_NUMBER-1))
    {
        *lat_registers[port] ^= PORT_MASK; 
    }
    else{ret = E_NOT_OK;}
    return ret;
}
#endif

/* Section : ISRs Definition */


/* Section : Helper Function Definition */ 