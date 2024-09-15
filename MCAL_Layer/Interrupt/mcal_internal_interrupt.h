/* 
 * File:   mcal_internal_interrupt.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:08 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the ADC Module */
#define ADC_InterruptEnable()           (PIE1bits.ADIE = 1)
/* This macro will disable interrupt for the ADC Module */
#define ADC_InterruptDisable()          (PIE1bits.ADIE = 0)
/* This macro will clear interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()        (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the ADC Module Interrupt Priority to be High priority */
#define ADC_PrioritySetHigh()           (IPR1bits.ADIP = 1)
/* This routine set the ADC Module Interrupt Priority to be Low priority */
#define ADC_PrioritySetLow()            (IPR1bits.ADIP = 0)

#endif

#endif

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the TIMER0 Module */
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This macro will disable interrupt for the TIMER0 Module */
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This macro will clear interrupt flag for the TIMER0 Module */
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the TIMER0 Module Interrupt Priority to be High priority */
#define TIMER0_PrioritySetHigh()          (INTCON2bits.TMR0IP = 1)
/* This routine set the TIMER0 Module Interrupt Priority to be Low priority */
#define TIMER0_PrioritySetLow()           (INTCON2bits.TMR0IP = 0)

#endif

#endif

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

