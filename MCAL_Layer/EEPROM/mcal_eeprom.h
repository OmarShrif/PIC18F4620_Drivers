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

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Functions Declarations */

Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData);

#endif	/* MCAL_EEPROM_H */

