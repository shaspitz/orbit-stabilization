/*******************************************************************************
* File Name: VSupply.h  
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

#if !defined(CY_PINS_VSupply_H) /* Pins VSupply_H */
#define CY_PINS_VSupply_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VSupply_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VSupply__PORT == 15 && ((VSupply__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VSupply_Write(uint8 value);
void    VSupply_SetDriveMode(uint8 mode);
uint8   VSupply_ReadDataReg(void);
uint8   VSupply_Read(void);
void    VSupply_SetInterruptMode(uint16 position, uint16 mode);
uint8   VSupply_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VSupply_SetDriveMode() function.
     *  @{
     */
        #define VSupply_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VSupply_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VSupply_DM_RES_UP          PIN_DM_RES_UP
        #define VSupply_DM_RES_DWN         PIN_DM_RES_DWN
        #define VSupply_DM_OD_LO           PIN_DM_OD_LO
        #define VSupply_DM_OD_HI           PIN_DM_OD_HI
        #define VSupply_DM_STRONG          PIN_DM_STRONG
        #define VSupply_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VSupply_MASK               VSupply__MASK
#define VSupply_SHIFT              VSupply__SHIFT
#define VSupply_WIDTH              1u

/* Interrupt constants */
#if defined(VSupply__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VSupply_SetInterruptMode() function.
     *  @{
     */
        #define VSupply_INTR_NONE      (uint16)(0x0000u)
        #define VSupply_INTR_RISING    (uint16)(0x0001u)
        #define VSupply_INTR_FALLING   (uint16)(0x0002u)
        #define VSupply_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VSupply_INTR_MASK      (0x01u) 
#endif /* (VSupply__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VSupply_PS                     (* (reg8 *) VSupply__PS)
/* Data Register */
#define VSupply_DR                     (* (reg8 *) VSupply__DR)
/* Port Number */
#define VSupply_PRT_NUM                (* (reg8 *) VSupply__PRT) 
/* Connect to Analog Globals */                                                  
#define VSupply_AG                     (* (reg8 *) VSupply__AG)                       
/* Analog MUX bux enable */
#define VSupply_AMUX                   (* (reg8 *) VSupply__AMUX) 
/* Bidirectional Enable */                                                        
#define VSupply_BIE                    (* (reg8 *) VSupply__BIE)
/* Bit-mask for Aliased Register Access */
#define VSupply_BIT_MASK               (* (reg8 *) VSupply__BIT_MASK)
/* Bypass Enable */
#define VSupply_BYP                    (* (reg8 *) VSupply__BYP)
/* Port wide control signals */                                                   
#define VSupply_CTL                    (* (reg8 *) VSupply__CTL)
/* Drive Modes */
#define VSupply_DM0                    (* (reg8 *) VSupply__DM0) 
#define VSupply_DM1                    (* (reg8 *) VSupply__DM1)
#define VSupply_DM2                    (* (reg8 *) VSupply__DM2) 
/* Input Buffer Disable Override */
#define VSupply_INP_DIS                (* (reg8 *) VSupply__INP_DIS)
/* LCD Common or Segment Drive */
#define VSupply_LCD_COM_SEG            (* (reg8 *) VSupply__LCD_COM_SEG)
/* Enable Segment LCD */
#define VSupply_LCD_EN                 (* (reg8 *) VSupply__LCD_EN)
/* Slew Rate Control */
#define VSupply_SLW                    (* (reg8 *) VSupply__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VSupply_PRTDSI__CAPS_SEL       (* (reg8 *) VSupply__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VSupply_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VSupply__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VSupply_PRTDSI__OE_SEL0        (* (reg8 *) VSupply__PRTDSI__OE_SEL0) 
#define VSupply_PRTDSI__OE_SEL1        (* (reg8 *) VSupply__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VSupply_PRTDSI__OUT_SEL0       (* (reg8 *) VSupply__PRTDSI__OUT_SEL0) 
#define VSupply_PRTDSI__OUT_SEL1       (* (reg8 *) VSupply__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VSupply_PRTDSI__SYNC_OUT       (* (reg8 *) VSupply__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VSupply__SIO_CFG)
    #define VSupply_SIO_HYST_EN        (* (reg8 *) VSupply__SIO_HYST_EN)
    #define VSupply_SIO_REG_HIFREQ     (* (reg8 *) VSupply__SIO_REG_HIFREQ)
    #define VSupply_SIO_CFG            (* (reg8 *) VSupply__SIO_CFG)
    #define VSupply_SIO_DIFF           (* (reg8 *) VSupply__SIO_DIFF)
#endif /* (VSupply__SIO_CFG) */

/* Interrupt Registers */
#if defined(VSupply__INTSTAT)
    #define VSupply_INTSTAT            (* (reg8 *) VSupply__INTSTAT)
    #define VSupply_SNAP               (* (reg8 *) VSupply__SNAP)
    
	#define VSupply_0_INTTYPE_REG 		(* (reg8 *) VSupply__0__INTTYPE)
#endif /* (VSupply__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VSupply_H */


/* [] END OF FILE */
