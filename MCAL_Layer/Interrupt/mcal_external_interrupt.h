/* 
 * File:   mcal_external_interrupt.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:09 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include "mcal_interrupt_cfg.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for external interrupt, INT0 */
#define EXT_INTERRUPT_INT0_InterruptEnable()          (INTCONbits.INT0IE = 1)
/* This macro will disable interrupt for external interrupt, INT0 */
#define EXT_INTERRUPT_INT0_InterruptDisable()         (INTCONbits.INT0IE = 0)
/* This macro will clear interrupt flag for external interrupt, INT0 */
#define EXT_INTERRUPT_INT0_InterruptFlagClear()       (INTCONbits.INT0IF = 0)
/* This macro will set the edge detect to rising edge for external interrupt, INT0 */
#define EXT_INTERRUPT_INT0_RisingEdgeSet()            (INTCON2bits.INTEDG0 = 1)
/* This macro will set the edge detect to falling edge for external interrupt, INT0 */
#define EXT_INTERRUPT_INT0_FallingEdgeSet()           (INTCON2bits.INTEDG0 = 0)


/* This macro will enable interrupt for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_InterruptEnable()          (INTCON3bits.INT1IE = 1)
/* This macro will disable interrupt for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_InterruptDisable()         (INTCON3bits.INT1IE = 0)
/* This macro will clear interrupt flag for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_InterruptFlagClear()       (INTCON3bits.INT1IF = 0)
/* This macro will set the edge detect to rising edge for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_RisingEdgeSet()            (INTCON2bits.INTEDG1 = 1)
/* This macro will set the edge detect to falling edge for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_FallingEdgeSet()           (INTCON2bits.INTEDG1 = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will set priority to high for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_PrioritySetHigh()          (INTCON3bits.INT1IP = 1)
/* This macro will set priority to low for external interrupt, INT1 */
#define EXT_INTERRUPT_INT1_PrioritySetLow()           (INTCON3bits.INT1IP = 0)

#endif

/* This macro will enable interrupt for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_InterruptEnable()          (INTCON3bits.INT2IE = 1)
/* This macro will disable interrupt for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_InterruptDisable()         (INTCON3bits.INT2IE = 0)
/* This macro will clear interrupt flag for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_InterruptFlagClear()       (INTCON3bits.INT2IF = 0)
/* This macro will set the edge detect to rising edge for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_RisingEdgeSet()            (INTCON2bits.INTEDG2 = 1)
/* This macro will set the edge detect to falling edge for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_FallingEdgeSet()           (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will set priority to high for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_PrioritySetHigh()          (INTCON3bits.INT2IP = 1)
/* This macro will set priority to low for external interrupt, INT2 */
#define EXT_INTERRUPT_INT2_PrioritySetLow()           (INTCON3bits.INT2IP = 0)

#endif


#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will enable interrupt for external interrupt, RBx */
#define EXT_INTERRUPT_RBx_InterruptEnable()           (INTCONbits.RBIE = 1)
/* This macro will disable interrupt for external interrupt, RBx */
#define EXT_INTERRUPT_RBx_InterruptDisable()          (INTCONbits.RBIE = 0)
/* This macro will clear interrupt flag for external interrupt, RBx */
#define EXT_INTERRUPT_RBx_InterruptFlagClear()        (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

/* This macro will set priority to high for external interrupt, RBx */
#define EXT_INTERRUPT_RBx_PrioritySetHigh()           (INTCON2bits.RBIP = 1)
/* This macro will set priority to low for external interrupt, RBx */
#define EXT_INTERRUPT_RBx_PrioritySetLow()            (INTCON2bits.RBIP = 0)

#endif

#endif

/* Section : Data Type Declarations */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

typedef enum
{
    EXTERNAL_INTERRUPT_FALLING_EDGE = 0,
    EXTERNAL_INTERRUPT_RISING_EDGE
    
}ext_interrupt_INTx_edge_t;

typedef struct
{
    void (*ext_interrupt_INTx_handler)(void);
    pin_config_t ext_interrupt_INTx_pin;
    ext_interrupt_INTx_edge_t ext_interrupt_INTx_edge;
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t ext_interrupt_INTx_priority;
    #endif
}ext_interrupt_INTx_t;

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

typedef struct
{
    void (*ext_interrupt_RBx_high_handler)(void);
    void (*ext_interrupt_RBx_low_handler)(void);
    pin_config_t ext_interrupt_RBx_pin;
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t ext_interrupt_RBx_priority;
    #endif
    
}ext_interrupt_RBx_t;

#endif

/* Section : Functions Declarations */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_INTx_Init(const ext_interrupt_INTx_t *int_obj);

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_INTx_DeInit(const ext_interrupt_INTx_t *int_obj);
#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_RBx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_RBx_Init(const ext_interrupt_RBx_t *int_obj);

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_RBx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_RBx_DeInit(const ext_interrupt_RBx_t *int_obj);
#endif

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

