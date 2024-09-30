/* 
 * File:   mcal_i2c.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 30, 2024, 5:46 PM
 */

#ifndef MCAL_I2C_H
#define	MCAL_I2C_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_i2c_cfg.h"

/* Section : Macro Declarations */

/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE       1
#define I2C_SLEW_RATE_ENABLE        0

/* SMBus Enable/Disable */
#define I2C_SMBus_ENABLE            1
#define I2C_SMBus_DISABLE           0

/* Slave Mode Data/Address Indication */
#define I2C_LAST_RT_BYTE_DATA       1
#define I2C_LAST_RT_BYTE_ADDRESS    0

/* Stop Condition Indication */
#define I2C_STOP_BIT_DETECTED       1
#define I2C_STOP_BIT_NOT_DETECTED   0

/* Start Condition Indication */
#define I2C_START_BIT_DETECTED      1
#define I2C_START_BIT_NOT_DETECTED  0

/* I2C : Master or Slave Mode */
#define I2C_MSSP_MASTER_MODE        1
#define I2C_MSSP_SLAVE_MODE         0

/* Master Synchronous Serial Port Mode Select */
#define I2C_SLAVE_MODE_7BIT_ADDRESS					0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS				0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE	0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE	0x0FU
#define I2C_MASTER_MODE_DEFINED_CLOCK				0x08U
#define I2C_MASTER_MODE_FIRMWARE_CONTROLLED			0x0BU

/* General Call Enable */
#define I2C_GENERAL_CALL_ENABLE             1
#define I2C_GENERAL_CALL_DISABLE            0

/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_ENABLE           1
#define I2C_MASTER_RECEIVE_DISABLE          0

/* Acknowledge Status bit (Master Transmit mode only) */
#define I2C_ACK_RECEIVED_FROM_SLAVE         0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE     1

/* Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK                 0
#define I2C_MASTER_SEND_NACK                1

/* Section : Macro Functions Declarations */

/* Slew Rate Enable/Disable */
#define I2C_SLEW_RATE_DISABLE_CFG()         (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()          (SSPSTATbits.SMP = 0)

/* SMBus Enable/Disable */
#define I2C_SMBus_DISABLE_CFG()             (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()              (SSPSTATbits.CKE = 1)

/* General Call Enable */
#define I2C_GENERAL_CALL_DISABLE_CFG()      (SSPCON2bits.GCEN = 0)
#define I2C_GENERAL_CALL_ENABLE_CFG()       (SSPCON2bits.GCEN = 1)

/* Master Mode Receive Enable */
#define I2C_MASTER_RECEIVE_DISABLE_CFG()    (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECEIVE_ENABLE_CFG()     (SSPCON2bits.RCEN = 1)

/* Master Synchronous Serial Port Enable */
#define MSSP_MODULE_ENABLE_CFG()            (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()           (SSPCON1bits.SSPEN = 0)

/* Clock Stretch */
#define I2C_CLOCK_STRETCH_ENABLE()          (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()         (SSPCON1bits.CKP = 1)

/* Section : Data Type Declarations */

typedef struct
{
	uint8 i2c_mode_cfg;                 /* Master Synchronous Serial Port Mode Select */
    uint8 i2c_slave_address;            /* I2C Slave Address */
	uint8 i2c_mode              : 1;	/* I2C : Master or Slave Mode */
	uint8 i2c_slew_rate         : 1; 	/* Slew Rate Enable/Disable */
	uint8 i2c_SMBus_control     : 1; 	/* SMBus Enable/Disable */
	uint8 i2c_general_call      : 1;	/* General Call Enable/Disable */
	uint8 i2c_master_rec_mode   : 1; 	/* Master Receive Mode Enable/Disable */
	uint8                       : 3;  
}mssp_i2c_t;

typedef struct
{
	uint32 i2c_clock;	/* Master Clock Frequency */
    mssp_i2c_t i2c_cfg; /* I2C Configurations */
    #if I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*I2C_InterruptHandler)(void);         /* Default Interrupt Handler */
        void (*I2C_Report_Write_Collision)(void);	/* Write Collision Indicator */
        void (*I2C_Report_Receive_Overflow)(void); 	/* Receive Overflow Indicator */
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_t i2c_priority;
            interrupt_priority_t i2c_bc_priority; 
        #endif 
    #endif    
}i2c_config_t;

/* Section : Functions Declarations */

Std_ReturnType i2c_Init(const i2c_config_t *i2c_obj);
Std_ReturnType i2c_DeInit(const i2c_config_t *i2c_obj);

Std_ReturnType i2c_Master_Send_Start(const i2c_config_t *i2c_obj);
Std_ReturnType i2c_Master_Send_Repeated_Start(const i2c_config_t *i2c_obj);
Std_ReturnType i2c_Master_Send_Stop(const i2c_config_t *i2c_obj);

Std_ReturnType i2c_Master_Write_Blocking(const i2c_config_t *i2c_obj, uint8 i2c_data, uint8 *_ack);
Std_ReturnType i2c_Master_Write_NBlocking(const i2c_config_t *i2c_obj, uint8 i2c_data, uint8 *_ack);

Std_ReturnType i2c_Master_Read_Blocking(const i2c_config_t *i2c_obj, uint8 ack, uint8 *i2c_data);
Std_ReturnType i2c_Master_Read_NBlocking(const i2c_config_t *i2c_obj, uint8 ack, uint8 *i2c_data);

#endif	/* MCAL_I2C_H */

