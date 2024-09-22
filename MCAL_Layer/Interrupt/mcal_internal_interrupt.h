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

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the TIMER1 Module */
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
/* This macro will disable interrupt for the TIMER1 Module */
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
/* This macro will clear interrupt flag for the TIMER1 Module */
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the TIMER1 Module Interrupt Priority to be High priority */
#define TIMER1_PrioritySetHigh()          (IPR1bits.TMR1IP = 1)
/* This routine set the TIMER1 Module Interrupt Priority to be Low priority */
#define TIMER1_PrioritySetLow()           (IPR1bits.TMR1IP = 0)

#endif

#endif

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the TIMER2 Module */
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE = 1)
/* This macro will disable interrupt for the TIMER2 Module */
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE = 0)
/* This macro will clear interrupt flag for the TIMER2 Module */
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the TIMER2 Module Interrupt Priority to be High priority */
#define TIMER2_PrioritySetHigh()          (IPR1bits.TMR2IP = 1)
/* This routine set the TIMER2 Module Interrupt Priority to be Low priority */
#define TIMER2_PrioritySetLow()           (IPR1bits.TMR2IP = 0)

#endif

#endif

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the TIMER3 Module */
#define TIMER3_InterruptEnable()          (PIE2bits.TMR3IE = 1)
/* This macro will disable interrupt for the TIMER3 Module */
#define TIMER3_InterruptDisable()         (PIE2bits.TMR3IE = 0)
/* This macro will clear interrupt flag for the TIMER3 Module */
#define TIMER3_InterruptFlagClear()       (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the TIMER3 Module Interrupt Priority to be High priority */
#define TIMER3_PrioritySetHigh()          (IPR2bits.TMR3IP = 1)
/* This routine set the TIMER3 Module Interrupt Priority to be Low priority */
#define TIMER3_PrioritySetLow()           (IPR2bits.TMR3IP = 0)

#endif

#endif

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the CCP1 Module */
#define CCP1_InterruptEnable()          (PIE1bits.CCP1IE = 1)
/* This macro will disable interrupt for the CCP1 Module */
#define CCP1_InterruptDisable()         (PIE1bits.CCP1IE = 0)
/* This macro will clear interrupt flag for the CCP1 Module */
#define CCP1_InterruptFlagClear()       (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the CCP1 Module Interrupt Priority to be High priority */
#define CCP1_PrioritySetHigh()          (IPR1bits.CCP1IP = 1)
/* This routine set the CCP1 Module Interrupt Priority to be Low priority */
#define CCP1_PrioritySetLow()           (IPR1bits.CCP1IP = 0)

#endif

#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the CCP2 Module */
#define CCP2_InterruptEnable()          (PIE2bits.CCP2IE = 1)
/* This macro will disable interrupt for the CCP2 Module */
#define CCP2_InterruptDisable()         (PIE2bits.CCP2IE = 0)
/* This macro will clear interrupt flag for the CCP2 Module */
#define CCP2_InterruptFlagClear()       (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the CCP2 Module Interrupt Priority to be High priority */
#define CCP2_PrioritySetHigh()          (IPR2bits.CCP2IP = 1)
/* This routine set the CCP2 Module Interrupt Priority to be Low priority */
#define CCP2_PrioritySetLow()           (IPR2bits.CCP2IP = 0)

#endif

#endif

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the EUSART TX Module */
#define EUSART_TX_InterruptEnable()          (PIE1bits.TXIE = 1)
/* This macro will disable interrupt for the EUSART TX Module */
#define EUSART_TX_InterruptDisable()         (PIE1bits.TXIE = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the EUSART TX Module Interrupt Priority to be High priority */
#define EUSART_TX_PrioritySetHigh()          (IPR1bits.TXIP = 1)
/* This routine set the EUSART TX Module Interrupt Priority to be Low priority */
#define EUSART_TX_PrioritySetLow()           (IPR1bits.TXIP = 0)

#endif

#endif

#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the EUSART RX Module */
#define EUSART_RX_InterruptEnable()          (PIE1bits.RCIE = 1)
/* This macro will disable interrupt for the EUSART RX Module */
#define EUSART_RX_InterruptDisable()         (PIE1bits.RCIE = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the EUSART RX Module Interrupt Priority to be High priority */
#define EUSART_RX_PrioritySetHigh()          (IPR1bits.RCIP = 1)
/* This routine set the EUSART RX Module Interrupt Priority to be Low priority */
#define EUSART_RX_PrioritySetLow()           (IPR1bits.RCIP = 0)

#endif

#endif

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the SPI Module */
#define SPI_InterruptEnable()          (PIE1bits.SSPIE = 1)
/* This macro will disable interrupt for the SPI Module */
#define SPI_InterruptDisable()         (PIE1bits.SSPIE = 0)
/* This macro will clear interrupt flag for the SPI Module */
#define SPI_InterruptFlagClear()       (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the SPI Module Interrupt Priority to be High priority */
#define SPI_PrioritySetHigh()          (IPR1bits.SSPIP = 1)
/* This routine set the SPI Module Interrupt Priority to be Low priority */
#define SPI_PrioritySetLow()           (IPR1bits.SSPIP = 0)

#endif

#endif

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for the I2C Module */
#define I2C_InterruptEnable()               (PIE1bits.SSPIE = 1)
#define I2C_BUS_COL_InterruptEnable()       (PIE2bits.BCLIE = 1)
/* This macro will disable interrupt for the I2C Module */
#define I2C_InterruptDisable()              (PIE1bits.SSPIE = 0)
#define I2C_BUS_COL_InterruptDisable()      (PIE2bits.BCLIE = 0)
/* This macro will clear interrupt flag for the I2C Module */
#define I2C_InterruptFlagClear()            (PIR2bits.SSPIF = 0)
#define I2C_BUS_COL_InterruptFlagClear()    (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

/* This routine set the I2C Module Interrupt Priority to be High priority */
#define I2C_PrioritySetHigh()               (IPR1bits.SSPIP = 1)
#define I2C_BUS_COL_PrioritySetHigh()       (IPR2bits.BCLIP = 1)
/* This routine set the I2C Module Interrupt Priority to be Low priority */
#define I2C_PrioritySetLow()                (IPR1bits.SSPIP = 0)
#define I2C_BUS_COL_PrioritySetLow()        (IPR2bits.BCLIP = 0)

#endif

#endif

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

