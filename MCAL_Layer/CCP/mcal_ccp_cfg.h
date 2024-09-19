/* 
 * File:   mcal_ccp_cfg.h
 * Author: Omar Shrif Mohamed
 * https://www.linkedin.com/in/omar-shrif-982413213/s
 * Created on September 19, 2024, 3:58 AM
 */

#ifndef MCAL_CCP_CFG_H
#define	MCAL_CCP_CFG_H

/* Section : Includes */

/* Section : Data Type Declarations */

/* Section : Macro Declarations */

#define CCP_MODULE_ENABLE               0X01
#define CCP_MODULE_DISENABLE            0X00

#define CCP_CFG_CAPTURE_MODE_SELECTED   0x00
#define CCP_CFG_COMPARE_MODE_SELECTED   0x01
#define CCP_CFG_PWM_MODE_SELECTED       0x02

#define CCP1_MODULE                     CCP_MODULE_ENABLE
#define CCP2_MODULE                     CCP_MODULE_ENABLE

#if CCP1_MODULE == CCP_MODULE_ENABLE
#define CCP1_CFG_SELECTED_MODE          CCP_CFG_PWM_MODE_SELECTED
#endif

#if CCP2_MODULE == CCP_MODULE_ENABLE
#define CCP2_CFG_SELECTED_MODE          CCP_CFG_PWM_MODE_SELECTED
#endif

/* Section : Macro Functions Declarations */

/* Section : Functions Declarations */

#endif	/* MCAL_CCP_CFG_H */

