/* 
 * File:   mcal_timer2.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 15, 2024, 8:28 AM
 */

#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H


/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_timer2_cfg.h"

/* Section : Macro Declarations */

/* Timer2 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15

/* Timer2 Input Clock Pre-scaler */
#define TIMER2_PRESCALER_DIV_BY_1        0
#define TIMER2_PRESCALER_DIV_BY_4        1
#define TIMER2_PRESCALER_DIV_BY_16       2

/* Section : Macro Functions Declarations */

/* Enable or Disable Timer1 Module */
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

/* Timer2 Input Clock Pre-scaler */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)

/* Timer2 Input Clock Post-scaler */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)


/* Section : Data Type Declarations */

typedef struct
{
    #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t timer2_priority;
    #endif
    #endif
    uint8 timer2_preload_value;
    uint8 timer2_prescaler_value    :2;
    uint8 timer2_postscaler_value   :4;
    uint8                           :2;
}timer2_config_t;

/* Section : Functions Declarations */

Std_ReturnType timer2_Init(const timer2_config_t *_timer);
Std_ReturnType timer2_DeInit(const timer2_config_t *_timer);
Std_ReturnType timer2_Write_Value(const timer2_config_t *_timer, uint8 _value);
Std_ReturnType timer2_Read_Value(const timer2_config_t *_timer, uint8 *_value);

#endif	/* MCAL_TIMER2_H */

