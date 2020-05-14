/*******************************************************************************
* File Name: PSTriggerOut.h  
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

#if !defined(CY_PINS_PSTriggerOut_H) /* Pins PSTriggerOut_H */
#define CY_PINS_PSTriggerOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PSTriggerOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PSTriggerOut__PORT == 15 && ((PSTriggerOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PSTriggerOut_Write(uint8 value);
void    PSTriggerOut_SetDriveMode(uint8 mode);
uint8   PSTriggerOut_ReadDataReg(void);
uint8   PSTriggerOut_Read(void);
void    PSTriggerOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   PSTriggerOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PSTriggerOut_SetDriveMode() function.
     *  @{
     */
        #define PSTriggerOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PSTriggerOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PSTriggerOut_DM_RES_UP          PIN_DM_RES_UP
        #define PSTriggerOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define PSTriggerOut_DM_OD_LO           PIN_DM_OD_LO
        #define PSTriggerOut_DM_OD_HI           PIN_DM_OD_HI
        #define PSTriggerOut_DM_STRONG          PIN_DM_STRONG
        #define PSTriggerOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PSTriggerOut_MASK               PSTriggerOut__MASK
#define PSTriggerOut_SHIFT              PSTriggerOut__SHIFT
#define PSTriggerOut_WIDTH              1u

/* Interrupt constants */
#if defined(PSTriggerOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PSTriggerOut_SetInterruptMode() function.
     *  @{
     */
        #define PSTriggerOut_INTR_NONE      (uint16)(0x0000u)
        #define PSTriggerOut_INTR_RISING    (uint16)(0x0001u)
        #define PSTriggerOut_INTR_FALLING   (uint16)(0x0002u)
        #define PSTriggerOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PSTriggerOut_INTR_MASK      (0x01u) 
#endif /* (PSTriggerOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PSTriggerOut_PS                     (* (reg8 *) PSTriggerOut__PS)
/* Data Register */
#define PSTriggerOut_DR                     (* (reg8 *) PSTriggerOut__DR)
/* Port Number */
#define PSTriggerOut_PRT_NUM                (* (reg8 *) PSTriggerOut__PRT) 
/* Connect to Analog Globals */                                                  
#define PSTriggerOut_AG                     (* (reg8 *) PSTriggerOut__AG)                       
/* Analog MUX bux enable */
#define PSTriggerOut_AMUX                   (* (reg8 *) PSTriggerOut__AMUX) 
/* Bidirectional Enable */                                                        
#define PSTriggerOut_BIE                    (* (reg8 *) PSTriggerOut__BIE)
/* Bit-mask for Aliased Register Access */
#define PSTriggerOut_BIT_MASK               (* (reg8 *) PSTriggerOut__BIT_MASK)
/* Bypass Enable */
#define PSTriggerOut_BYP                    (* (reg8 *) PSTriggerOut__BYP)
/* Port wide control signals */                                                   
#define PSTriggerOut_CTL                    (* (reg8 *) PSTriggerOut__CTL)
/* Drive Modes */
#define PSTriggerOut_DM0                    (* (reg8 *) PSTriggerOut__DM0) 
#define PSTriggerOut_DM1                    (* (reg8 *) PSTriggerOut__DM1)
#define PSTriggerOut_DM2                    (* (reg8 *) PSTriggerOut__DM2) 
/* Input Buffer Disable Override */
#define PSTriggerOut_INP_DIS                (* (reg8 *) PSTriggerOut__INP_DIS)
/* LCD Common or Segment Drive */
#define PSTriggerOut_LCD_COM_SEG            (* (reg8 *) PSTriggerOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define PSTriggerOut_LCD_EN                 (* (reg8 *) PSTriggerOut__LCD_EN)
/* Slew Rate Control */
#define PSTriggerOut_SLW                    (* (reg8 *) PSTriggerOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PSTriggerOut_PRTDSI__CAPS_SEL       (* (reg8 *) PSTriggerOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PSTriggerOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PSTriggerOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PSTriggerOut_PRTDSI__OE_SEL0        (* (reg8 *) PSTriggerOut__PRTDSI__OE_SEL0) 
#define PSTriggerOut_PRTDSI__OE_SEL1        (* (reg8 *) PSTriggerOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PSTriggerOut_PRTDSI__OUT_SEL0       (* (reg8 *) PSTriggerOut__PRTDSI__OUT_SEL0) 
#define PSTriggerOut_PRTDSI__OUT_SEL1       (* (reg8 *) PSTriggerOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PSTriggerOut_PRTDSI__SYNC_OUT       (* (reg8 *) PSTriggerOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PSTriggerOut__SIO_CFG)
    #define PSTriggerOut_SIO_HYST_EN        (* (reg8 *) PSTriggerOut__SIO_HYST_EN)
    #define PSTriggerOut_SIO_REG_HIFREQ     (* (reg8 *) PSTriggerOut__SIO_REG_HIFREQ)
    #define PSTriggerOut_SIO_CFG            (* (reg8 *) PSTriggerOut__SIO_CFG)
    #define PSTriggerOut_SIO_DIFF           (* (reg8 *) PSTriggerOut__SIO_DIFF)
#endif /* (PSTriggerOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(PSTriggerOut__INTSTAT)
    #define PSTriggerOut_INTSTAT            (* (reg8 *) PSTriggerOut__INTSTAT)
    #define PSTriggerOut_SNAP               (* (reg8 *) PSTriggerOut__SNAP)
    
	#define PSTriggerOut_0_INTTYPE_REG 		(* (reg8 *) PSTriggerOut__0__INTTYPE)
#endif /* (PSTriggerOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PSTriggerOut_H */


/* [] END OF FILE */
