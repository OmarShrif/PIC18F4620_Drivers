/* 
 * File:   mcal_timer1.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H


/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_timer1_cfg.h"

/* Section : Macro Declarations */

/* Timer1 Clock Source (Timer or Counter) */
#define TIMER1_COUNTER_MODE            1
#define TIMER1_TIMER_MODE              0
/* Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0
/* Timer1 Oscillator */
#define TIMER1_OSCILLATOR_ENABLE       1
#define TIMER1_OSCILLATOR_DISABLE      0
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALER_DIV_BY_1      0
#define TIMER1_PRESCALER_DIV_BY_2      1
#define TIMER1_PRESCALER_DIV_BY_4      2
#define TIMER1_PRESCALER_DIV_BY_8      3
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8Bit_MODE        0
#define TIMER1_RW_REG_16Bit_MODE       1

/* Section : Macro Functions Declarations */

/* Enable or Disable Timer1 Module */
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)
/*  Timer1 Clock Source (Timer or Counter) */
#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)
/*  Timer1 External Clock Input Synchronization */
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()  (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 0)
/* Timer1 Oscillator */
#define TIMER1_OSC_HW_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE()             (T1CONbits.T1OSCEN = 0)
/* Timer1 Input Clock Pre-scaler */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_) (T1CONbits.T1CKPS = _PRESCALER_)
/* Timer1 System Clock Status */
#define TIMER1_SYSTEM_CLK_STATUS()          (T1CONbits.T1RUN)
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()    (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()   (T1CONbits.RD16 = 1)

/* Section : Data Type Declarations */

typedef struct 
{
    #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t timer1_priority;
    #endif
    #endif
    uint16 timer1_preload_value;         /* Pre-load value configuration */
    uint8 timer1_prescaler_value    : 2; /* Pre-scale value configuration */
    uint8 timer1_mode               : 1; /* Timer Mode / Counter Mode */
    uint8 timer1_counter_mode       : 1; /* Synchronous or ASynchronous Counter */
    uint8 timer1_osc_cfg            : 1; /* Timer1 Oscillator or Another source*/
    uint8 timer1_reg_wr_mode        : 1; /* One 16-bit operation or Two 8-bit operations */
    uint8                           : 2;
} timer1_config_t;

/* Section : Functions Declarations */

Std_ReturnType timer1_Init(const timer1_config_t *_timer);
Std_ReturnType timer1_DeInit(const timer1_config_t *_timer);
Std_ReturnType timer1_Write_Value(const timer1_config_t *_timer, uint16 _value);
Std_ReturnType timer1_Read_Value(const timer1_config_t *_timer, uint16 *_value);

#endif	/* MCAL_TIMER1_H */

