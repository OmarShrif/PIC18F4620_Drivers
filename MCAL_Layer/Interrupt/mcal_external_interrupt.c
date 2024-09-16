/* 
 * File:   mcal_external_interrupt.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 2, 2024, 4:09 AM
 */

/* Section : Includes */

#include "mcal_external_interrupt.h"

/* Section : Global Variables Definition */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

static void (*RB4_Low_InterruptHandler)(void) = NULL;
static void (*RB4_High_InterruptHandler)(void) = NULL;
static void (*RB5_Low_InterruptHandler)(void) = NULL;
static void (*RB5_High_InterruptHandler)(void) = NULL;
static void (*RB6_Low_InterruptHandler)(void) = NULL;
static void (*RB6_High_InterruptHandler)(void) = NULL;
static void (*RB7_Low_InterruptHandler)(void) = NULL;
static void (*RB7_High_InterruptHandler)(void) = NULL;

#endif

/* Section : Helper Function Declaration */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType ext_interrupt_INTx_Enable(const ext_interrupt_INTx_t *int_obj);
static Std_ReturnType ext_interrupt_INTx_Disable(const ext_interrupt_INTx_t *int_obj);
static Std_ReturnType ext_interrupt_INTx_Edge_Init(const ext_interrupt_INTx_t *int_obj);
static Std_ReturnType ext_interrupt_INTx_Clear_Flag(const ext_interrupt_INTx_t *int_obj);
static Std_ReturnType ext_interrupt_INTx_SetInterruptHandler(const ext_interrupt_INTx_t *int_obj);
#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType ext_interrupt_INTx_Priority_Init(const ext_interrupt_INTx_t *int_obj);
#endif

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType ext_interrupt_RBx_SetInterruptHandler(const ext_interrupt_RBx_t *int_obj);

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType ext_interrupt_RBx_Priority_Init(const ext_interrupt_RBx_t *int_obj);
#endif

#endif

/* Section : Functions Definition */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_INTx_Init(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        /* Disable the External Interrupt */
        ret = ext_interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External Interrupt didn't occur */
        ret |= ext_interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External Interrupt Edge */
        ret |= ext_interrupt_INTx_Edge_Init(int_obj);
        /* Configure External Interrupt Priority*/
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
        ret |= ext_interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure External Interrupt Pin*/
        ret |= gpio_pin_direction_initialize(&(int_obj->ext_interrupt_INTx_pin));
        /* Configure Default External Interrupt CallBack*/
        ret |= ext_interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External Interrupt */
        ret |= ext_interrupt_INTx_Enable(int_obj);
        /* Enable the Global Interrupt */
        global_interrupt_Enable();
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_INTx_DeInit(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        /* Disable the External Interrupt */
        ret = ext_interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External Interrupt didn't occur */
        ret |= ext_interrupt_INTx_Clear_Flag(int_obj);
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_RBx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_RBx_Init(const ext_interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        /* Disable the External Interrupt */
        EXT_INTERRUPT_RBx_InterruptDisable();
        /* Clear Interrupt Flag : External Interrupt didn't occur */
        EXT_INTERRUPT_RBx_InterruptFlagClear();
        /* Configure External Interrupt Priority*/
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
        ret = ext_interrupt_RBx_Priority_Init(int_obj);
        #endif
        /* Configure External Interrupt Pin*/
        ret |= gpio_pin_direction_initialize(&(int_obj->ext_interrupt_RBx_pin));
        /* Configure Default External Interrupt CallBack*/
        ret |= ext_interrupt_RBx_SetInterruptHandler(int_obj);
        /* Enable the External Interrupt */
        EXT_INTERRUPT_RBx_InterruptEnable();
        /* Enable the Global Interrupt */
        global_interrupt_Enable();
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_RBx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ext_interrupt_RBx_DeInit(const ext_interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        /* Disable the External Interrupt */
        EXT_INTERRUPT_RBx_InterruptDisable();
        /* Clear Interrupt Flag : External Interrupt didn't occur */
        EXT_INTERRUPT_RBx_InterruptFlagClear();
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

#endif

/* Section : ISRs Definition */

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE
/**
 * @brief
 */
void INT0_ISR(void)
{
    /* The INT0 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_INT0_InterruptFlagClear();
    /* Code */
     
    /* Callback function gets called every time this ISR executed */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{/* Nothing */}
}

/**
 * @brief
 */
void INT1_ISR(void)
{
    /* The INT1 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_INT1_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{/* Nothing */}
}

/**
 * @brief
 */
void INT2_ISR(void)
{
    /* The INT2 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_INT2_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{/* Nothing */}
}

#endif


#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief
 */
void RB4_ISR(uint8 source)
{
    /* The RB4 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(0 == source)
    {
        if(RB4_Low_InterruptHandler){ RB4_Low_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else if(1 == source)
    {
        if(RB4_High_InterruptHandler){ RB4_High_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else{/* Nothing */ }
}

/**
 * @brief
 */
void RB5_ISR(uint8 source)
{
    /* The RB5 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(0 == source)
    {
        if(RB5_Low_InterruptHandler){ RB5_Low_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else if(1 == source)
    {
        if(RB5_High_InterruptHandler){ RB5_High_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else{/* Nothing */ }
}

/**
 * @brief
 */
void RB6_ISR(uint8 source)
{
    /* The RB6 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(0 == source)
    {
        if(RB6_Low_InterruptHandler){ RB6_Low_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else if(1 == source)
    {
        if(RB6_High_InterruptHandler){ RB6_High_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else{/* Nothing */ }
}

/**
 * @brief
 */
void RB7_ISR(uint8 source)
{
    /* The RB7 external interrupt occurred (must be cleared by software) */
    EXT_INTERRUPT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(0 == source)
    {
        if(RB7_Low_InterruptHandler){ RB7_Low_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else if(1 == source)
    {
        if(RB7_High_InterruptHandler){ RB7_High_InterruptHandler(); }
        else{/* Nothing */ }
    }
    else{/* Nothing */ }
}

#endif

/* Section : Helper Function Definition */ 

#if EXTERNAL_INTERRUPT_INTx_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_Enable(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN0 : EXT_INTERRUPT_INT0_InterruptEnable(); break;
            case GPIO_PIN1 : EXT_INTERRUPT_INT1_InterruptEnable(); break;
            case GPIO_PIN2 : EXT_INTERRUPT_INT2_InterruptEnable(); break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_Disable(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN0 : EXT_INTERRUPT_INT0_InterruptDisable(); break;
            case GPIO_PIN1 : EXT_INTERRUPT_INT1_InterruptDisable(); break;
            case GPIO_PIN2 : EXT_INTERRUPT_INT2_InterruptDisable(); break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_Edge_Init(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN0 :
              
            switch (int_obj->ext_interrupt_INTx_edge)
            {
                case EXTERNAL_INTERRUPT_FALLING_EDGE : EXT_INTERRUPT_INT0_FallingEdgeSet(); break;
                case EXTERNAL_INTERRUPT_RISING_EDGE : EXT_INTERRUPT_INT0_RisingEdgeSet(); break;
                default : ret = E_NOT_OK; break;
            }
            break;
            
            case GPIO_PIN1 :
              
            switch (int_obj->ext_interrupt_INTx_edge)
            {
                case EXTERNAL_INTERRUPT_FALLING_EDGE : EXT_INTERRUPT_INT1_FallingEdgeSet(); break;
                case EXTERNAL_INTERRUPT_RISING_EDGE : EXT_INTERRUPT_INT1_RisingEdgeSet(); break;
                default : ret = E_NOT_OK; break;
            }
            break;
            
            case GPIO_PIN2 :
              
            switch (int_obj->ext_interrupt_INTx_edge)
            {
                case EXTERNAL_INTERRUPT_FALLING_EDGE : EXT_INTERRUPT_INT2_FallingEdgeSet(); break;
                case EXTERNAL_INTERRUPT_RISING_EDGE : EXT_INTERRUPT_INT2_RisingEdgeSet(); break;
                default : ret = E_NOT_OK; break;
            }
            break;
            
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_Clear_Flag(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN0 : EXT_INTERRUPT_INT0_InterruptFlagClear(); break;
            case GPIO_PIN1 : EXT_INTERRUPT_INT1_InterruptFlagClear(); break;
            case GPIO_PIN2 : EXT_INTERRUPT_INT2_InterruptFlagClear(); break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_Priority_Init(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN1 :
              
            switch (int_obj->ext_interrupt_INTx_priority)
            {
                case INTERRUPT_PRIORITY_LOW : EXT_INTERRUPT_INT1_PrioritySetLow(); break;
                case INTERRUPT_PRIORITY_HIGH : EXT_INTERRUPT_INT1_PrioritySetHigh(); break;
                default : ret = E_NOT_OK; break;
            }
            break;
            
            case GPIO_PIN2 :
              
            switch (int_obj->ext_interrupt_INTx_priority)
            {
                case INTERRUPT_PRIORITY_LOW : EXT_INTERRUPT_INT2_PrioritySetLow(); break;
                case INTERRUPT_PRIORITY_HIGH : EXT_INTERRUPT_INT2_PrioritySetHigh(); break;
                default : ret = E_NOT_OK; break;
            }
            break;
            
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;   
}

#endif

/**
 * @brief 
 * @param int_obj pointer to the configuration @ref ext_interrupt_INTx_t
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType ext_interrupt_INTx_SetInterruptHandler(const ext_interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_INTx_pin.pin)
        {
            case GPIO_PIN0 : INT0_InterruptHandler = int_obj->ext_interrupt_INTx_handler; break;
            case GPIO_PIN1 : INT1_InterruptHandler = int_obj->ext_interrupt_INTx_handler; break;
            case GPIO_PIN2 : INT2_InterruptHandler = int_obj->ext_interrupt_INTx_handler; break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}

#endif

#if EXTERNAL_INTERRUPT_OneChange_FEATURE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType ext_interrupt_RBx_SetInterruptHandler(const ext_interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_RBx_pin.pin)
        {
            case GPIO_PIN4 : 
                RB4_Low_InterruptHandler = int_obj->ext_interrupt_RBx_low_handler;
                RB4_High_InterruptHandler = int_obj->ext_interrupt_RBx_high_handler;
            case GPIO_PIN5 : 
                RB5_Low_InterruptHandler = int_obj->ext_interrupt_RBx_low_handler;
                RB5_High_InterruptHandler = int_obj->ext_interrupt_RBx_high_handler;
                break;
            case GPIO_PIN6 : 
                RB6_Low_InterruptHandler = int_obj->ext_interrupt_RBx_low_handler; 
                RB6_High_InterruptHandler = int_obj->ext_interrupt_RBx_high_handler;
                break;
            case GPIO_PIN7 : 
                RB7_Low_InterruptHandler = int_obj->ext_interrupt_RBx_low_handler;
                RB7_High_InterruptHandler = int_obj->ext_interrupt_RBx_high_handler;
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;  
}


#if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE

static Std_ReturnType ext_interrupt_RBx_Priority_Init(const ext_interrupt_RBx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    if(NULL != int_obj)
    {
        switch (int_obj->ext_interrupt_RBx_priority)
        {
            case INTERRUPT_PRIORITY_LOW : EXT_INTERRUPT_RBx_PrioritySetLow(); break;
            case INTERRUPT_PRIORITY_HIGH : EXT_INTERRUPT_RBx_PrioritySetHigh(); break;
            default : ret = E_NOT_OK; break;
        }
    }
    else{ret = E_NOT_OK;}
    
    return ret;
}

#endif

#endif