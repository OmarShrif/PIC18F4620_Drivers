/* 
 * File:   mcal_spi.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 30, 2024, 5:32 PM
 */

/* Section : Includes */

#include "mcal_spi.h"

/* Section : Global Variables Definition */

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

/* Section : Helper Function Declaration */

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void spi_Interrupt_Init(const spi_config_t *Config);
#endif
static void spi_Master_Mode_GPIO_PIN_Configurations(const spi_config_t *Config);
static void spi_Slave_Mode_GPIO_PIN_Configurations(const spi_config_t *Config);

/* Section : Functions Definition */

Std_ReturnType spi_Init(const spi_config_t *Config)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != Config)
    {
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if((Config->spi_mode == SPI_MASTER_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV16) ||
            (Config->spi_mode == SPI_MASTER_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)){
            spi_Master_Mode_GPIO_PIN_Configurations(Config);
        }
        else if((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DISABLE)){
            spi_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->ClockPolarity;
        /* SPI Sample time Select */
        SSPSTATbits.SMP = Config->SampleTime;
        /* SPI Clock Phase Select */
         SSPSTATbits.CKE = Config->ClockPhase;
        /* SPI Interrupt Configurations*/
        #if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        spi_Interrupt_Init(Config);
        #endif
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType spi_DeInit(const spi_config_t *Config)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != Config)
    {
        /* Disable the SPI Module*/
        SPI_DISABLE_MODULE();
        #if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of the SPI Module*/
        SPI_InterruptDisable();
        /* Clear Interrupt Flag for the SPI Module */
        SPI_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType spi_Send_Byte_Blocking(const spi_config_t *Config, const uint8 _data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != Config)
    {
        SSPBUF = _data;
        /* Waiting to transmit */
        while(!(PIR1bits.SSPIF)){} 
        SPI_InterruptFlagClear();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType spi_Send_Byte_NonBlocking(const spi_config_t *Config, const uint8 _data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != Config)
    {
        SSPBUF = _data;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType spi_Read_Byte_Blocking(const spi_config_t *Config, uint8 *_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != Config) && (NULL != _data))
    {
        /* Receive not complete, SSPBUF is empty */
        while(SSPSTATbits.BF == 0); 
        *_data = SSPBUF;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType spi_Read_Byte_NonBlocking(const spi_config_t *Config, uint8 *_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != Config) && (NULL != _data))
    {
        *_data = SSPBUF;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/* Section : Helper Function Definition */ 

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static void spi_Interrupt_Init(const spi_config_t *Config)
{
    /* Interrupt Configurations */
    SPI_InterruptHandler = Config->SPI_InterruptHandler;
    /* Interrupt Priority Configurations */
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
    if(INTERRUPT_PRIORITY_HIGH == Config->spi_priority)
    { 
        SPI_PrioritySetHigh(); 
    }
    else if(INTERRUPT_PRIORITY_LOW == Config->spi_priority)
    {
        SPI_PrioritySetLow(); 
    }
    else{ /* Nothing  */}
    #endif
    SPI_InterruptFlagClear();
    SPI_InterruptEnable();
    global_interrupt_Enable();   
}

#endif

static void spi_Master_Mode_GPIO_PIN_Configurations(const spi_config_t *Config)
{
    Std_ReturnType ret = E_OK;
    pin_config_t SPI_CLK = {.port = GPIO_PORTC, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = GPIO_PORTC, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SDO = {.port = GPIO_PORTC, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    
    ret = gpio_pin_direction_initialize(&SPI_CLK);
    ret = gpio_pin_direction_initialize(&SPI_SDI);
    ret = gpio_pin_direction_initialize(&SPI_SDO); 
}

static void spi_Slave_Mode_GPIO_PIN_Configurations(const spi_config_t *Config)
{
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_CLK = {.port = GPIO_PORTC, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SDI = {.port = GPIO_PORTC, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SDO = {.port = GPIO_PORTC, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SS  = {.port = GPIO_PORTA, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};
    
    ret = gpio_pin_direction_initialize(&SPI_CLK); 
    ret = gpio_pin_direction_initialize(&SPI_SDI);
    ret = gpio_pin_direction_initialize(&SPI_SDO); 
    
    if(SPI_SLAVE_SS_ENABLE == Config->spi_mode)
    {
        ret = gpio_pin_direction_initialize(&SPI_SS);
    }
    else{/* Nothing */}
}

/* Section : ISRs Definition */

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void SPI_ISR(void)
{
    /* The SPI interrupt occurred (flag must be cleared by software) */
    SPI_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(SPI_InterruptHandler)
    {
        SPI_InterruptHandler();
    }
    else{/* Nothing */}
} 

#endif