/*******************************************************************************
* File Name: MotorDirection.h  
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

#if !defined(CY_PINS_MotorDirection_H) /* Pins MotorDirection_H */
#define CY_PINS_MotorDirection_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorDirection_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorDirection__PORT == 15 && ((MotorDirection__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorDirection_Write(uint8 value);
void    MotorDirection_SetDriveMode(uint8 mode);
uint8   MotorDirection_ReadDataReg(void);
uint8   MotorDirection_Read(void);
void    MotorDirection_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorDirection_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorDirection_SetDriveMode() function.
     *  @{
     */
        #define MotorDirection_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorDirection_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorDirection_DM_RES_UP          PIN_DM_RES_UP
        #define MotorDirection_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorDirection_DM_OD_LO           PIN_DM_OD_LO
        #define MotorDirection_DM_OD_HI           PIN_DM_OD_HI
        #define MotorDirection_DM_STRONG          PIN_DM_STRONG
        #define MotorDirection_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorDirection_MASK               MotorDirection__MASK
#define MotorDirection_SHIFT              MotorDirection__SHIFT
#define MotorDirection_WIDTH              1u

/* Interrupt constants */
#if defined(MotorDirection__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorDirection_SetInterruptMode() function.
     *  @{
     */
        #define MotorDirection_INTR_NONE      (uint16)(0x0000u)
        #define MotorDirection_INTR_RISING    (uint16)(0x0001u)
        #define MotorDirection_INTR_FALLING   (uint16)(0x0002u)
        #define MotorDirection_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorDirection_INTR_MASK      (0x01u) 
#endif /* (MotorDirection__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorDirection_PS                     (* (reg8 *) MotorDirection__PS)
/* Data Register */
#define MotorDirection_DR                     (* (reg8 *) MotorDirection__DR)
/* Port Number */
#define MotorDirection_PRT_NUM                (* (reg8 *) MotorDirection__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorDirection_AG                     (* (reg8 *) MotorDirection__AG)                       
/* Analog MUX bux enable */
#define MotorDirection_AMUX                   (* (reg8 *) MotorDirection__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorDirection_BIE                    (* (reg8 *) MotorDirection__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorDirection_BIT_MASK               (* (reg8 *) MotorDirection__BIT_MASK)
/* Bypass Enable */
#define MotorDirection_BYP                    (* (reg8 *) MotorDirection__BYP)
/* Port wide control signals */                                                   
#define MotorDirection_CTL                    (* (reg8 *) MotorDirection__CTL)
/* Drive Modes */
#define MotorDirection_DM0                    (* (reg8 *) MotorDirection__DM0) 
#define MotorDirection_DM1                    (* (reg8 *) MotorDirection__DM1)
#define MotorDirection_DM2                    (* (reg8 *) MotorDirection__DM2) 
/* Input Buffer Disable Override */
#define MotorDirection_INP_DIS                (* (reg8 *) MotorDirection__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorDirection_LCD_COM_SEG            (* (reg8 *) MotorDirection__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorDirection_LCD_EN                 (* (reg8 *) MotorDirection__LCD_EN)
/* Slew Rate Control */
#define MotorDirection_SLW                    (* (reg8 *) MotorDirection__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorDirection_PRTDSI__CAPS_SEL       (* (reg8 *) MotorDirection__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorDirection_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorDirection__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorDirection_PRTDSI__OE_SEL0        (* (reg8 *) MotorDirection__PRTDSI__OE_SEL0) 
#define MotorDirection_PRTDSI__OE_SEL1        (* (reg8 *) MotorDirection__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorDirection_PRTDSI__OUT_SEL0       (* (reg8 *) MotorDirection__PRTDSI__OUT_SEL0) 
#define MotorDirection_PRTDSI__OUT_SEL1       (* (reg8 *) MotorDirection__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorDirection_PRTDSI__SYNC_OUT       (* (reg8 *) MotorDirection__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorDirection__SIO_CFG)
    #define MotorDirection_SIO_HYST_EN        (* (reg8 *) MotorDirection__SIO_HYST_EN)
    #define MotorDirection_SIO_REG_HIFREQ     (* (reg8 *) MotorDirection__SIO_REG_HIFREQ)
    #define MotorDirection_SIO_CFG            (* (reg8 *) MotorDirection__SIO_CFG)
    #define MotorDirection_SIO_DIFF           (* (reg8 *) MotorDirection__SIO_DIFF)
#endif /* (MotorDirection__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorDirection__INTSTAT)
    #define MotorDirection_INTSTAT            (* (reg8 *) MotorDirection__INTSTAT)
    #define MotorDirection_SNAP               (* (reg8 *) MotorDirection__SNAP)
    
	#define MotorDirection_0_INTTYPE_REG 		(* (reg8 *) MotorDirection__0__INTTYPE)
#endif /* (MotorDirection__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorDirection_H */


/* [] END OF FILE */
