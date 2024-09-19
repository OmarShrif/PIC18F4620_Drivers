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

#define INTERRUPT_FEATURE_ENABLE    1
#define INTERRUPT_FEATURE_DISABLE   0

#define INTERRUPT_PRIORITY_LEVELS_FEATURE       INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE         INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OneChange_FEATURE    INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE                   INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE                INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_FEATURE             INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE             INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE              INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_FEATURE                  INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE                  INTERRUPT_FEATURE_ENABLE

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

