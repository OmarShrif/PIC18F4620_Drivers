/* 
 * File:   mcal_interrupt_manager.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:07 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section : Includes */
#include "mcal_interrupt_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

void RB4_ISR(uint8 source);
void RB5_ISR(uint8 source);
void RB6_ISR(uint8 source);
void RB7_ISR(uint8 source);

#endif

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void ADC_ISR(void);

#endif

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER0_ISR(void);

#endif

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER1_ISR(void);

#endif

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER2_ISR(void);

#endif

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void TIMER3_ISR(void);

#endif

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void CCP1_ISR(void);

#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void CCP2_ISR(void);

#endif

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void EUSART_TX_ISR(void);

#endif

#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void EUSART_RX_ISR(void);

#endif

#if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void SPI_ISR(void);

#endif

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void I2C_ISR(void);
void I2C_BC_ISR(void);

#endif


#endif	/* MCAL_INTERRUPT_MANAGER_H */

