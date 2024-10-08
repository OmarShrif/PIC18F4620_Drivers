/* 
 * File:   mcal_interrupt_manager.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:07 AM
 */

/* Section : Includes */

#include "mcal_interrupt_manager.h"
 
/* Section : Global Variables Definition */

/* External Interrupt OneChange RBx */
#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

static volatile uint8 RB4_flag = 0;
static volatile uint8 RB5_flag = 0;
static volatile uint8 RB6_flag = 0;
static volatile uint8 RB7_flag = 0;

#endif

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

/* Section : ISRs Definition */

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
    #if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt OneChange RBx */
    #if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB4) && (1 == RB4_flag))
    {
        RB4_flag = 0;
        RB4_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB4) && (0 == RB4_flag))
    {
        RB4_flag = 1;
        RB4_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB5) && (1 == RB5_flag))
    {
        RB5_flag = 0;
        RB5_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB5) && (0 == RB5_flag))
    {
        RB5_flag = 1;
        RB5_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB6) && (1 == RB6_flag))
    {
        RB6_flag = 0;
        RB6_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB6) && (0 == RB6_flag))
    {
        RB6_flag = 1;
        RB6_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB7) && (1 == RB7_flag))
    {
        RB7_flag = 0;
        RB7_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB7) && (0 == RB7_flag))
    {
        RB7_flag = 1;
        RB7_ISR(1);
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* ADC Interrupt */
    #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER0 Interrupt */
    #if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER1 Interrupt */
    #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER2 Interrupt */
    #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER3 Interrupt */
    #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* CCP1 Interrupt */
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* CCP2 Interrupt */
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* EUSART_TX Interrupt */
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_TX_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* EUSART_RX Interrupt */
    #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_RX_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* SPI Interrupt */
    #if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        SPI_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* I2C Interrupt */
    #if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        I2C_ISR();
        I2C_BC_ISR();
    }
    else{/* Nothing */}
    #endif
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
    #if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/* Nothing */}
    #endif
}

#elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE

void __interrupt() InterruptManager(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
    #if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt OneChange RBx */
    #if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB4) && (1 == RB4_flag))
    {
        RB4_flag = 0;
        RB4_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB4) && (0 == RB4_flag))
    {
        RB4_flag = 1;
        RB4_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB5) && (1 == RB5_flag))
    {
        RB5_flag = 0;
        RB5_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB5) && (0 == RB5_flag))
    {
        RB5_flag = 1;
        RB5_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB6) && (1 == RB6_flag))
    {
        RB6_flag = 0;
        RB6_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB6) && (0 == RB6_flag))
    {
        RB6_flag = 1;
        RB6_ISR(1);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_LOW == PORTBbits.RB7) && (1 == RB7_flag))
    {
        RB7_flag = 0;
        RB7_ISR(0);
    }
    else{/* Nothing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (GPIO_LOGIC_HIGH == PORTBbits.RB7) && (0 == RB7_flag))
    {
        RB7_flag = 1;
        RB7_ISR(1);
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* ADC Interrupt */
    #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF))
    {
        ADC_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER0 Interrupt */
    #if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF))
    {
        TIMER0_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER1 Interrupt */
    #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TIMER1_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER2 Interrupt */
    #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))
    {
        TIMER2_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* TIMER3 Interrupt */
    #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))
    {
        TIMER3_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* CCP1 Interrupt */
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF))
    {
        CCP1_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* CCP2 Interrupt */
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF))
    {
        CCP2_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* EUSART_TX Interrupt */
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF))
    {
        EUSART_TX_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* EUSART_RX Interrupt */
    #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF))
    {
        EUSART_RX_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* SPI Interrupt */
    #if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF))
    {
        SPI_ISR();
    }
    else{/* Nothing */}
    #endif
    /* --------------------------------------------------------------------------------------------------  */
    /* I2C Interrupt */
    #if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF))
    {
        I2C_ISR();
        I2C_BC_ISR();
    }
    else{/* Nothing */}
    #endif
}

#endif

/* Section : Helper Function Definition */ 
