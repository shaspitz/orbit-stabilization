/*******************************************************************************
* File Name: MotorOut.h  
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

#if !defined(CY_PINS_MotorOut_H) /* Pins MotorOut_H */
#define CY_PINS_MotorOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorOut__PORT == 15 && ((MotorOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorOut_Write(uint8 value);
void    MotorOut_SetDriveMode(uint8 mode);
uint8   MotorOut_ReadDataReg(void);
uint8   MotorOut_Read(void);
void    MotorOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorOut_SetDriveMode() function.
     *  @{
     */
        #define MotorOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorOut_DM_RES_UP          PIN_DM_RES_UP
        #define MotorOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorOut_DM_OD_LO           PIN_DM_OD_LO
        #define MotorOut_DM_OD_HI           PIN_DM_OD_HI
        #define MotorOut_DM_STRONG          PIN_DM_STRONG
        #define MotorOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorOut_MASK               MotorOut__MASK
#define MotorOut_SHIFT              MotorOut__SHIFT
#define MotorOut_WIDTH              1u

/* Interrupt constants */
#if defined(MotorOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorOut_SetInterruptMode() function.
     *  @{
     */
        #define MotorOut_INTR_NONE      (uint16)(0x0000u)
        #define MotorOut_INTR_RISING    (uint16)(0x0001u)
        #define MotorOut_INTR_FALLING   (uint16)(0x0002u)
        #define MotorOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorOut_INTR_MASK      (0x01u) 
#endif /* (MotorOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorOut_PS                     (* (reg8 *) MotorOut__PS)
/* Data Register */
#define MotorOut_DR                     (* (reg8 *) MotorOut__DR)
/* Port Number */
#define MotorOut_PRT_NUM                (* (reg8 *) MotorOut__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorOut_AG                     (* (reg8 *) MotorOut__AG)                       
/* Analog MUX bux enable */
#define MotorOut_AMUX                   (* (reg8 *) MotorOut__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorOut_BIE                    (* (reg8 *) MotorOut__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorOut_BIT_MASK               (* (reg8 *) MotorOut__BIT_MASK)
/* Bypass Enable */
#define MotorOut_BYP                    (* (reg8 *) MotorOut__BYP)
/* Port wide control signals */                                                   
#define MotorOut_CTL                    (* (reg8 *) MotorOut__CTL)
/* Drive Modes */
#define MotorOut_DM0                    (* (reg8 *) MotorOut__DM0) 
#define MotorOut_DM1                    (* (reg8 *) MotorOut__DM1)
#define MotorOut_DM2                    (* (reg8 *) MotorOut__DM2) 
/* Input Buffer Disable Override */
#define MotorOut_INP_DIS                (* (reg8 *) MotorOut__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorOut_LCD_COM_SEG            (* (reg8 *) MotorOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorOut_LCD_EN                 (* (reg8 *) MotorOut__LCD_EN)
/* Slew Rate Control */
#define MotorOut_SLW                    (* (reg8 *) MotorOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorOut_PRTDSI__CAPS_SEL       (* (reg8 *) MotorOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorOut_PRTDSI__OE_SEL0        (* (reg8 *) MotorOut__PRTDSI__OE_SEL0) 
#define MotorOut_PRTDSI__OE_SEL1        (* (reg8 *) MotorOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorOut_PRTDSI__OUT_SEL0       (* (reg8 *) MotorOut__PRTDSI__OUT_SEL0) 
#define MotorOut_PRTDSI__OUT_SEL1       (* (reg8 *) MotorOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorOut_PRTDSI__SYNC_OUT       (* (reg8 *) MotorOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorOut__SIO_CFG)
    #define MotorOut_SIO_HYST_EN        (* (reg8 *) MotorOut__SIO_HYST_EN)
    #define MotorOut_SIO_REG_HIFREQ     (* (reg8 *) MotorOut__SIO_REG_HIFREQ)
    #define MotorOut_SIO_CFG            (* (reg8 *) MotorOut__SIO_CFG)
    #define MotorOut_SIO_DIFF           (* (reg8 *) MotorOut__SIO_DIFF)
#endif /* (MotorOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorOut__INTSTAT)
    #define MotorOut_INTSTAT            (* (reg8 *) MotorOut__INTSTAT)
    #define MotorOut_SNAP               (* (reg8 *) MotorOut__SNAP)
    
	#define MotorOut_0_INTTYPE_REG 		(* (reg8 *) MotorOut__0__INTTYPE)
#endif /* (MotorOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorOut_H */


/* [] END OF FILE */
