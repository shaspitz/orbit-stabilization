/*******************************************************************************
* File Name: FanControlOut.h  
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

#if !defined(CY_PINS_FanControlOut_H) /* Pins FanControlOut_H */
#define CY_PINS_FanControlOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FanControlOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FanControlOut__PORT == 15 && ((FanControlOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FanControlOut_Write(uint8 value);
void    FanControlOut_SetDriveMode(uint8 mode);
uint8   FanControlOut_ReadDataReg(void);
uint8   FanControlOut_Read(void);
void    FanControlOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   FanControlOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FanControlOut_SetDriveMode() function.
     *  @{
     */
        #define FanControlOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FanControlOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FanControlOut_DM_RES_UP          PIN_DM_RES_UP
        #define FanControlOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define FanControlOut_DM_OD_LO           PIN_DM_OD_LO
        #define FanControlOut_DM_OD_HI           PIN_DM_OD_HI
        #define FanControlOut_DM_STRONG          PIN_DM_STRONG
        #define FanControlOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FanControlOut_MASK               FanControlOut__MASK
#define FanControlOut_SHIFT              FanControlOut__SHIFT
#define FanControlOut_WIDTH              1u

/* Interrupt constants */
#if defined(FanControlOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FanControlOut_SetInterruptMode() function.
     *  @{
     */
        #define FanControlOut_INTR_NONE      (uint16)(0x0000u)
        #define FanControlOut_INTR_RISING    (uint16)(0x0001u)
        #define FanControlOut_INTR_FALLING   (uint16)(0x0002u)
        #define FanControlOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FanControlOut_INTR_MASK      (0x01u) 
#endif /* (FanControlOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FanControlOut_PS                     (* (reg8 *) FanControlOut__PS)
/* Data Register */
#define FanControlOut_DR                     (* (reg8 *) FanControlOut__DR)
/* Port Number */
#define FanControlOut_PRT_NUM                (* (reg8 *) FanControlOut__PRT) 
/* Connect to Analog Globals */                                                  
#define FanControlOut_AG                     (* (reg8 *) FanControlOut__AG)                       
/* Analog MUX bux enable */
#define FanControlOut_AMUX                   (* (reg8 *) FanControlOut__AMUX) 
/* Bidirectional Enable */                                                        
#define FanControlOut_BIE                    (* (reg8 *) FanControlOut__BIE)
/* Bit-mask for Aliased Register Access */
#define FanControlOut_BIT_MASK               (* (reg8 *) FanControlOut__BIT_MASK)
/* Bypass Enable */
#define FanControlOut_BYP                    (* (reg8 *) FanControlOut__BYP)
/* Port wide control signals */                                                   
#define FanControlOut_CTL                    (* (reg8 *) FanControlOut__CTL)
/* Drive Modes */
#define FanControlOut_DM0                    (* (reg8 *) FanControlOut__DM0) 
#define FanControlOut_DM1                    (* (reg8 *) FanControlOut__DM1)
#define FanControlOut_DM2                    (* (reg8 *) FanControlOut__DM2) 
/* Input Buffer Disable Override */
#define FanControlOut_INP_DIS                (* (reg8 *) FanControlOut__INP_DIS)
/* LCD Common or Segment Drive */
#define FanControlOut_LCD_COM_SEG            (* (reg8 *) FanControlOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define FanControlOut_LCD_EN                 (* (reg8 *) FanControlOut__LCD_EN)
/* Slew Rate Control */
#define FanControlOut_SLW                    (* (reg8 *) FanControlOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FanControlOut_PRTDSI__CAPS_SEL       (* (reg8 *) FanControlOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FanControlOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FanControlOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FanControlOut_PRTDSI__OE_SEL0        (* (reg8 *) FanControlOut__PRTDSI__OE_SEL0) 
#define FanControlOut_PRTDSI__OE_SEL1        (* (reg8 *) FanControlOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FanControlOut_PRTDSI__OUT_SEL0       (* (reg8 *) FanControlOut__PRTDSI__OUT_SEL0) 
#define FanControlOut_PRTDSI__OUT_SEL1       (* (reg8 *) FanControlOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FanControlOut_PRTDSI__SYNC_OUT       (* (reg8 *) FanControlOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FanControlOut__SIO_CFG)
    #define FanControlOut_SIO_HYST_EN        (* (reg8 *) FanControlOut__SIO_HYST_EN)
    #define FanControlOut_SIO_REG_HIFREQ     (* (reg8 *) FanControlOut__SIO_REG_HIFREQ)
    #define FanControlOut_SIO_CFG            (* (reg8 *) FanControlOut__SIO_CFG)
    #define FanControlOut_SIO_DIFF           (* (reg8 *) FanControlOut__SIO_DIFF)
#endif /* (FanControlOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(FanControlOut__INTSTAT)
    #define FanControlOut_INTSTAT            (* (reg8 *) FanControlOut__INTSTAT)
    #define FanControlOut_SNAP               (* (reg8 *) FanControlOut__SNAP)
    
	#define FanControlOut_0_INTTYPE_REG 		(* (reg8 *) FanControlOut__0__INTTYPE)
#endif /* (FanControlOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FanControlOut_H */


/* [] END OF FILE */
