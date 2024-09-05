/* 
 * File:   mcal_eeprom.c
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/
 * Created on September 3, 2024, 3:53 PM
 */

/* Section : Includes */

#include "mcal_eeprom.h"

/* Section : Global Variables Definition */

/* Section : Helper Function Declaration */

/* Section : Functions Definition */

/**
 * @brief   Writes a data byte to Data EEPROM
 * @param bAdd  Data EEPROM location to which data to be written
 * @param bData  Data to be written to Data EEPROM location
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData)
{
    Std_ReturnType ret = E_OK;
    
    /* Read the General Interrupt Status "Enabled or Disabled" */
    uint8 General_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to flash program/data EEPTOM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts "General Interrupt" */
    #if INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_GlobalInterruptHighDisable();
    #elif INTERRUPT_PRIORITY_LEVELS_FEATURE == INTERRUPT_FEATURE_DISABLE
    INTERRUPT_GlobalInterruptDisable();
    #endif
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the General Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = General_Interrupt_Status;
    
    return ret;
}

/**
 * @brief   Reads a data byte from Data EEPROM
 * @param bAdd  Data EEPROM location from which data has to be read
 * @param bData  Data byte read from given Data EEPROM location
 * @return Status of the function 
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != bData)
    {
        /* Update the Address Registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /* Return data */
        *bData = EEDATA;
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/* Section : ISRs Definition */

/* Section : Helper Function Definition */ 