/* 
 * File:   mcal_ccp.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 19, 2024, 3:57 AM
 */

/* Section : Includes */

#include "mcal_ccp.h"

/* Section : Global Variables Definition */

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
    
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
    
/* Section : Helper Function Declaration */

#if CCP1_MODULE == CCP_MODULE_ENABLE
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
    static Std_ReturnType ccp1_Capture_Mode_Config(const ccp_config_t *_ccp_obj);
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp1_Interrupt_Config(const ccp_config_t *_ccp_obj);
    #endif
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
    static Std_ReturnType ccp1_Compare_Mode_Config(const ccp_config_t *_ccp_obj);
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp1_Interrupt_Config(const ccp_config_t *_ccp_obj);
    #endif
#endif
#endif

#if CCP2_MODULE == CCP_MODULE_ENABLE
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
    static Std_ReturnType ccp2_Capture_Mode_Config(const ccp_config_t *_ccp_obj);
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp2_Interrupt_Config(const ccp_config_t *_ccp_obj);
    #endif
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
    static Std_ReturnType ccp2_Compare_Mode_Config(const ccp_config_t *_ccp_obj);
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp2_Interrupt_Config(const ccp_config_t *_ccp_obj);
    #endif
#endif
#endif

#if (CCP1_MODULE == CCP_MODULE_ENABLE) || (CCP2_MODULE == CCP_MODULE_ENABLE)
#if (CCP1_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
    static void ccp_Mode_Timer_Select(const ccp_config_t *_ccp_obj);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
    static void ccp_PWM_Mode_Config(const ccp_config_t *_ccp_obj);
#endif
#endif

/* Section : Functions Definition */

#if (CCP1_MODULE == CCP_MODULE_ENABLE) && (CCP2_MODULE == CCP_MODULE_ENABLE)
    Std_ReturnType ccp_Init(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _ccp_obj)
        {
            ret = ccp1_Init(_ccp_obj);
            ret = ccp2_Init(_ccp_obj);
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }
        
    Std_ReturnType ccp_DeInit(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _ccp_obj)
        {
            ret = ccp1_DeInit(_ccp_obj);
            ret = ccp2_DeInit(_ccp_obj);
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }
        
#endif
    
#if CCP1_MODULE == CCP_MODULE_ENABLE
    Std_ReturnType ccp1_Init(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _ccp_obj)
        {
            /* CCP1 Module Disable */
            CCP1_SET_MODE(CCP_MODULE_DISABLE);

            /* PIN Configurations */
            ret = gpio_pin_initialize(&(_ccp_obj->ccp1_pin));

            #if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
                /* Interrupt Configurations for CCP1 Module */
                #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                ccp1_Interrupt_Config(_ccp_obj);
                #endif
                ccp_Mode_Timer_Select(_ccp_obj);
                ccp1_Capture_Mode_Config(_ccp_obj);
            #elif CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
                /* Interrupt Configurations for CCP1 Module */
                #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                ccp1_Interrupt_Config(_ccp_obj);
                #endif
                ccp_Mode_Timer_Select(_ccp_obj);
                ccp1_Compare_Mode_Config(_ccp_obj);
            #elif CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
                ccp_PWM_Mode_Config(_ccp_obj);
                CCP1_SET_MODE(CCP_PWM_MODE);
            #endif

            /* CCP1 Module Disable */
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }
        
    Std_ReturnType ccp1_DeInit(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;
        
        if(NULL != _ccp_obj)
        {
            /* Disable the CCP1 Module*/
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
            #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            /* Disable the interrupt of the CCP1 Module*/
            CCP1_InterruptDisable();
            /* Clear Interrupt Flag for the CCP1 Module */
            CCP1_InterruptFlagClear();
            #endif
        }
        else{ ret = E_NOT_OK; }
        
        return ret;
    }
        
    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
        Std_ReturnType ccp1_IsCapturedDataReady(uint8 *_capture_status)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _capture_status)
            {
                if(CCP_CAPTURE_READY == PIR1bits.CCP1IF)
                {
                    *_capture_status = CCP_CAPTURE_READY;
                    CCP1_InterruptFlagClear();
                }
                else
                {
                    *_capture_status = CCP_CAPTURE_NOT_READY;
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp1_Capture_Mode_Read_Value(uint16 *capture_value)
        {
            Std_ReturnType ret = E_OK;
            CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};

            if(NULL != capture_value)
            {
                /* Copy captured value */
                capture_temp_value.ccpr_low = CCPR1L;
                capture_temp_value.ccpr_high = CCPR1H;
                /* Write the 16-bit capture value */
                *capture_value = capture_temp_value.ccpr_16Bit;
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
    #endif

    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
        Std_ReturnType ccp1_IsCompareComplete(uint8 *_compare_status)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _compare_status)
            {
                if(CCP_COMPARE_READY == PIR1bits.CCP1IF)
                {
                    *_compare_status = CCP_COMPARE_READY;
                    CCP1_InterruptFlagClear();
                }
                else
                {
                    *_compare_status = CCP_COMPARE_NOT_READY;
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp1_Compare_Mode_Set_Value(const ccp_config_t *_ccp_obj, uint16 compare_value)
        {
            Std_ReturnType ret = E_OK;
            CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};

            if(NULL != _ccp_obj)
            {
                /* Copy compared value */
                capture_temp_value.ccpr_16Bit = compare_value;
                CCPR1L = capture_temp_value.ccpr_low;
                CCPR1H = capture_temp_value.ccpr_high;
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
    #endif

    #if CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
        Std_ReturnType ccp1_PWM_Set_Duty(const ccp_config_t *_ccp_obj, const uint8 _duty)
        {
            Std_ReturnType ret = E_OK;
            uint16 l_duty_temp = 0;
            if(NULL != _ccp_obj)
            {
                l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
                CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
                CCPR1L = (uint8)(l_duty_temp >> 2);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp1_PWM_Start(const ccp_config_t *_ccp_obj)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _ccp_obj)
            {
                CCP1_SET_MODE(CCP_PWM_MODE);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp1_PWM_Stop(const ccp_config_t *_ccp_obj)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _ccp_obj)
            {
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
    #endif
#endif
    
#if CCP2_MODULE == CCP_MODULE_ENABLE
        
    Std_ReturnType ccp2_Init(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        if(NULL != _ccp_obj)
        {
            /* CCP2 Module Disable */
            CCP2_SET_MODE(CCP_MODULE_DISABLE);

            /* PIN Configurations */
            ret = gpio_pin_initialize(&(_ccp_obj->ccp2_pin));

            #if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
                /* Interrupt Configurations for CCP2 Module */
                #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                ccp2_Interrupt_Config(_ccp_obj);
                #endif
                ccp_Mode_Timer_Select(_ccp_obj);
                ccp2_Capture_Mode_Config(_ccp_obj);
            #elif CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
                /* Interrupt Configurations for CCP2 Module */
                #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
                ccp2_Interrupt_Config(_ccp_obj);
                #endif
                ccp_Mode_Timer_Select(_ccp_obj);
                ccp2_Compare_Mode_Config(_ccp_obj);
            #elif CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
                ccp_PWM_Mode_Config(_ccp_obj);
                CCP2_SET_MODE(CCP_PWM_MODE);
            #endif

            /* CCP2 Module Disable */
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else{ ret = E_NOT_OK; }

        return ret;
    }
        
    Std_ReturnType ccp2_DeInit(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        if(NULL != _ccp_obj)
        {
            /* Disable the CCP2 Module*/
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
            #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            /* Disable the interrupt of the CCP2 Module*/
            CCP2_InterruptDisable();
            /* Clear Interrupt Flag for the CCP2 Module */
            CCP2_InterruptFlagClear();
            #endif
        }
        else{ ret = E_NOT_OK; }

        return ret;
    }
        
    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
        Std_ReturnType CCP2_IsCapturedDataReady(uint8 *_capture_status)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _capture_status)
            {
                if(CCP_CAPTURE_READY == PIR2bits.CCP2IF)
                {
                    *_capture_status = CCP_CAPTURE_READY;
                    CCP2_InterruptFlagClear();
                }
                else
                {
                    *_capture_status = CCP_CAPTURE_NOT_READY;
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType CCP2_Capture_Mode_Read_Value(uint16 *capture_value)
        {
            Std_ReturnType ret = E_OK;
            CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
            
            if(NULL != capture_value)
            {
                /* Copy captured value */
                capture_temp_value.ccpr_low = CCPR2L;
                capture_temp_value.ccpr_high = CCPR2H;
                /* Write the 16-bit capture value */
                *capture_value = capture_temp_value.ccpr_16Bit;
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
    #endif

    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
        Std_ReturnType ccp2_IsCompareComplete(uint8 *_compare_status)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _compare_status)
            {
                if(CCP_COMPARE_READY == PIR2bits.CCP2IF)
                {
                    *_compare_status = CCP_COMPARE_READY;
                    CCP2_InterruptFlagClear();
                }
                else
                {
                    *_compare_status = CCP_COMPARE_NOT_READY;
                }
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp2_Compare_Mode_Set_Value(const ccp_config_t *_ccp_obj, uint16 compare_value)
        {
            Std_ReturnType ret = E_OK;
            CCP_REG_T capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};

            if(NULL != _ccp_obj)
            {
                /* Copy compared value */
                capture_temp_value.ccpr_16Bit = compare_value;
                CCPR2L = capture_temp_value.ccpr_low;
                CCPR2H = capture_temp_value.ccpr_high;
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
    #endif

    #if CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED
        Std_ReturnType ccp2_PWM_Set_Duty(const ccp_config_t *_ccp_obj, const uint8 _duty)
        {
            Std_ReturnType ret = E_OK;
            uint16 l_duty_temp = 0;

            if(NULL != _ccp_obj)
            {
                l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)_duty / 100.0));
                CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
                CCPR2L = (uint8)(l_duty_temp >> 2);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp2_PWM_Start(const ccp_config_t *_ccp_obj)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _ccp_obj)
            {
                CCP2_SET_MODE(CCP_PWM_MODE);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
        
        Std_ReturnType ccp2_PWM_Stop(const ccp_config_t *_ccp_obj)
        {
            Std_ReturnType ret = E_OK;

            if(NULL != _ccp_obj)
            {
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
            }
            else{ ret = E_NOT_OK; }

            return ret;
        }
    #endif
#endif

/* Section : Helper Function Definition */ 

#if CCP1_MODULE == CCP_MODULE_ENABLE
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
    static Std_ReturnType ccp1_Capture_Mode_Config(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        /* CCP1 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp1_capture_mode)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }

        return ret;
    }
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp1_Interrupt_Config(const ccp_config_t *_ccp_obj)
        {
            /* Configure the interrupt for the CCP1 Module */
            CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
            /* Interrupt Priority Configurations */
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
            if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP1_priority)
            { 
                CCP1_PrioritySetHigh(); 
            }
            else if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP1_priority)
            {
                CCP1_PrioritySetLow(); 
            }
            else{ /* Nothing  */}
            #endif
            CCP1_InterruptFlagClear();
            CCP1_InterruptEnable();
            global_interrupt_Enable();
        }
    #endif
#elif CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
    static Std_ReturnType ccp1_Compare_Mode_Config(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp1_compare_mode)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }

        return ret;
    }
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp1_Interrupt_Config(const ccp_config_t *_ccp_obj)
        {
            /* Configure the interrupt for the CCP1 Module */
            CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
            /* Interrupt Priority Configurations */
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
            if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP1_priority)
            { 
                CCP1_PrioritySetHigh(); 
            }
            else if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP1_priority)
            {
                CCP1_PrioritySetLow(); 
            }
            else{ /* Nothing  */}
            #endif
            CCP1_InterruptFlagClear();
            CCP1_InterruptEnable();
            global_interrupt_Enable();
        }
    #endif
#endif
#endif

#if CCP2_MODULE == CCP_MODULE_ENABLE
#if CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED
    static Std_ReturnType ccp2_Capture_Mode_Config(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        /* CCP2 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp1_capture_mode)
        {
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }

        return ret;
    }
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp2_Interrupt_Config(const ccp_config_t *_ccp_obj)
        {
            /* Configure the interrupt for the CCP2 Module */
            CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
            /* Interrupt Priority Configurations */
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
            if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP2_priority)
            { 
                CCP2_PrioritySetHigh(); 
            }
            else if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP2_priority)
            {
                CCP2_PrioritySetLow(); 
            }
            else{ /* Nothing  */}
            #endif
            CCP2_InterruptFlagClear();
            CCP2_InterruptEnable();
            global_interrupt_Enable();
        }
    #endif
#elif CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED
    static Std_ReturnType ccp2_Compare_Mode_Config(const ccp_config_t *_ccp_obj)
    {
        Std_ReturnType ret = E_OK;

        /* CCP2 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp2_compare_mode)
        {
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }

        return ret;
    }
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        static void ccp2_Interrupt_Config(const ccp_config_t *_ccp_obj)
        {
            /* Configure the interrupt for the CCP2 Module */
            CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
            /* Interrupt Priority Configurations */
            #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
            if(INTERRUPT_PRIORITY_HIGH == _ccp_obj->CCP2_priority)
            { 
                CCP2_PrioritySetHigh(); 
            }
            else if(INTERRUPT_PRIORITY_LOW == _ccp_obj->CCP2_priority)
            {
                CCP2_PrioritySetLow(); 
            }
            else{ /* Nothing  */}
            #endif
            CCP2_InterruptFlagClear();
            CCP2_InterruptEnable();
            global_interrupt_Enable();
        }
    #endif
#endif
#endif

#if (CCP1_MODULE == CCP_MODULE_ENABLE) || (CCP2_MODULE == CCP_MODULE_ENABLE)
#if (CCP1_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
    static void ccp_Mode_Timer_Select(const ccp_config_t *_ccp_obj)
    {
        if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer)
        {
            /* Timer3 is the capture/compare clock source for the CCP modules */
            T3CONbits.T3CCP1 = 0; 
            T3CONbits.T3CCP2 = 1;
        }
        else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
            /* Timer3 is the capture/compare clock source for CCP2 */
            /* Timer1 is the capture/compare clock source for CCP1 */
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer){
            /* Timer1 is the capture/compare clock source for the CCP modules */
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
        else{ /* Nothing */ }
    }
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
static void ccp_PWM_Mode_Config(const ccp_config_t *_ccp_obj)
{
    /* PWM Frequency Initialization */
    PR2 = (uint8)( ((float)_XTAL_FREQ / ((float)_ccp_obj->PWM_Frequency * 4.0 *
                    (float)_ccp_obj->timer2_prescaler_value * 
                    (float)_ccp_obj->timer2_postscaler_value)) - 1);
}
#endif
#endif

/* Section : ISRs Definition */ 

#if (CCP1_MODULE == CCP_MODULE_ENABLE) && (CCP1_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void CCP1_ISR(void)
{
    /* The CCP1 interrupt occurred (flag must be cleared by software) */
    CCP1_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}

#endif
#endif
        
#if (CCP2_MODULE == CCP_MODULE_ENABLE) && (CCP2_CFG_SELECTED_MODE != CCP_CFG_PWM_MODE_SELECTED)
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void CCP2_ISR(void)
{
    /* The CCP1 interrupt occurred (flag must be cleared by software) */
    CCP2_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}

#endif
#endif