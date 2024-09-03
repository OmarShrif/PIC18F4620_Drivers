/* 
 * File:   mcal_interrupt_manager.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:07 AM
 */

/* Section : Includes */

#include "mcal_interrupt_manager.h"
 
/* Section : Global Variables Definition */

static volatile uint8 RB4_flag = 0;
static volatile uint8 RB5_flag = 0;
static volatile uint8 RB6_flag = 0;
static volatile uint8 RB7_flag = 0;

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

/* Section : ISRs Definition */

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/* Nothing */}
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt OneChange RBx */
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
    /* --------------------------------------------------------------------------------------------------  */
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
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
}

#elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE

void __interrupt() InterruptManager(void)
{
    /* --------------------------------------------------------------------------------------------------  */
    /* External Interrupt INTx */
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
}

#endif

/* Section : Helper Function Definition */ 
