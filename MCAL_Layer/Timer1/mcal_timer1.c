/* 
 * File:   mcal_timer1.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

/* Section : Includes */

#include "mcal_timer1.h"

/* Section : Global Variables Definition */

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_InterruptHandler)(void) = NULL;
#endif
static uint16 timer1_preload = ZERO_INIT;

/* Section : Helper Function Declaration */

static inline void timer1_Mode_Select(const timer1_config_t *_timer);
static inline void timer1_RW_REG_Bit_Mode_Select(const timer1_config_t *_timer);
static inline void timer1_OSC_HW_Mode_Select(const timer1_config_t *_timer);

/* Section : Functions Definition */

Std_ReturnType timer1_Init(const timer1_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER1 Module */
        TIMER1_MODULE_DISABLE();
        /* Select Timer1 Mode_ */
        timer1_Mode_Select(_timer);
        timer1_RW_REG_Bit_Mode_Select(_timer);
        timer1_OSC_HW_Mode_Select(_timer);
        /* Configure Pre-scaler Value */
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        /* Configure The Pre-loaded value */
        TMR0H = (_timer->timer1_preload_value) >> 8;
        TMR0L = (uint8) (_timer->timer1_preload_value);
        /* Cope and Save The Pre-loaded value */
        timer1_preload = _timer->timer1_preload_value;
        /* Interrupt Configurations */
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TIMER1_InterruptHandler = _timer->TIMER1_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _timer->timer1_priority)
        { 
            TIMER1_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _timer->timer1_priority)
        {
            TIMER1_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        TIMER1_InterruptFlagClear();
        TIMER1_InterruptEnable();
        global_interrupt_Enable();
        #endif
        /* Enable TIMER1 Module */
        TIMER1_MODULE_ENABLE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer1_DeInit(const timer1_config_t *_timer)
{
    Std_ReturnType ret = E_OK;
    
    if (NULL != _timer)
    {
        /* Disable TIMER1 Module */
        TIMER1_MODULE_DISABLE();
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of TIMER1 Module*/
        TIMER1_InterruptDisable();
        /* Clear Interrupt Flag for TIMER1 Module */
        TIMER1_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer1_Write_Value(const timer1_config_t *_timer, uint16 _value)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _timer)
    {
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType timer1_Read_Value(const timer1_config_t *_timer, uint16 *_value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1l = ZERO_INIT, l_tmr1h = ZERO_INIT;
    
    if((NULL != _timer) && (NULL != _value))
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_value = (uint16)((l_tmr1h << 8) + l_tmr1l);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}


/* Section : Helper Function Definition */

static inline void timer1_Mode_Select(const timer1_config_t *_timer)
{
    if(TIMER1_TIMER_MODE == _timer->timer1_mode)
    {
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode)
    {
        TIMER1_COUNTER_MODE_ENABLE();
        SET_BIT(TRISC, _TRISC_RC0_POSN);
        if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode)
        {
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static inline void timer1_RW_REG_Bit_Mode_Select(const timer1_config_t *_timer)
{
    if(TIMER1_RW_REG_8Bit_MODE == _timer->timer1_reg_wr_mode)
    {
        TIMER1_RW_REG_8BIT_MODE_ENABLE();
    }
    else if(TIMER1_RW_REG_16Bit_MODE == _timer->timer1_reg_wr_mode)
    {
        TIMER1_RW_REG_16BIT_MODE_ENABLE();
    }
    else{ /* Nothing */ }
    
}

static inline void timer1_OSC_HW_Mode_Select(const timer1_config_t *_timer)
{
    if(TIMER1_OSCILLATOR_ENABLE == _timer->timer1_osc_cfg)
    {
        TIMER1_OSC_HW_ENABLE();
    }
    else if(TIMER1_OSCILLATOR_DISABLE == _timer->timer1_osc_cfg)
    {
        TIMER1_OSC_HW_DISABLE();
    }
    else{ /* Nothing */ }
}

/* Section : ISRs Definition */

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER1_ISR(void)
{
    /* Clear the interrupt flag */
    TIMER1_InterruptFlagClear();     
    /* Initialize the pre-loaded value again */
    TMR1H = (timer1_preload) >> 8;   
    TMR1L = (uint8)(timer1_preload);
    /* Call the callback function */
    if(TIMER1_InterruptHandler)
    {
        TIMER1_InterruptHandler();     
    }
    else{ /* Nothing */ }
}

#endif