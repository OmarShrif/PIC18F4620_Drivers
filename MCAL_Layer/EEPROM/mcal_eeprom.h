/* 
 * File:   mcal_eeprom.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 3, 2024, 3:53 PM
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/* Section : Includes */

#include "../Interrupt/mcal_internal_interrupt.h"
#include "mcal_eeprom_cfg.h"

/* Section : Macro Declarations */

/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

/**
 * @brief   Writes a data byte to Data EEPROM
 * @param bAdd  Data EEPROM location to which data to be written
 * @param bData  Data to be written to Data EEPROM location
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData);

/**
 * @brief   Reads a data byte from Data EEPROM
 * @param bAdd  Data EEPROM location from which data has to be read
 * @param bData  Data byte read from given Data EEPROM location
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData);

#endif	/* MCAL_EEPROM_H */

