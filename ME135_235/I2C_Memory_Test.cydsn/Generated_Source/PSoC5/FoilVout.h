/*******************************************************************************
* File Name: FoilVout.h  
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

#if !defined(CY_PINS_FoilVout_H) /* Pins FoilVout_H */
#define CY_PINS_FoilVout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FoilVout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FoilVout__PORT == 15 && ((FoilVout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FoilVout_Write(uint8 value);
void    FoilVout_SetDriveMode(uint8 mode);
uint8   FoilVout_ReadDataReg(void);
uint8   FoilVout_Read(void);
void    FoilVout_SetInterruptMode(uint16 position, uint16 mode);
uint8   FoilVout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FoilVout_SetDriveMode() function.
     *  @{
     */
        #define FoilVout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FoilVout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FoilVout_DM_RES_UP          PIN_DM_RES_UP
        #define FoilVout_DM_RES_DWN         PIN_DM_RES_DWN
        #define FoilVout_DM_OD_LO           PIN_DM_OD_LO
        #define FoilVout_DM_OD_HI           PIN_DM_OD_HI
        #define FoilVout_DM_STRONG          PIN_DM_STRONG
        #define FoilVout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FoilVout_MASK               FoilVout__MASK
#define FoilVout_SHIFT              FoilVout__SHIFT
#define FoilVout_WIDTH              1u

/* Interrupt constants */
#if defined(FoilVout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FoilVout_SetInterruptMode() function.
     *  @{
     */
        #define FoilVout_INTR_NONE      (uint16)(0x0000u)
        #define FoilVout_INTR_RISING    (uint16)(0x0001u)
        #define FoilVout_INTR_FALLING   (uint16)(0x0002u)
        #define FoilVout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FoilVout_INTR_MASK      (0x01u) 
#endif /* (FoilVout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FoilVout_PS                     (* (reg8 *) FoilVout__PS)
/* Data Register */
#define FoilVout_DR                     (* (reg8 *) FoilVout__DR)
/* Port Number */
#define FoilVout_PRT_NUM                (* (reg8 *) FoilVout__PRT) 
/* Connect to Analog Globals */                                                  
#define FoilVout_AG                     (* (reg8 *) FoilVout__AG)                       
/* Analog MUX bux enable */
#define FoilVout_AMUX                   (* (reg8 *) FoilVout__AMUX) 
/* Bidirectional Enable */                                                        
#define FoilVout_BIE                    (* (reg8 *) FoilVout__BIE)
/* Bit-mask for Aliased Register Access */
#define FoilVout_BIT_MASK               (* (reg8 *) FoilVout__BIT_MASK)
/* Bypass Enable */
#define FoilVout_BYP                    (* (reg8 *) FoilVout__BYP)
/* Port wide control signals */                                                   
#define FoilVout_CTL                    (* (reg8 *) FoilVout__CTL)
/* Drive Modes */
#define FoilVout_DM0                    (* (reg8 *) FoilVout__DM0) 
#define FoilVout_DM1                    (* (reg8 *) FoilVout__DM1)
#define FoilVout_DM2                    (* (reg8 *) FoilVout__DM2) 
/* Input Buffer Disable Override */
#define FoilVout_INP_DIS                (* (reg8 *) FoilVout__INP_DIS)
/* LCD Common or Segment Drive */
#define FoilVout_LCD_COM_SEG            (* (reg8 *) FoilVout__LCD_COM_SEG)
/* Enable Segment LCD */
#define FoilVout_LCD_EN                 (* (reg8 *) FoilVout__LCD_EN)
/* Slew Rate Control */
#define FoilVout_SLW                    (* (reg8 *) FoilVout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FoilVout_PRTDSI__CAPS_SEL       (* (reg8 *) FoilVout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FoilVout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FoilVout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FoilVout_PRTDSI__OE_SEL0        (* (reg8 *) FoilVout__PRTDSI__OE_SEL0) 
#define FoilVout_PRTDSI__OE_SEL1        (* (reg8 *) FoilVout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FoilVout_PRTDSI__OUT_SEL0       (* (reg8 *) FoilVout__PRTDSI__OUT_SEL0) 
#define FoilVout_PRTDSI__OUT_SEL1       (* (reg8 *) FoilVout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FoilVout_PRTDSI__SYNC_OUT       (* (reg8 *) FoilVout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FoilVout__SIO_CFG)
    #define FoilVout_SIO_HYST_EN        (* (reg8 *) FoilVout__SIO_HYST_EN)
    #define FoilVout_SIO_REG_HIFREQ     (* (reg8 *) FoilVout__SIO_REG_HIFREQ)
    #define FoilVout_SIO_CFG            (* (reg8 *) FoilVout__SIO_CFG)
    #define FoilVout_SIO_DIFF           (* (reg8 *) FoilVout__SIO_DIFF)
#endif /* (FoilVout__SIO_CFG) */

/* Interrupt Registers */
#if defined(FoilVout__INTSTAT)
    #define FoilVout_INTSTAT            (* (reg8 *) FoilVout__INTSTAT)
    #define FoilVout_SNAP               (* (reg8 *) FoilVout__SNAP)
    
	#define FoilVout_0_INTTYPE_REG 		(* (reg8 *) FoilVout__0__INTTYPE)
#endif /* (FoilVout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FoilVout_H */


/* [] END OF FILE */
