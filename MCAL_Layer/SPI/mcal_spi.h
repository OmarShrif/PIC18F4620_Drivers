/* 
 * File:   mcal_spi.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 30, 2024, 5:32 PM
 */

#ifndef MCAL_SPI_H
#define	MCAL_SPI_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_spi_cfg.h"

/* Section : Macro Declarations */

/* Master Synchronous Serial Port Mode Select */
#define SPI_MASTER_FOSC_DIV4   0 /* SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin */
#define SPI_MASTER_FOSC_DIV16  1 /* SPI Slave mode, clock = SCK pin, SS pin control enabled */
#define SPI_MASTER_FOSC_DIV64  2 /* SPI Master mode, clock = TMR2 output/2 */
#define SPI_MASTER_FOSC_TMR2   3 /* SPI Master mode, clock = FOSC/64 */
#define SPI_SLAVE_SS_ENABLE    4 /* SPI Master mode, clock = FOSC/16 */
#define SPI_SLAVE_SS_DISABLE   5 /* SPI Master mode, clock = FOSC/4 */

/* Clock Polarity Select */
#define SPI_IDLE_STATE_HIGH_LEVEL   1 /* Idle state for clock is a high level */
#define SPI_IDLE_STATE_LOW_LEVEL    0 /* Idle state for clock is a low level */

/* SPI Sample Select */
#define SPI_DATA_SAMPLE_MIDDLE      0 /* Input data sampled at middle of data output time */
#define SPI_DATA_SAMPLE_END         1 /* Input data sampled at end of data output time */

/* SPI Clock Select */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE 1 /* Transmit occurs on transition from active to Idle clock state */
#define SPI_TRANSMIT_IDLE_TO_ACTIVE 0 /* Transmit occurs on transition from Idle to active clock state */

/* Receive Overflow Indicator */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0

/* Buffer Full Status bit (Receive mode only) */ 
#define SPI_BUFFER_FULL_RECEIVE_COMPLETE         1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE     0

/* Section : Macro Functions Declarations */

/* Master Synchronous Serial Port Enable */
#define SPI_ENABLE_MODULE()    (SSPCON1bits.SSPEN = 1) /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins */
#define SPI_DISABLE_MODULE()   (SSPCON1bits.SSPEN = 0) /*  Disables serial port and configures these pins as I/O port pins */

/* Section : Data Type Declarations */

typedef struct
{
    uint8 ClockPolarity : 2; /* Clock Polarity Select */
    uint8 SampleSelect  : 2;  /* SPI Sample Select */
    uint8 ClockSelect   : 2;   /* SPI Clock Select */
    uint8               : 2;
}spi_control_config;

typedef struct
{
    #if SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        void (*SPI_InterruptHandler)(void);
        #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
            interrupt_priority_t spi_priority;
        #endif
    #endif
    uint8 spi_mode;
    spi_control_config spi_config;
}spi_config_t;

/* Section : Functions Declarations */

Std_ReturnType spi_Init(const spi_config_t *Config);
Std_ReturnType spi_DeInit(const spi_config_t *Config);
Std_ReturnType spi_Send_Byte(const spi_config_t *Config, const uint8 _data);
Std_ReturnType spi_Read_Byte(const spi_config_t *Config, uint8 *_data);
Std_ReturnType spi_Send_Byte_NonBlocking(const spi_config_t *Config, const uint8 _data);
Std_ReturnType spi_Read_Byte_NonBlocking(const spi_config_t *Config, uint8 *_data);

#endif	/* MCAL_SPI_H */

