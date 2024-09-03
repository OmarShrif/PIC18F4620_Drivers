/* 
 * File:   mcal_interrupt_cfg.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:06 AM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/* Section : Includes */

#include "../GPIO/mcal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* Section : Macro Declarations */

#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0

#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0

/* Section : Macro Functions Declarations */

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable priority levels on interrupts */
#define INTERRUPT_PriorityLevelsEnable()            (RCONbits.IPEN = 1)
/* This macro will disable priority levels on interrupts */
#define INTERRUPT_PriorityLevelsDisable()           (RCONbits.IPEN = 0)

/* This macro will enable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighEnable()       (INTCONbits.GIEH = 1)
/* This macro will disable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighDisable()      (INTCONbits.GIEH = 0)

/* This macro will enable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowEnable()        (INTCONbits.GIEL = 1)
/* This macro will disable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowDisable()       (INTCONbits.GIEL = 0)

#elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE

/* This macro will enable global interrupts */
#define INTERRUPT_GlobalInterruptEnable()           (INTCONbits.GIE = 1)
/* This macro will disable global interrupts */
#define INTERRUPT_GlobalInterruptDisable()          (INTCONbits.GIE = 0)

/* This macro will enable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()       (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable()      (INTCONbits.PEIE = 0)

#endif
/* Section : Data Type Declarations */

typedef enum
{
    INTERRUPT_PRIORITY_LOW = 0,
    INTERRUPT_PRIORITY_HIGH
            
}interrupt_priority_t;

/* Section : Functions Declarations */

#endif	/* MCAL_INTERRUPT_CFG_H */

