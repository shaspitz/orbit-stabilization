/*******************************************************************************
* File Name: JSVout.h  
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

#if !defined(CY_PINS_JSVout_H) /* Pins JSVout_H */
#define CY_PINS_JSVout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "JSVout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 JSVout__PORT == 15 && ((JSVout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    JSVout_Write(uint8 value);
void    JSVout_SetDriveMode(uint8 mode);
uint8   JSVout_ReadDataReg(void);
uint8   JSVout_Read(void);
void    JSVout_SetInterruptMode(uint16 position, uint16 mode);
uint8   JSVout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the JSVout_SetDriveMode() function.
     *  @{
     */
        #define JSVout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define JSVout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define JSVout_DM_RES_UP          PIN_DM_RES_UP
        #define JSVout_DM_RES_DWN         PIN_DM_RES_DWN
        #define JSVout_DM_OD_LO           PIN_DM_OD_LO
        #define JSVout_DM_OD_HI           PIN_DM_OD_HI
        #define JSVout_DM_STRONG          PIN_DM_STRONG
        #define JSVout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define JSVout_MASK               JSVout__MASK
#define JSVout_SHIFT              JSVout__SHIFT
#define JSVout_WIDTH              1u

/* Interrupt constants */
#if defined(JSVout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in JSVout_SetInterruptMode() function.
     *  @{
     */
        #define JSVout_INTR_NONE      (uint16)(0x0000u)
        #define JSVout_INTR_RISING    (uint16)(0x0001u)
        #define JSVout_INTR_FALLING   (uint16)(0x0002u)
        #define JSVout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define JSVout_INTR_MASK      (0x01u) 
#endif /* (JSVout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JSVout_PS                     (* (reg8 *) JSVout__PS)
/* Data Register */
#define JSVout_DR                     (* (reg8 *) JSVout__DR)
/* Port Number */
#define JSVout_PRT_NUM                (* (reg8 *) JSVout__PRT) 
/* Connect to Analog Globals */                                                  
#define JSVout_AG                     (* (reg8 *) JSVout__AG)                       
/* Analog MUX bux enable */
#define JSVout_AMUX                   (* (reg8 *) JSVout__AMUX) 
/* Bidirectional Enable */                                                        
#define JSVout_BIE                    (* (reg8 *) JSVout__BIE)
/* Bit-mask for Aliased Register Access */
#define JSVout_BIT_MASK               (* (reg8 *) JSVout__BIT_MASK)
/* Bypass Enable */
#define JSVout_BYP                    (* (reg8 *) JSVout__BYP)
/* Port wide control signals */                                                   
#define JSVout_CTL                    (* (reg8 *) JSVout__CTL)
/* Drive Modes */
#define JSVout_DM0                    (* (reg8 *) JSVout__DM0) 
#define JSVout_DM1                    (* (reg8 *) JSVout__DM1)
#define JSVout_DM2                    (* (reg8 *) JSVout__DM2) 
/* Input Buffer Disable Override */
#define JSVout_INP_DIS                (* (reg8 *) JSVout__INP_DIS)
/* LCD Common or Segment Drive */
#define JSVout_LCD_COM_SEG            (* (reg8 *) JSVout__LCD_COM_SEG)
/* Enable Segment LCD */
#define JSVout_LCD_EN                 (* (reg8 *) JSVout__LCD_EN)
/* Slew Rate Control */
#define JSVout_SLW                    (* (reg8 *) JSVout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define JSVout_PRTDSI__CAPS_SEL       (* (reg8 *) JSVout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define JSVout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) JSVout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define JSVout_PRTDSI__OE_SEL0        (* (reg8 *) JSVout__PRTDSI__OE_SEL0) 
#define JSVout_PRTDSI__OE_SEL1        (* (reg8 *) JSVout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define JSVout_PRTDSI__OUT_SEL0       (* (reg8 *) JSVout__PRTDSI__OUT_SEL0) 
#define JSVout_PRTDSI__OUT_SEL1       (* (reg8 *) JSVout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define JSVout_PRTDSI__SYNC_OUT       (* (reg8 *) JSVout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(JSVout__SIO_CFG)
    #define JSVout_SIO_HYST_EN        (* (reg8 *) JSVout__SIO_HYST_EN)
    #define JSVout_SIO_REG_HIFREQ     (* (reg8 *) JSVout__SIO_REG_HIFREQ)
    #define JSVout_SIO_CFG            (* (reg8 *) JSVout__SIO_CFG)
    #define JSVout_SIO_DIFF           (* (reg8 *) JSVout__SIO_DIFF)
#endif /* (JSVout__SIO_CFG) */

/* Interrupt Registers */
#if defined(JSVout__INTSTAT)
    #define JSVout_INTSTAT            (* (reg8 *) JSVout__INTSTAT)
    #define JSVout_SNAP               (* (reg8 *) JSVout__SNAP)
    
	#define JSVout_0_INTTYPE_REG 		(* (reg8 *) JSVout__0__INTTYPE)
#endif /* (JSVout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_JSVout_H */


/* [] END OF FILE */
