/* 
 * File:   mcal_adc.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 10, 2024, 12:40 PM
 */


/* Section : Includes */

#include "mcal_adc.h"

/* Section : Global Variables Definition */

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

/* Section : Helper Function Declaration */

static inline Std_ReturnType adc_input_channel_port_configure(adc_channel_select_t channel);
static inline Std_ReturnType select_result_format(const adc_config_t *_adc);
static inline Std_ReturnType configure_voltage_reference(const adc_config_t *_adc);

/* Section : Functions Definition */

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_Init(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        /* Disable the ADC Module */
        ADC_CONVERTER_DISABLE();
        /* Analog-To-Digital Port Configuration Control */
        ADC_ANALOG_DIGITAL_PORT_CONFIG(_adc->adc_port_configuration);
        /* Configure the acquisition time */
        ADCON2bits.ACQT = _adc->adc_acquisition_time;
        /* Configure the conversion clock */
        ADCON2bits.ADCS = _adc->adc_conversion_clock;
        /* Configure the default channel */
        ret = adc_SelectChannel(_adc, _adc->adc_channel);
        /* Configure the interrupt for the ADC Module */
        #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
        /* Interrupt Priority Configurations */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_PRIORITY_HIGH == _adc->adc_priority)
        { 
            ADC_PrioritySetHigh(); 
        }
        else if(INTERRUPT_PRIORITY_LOW == _adc->adc_priority)
        {
            ADC_PrioritySetLow(); 
        }
        else{ /* Nothing  */}
        #endif
        ADC_InterruptFlagClear();
        ADC_InterruptEnable();
        global_interrupt_Enable();
        #endif
        /* Configure the result format */
        ret = select_result_format(_adc);
        /* Configure the voltage reference */
        ret = configure_voltage_reference(_adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_DeInit(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        /* Disable the ADC Module*/
        ADC_CONVERTER_DISABLE();
        #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of the ADC Module*/
        ADC_InterruptDisable();
        /* Clear Interrupt Flag for the ADC Module */
        ADC_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        /* Configure the default channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_StartConversion(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        ADC_START_CONVERSION();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != _adc) && (NULL != conversion_status))
    {
        *conversion_status = (uint8)(!(ADC_CONVERSION_STATUS()));
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_result)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != _adc) && (NULL != conversion_result))
    {
        if(ADC_RESULT_RIGHT == _adc->adc_result_format)
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->adc_result_format)
        {
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_GetConversion_Blocking(const adc_config_t *_adc, adc_channel_select_t channel, 
                                          adc_result_t *conversion_result)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != _adc) && (NULL != conversion_result))
    {
        /* select the A/D channel */
        ret = adc_SelectChannel(_adc, channel);
        /* Start the conversion */
        ret = adc_StartConversion(_adc);
        /* Check if conversion is completed */
        while(ADC_CONVERSION_STATUS());
        ret = adc_GetConversionResult(_adc, conversion_result);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @Summary Starts the ADC conversion as Interrupt, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine starts the analog to digital conversion with Interrupt.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        /* The ADC interrupt occurred (flag must be cleared by software) */
        ADC_InterruptFlagClear();
        /* select the A/D channel */
        ret = adc_SelectChannel(_adc, channel);
        /* Start the conversion */
        ret = adc_StartConversion(_adc);
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

#endif

/* Section : Helper Function Definition */ 

static inline Std_ReturnType adc_input_channel_port_configure(adc_channel_select_t channel)
{
    Std_ReturnType ret = E_OK;
    
    switch(channel)
    {
        /* Configure pin as input */
        case ADC_CHANNEL_AN0  : SET_BIT(TRISA, _TRISA_RA0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN1  : SET_BIT(TRISA, _TRISA_RA1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN2  : SET_BIT(TRISA, _TRISA_RA2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN3  : SET_BIT(TRISA, _TRISA_RA3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN4  : SET_BIT(TRISA, _TRISA_RA5_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN5  : SET_BIT(TRISE, _TRISE_RE0_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN6  : SET_BIT(TRISE, _TRISE_RE1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN7  : SET_BIT(TRISE, _TRISE_RE2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN8  : SET_BIT(TRISB, _TRISB_RB2_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN9  : SET_BIT(TRISB, _TRISB_RB3_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break; /* Disable the digital output driver */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break; /* Disable the digital output driver */
        default : ret = E_NOT_OK;
    }
    
    return ret;
}

static inline Std_ReturnType select_result_format(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        if(ADC_RESULT_RIGHT == _adc->adc_result_format)
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
        else if(ADC_RESULT_LEFT == _adc->adc_result_format)
        {
            ADC_RESULT_LEFT_FORMAT();
        }
        else
        {
            ADC_RESULT_RIGHT_FORMAT();
        }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

static inline Std_ReturnType configure_voltage_reference(const adc_config_t *_adc)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != _adc)
    {
        if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->adc_voltage_reference)
        {
            ADC_ENABLE_VOLTAGE_REFERENCE();
        }
        else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->adc_voltage_reference)
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
        else
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
    
}

/* Section : ISRs Definition */

#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void ADC_ISR(void)
{
    /* The ADC interrupt occurred (flag must be cleared by software) */
    ADC_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
    else{/* Nothing */}
}

#endif