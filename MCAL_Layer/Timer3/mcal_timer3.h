/* 
 * File:   mcal_timer3.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

#ifndef MCAL_TIMER3_H
#define	MCAL_TIMER3_H


/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_timer3_cfg.h"

/* Section : Macro Declarations */

/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE              0
#define TIMER3_COUNTER_MODE            1
/* Timer3 External Clock Input Synchronization */
#define TIMER3_SYNC_COUNTER_MODE       0
#define TIMER3_ASYNC_COUNTER_MODE      1
/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALER_DIV_BY_1      0
#define TIMER3_PRESCALER_DIV_BY_2      1
#define TIMER3_PRESCALER_DIV_BY_4      2
#define TIMER3_PRESCALER_DIV_BY_8      3
/* Timer3 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8Bit_MODE        0
#define TIMER3_RW_REG_16Bit_MODE       1

/* Section : Macro Functions Declarations */

/* Enable or Disable Timer3 Module */
#define TIMER3_MODULE_ENABLE()              (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()             (T3CONbits.TMR3ON = 0)
/*  Timer3 Clock Source (Timer or Counter) */
#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1)
/*  Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()  (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 0)
/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_) (T3CONbits.T3CKPS = _PRESCALER_)
/* Timer3 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()   (T3CONbits.RD16 = 1)

/* Section : Data Type Declarations */

typedef struct
{
    #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER3_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t timer3_priority;
    #endif
    #endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value    : 2;
    uint8 timer3_mode               : 1;
    uint8 timer3_counter_mode       : 1;
    uint8 timer3_reg_wr_mode        : 1;
    uint8                           : 3;
}timer3_config_t;

/* Section : Functions Declarations */

Std_ReturnType timer3_Init(const timer3_config_t *_timer);
Std_ReturnType timer3_DeInit(const timer3_config_t *_timer);
Std_ReturnType timer3_Write_Value(const timer3_config_t *_timer, uint16 _value);
Std_ReturnType timer3_Read_Value(const timer3_config_t *_timer, uint16 *_value);


#endif	/* MCAL_TIMER3_H */

