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

Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData)
{
    Std_ReturnType ret = E_OK;
    
    return ret;
}

Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL != bData)
    {
        
    }
    else{ ret = E_NOT_OK; }
    
    return ret;
}

/* Section : ISRs Definition */

/* Section : Helper Function Definition */ 