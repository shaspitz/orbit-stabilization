/*******************************************************************************
* File Name: ModelVout.h  
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

#if !defined(CY_PINS_ModelVout_H) /* Pins ModelVout_H */
#define CY_PINS_ModelVout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ModelVout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ModelVout__PORT == 15 && ((ModelVout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ModelVout_Write(uint8 value);
void    ModelVout_SetDriveMode(uint8 mode);
uint8   ModelVout_ReadDataReg(void);
uint8   ModelVout_Read(void);
void    ModelVout_SetInterruptMode(uint16 position, uint16 mode);
uint8   ModelVout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ModelVout_SetDriveMode() function.
     *  @{
     */
        #define ModelVout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ModelVout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ModelVout_DM_RES_UP          PIN_DM_RES_UP
        #define ModelVout_DM_RES_DWN         PIN_DM_RES_DWN
        #define ModelVout_DM_OD_LO           PIN_DM_OD_LO
        #define ModelVout_DM_OD_HI           PIN_DM_OD_HI
        #define ModelVout_DM_STRONG          PIN_DM_STRONG
        #define ModelVout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ModelVout_MASK               ModelVout__MASK
#define ModelVout_SHIFT              ModelVout__SHIFT
#define ModelVout_WIDTH              1u

/* Interrupt constants */
#if defined(ModelVout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ModelVout_SetInterruptMode() function.
     *  @{
     */
        #define ModelVout_INTR_NONE      (uint16)(0x0000u)
        #define ModelVout_INTR_RISING    (uint16)(0x0001u)
        #define ModelVout_INTR_FALLING   (uint16)(0x0002u)
        #define ModelVout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ModelVout_INTR_MASK      (0x01u) 
#endif /* (ModelVout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ModelVout_PS                     (* (reg8 *) ModelVout__PS)
/* Data Register */
#define ModelVout_DR                     (* (reg8 *) ModelVout__DR)
/* Port Number */
#define ModelVout_PRT_NUM                (* (reg8 *) ModelVout__PRT) 
/* Connect to Analog Globals */                                                  
#define ModelVout_AG                     (* (reg8 *) ModelVout__AG)                       
/* Analog MUX bux enable */
#define ModelVout_AMUX                   (* (reg8 *) ModelVout__AMUX) 
/* Bidirectional Enable */                                                        
#define ModelVout_BIE                    (* (reg8 *) ModelVout__BIE)
/* Bit-mask for Aliased Register Access */
#define ModelVout_BIT_MASK               (* (reg8 *) ModelVout__BIT_MASK)
/* Bypass Enable */
#define ModelVout_BYP                    (* (reg8 *) ModelVout__BYP)
/* Port wide control signals */                                                   
#define ModelVout_CTL                    (* (reg8 *) ModelVout__CTL)
/* Drive Modes */
#define ModelVout_DM0                    (* (reg8 *) ModelVout__DM0) 
#define ModelVout_DM1                    (* (reg8 *) ModelVout__DM1)
#define ModelVout_DM2                    (* (reg8 *) ModelVout__DM2) 
/* Input Buffer Disable Override */
#define ModelVout_INP_DIS                (* (reg8 *) ModelVout__INP_DIS)
/* LCD Common or Segment Drive */
#define ModelVout_LCD_COM_SEG            (* (reg8 *) ModelVout__LCD_COM_SEG)
/* Enable Segment LCD */
#define ModelVout_LCD_EN                 (* (reg8 *) ModelVout__LCD_EN)
/* Slew Rate Control */
#define ModelVout_SLW                    (* (reg8 *) ModelVout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ModelVout_PRTDSI__CAPS_SEL       (* (reg8 *) ModelVout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ModelVout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ModelVout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ModelVout_PRTDSI__OE_SEL0        (* (reg8 *) ModelVout__PRTDSI__OE_SEL0) 
#define ModelVout_PRTDSI__OE_SEL1        (* (reg8 *) ModelVout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ModelVout_PRTDSI__OUT_SEL0       (* (reg8 *) ModelVout__PRTDSI__OUT_SEL0) 
#define ModelVout_PRTDSI__OUT_SEL1       (* (reg8 *) ModelVout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ModelVout_PRTDSI__SYNC_OUT       (* (reg8 *) ModelVout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ModelVout__SIO_CFG)
    #define ModelVout_SIO_HYST_EN        (* (reg8 *) ModelVout__SIO_HYST_EN)
    #define ModelVout_SIO_REG_HIFREQ     (* (reg8 *) ModelVout__SIO_REG_HIFREQ)
    #define ModelVout_SIO_CFG            (* (reg8 *) ModelVout__SIO_CFG)
    #define ModelVout_SIO_DIFF           (* (reg8 *) ModelVout__SIO_DIFF)
#endif /* (ModelVout__SIO_CFG) */

/* Interrupt Registers */
#if defined(ModelVout__INTSTAT)
    #define ModelVout_INTSTAT            (* (reg8 *) ModelVout__INTSTAT)
    #define ModelVout_SNAP               (* (reg8 *) ModelVout__SNAP)
    
	#define ModelVout_0_INTTYPE_REG 		(* (reg8 *) ModelVout__0__INTTYPE)
#endif /* (ModelVout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ModelVout_H */


/* [] END OF FILE */
