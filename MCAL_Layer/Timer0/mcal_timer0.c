/* 
 * File:   mcal_timer0.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

/* Section : Includes */

#include "mcal_timer0.h"

/* Section : Global Variables Definition */

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_InterruptHandler)(void) = NULL;
#endif
static uint16 timer0_preload = ZERO_INIT;


/* Section : Helper Function Declaration */

static inline void timer0_Prescaler_Config(const timer0_config_t *_timer);
static inline void timer0_Mode_Select(const timer0_config_t *_timer);
static inline void timer0_Register_Size_Config(const timer0_config_t *_timer);

/* Section : Functions Definition */

Std_ReturnType timer0_Init(const timer0_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER0 Module */
        TIMER0_MODULE_DISABLE();
        /* Configure Pre-scaler Value */
        timer0_Prescaler_Config(_timer);
        /* Select Timer0 Mode_ */
        timer0_Mode_Select(_timer);
        /* Select Register Size for TIMER0 Module */
        timer0_Register_Size_Config(_timer);
        /* Configure The Pre-loaded value */
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (uint8) (_timer->timer0_preload_value);
        /* Cope and Save The Pre-loaded value */
        timer0_preload = _timer->timer0_preload_value;
        /* Interrupt Configurations */
        #if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _timer->priority)
        { 
            TIMER0_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _timer->priority)
        {
            TIMER0_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        TIMER0_InterruptFlagClear();
        TIMER0_InterruptEnable();
        global_interrupt_Enable();
        #endif
        /* Enable TIMER0 Module */
        TIMER0_MODULE_ENABLE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer0_DeInit(const timer0_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER0 Module */
        TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of TIMER0 Module*/
        TIMER0_InterruptDisable();
        /* Clear Interrupt Flag for TIMER0 Module */
        TIMER0_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer0_Write_Value(const timer0_config_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        TMR0H = (_value) >> 8;
        TMR0L = (uint8) (_value);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer0_Read_Value(const timer0_config_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;
    
    if (NULL != _timer)
    {
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_value = (uint16) ((l_tmr0h << 8) + l_tmr0l);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/* Section : Helper Function Definition */

static inline void timer0_Prescaler_Config(const timer0_config_t *_timer)
{
    if (TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if (TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else{ /* Nothing */ }
}

static inline void timer0_Mode_Select(const timer0_config_t *_timer)
{
    if (TIMER0_TIMER_MODE == _timer->timer0_mode)
    {
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if (TIMER0_COUNTER_MODE == _timer->timer0_mode)
    {
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_COUNTER_RISING_EDGE_CFG == _timer->timer0_counter_edge)
        {
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if (TIMER0_COUNTER_FALLING_EDGE_CFG == _timer->timer0_counter_edge)
        {
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static inline void timer0_Register_Size_Config(const timer0_config_t *_timer)
{
    if (TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    else if (TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size)
    {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    }
    else{ /* Nothing */ }
}

/* Section : ISRs Definition */

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER0_ISR(void)
{
    /* The TIMER0 interrupt occurred (flag must be cleared by software) */
    TIMER0_InterruptFlagClear();
    /* Configure The Pre-loaded value */
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8) (timer0_preload);
    /* Callback function gets called every time this ISR executed */
    if (TIMER0_InterruptHandler)
    {
        TIMER0_InterruptHandler();
    }
    else{ /* Nothing */ }
}

#endif
