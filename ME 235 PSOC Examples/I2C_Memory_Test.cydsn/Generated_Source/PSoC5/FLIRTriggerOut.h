/*******************************************************************************
* File Name: FLIRTriggerOut.h  
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

#if !defined(CY_PINS_FLIRTriggerOut_H) /* Pins FLIRTriggerOut_H */
#define CY_PINS_FLIRTriggerOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FLIRTriggerOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FLIRTriggerOut__PORT == 15 && ((FLIRTriggerOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FLIRTriggerOut_Write(uint8 value);
void    FLIRTriggerOut_SetDriveMode(uint8 mode);
uint8   FLIRTriggerOut_ReadDataReg(void);
uint8   FLIRTriggerOut_Read(void);
void    FLIRTriggerOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   FLIRTriggerOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FLIRTriggerOut_SetDriveMode() function.
     *  @{
     */
        #define FLIRTriggerOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FLIRTriggerOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FLIRTriggerOut_DM_RES_UP          PIN_DM_RES_UP
        #define FLIRTriggerOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define FLIRTriggerOut_DM_OD_LO           PIN_DM_OD_LO
        #define FLIRTriggerOut_DM_OD_HI           PIN_DM_OD_HI
        #define FLIRTriggerOut_DM_STRONG          PIN_DM_STRONG
        #define FLIRTriggerOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FLIRTriggerOut_MASK               FLIRTriggerOut__MASK
#define FLIRTriggerOut_SHIFT              FLIRTriggerOut__SHIFT
#define FLIRTriggerOut_WIDTH              1u

/* Interrupt constants */
#if defined(FLIRTriggerOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FLIRTriggerOut_SetInterruptMode() function.
     *  @{
     */
        #define FLIRTriggerOut_INTR_NONE      (uint16)(0x0000u)
        #define FLIRTriggerOut_INTR_RISING    (uint16)(0x0001u)
        #define FLIRTriggerOut_INTR_FALLING   (uint16)(0x0002u)
        #define FLIRTriggerOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FLIRTriggerOut_INTR_MASK      (0x01u) 
#endif /* (FLIRTriggerOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FLIRTriggerOut_PS                     (* (reg8 *) FLIRTriggerOut__PS)
/* Data Register */
#define FLIRTriggerOut_DR                     (* (reg8 *) FLIRTriggerOut__DR)
/* Port Number */
#define FLIRTriggerOut_PRT_NUM                (* (reg8 *) FLIRTriggerOut__PRT) 
/* Connect to Analog Globals */                                                  
#define FLIRTriggerOut_AG                     (* (reg8 *) FLIRTriggerOut__AG)                       
/* Analog MUX bux enable */
#define FLIRTriggerOut_AMUX                   (* (reg8 *) FLIRTriggerOut__AMUX) 
/* Bidirectional Enable */                                                        
#define FLIRTriggerOut_BIE                    (* (reg8 *) FLIRTriggerOut__BIE)
/* Bit-mask for Aliased Register Access */
#define FLIRTriggerOut_BIT_MASK               (* (reg8 *) FLIRTriggerOut__BIT_MASK)
/* Bypass Enable */
#define FLIRTriggerOut_BYP                    (* (reg8 *) FLIRTriggerOut__BYP)
/* Port wide control signals */                                                   
#define FLIRTriggerOut_CTL                    (* (reg8 *) FLIRTriggerOut__CTL)
/* Drive Modes */
#define FLIRTriggerOut_DM0                    (* (reg8 *) FLIRTriggerOut__DM0) 
#define FLIRTriggerOut_DM1                    (* (reg8 *) FLIRTriggerOut__DM1)
#define FLIRTriggerOut_DM2                    (* (reg8 *) FLIRTriggerOut__DM2) 
/* Input Buffer Disable Override */
#define FLIRTriggerOut_INP_DIS                (* (reg8 *) FLIRTriggerOut__INP_DIS)
/* LCD Common or Segment Drive */
#define FLIRTriggerOut_LCD_COM_SEG            (* (reg8 *) FLIRTriggerOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define FLIRTriggerOut_LCD_EN                 (* (reg8 *) FLIRTriggerOut__LCD_EN)
/* Slew Rate Control */
#define FLIRTriggerOut_SLW                    (* (reg8 *) FLIRTriggerOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FLIRTriggerOut_PRTDSI__CAPS_SEL       (* (reg8 *) FLIRTriggerOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FLIRTriggerOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FLIRTriggerOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FLIRTriggerOut_PRTDSI__OE_SEL0        (* (reg8 *) FLIRTriggerOut__PRTDSI__OE_SEL0) 
#define FLIRTriggerOut_PRTDSI__OE_SEL1        (* (reg8 *) FLIRTriggerOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FLIRTriggerOut_PRTDSI__OUT_SEL0       (* (reg8 *) FLIRTriggerOut__PRTDSI__OUT_SEL0) 
#define FLIRTriggerOut_PRTDSI__OUT_SEL1       (* (reg8 *) FLIRTriggerOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FLIRTriggerOut_PRTDSI__SYNC_OUT       (* (reg8 *) FLIRTriggerOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FLIRTriggerOut__SIO_CFG)
    #define FLIRTriggerOut_SIO_HYST_EN        (* (reg8 *) FLIRTriggerOut__SIO_HYST_EN)
    #define FLIRTriggerOut_SIO_REG_HIFREQ     (* (reg8 *) FLIRTriggerOut__SIO_REG_HIFREQ)
    #define FLIRTriggerOut_SIO_CFG            (* (reg8 *) FLIRTriggerOut__SIO_CFG)
    #define FLIRTriggerOut_SIO_DIFF           (* (reg8 *) FLIRTriggerOut__SIO_DIFF)
#endif /* (FLIRTriggerOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(FLIRTriggerOut__INTSTAT)
    #define FLIRTriggerOut_INTSTAT            (* (reg8 *) FLIRTriggerOut__INTSTAT)
    #define FLIRTriggerOut_SNAP               (* (reg8 *) FLIRTriggerOut__SNAP)
    
	#define FLIRTriggerOut_0_INTTYPE_REG 		(* (reg8 *) FLIRTriggerOut__0__INTTYPE)
#endif /* (FLIRTriggerOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FLIRTriggerOut_H */


/* [] END OF FILE */
