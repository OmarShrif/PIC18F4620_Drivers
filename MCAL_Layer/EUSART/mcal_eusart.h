/* 
 * File:   mcal_eusart.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 22, 2024, 8:45 AM
 */

#ifndef MCAL_EUSART_H
#define	MCAL_EUSART_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_eusart_cfg.h"

/* Section : Macro Declarations */

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE                     1
#define EUSART_ASYNCHRONOUS_MODE                    0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED              1
#define EUSART_ASYNCHRONOUS_LOW_SPEED               0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN                   1
#define EUSART_08BIT_BAUDRATE_GEN                   0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE               1
#define EUSART_ASYNCHRONOUS_TX_DISABLE              0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE    0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE         0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE               1
#define EUSART_ASYNCHRONOUS_RX_DISABLE              0
/* EUSART Receiver Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE    0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE         0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED               1
#define EUSART_FRAMING_ERROR_CLEARED                0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED               1
#define EUSART_OVERRUN_ERROR_CLEARED                0


/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

typedef enum
{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
}baudrate_gen_t;

#if (EUSART_TX_MODULE == EUSART_MODULE_ENABLE) || (EUSART_RX_MODULE == EUSART_MODULE_ENABLE)

typedef struct
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_gonfig;  
    #if EUSART_TX_MODULE == EUSART_MODULE_ENABLE
        uint8 eusart_tx_9bit_enable  : 1;
        #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            /* Call back used for all EUSART TX Modes */
            void (* EUSART_TX_InterruptHandler)(void);   
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                /* Configure the EUSART TX interrupt priority */
                interrupt_priority_t eusart_tx_priority;   
            #endif
        #endif
    #endif  
    #if EUSART_RX_MODULE == EUSART_MODULE_ENABLE
        uint8 eusart_rx_9bit_enable  : 1;
        uint8 eusart_ferr            : 1;
        uint8 eusart_oerr            : 1;
        #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            /* Call back used for all EUSART RX Modes */
            void (*EUSART_RX_InterruptHandler)(void);
            void (*EUSART_FramingErrorHandler)(void);
            void (*EUSART_OverrunErrorHandler)(void); 
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                /* Configure the EUSART RX interrupt priority */
                interrupt_priority_t eusart_rx_priority; 
            #endif
        #endif
    #endif
}eusart_config_t;

#endif

/* Section : Functions Declarations */

#if (EUSART_TX_MODULE == EUSART_MODULE_ENABLE) || (EUSART_RX_MODULE == EUSART_MODULE_ENABLE)

    Std_ReturnType eusart_async_Init(const eusart_config_t *_eusart);
    Std_ReturnType eusart_async_DeInit(const eusart_config_t *_eusart);

    #if EUSART_RX_MODULE == EUSART_MODULE_ENABLE

        Std_ReturnType eusart_async_ReadByteBlocking(uint8 *_data);
        Std_ReturnType eusart_async_ReadByteNonBlocking(uint8 *_data);
        Std_ReturnType eusart_async_RX_Restart(void);

    #endif

    #if EUSART_TX_MODULE == EUSART_MODULE_ENABLE

        Std_ReturnType eusart_async_WriteByteBlocking(uint8 _data);
        Std_ReturnType eusart_async_WriteStringBlocking(uint8 *_data, uint16 str_len);
        Std_ReturnType eusart_async_WriteByteNonBlocking(uint8 _data);
        Std_ReturnType eusart_async_WriteStringNonBlocking(uint8 *_data, uint16 str_len);

    #endif

#endif

#endif	/* MCAL_EUSART_H */

