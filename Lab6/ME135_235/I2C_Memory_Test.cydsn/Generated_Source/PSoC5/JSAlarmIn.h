/*******************************************************************************
* File Name: JSAlarmIn.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_JSAlarmIn_H) /* Pins JSAlarmIn_H */
#define CY_PINS_JSAlarmIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "JSAlarmIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 JSAlarmIn__PORT == 15 && ((JSAlarmIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    JSAlarmIn_Write(uint8 value);
void    JSAlarmIn_SetDriveMode(uint8 mode);
uint8   JSAlarmIn_ReadDataReg(void);
uint8   JSAlarmIn_Read(void);
void    JSAlarmIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   JSAlarmIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the JSAlarmIn_SetDriveMode() function.
     *  @{
     */
        #define JSAlarmIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define JSAlarmIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define JSAlarmIn_DM_RES_UP          PIN_DM_RES_UP
        #define JSAlarmIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define JSAlarmIn_DM_OD_LO           PIN_DM_OD_LO
        #define JSAlarmIn_DM_OD_HI           PIN_DM_OD_HI
        #define JSAlarmIn_DM_STRONG          PIN_DM_STRONG
        #define JSAlarmIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define JSAlarmIn_MASK               JSAlarmIn__MASK
#define JSAlarmIn_SHIFT              JSAlarmIn__SHIFT
#define JSAlarmIn_WIDTH              1u

/* Interrupt constants */
#if defined(JSAlarmIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in JSAlarmIn_SetInterruptMode() function.
     *  @{
     */
        #define JSAlarmIn_INTR_NONE      (uint16)(0x0000u)
        #define JSAlarmIn_INTR_RISING    (uint16)(0x0001u)
        #define JSAlarmIn_INTR_FALLING   (uint16)(0x0002u)
        #define JSAlarmIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define JSAlarmIn_INTR_MASK      (0x01u) 
#endif /* (JSAlarmIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JSAlarmIn_PS                     (* (reg8 *) JSAlarmIn__PS)
/* Data Register */
#define JSAlarmIn_DR                     (* (reg8 *) JSAlarmIn__DR)
/* Port Number */
#define JSAlarmIn_PRT_NUM                (* (reg8 *) JSAlarmIn__PRT) 
/* Connect to Analog Globals */                                                  
#define JSAlarmIn_AG                     (* (reg8 *) JSAlarmIn__AG)                       
/* Analog MUX bux enable */
#define JSAlarmIn_AMUX                   (* (reg8 *) JSAlarmIn__AMUX) 
/* Bidirectional Enable */                                                        
#define JSAlarmIn_BIE                    (* (reg8 *) JSAlarmIn__BIE)
/* Bit-mask for Aliased Register Access */
#define JSAlarmIn_BIT_MASK               (* (reg8 *) JSAlarmIn__BIT_MASK)
/* Bypass Enable */
#define JSAlarmIn_BYP                    (* (reg8 *) JSAlarmIn__BYP)
/* Port wide control signals */                                                   
#define JSAlarmIn_CTL                    (* (reg8 *) JSAlarmIn__CTL)
/* Drive Modes */
#define JSAlarmIn_DM0                    (* (reg8 *) JSAlarmIn__DM0) 
#define JSAlarmIn_DM1                    (* (reg8 *) JSAlarmIn__DM1)
#define JSAlarmIn_DM2                    (* (reg8 *) JSAlarmIn__DM2) 
/* Input Buffer Disable Override */
#define JSAlarmIn_INP_DIS                (* (reg8 *) JSAlarmIn__INP_DIS)
/* LCD Common or Segment Drive */
#define JSAlarmIn_LCD_COM_SEG            (* (reg8 *) JSAlarmIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define JSAlarmIn_LCD_EN                 (* (reg8 *) JSAlarmIn__LCD_EN)
/* Slew Rate Control */
#define JSAlarmIn_SLW                    (* (reg8 *) JSAlarmIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define JSAlarmIn_PRTDSI__CAPS_SEL       (* (reg8 *) JSAlarmIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define JSAlarmIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) JSAlarmIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define JSAlarmIn_PRTDSI__OE_SEL0        (* (reg8 *) JSAlarmIn__PRTDSI__OE_SEL0) 
#define JSAlarmIn_PRTDSI__OE_SEL1        (* (reg8 *) JSAlarmIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define JSAlarmIn_PRTDSI__OUT_SEL0       (* (reg8 *) JSAlarmIn__PRTDSI__OUT_SEL0) 
#define JSAlarmIn_PRTDSI__OUT_SEL1       (* (reg8 *) JSAlarmIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define JSAlarmIn_PRTDSI__SYNC_OUT       (* (reg8 *) JSAlarmIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(JSAlarmIn__SIO_CFG)
    #define JSAlarmIn_SIO_HYST_EN        (* (reg8 *) JSAlarmIn__SIO_HYST_EN)
    #define JSAlarmIn_SIO_REG_HIFREQ     (* (reg8 *) JSAlarmIn__SIO_REG_HIFREQ)
    #define JSAlarmIn_SIO_CFG            (* (reg8 *) JSAlarmIn__SIO_CFG)
    #define JSAlarmIn_SIO_DIFF           (* (reg8 *) JSAlarmIn__SIO_DIFF)
#endif /* (JSAlarmIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(JSAlarmIn__INTSTAT)
    #define JSAlarmIn_INTSTAT            (* (reg8 *) JSAlarmIn__INTSTAT)
    #define JSAlarmIn_SNAP               (* (reg8 *) JSAlarmIn__SNAP)
    
	#define JSAlarmIn_0_INTTYPE_REG 		(* (reg8 *) JSAlarmIn__0__INTTYPE)
#endif /* (JSAlarmIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_JSAlarmIn_H */


/* [] END OF FILE */
