/* 
 * File:   mcal_timer2.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

/* Section : Includes */

#include "mcal_timer2.h"

/* Section : Global Variables Definition */

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
 void (*TIMER2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer2_preload = ZERO_INIT;

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

Std_ReturnType timer2_Init(const timer2_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER2 Module */
        TIMER2_MODULE_DISABLE();
        /* Configure Pre-scaler Value */
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        /* Configure The Pre-loaded value */
        TMR2 = _timer->timer2_preload_value;
        /* Cope and Save The Pre-loaded value */
        timer2_preload = _timer->timer2_preload_value;
        /* Interrupt Configurations */
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _timer->timer2_priority)
        { 
            TIMER2_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _timer->timer2_priority)
        {
            TIMER2_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        TIMER2_InterruptFlagClear();
        TIMER2_InterruptEnable();
        global_interrupt_Enable();
        #endif
        /* Enable TIMER2 Module */
        TIMER2_MODULE_ENABLE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer2_DeInit(const timer2_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER2 Module */
        TIMER2_MODULE_DISABLE();
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of TIMER2 Module*/
        TIMER2_InterruptDisable();
        /* Clear Interrupt Flag for TIMER2 Module */
        TIMER2_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer2_Write_Value(const timer2_config_t *_timer, uint8 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _timer)
    {
        TMR2 = _value;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer2_Read_Value(const timer2_config_t *_timer, uint8 *_value)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != _timer) && (NULL != _value))
    {
        *_value = TMR2;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/* Section : Helper Function Definition */


/* Section : ISRs Definition */

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER2_ISR(void)
{
    /* Clear the interrupt flag */
    TIMER2_InterruptFlagClear();     
    /* Initialize the pre-loaded value again */
    TMR2 = timer2_preload;
    /* Call the callback function */
    if(TIMER2_InterruptHandler)
    {
        TIMER2_InterruptHandler();     
    }
    else{ /* Nothing */ }
}

#endif