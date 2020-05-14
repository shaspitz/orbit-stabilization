/*******************************************************************************
* File Name: MOtorDir.h  
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

#if !defined(CY_PINS_MOtorDir_H) /* Pins MOtorDir_H */
#define CY_PINS_MOtorDir_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOtorDir_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MOtorDir__PORT == 15 && ((MOtorDir__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOtorDir_Write(uint8 value);
void    MOtorDir_SetDriveMode(uint8 mode);
uint8   MOtorDir_ReadDataReg(void);
uint8   MOtorDir_Read(void);
void    MOtorDir_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOtorDir_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOtorDir_SetDriveMode() function.
     *  @{
     */
        #define MOtorDir_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MOtorDir_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MOtorDir_DM_RES_UP          PIN_DM_RES_UP
        #define MOtorDir_DM_RES_DWN         PIN_DM_RES_DWN
        #define MOtorDir_DM_OD_LO           PIN_DM_OD_LO
        #define MOtorDir_DM_OD_HI           PIN_DM_OD_HI
        #define MOtorDir_DM_STRONG          PIN_DM_STRONG
        #define MOtorDir_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOtorDir_MASK               MOtorDir__MASK
#define MOtorDir_SHIFT              MOtorDir__SHIFT
#define MOtorDir_WIDTH              1u

/* Interrupt constants */
#if defined(MOtorDir__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOtorDir_SetInterruptMode() function.
     *  @{
     */
        #define MOtorDir_INTR_NONE      (uint16)(0x0000u)
        #define MOtorDir_INTR_RISING    (uint16)(0x0001u)
        #define MOtorDir_INTR_FALLING   (uint16)(0x0002u)
        #define MOtorDir_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MOtorDir_INTR_MASK      (0x01u) 
#endif /* (MOtorDir__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOtorDir_PS                     (* (reg8 *) MOtorDir__PS)
/* Data Register */
#define MOtorDir_DR                     (* (reg8 *) MOtorDir__DR)
/* Port Number */
#define MOtorDir_PRT_NUM                (* (reg8 *) MOtorDir__PRT) 
/* Connect to Analog Globals */                                                  
#define MOtorDir_AG                     (* (reg8 *) MOtorDir__AG)                       
/* Analog MUX bux enable */
#define MOtorDir_AMUX                   (* (reg8 *) MOtorDir__AMUX) 
/* Bidirectional Enable */                                                        
#define MOtorDir_BIE                    (* (reg8 *) MOtorDir__BIE)
/* Bit-mask for Aliased Register Access */
#define MOtorDir_BIT_MASK               (* (reg8 *) MOtorDir__BIT_MASK)
/* Bypass Enable */
#define MOtorDir_BYP                    (* (reg8 *) MOtorDir__BYP)
/* Port wide control signals */                                                   
#define MOtorDir_CTL                    (* (reg8 *) MOtorDir__CTL)
/* Drive Modes */
#define MOtorDir_DM0                    (* (reg8 *) MOtorDir__DM0) 
#define MOtorDir_DM1                    (* (reg8 *) MOtorDir__DM1)
#define MOtorDir_DM2                    (* (reg8 *) MOtorDir__DM2) 
/* Input Buffer Disable Override */
#define MOtorDir_INP_DIS                (* (reg8 *) MOtorDir__INP_DIS)
/* LCD Common or Segment Drive */
#define MOtorDir_LCD_COM_SEG            (* (reg8 *) MOtorDir__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOtorDir_LCD_EN                 (* (reg8 *) MOtorDir__LCD_EN)
/* Slew Rate Control */
#define MOtorDir_SLW                    (* (reg8 *) MOtorDir__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOtorDir_PRTDSI__CAPS_SEL       (* (reg8 *) MOtorDir__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOtorDir_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOtorDir__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOtorDir_PRTDSI__OE_SEL0        (* (reg8 *) MOtorDir__PRTDSI__OE_SEL0) 
#define MOtorDir_PRTDSI__OE_SEL1        (* (reg8 *) MOtorDir__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOtorDir_PRTDSI__OUT_SEL0       (* (reg8 *) MOtorDir__PRTDSI__OUT_SEL0) 
#define MOtorDir_PRTDSI__OUT_SEL1       (* (reg8 *) MOtorDir__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOtorDir_PRTDSI__SYNC_OUT       (* (reg8 *) MOtorDir__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOtorDir__SIO_CFG)
    #define MOtorDir_SIO_HYST_EN        (* (reg8 *) MOtorDir__SIO_HYST_EN)
    #define MOtorDir_SIO_REG_HIFREQ     (* (reg8 *) MOtorDir__SIO_REG_HIFREQ)
    #define MOtorDir_SIO_CFG            (* (reg8 *) MOtorDir__SIO_CFG)
    #define MOtorDir_SIO_DIFF           (* (reg8 *) MOtorDir__SIO_DIFF)
#endif /* (MOtorDir__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOtorDir__INTSTAT)
    #define MOtorDir_INTSTAT            (* (reg8 *) MOtorDir__INTSTAT)
    #define MOtorDir_SNAP               (* (reg8 *) MOtorDir__SNAP)
    
	#define MOtorDir_0_INTTYPE_REG 		(* (reg8 *) MOtorDir__0__INTTYPE)
#endif /* (MOtorDir__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MOtorDir_H */


/* [] END OF FILE */
