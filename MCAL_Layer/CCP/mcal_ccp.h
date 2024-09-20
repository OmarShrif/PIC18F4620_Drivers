/* 
 * File:   mcal_ccp.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 19, 2024, 3:57 AM
 */

#ifndef MCAL_CCP_H
#define	MCAL_CCP_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_ccp_cfg.h"

/* Section : Macro Declarations */

/* CCP Module Mode Select  */
#define CCP_MODULE_DISABLE                 ((uint8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((uint8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((uint8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((uint8)0x0B)
#define CCP_PWM_MODE                       ((uint8)0x0C)

/* CCP Capture Mode State  */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01

/* CCP Compare Mode State  */
#define CCP_COMPARE_NOT_READY              0X00
#define CCP_COMPARE_READY                  0X01

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16

/* Section : Macro Functions Declarations */

/* Set the CCP Mode Variant */
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)

/* Section : Data Type Declarations */

/*
  @Summary      Define the values to select the CCP Main mode
*/
typedef enum
{
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP Capture Mode */
    CCP_COMPARE_MODE_SELECTED,     /* Select CCP Compare Mode */
    CCP_PWM_MODE_SELECTED          /* Select CCP PWM Mode */
}ccp_mode_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union
{
    struct
    {
        uint8 ccpr_low;  /* CCPR low register */
        uint8 ccpr_high; /* CCPR high register */
    };
    struct
    {
        uint16 ccpr_16Bit; /* Read CCPR as a 16 Bit value */
    };
}CCP_REG_T;

typedef enum
{
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3
}ccp_capture_timer_t;

#if (CCP1_MODULE == CCP_MODULE_ENABLE) || (CCP2_MODULE == CCP_MODULE_ENABLE)

/*
  @Summary      CCP Module configurations
  @Description  This data type used to describe the module initialization configuration
*/
typedef struct
{
    #if CCP1_MODULE == CCP_MODULE_ENABLE

        pin_config_t ccp1_pin;      /* CCP1 Pin I/O configurations */
        #if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED

            uint8 ccp1_capture_mode;    /* CCP1 selected capture mode */
            #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

                void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
                #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                    interrupt_priority_t CCP1_priority;   /* Configure the CCP1 mode interrupt */
                #endif

            #endif
        #elif CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED

            uint8 ccp1_compare_mode;    /* CCP1 selected compare mode */
            #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

                void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
                #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                    interrupt_priority_t CCP1_priority;   /* Configure the CCP1 mode interrupt */
                #endif

            #endif
        #elif (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) && (CCP2_MODULE != CCP_MODULE_ENABLE)
            uint32 PWM_Frequency;      /* CCP modes PWM frequency */
            uint8 timer2_postscaler_value;
            uint8 timer2_prescaler_value;
        #endif

    #endif

    #if CCP2_MODULE == CCP_MODULE_ENABLE
        pin_config_t ccp2_pin;      /* CCP2 Pin I/O configurations */
        #if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED

            uint8 ccp2_capture_mode;    /* CCP2 selected capture mode */
            #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

                void (* CCP2_InterruptHandler)(void);   /* Call back used for all CCP2 Modes */
                #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                    interrupt_priority_t CCP2_priority;   /* Configure the CCP1 mode interrupt */
                #endif

            #endif
        #elif CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED

            uint8 ccp2_compare_mode;    /* CCP2 selected compare mode */
            #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

                void (* CCP2_InterruptHandler)(void);   /* Call back used for all CCP2 Modes */
                #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
                    interrupt_priority_t CCP2_priority;   /* Configure the CCP1 mode interrupt */
                #endif

            #endif
        #elif (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) && (CCP1_MODULE != CCP_MODULE_ENABLE)
            uint32 PWM_Frequency;      /* CCP modes PWM frequency */
            uint8 timer2_postscaler_value;
            uint8 timer2_prescaler_value;
        #endif

    #endif

    #if (CCP1_MODULE == CCP_MODULE_ENABLE) && (CCP2_MODULE == CCP_MODULE_ENABLE)

        #if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) && (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
            uint32 PWM_Frequency;      /* CCP modes PWM frequency */
            uint8 timer2_postscaler_value;
            uint8 timer2_prescaler_value;
        #elif (CCP1_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED) && (CCP2_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
            ccp_capture_timer_t ccp_capture_timer;
        #else
            ccp_capture_timer_t ccp_capture_timer;
            uint32 PWM_Frequency;
            uint8 timer2_postscaler_value;
            uint8 timer2_prescaler_value;
        #endif
    #elif (CCP1_MODULE == CCP_MODULE_ENABLE) && (CCP2_MODULE != CCP_MODULE_ENABLE) && (CCP1_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
        ccp_capture_timer_t ccp_capture_timer;
    #elif (CCP1_MODULE != CCP_MODULE_ENABLE) && (CCP2_MODULE == CCP_MODULE_ENABLE) && (CCP2_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
        ccp_capture_timer_t ccp_capture_timer;
    #endif
}ccp_config_t;

#endif

/* Section : Functions Declarations */

#if (CCP1_MODULE == CCP_MODULE_ENABLE) && (CCP2_MODULE == CCP_MODULE_ENABLE)
    Std_ReturnType ccp_Init(const ccp_config_t *_ccp_obj);
    Std_ReturnType ccp_DeInit(const ccp_config_t *_ccp_obj);
#endif
    
#if CCP1_MODULE == CCP_MODULE_ENABLE
    Std_ReturnType ccp1_Init(const ccp_config_t *_ccp_obj);
    Std_ReturnType ccp1_DeInit(const ccp_config_t *_ccp_obj);

    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
        Std_ReturnType ccp1_IsCapturedDataReady(uint8 *_capture_status);
        Std_ReturnType ccp1_Capture_Mode_Read_Value(uint16 *capture_value);
    #endif

    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
        Std_ReturnType ccp1_IsCompareComplete(uint8 *_compare_status);
        Std_ReturnType ccp1_Compare_Mode_Set_Value(const ccp_config_t *_ccp_obj, uint16 compare_value);
    #endif

    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
        Std_ReturnType ccp1_PWM_Set_Duty(const ccp_config_t *_ccp_obj, const uint8 _duty);
        Std_ReturnType ccp1_PWM_Start(const ccp_config_t *_ccp_obj);
        Std_ReturnType ccp1_PWM_Stop(const ccp_config_t *_ccp_obj);
    #endif
#endif
    
#if CCP2_MODULE == CCP_MODULE_ENABLE
        
    Std_ReturnType ccp2_Init(const ccp_config_t *_ccp_obj);
    Std_ReturnType ccp2_DeInit(const ccp_config_t *_ccp_obj);
    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
        Std_ReturnType ccp2_IsCapturedDataReady(uint8 *_capture_status);
        Std_ReturnType ccp2_Capture_Mode_Read_Value(uint16 *capture_value);
    #endif

    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
        Std_ReturnType ccp2_IsCompareComplete(uint8 *_compare_status);
        Std_ReturnType ccp2_Compare_Mode_Set_Value(const ccp_config_t *_ccp_obj, uint16 compare_value);
    #endif

    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
        Std_ReturnType ccp2_PWM_Set_Duty(const ccp_config_t *_ccp_obj, const uint8 _duty);
        Std_ReturnType ccp2_PWM_Start(const ccp_config_t *_ccp_obj);
        Std_ReturnType ccp2_PWM_Stop(const ccp_config_t *_ccp_obj);
    #endif
#endif

#endif	/* MCAL_CCP_H */

