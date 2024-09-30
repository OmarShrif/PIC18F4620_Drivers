/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 5:06 AM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* Section : Includes */

/* Section : Macro Declarations */

#define INTERRUPT_FEATURE_ENABLE                1
#define INTERRUPT_FEATURE_DISABLE               0

#define INTERRUPT_PRIORITY_LEVELS_FEATURE       INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE         INTERRUPT_FEATURE_DISABLE
#define EXTERNAL_INTERRUPT_OneChange_FEATURE    INTERRUPT_FEATURE_DISABLE

#define ADC_INTERRUPT_FEATURE                   INTERRUPT_FEATURE_DISABLE

#define TIMER0_INTERRUPT_FEATURE                INTERRUPT_FEATURE_DISABLE
#define TIMER1_INTERRUPT_FEATURE                INTERRUPT_FEATURE_DISABLE
#define TIMER2_INTERRUPT_FEATURE                INTERRUPT_FEATURE_DISABLE
#define TIMER3_INTERRUPT_FEATURE                INTERRUPT_FEATURE_DISABLE

#define CCP1_INTERRUPT_FEATURE                  INTERRUPT_FEATURE_DISABLE
#define CCP2_INTERRUPT_FEATURE                  INTERRUPT_FEATURE_DISABLE

#define EUSART_TX_INTERRUPT_FEATURE             INTERRUPT_FEATURE_DISABLE
#define EUSART_RX_INTERRUPT_FEATURE             INTERRUPT_FEATURE_DISABLE

#define SPI_INTERRUPT_FEATURE                   INTERRUPT_FEATURE_ENABLE

#define I2C_INTERRUPT_FEATURE                   INTERRUPT_FEATURE_ENABLE

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

