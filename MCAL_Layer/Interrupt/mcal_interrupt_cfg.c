/* 
 * File:   mcal_interrupt_cfg.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:06 AM
 */

/* Section : Includes */

#include "mcal_interrupt_cfg.h"

/* Section : Global Variables Definition */

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

void global_interrupt_Enable(void)
{
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    #elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    #endif
}

void global_interrupt_Disable(void)
{
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsDisable();
    INTERRUPT_GlobalInterruptHighDisable();
    INTERRUPT_GlobalInterruptLowDisable();
    #elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();
    #endif
}
/* Section : ISRs Definition */

/* Section : Helper Function Definition */ 