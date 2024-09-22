/* 
 * File:   mcal_eusart.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 22, 2024, 8:45 AM
 */


/* Section : Includes */

#include "mcal_eusart.h"

/* Section : Global Variables Definition */

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_TX_InterruptHandler)(void) = NULL;
#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (*EUSART_RX_InterruptHandler)(void) = NULL;
    static void (*EUSART_FramingErrorHandler)(void) = NULL;
    static void (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif  

/* Section : Helper Function Declaration */

#if (EUSART_TX_MODULE == EUSART_MODULE_ENABLE) || (EUSART_RX_MODULE == EUSART_MODULE_ENABLE)
    static void eusart_Baud_Rate_Calculation(const eusart_config_t *_eusart);
#endif  
    
#if EUSART_TX_MODULE == EUSART_MODULE_ENABLE
    static void eusart_async_TX_Init(const eusart_config_t *_eusart);
#endif  

#if EUSART_RX_MODULE == EUSART_MODULE_ENABLE
    static void eusart_async_RX_Init(const eusart_config_t *_eusart);
#endif  

/* Section : Functions Definition */

#if (EUSART_TX_MODULE == EUSART_MODULE_ENABLE) || (EUSART_RX_MODULE == EUSART_MODULE_ENABLE)

    Std_ReturnType eusart_async_Init(const eusart_config_t *_eusart)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _eusart)
        {   
            /* Disable EUSART Module */
            RCSTAbits.SPEN = EUSART_MODULE_DISABLE; 
            /* TX : Input Configuration as needed */
            TRISCbits.RC6 = 1;  
            /* RX : Input Configuration as needed */
            TRISCbits.RC7 = 1;                    
            eusart_Baud_Rate_Calculation(_eusart);
            #if EUSART_TX_MODULE == EUSART_MODULE_ENABLE
                ret = eusart_async_TX_Init(_eusart);
            #endif  

            #if EUSART_RX_MODULE == EUSART_MODULE_ENABLE
                ret = eusart_async_RX_Init(_eusart);
            #endif 
            /* Enable EUSART Module */
            RCSTAbits.SPEN = EUSART_MODULE_ENABLE;  
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }

    Std_ReturnType eusart_async_DeInit(const eusart_config_t *_eusart)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _eusart)
        {    
            RCSTAbits.SPEN = EUSART_MODULE_DISABLE; /* Disable EUSART Module */
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }


    #if EUSART_RX_MODULE == EUSART_MODULE_ENABLE

        Std_ReturnType eusart_async_ReadByteBlocking(uint8 *_data)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _data)
            {    
                while(!PIR1bits.RCIF);
                *_data = RCREG;
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }

        Std_ReturnType eusart_async_ReadByteNonBlocking(uint8 *_data)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _data)
            {    
                if(1 == PIR1bits.RCIF)
                {
                    *_data = RCREG;
                }
                else{ ret = E_NOT_OK; }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }

        Std_ReturnType eusart_async_RX_Restart(void)
        {
            Std_ReturnType ret = E_OK;

            RCSTAbits.CREN = 0; /* Disables receiver */
            RCSTAbits.CREN = 1; /* Enables receiver */
            
            return ret;
        }

    #endif

    #if EUSART_TX_MODULE == EUSART_MODULE_ENABLE

        Std_ReturnType eusart_async_WriteByteBlocking(uint8 _data)
        {
            Std_ReturnType ret = E_OK;

            while(!TXSTAbits.TRMT);
            #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                EUSART_TX_InterruptEnable();
            #endif
            TXREG = _data;
            
            return ret;
        }

        Std_ReturnType eusart_async_WriteStringBlocking(uint8 *_data, uint16 str_len)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _data)
            {    
                uint16 char_counter = ZERO_INIT;
                
                for(char_counter = ZERO_INIT ; char_counter < str_len ; char_counter++)
                {
                    ret = eusart_async_WriteByteBlocking(_data[char_counter]);
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }

        Std_ReturnType eusart_async_WriteByteNonBlocking(uint8 _data)
        {
            Std_ReturnType ret = E_OK;  
            
            if(1 == PIR1bits.TXIF)
            {
                TXREG = _data;
            }
            else{ ret = E_NOT_OK; }
            
            return ret;
        }

        Std_ReturnType eusart_async_WriteStringNonBlocking(uint8 *_data, uint16 str_len)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _data)
            {        
                uint16 char_counter = ZERO_INIT;
                
                for(char_counter = ZERO_INIT ; char_counter < str_len ; char_counter++)
                {
                    ret = eusart_async_WriteByteNonBlocking(_data[char_counter]);
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }

    #endif

#endif

/* Section : Helper Function Definition */

#if (EUSART_TX_MODULE == EUSART_MODULE_ENABLE) || (EUSART_RX_MODULE == EUSART_MODULE_ENABLE)

static void eusart_Baud_Rate_Calculation(const eusart_config_t *_eusart)
{
    float Baud_Rate_Temp = 0;
    switch(_eusart->baudrate_gen_gonfig)
    {
        case BAUDRATE_ASYN_8BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 64) - 1;
            break;
        case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_lOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_8BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYN_16BIT:
            TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart->baudrate) / 4) - 1;
            break;
        default : ;
    }
    SPBRG = (uint8)((uint32)Baud_Rate_Temp);
    SPBRGH = (uint8)(((uint32)Baud_Rate_Temp) >> 8);
}

#endif
    
#if EUSART_TX_MODULE == EUSART_MODULE_ENABLE

static void eusart_async_TX_Init(const eusart_config_t *_eusart)
{
    TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_DISABLE;
    
    /* EUSART Transmit Interrupt Configuration */
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

        EUSART_TX_InterruptHandler = _eusart->EUSART_TX_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _eusart->eusart_tx_priority)
        { 
            EUSART_TX_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _eusart->eusart_tx_priority)
        {
            EUSART_TX_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        EUSART_TX_InterruptEnable();
        global_interrupt_Enable();
        
    #endif

    /* EUSART  9-Bit Transmit Configuration */
    if(EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE == _eusart->eusart_tx_9bit_enable)
    {
        TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE == _eusart->eusart_tx_9bit_enable)
    {
        TXSTAbits.TX9 = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    }
    else{ /* Nothing */}
        
    TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
}

#endif

#if EUSART_RX_MODULE == EUSART_MODULE_ENABLE

static void eusart_async_RX_Init(const eusart_config_t *_eusart)
{
    RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_DISABLE;

    /* EUSART Receiver Interrupt Configuration */
    #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

        EUSART_RX_InterruptHandler = _eusart->EUSART_RX_InterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _eusart->eusart_rx_priority)
        { 
            EUSART_RX_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _eusart->eusart_rx_priority)
        {
            EUSART_RX_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        EUSART_RX_InterruptEnable();
        global_interrupt_Enable();

    #endif

    /* EUSART  9-Bit Receiver Configuration */
    if(EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE == _eusart->eusart_rx_9bit_enable)
    {
        RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE;
    }
    else if(EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE == _eusart->eusart_rx_9bit_enable)
    {
        RCSTAbits.RX9 = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    }
    else{ /* Nothing */}
        
    RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
} 

#endif

/* Section : ISRs Definition */ 

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void EUSART_TX_ISR(void)
{
    /* Disable the interrupt of the EUSART TX Module*/
    EUSART_TX_InterruptDisable();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(EUSART_TX_InterruptHandler)
    {
        EUSART_TX_InterruptHandler();
    }
    else{ /* Nothing */ }
}

#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void EUSART_RX_ISR(void)
{
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(EUSART_RX_InterruptHandler)
    {
        EUSART_RX_InterruptHandler();
    }
    else { /* Nothing */}
    if(EUSART_FramingErrorHandler)
    {
        EUSART_FramingErrorHandler();
    }
    else { /* Nothing */}
    if(EUSART_OverrunErrorHandler)
    {
        EUSART_OverrunErrorHandler();
    }
    else { /* Nothing */}
}

#endif  