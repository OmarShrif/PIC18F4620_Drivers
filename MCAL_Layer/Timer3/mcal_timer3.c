/* 
 * File:   mcal_timer3.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

/* Section : Includes */

#include "mcal_timer3.h"

/* Section : Global Variables Definition */

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif
static uint16 timer3_preload = ZERO_INIT;

/* Section : Helper Function Declaration */

static inline void timer3_Mode_Select(const timer3_config_t *_timer);
static inline void timer3_RW_REG_Bit_Mode_Select(const timer3_config_t *_timer);

/* Section : Functions Definition */

Std_ReturnType timer3_Init(const timer3_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER0 Module */
        TIMER3_MODULE_DISABLE();
        /* Configure Pre-scaler Value */
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        /* Select Timer3 Mode_ */
        timer3_Mode_Select(_timer);
        timer3_RW_REG_Bit_Mode_Select(_timer);
        /* Select Register Size for TIMER3 Module */
        /* Configure The Pre-loaded value */
        TMR3H = (_timer->timer3_preload_value) >> 8;
        TMR3L = (uint8) (_timer->timer3_preload_value);
        /* Cope and Save The Pre-loaded value */
        timer3_preload = _timer->timer3_preload_value;
        /* Interrupt Configurations */
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _timer->timer3_priority)
        { 
            TIMER3_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _timer->timer3_priority)
        {
            TIMER3_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        TIMER3_InterruptFlagClear();
        TIMER3_InterruptEnable();
        global_interrupt_Enable();
        #endif
        /* Enable TIMER3 Module */
        TIMER3_MODULE_ENABLE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer3_DeInit(const timer3_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER3 Module */
        TIMER3_MODULE_DISABLE();
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of TIMER3 Module*/
        TIMER3_InterruptDisable();
        /* Clear Interrupt Flag for TIMER3 Module */
        TIMER3_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer3_Write_Value(const timer3_config_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _timer)
    {
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer3_Read_Value(const timer3_config_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    
    if((NULL != _timer) && (NULL != _value))
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}


/* Section : Helper Function Definition */

static inline void timer3_Mode_Select(const timer3_config_t *_timer)
{
    if(TIMER3_TIMER_MODE == _timer->timer3_mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        SET_BIT(TRISC, _TRISC_RC0_POSN);
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode)
        {
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static inline void timer3_RW_REG_Bit_Mode_Select(const timer3_config_t *_timer)
{
    if(TIMER3_RW_REG_8Bit_MODE == _timer->timer3_reg_wr_mode)
    {
        TIMER3_RW_REG_8BIT_MODE_ENABLE();
    }
    else if(TIMER3_RW_REG_16Bit_MODE == _timer->timer3_reg_wr_mode)
    {
        TIMER3_RW_REG_16BIT_MODE_ENABLE();
    }
    else{ /* Nothing */ }
    
}

/* Section : ISRs Definition */

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER3_ISR(void)
{
    /* Clear the interrupt flag */
    TIMER3_InterruptFlagClear();     
    /* Initialize the pre-loaded value again */
    TMR3H = (timer3_preload) >> 8;   
    TMR3L = (uint8)(timer3_preload);
    /* Call the callback function */
    if(TIMER3_InterruptHandler)
    {
        TIMER3_InterruptHandler();     
    }
    else{ /* Nothing */ }
}

#endif