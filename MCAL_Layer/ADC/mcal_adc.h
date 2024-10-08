/* 
 * File:   mcal_adc.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 10, 2024, 12:40 PM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_adc_cfg.h"

/* Section : Macro Declarations */

/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

/* A/D Result Format Select */
#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

/* Voltage Reference Configuration */
#define ADC_VOLTAGE_REFERENCE_ENABLED       0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED      0x00U

#define ADC_CONVERSION_COMPLETED  0x01U
#define ADC_CONVERSION_INPROGRESS 0x00U

/* Section : Macro Functions Declarations */

/* A/D conversion status : A/D conversion in progress or A/D Idle */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GODONE)

/**
 * @brief Start the Analog-To-Digital Conversion
 */
#define ADC_START_CONVERSION()  (ADCON0bits.GODONE = 1)

/**
 * @brief   Analog-To-Digital Control
 * @note    ADC_CONVERTER_ENABLE()  : Enables  the Analog-To-Digital
 *          ADC_CONVERTER_DISABLE() : Disables the Analog-To-Digital
 */
#define ADC_CONVERTER_ENABLE()      (ADCON0bits.ADON = 1)
#define ADC_CONVERTER_DISABLE()     (ADCON0bits.ADON = 0)

/**
 * @brief  Voltage Reference Configuration
 * @note   ADC_ENABLE_VOLTAGE_REFERENCE()  : Voltage Reference is VREF- & VREF+
 *         ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage Reference is VSS   & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()  ADCON1bits.VCFG1 = 1;\
                                        ADCON1bits.VCFG0 = 1;

#define ADC_DISABLE_VOLTAGE_REFERENCE() ADCON1bits.VCFG1 = 0;\
                                        ADCON1bits.VCFG0 = 0;

/**
 * @brief   Analog-To-Digital Port Configuration Control
 * @param   _CONFIG  is one of the Analog-To-Digital Port Configuration Control options
 * @note    Example : ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN4_ANALOG_FUNCTIONALITY);
 *          When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *          AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 *          @ref Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/**
 * @brief  A/D Result Format Select
 */
#define ADC_RESULT_RIGHT_FORMAT()  (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()   (ADCON2bits.ADFM = 0)

/* Section : Data Type Declarations */

/**
 * @brief   Analog channel select
 */
typedef enum
{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12  
}adc_channel_select_t;

/**
 * @brief  A/D Acquisition Time Select 
 * @note   Acquisition time (sampling time) is the time required for the (ADC) to 
 *         capture the input voltage during sampling.
 * @note   Acquisition time of a Successive Approximation Register (SAR) ADC is the amount of time 
 *         required to charge the holding capacitor (CHOLD) on the front end of an ADC
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

/**
 * @brief  A/D Conversion Clock Select
 * @note   If the A/D FRC clock source is selected, a delay of one TCY (instruction cycle) 
 *         is added before the A/D clock starts.
 * @note   This allows the SLEEP instruction to be executed before starting a conversion.
 */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

/**
 * ADC Configurations
 */
typedef struct
{
    #if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);      /* Interrupt CallBack Function */
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t adc_priority;            /* @ref interrupt_priority_t*/
    #endif
    #endif
    adc_acquisition_time_t adc_acquisition_time ; /* @ref adc_acquisition_time_t*/
    adc_conversion_clock_t adc_conversion_clock ; /* @ref adc_conversion_clock_t*/
    adc_channel_select_t adc_channel            ; /* used as default channel in initialization @ref adc_channel_select_t*/
    uint8 adc_voltage_reference     : 1;          /* Voltage Reference Configuration */
    uint8 adc_result_format         : 1;          /* A/D Result Format Select */
    uint8 adc_port_configuration    : 6;          /* @note use ADC_AN0_ANALOG_FUNCTIONALITY @ref adc_port_configuration*/
}adc_config_t;

/**
 * Result size of an A/D conversion
 */
typedef uint16 adc_result_t;

/* Section : Functions Declarations */

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
Std_ReturnType adc_Init(const adc_config_t *_adc);

/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_DeInit(const adc_config_t *_adc);

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
Std_ReturnType adc_SelectChannel(const adc_config_t *_adc, adc_channel_select_t channel);

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType adc_StartConversion(const adc_config_t *_adc);

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
Std_ReturnType adc_IsConversionDone(const adc_config_t *_adc, uint8 *conversion_status);

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
Std_ReturnType adc_GetConversionResult(const adc_config_t *_adc, adc_result_t *conversion_result);

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
                                          adc_result_t *conversion_result);

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
Std_ReturnType adc_StartConversion_Interrupt(const adc_config_t *_adc, adc_channel_select_t channel);
#endif
#endif	/* MCAL_ADC_H */

