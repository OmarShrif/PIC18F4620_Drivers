/* 
 * File:   mcal_i2c.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 30, 2024, 5:46 PM
 */

/* Section : Includes */

#include "mcal_i2c.h"

/* Section : Global Variables Definition */

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static void (*I2C_InterruptHandle)(void) = NULL;
static void (*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void (*I2C_Report_Receive_Overflow_InterruptHandle)(void) = NULL;

#endif

/* Section : Helper Function Declaration */

static inline void i2c_Mode_GPIO_CFG(void);
static inline void i2c_Master_Mode_Clock_Configurations(const i2c_config_t *i2c_obj);
static inline void i2c_Slave_Mode_Configurations(const i2c_config_t *i2c_obj);

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 

static inline void i2c_Interrupt_Configurations(const i2c_config_t *i2c_obj);

#endif

/* Section : Functions Definition */

Std_ReturnType i2c_Init(const i2c_config_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != i2c_obj)
    {
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        
        /* MSSP I2C Select Mode */
        if(I2C_MSSP_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode)
        { 
            /* MSSP I2C Master Mode Configurations */  
            /* I2C Master Mode Clock Configurations */
            i2c_Master_Mode_Clock_Configurations(i2c_obj);
        }
        else if(I2C_MSSP_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode)
        { 
            /* MSSP I2C Slave Mode Configurations */
            /* I2C Slave Mode General Call Configurations */
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call)
            {
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else { /* Nothing */ }
            
            /* Clear the Write Collision Detect */
            SSPCON1bits.WCOL = 0; /* No Collision */
            /* Clear the Receive Overflow Indicator */
            SSPCON1bits.SSPOV = 0; /* No Overflow */
            /* Release the clock */
            SSPCON1bits.CKP = 1;
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* I2C Slave Mode Configurations */
            i2c_Slave_Mode_Configurations(i2c_obj);
        }
        else { /* Nothing */ }
        
        /* I2C Master Mode GPIO Configurations */
        i2c_Mode_GPIO_CFG();
        
        /* MSSP I2C Slew Rate Control */
        if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate)
        {
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else { /* Nothing */ }
        
        /* MSSP I2C SMBus Control */
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control)
        {
            I2C_SMBus_DISABLE_CFG();
        }
        else { /* Nothing */ }
        
        /* Interrupt Configurations */
        #if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
          i2c_Interrupt_Configurations(i2c_obj);
        #endif
        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_DeInit(const i2c_config_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != i2c_obj)
    {
        /* Disable the I2C Module*/
        MSSP_MODULE_DISABLE_CFG();
        #if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        /* Disable the interrupt of the I2C Module*/
        I2C_InterruptDisable();
        I2C_BUS_COL_InterruptDisable();
        /* Clear Interrupt Flag for the I2C Module */
        I2C_InterruptFlagClear();
        #endif
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Send_Start(const i2c_config_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != i2c_obj)
    {
        /* Initiates Start condition on SDA and SCL pins */
        SSPCON2bits.SEN = 1; /* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. */
        /* Wait for the completion of the Start condition */
        while(SSPCON2bits.SEN){}
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report The Start Condition Detection */
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S)
        {
            ret = E_OK; /* Indicates that a Start bit has been detected last */
        }
        else{ ret = E_NOT_OK; /* Start bit was not detected last */ }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Send_Repeated_Start(const i2c_config_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != i2c_obj)
    {
        /* Initiates Repeated Start condition on SDA and SCL pins */
        SSPCON2bits.RSEN = 1; /* Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
        /* Wait for the completion of the Repeated Start condition */
        while(SSPCON2bits.RSEN){}
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Send_Stop(const i2c_config_t *i2c_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != i2c_obj)
    {
        /* Initiates Stop condition on SDA and SCL pins */
        SSPCON2bits.PEN = 1; /* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
        /* Wait for the completion of the Stop condition */
        while(SSPCON2bits.PEN){}
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report The Stop Condition Detection */
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P)
        {
            ret = E_OK; /* Indicates that a Stop bit has been detected last */
        }
        else{ ret = E_NOT_OK; /* Stop bit was not detected last */ }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}


Std_ReturnType i2c_Master_Write_Blocking(const i2c_config_t *i2c_obj, uint8 i2c_data, uint8 *_ack)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != i2c_obj) && (NULL != _ack))
    {
        /* Write Data to the Data register */
        SSPBUF = i2c_data;
        /* Wait The transmission to be completed */
        while(SSPSTATbits.BF){}
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the acknowledge received from the slave */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT)
        {
            *_ack = I2C_ACK_RECEIVED_FROM_SLAVE; /* Acknowledge was received from slave */
        }
        else{ *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE; /* Acknowledge was not received from slave */ }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Write_NBlocking(const i2c_config_t *i2c_obj, uint8 i2c_data, uint8 *_ack)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != i2c_obj) && (NULL != _ack))
    {
        
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Read_Blocking(const i2c_config_t *i2c_obj, uint8 ack, uint8 *i2c_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != i2c_obj) && (NULL != i2c_data))
    {
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for buffer full flag : A complete byte received */
        while(!SSPSTATbits.BF){}
        /* Copy The data registers to buffer variable */
        *i2c_data = SSPBUF;
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == ack)
        {
            SSPCON2bits.ACKDT = 0; /* Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1; 
            while(SSPCON2bits.ACKEN){} /* Automatically cleared by hardware */
        }
        else if(I2C_MASTER_SEND_NACK == ack)
        {
            SSPCON2bits.ACKDT = 1; /* Not Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN){} /* Automatically cleared by hardware */
        }
        else { /* Nothing */ }
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

Std_ReturnType i2c_Master_Read_NBlocking(const i2c_config_t *i2c_obj, uint8 ack, uint8 *i2c_data)
{
    Std_ReturnType ret = E_OK;
    
    if((NULL != i2c_obj) && (NULL != i2c_data))
    {
        
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}


/* Section : Helper Function Definition */ 

static inline void i2c_Mode_GPIO_CFG(void)
{
    TRISCbits.TRISC3 = 1; /* Serial clock (SCL) is Input */
    TRISCbits.TRISC4 = 1; /* Serial data (SDA) is Input */
}

static inline void i2c_Master_Mode_Clock_Configurations(const i2c_config_t *i2c_obj)
{
    /*  I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) - 1);
}

static inline void i2c_Slave_Mode_Configurations(const i2c_config_t *i2c_obj)
{
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 

static inline void i2c_Interrupt_Configurations(const i2c_config_t *i2c_obj)
{
    
    /* Interrupt Configurations */
    I2C_InterruptHandle = i2c_obj->I2C_InterruptHandler;
    I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
    I2C_Report_Receive_Overflow_InterruptHandle = i2c_obj->I2C_Report_Receive_Overflow;
    /* Interrupt Priority Configurations */
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE 

    if(INTERRUPT_PRIORITY_HIGH == i2c_obj->i2c_priority)
    { 
        I2C_PrioritySetHigh(); 
    }
    else if(INTERRUPT_PRIORITY_LOW == i2c_obj->i2c_priority)
    {
        I2C_PrioritySetLow(); 
    }
    else{ /* Nothing  */}
    
    if(INTERRUPT_PRIORITY_HIGH == i2c_obj->i2c_bc_priority)
    { 
        I2C_BUS_COL_PrioritySetHigh(); 
    }
    else if(INTERRUPT_PRIORITY_LOW == i2c_obj->i2c_bc_priority)
    {
        I2C_BUS_COL_PrioritySetLow(); 
    }
    else{ /* Nothing  */}
    
    #endif

    I2C_InterruptFlagClear();
    I2C_BUS_COL_InterruptFlagClear();
    I2C_InterruptEnable();
    I2C_BUS_COL_InterruptEnable();
    global_interrupt_Enable();
}

#endif

/* Section : ISRs Definition */ 
#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE  

void I2C_ISR(void)
{  
    /* The I2C interrupt occurred (flag must be cleared by software) */
    I2C_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(I2C_InterruptHandle)
    {
        I2C_InterruptHandle();
    }
    else{/* Nothing */}
}

#endif

#if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

void I2C_BC_ISR(void)
{
    /* The I2C interrupt occurred (flag must be cleared by software) */
    I2C_BUS_COL_InterruptFlagClear();
    /* Code */
    
    /* Callback function gets called every time this ISR executed */
    if(I2C_Report_Write_Collision_InterruptHandler)
    {
        I2C_Report_Write_Collision_InterruptHandler();
    }
    else{/* Nothing */}
}

#endif
