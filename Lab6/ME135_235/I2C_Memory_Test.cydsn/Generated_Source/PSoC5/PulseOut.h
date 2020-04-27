/*******************************************************************************
* File Name: PulseOut.h  
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

#if !defined(CY_PINS_PulseOut_H) /* Pins PulseOut_H */
#define CY_PINS_PulseOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PulseOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PulseOut__PORT == 15 && ((PulseOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PulseOut_Write(uint8 value);
void    PulseOut_SetDriveMode(uint8 mode);
uint8   PulseOut_ReadDataReg(void);
uint8   PulseOut_Read(void);
void    PulseOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   PulseOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PulseOut_SetDriveMode() function.
     *  @{
     */
        #define PulseOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PulseOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PulseOut_DM_RES_UP          PIN_DM_RES_UP
        #define PulseOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define PulseOut_DM_OD_LO           PIN_DM_OD_LO
        #define PulseOut_DM_OD_HI           PIN_DM_OD_HI
        #define PulseOut_DM_STRONG          PIN_DM_STRONG
        #define PulseOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PulseOut_MASK               PulseOut__MASK
#define PulseOut_SHIFT              PulseOut__SHIFT
#define PulseOut_WIDTH              1u

/* Interrupt constants */
#if defined(PulseOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PulseOut_SetInterruptMode() function.
     *  @{
     */
        #define PulseOut_INTR_NONE      (uint16)(0x0000u)
        #define PulseOut_INTR_RISING    (uint16)(0x0001u)
        #define PulseOut_INTR_FALLING   (uint16)(0x0002u)
        #define PulseOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PulseOut_INTR_MASK      (0x01u) 
#endif /* (PulseOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PulseOut_PS                     (* (reg8 *) PulseOut__PS)
/* Data Register */
#define PulseOut_DR                     (* (reg8 *) PulseOut__DR)
/* Port Number */
#define PulseOut_PRT_NUM                (* (reg8 *) PulseOut__PRT) 
/* Connect to Analog Globals */                                                  
#define PulseOut_AG                     (* (reg8 *) PulseOut__AG)                       
/* Analog MUX bux enable */
#define PulseOut_AMUX                   (* (reg8 *) PulseOut__AMUX) 
/* Bidirectional Enable */                                                        
#define PulseOut_BIE                    (* (reg8 *) PulseOut__BIE)
/* Bit-mask for Aliased Register Access */
#define PulseOut_BIT_MASK               (* (reg8 *) PulseOut__BIT_MASK)
/* Bypass Enable */
#define PulseOut_BYP                    (* (reg8 *) PulseOut__BYP)
/* Port wide control signals */                                                   
#define PulseOut_CTL                    (* (reg8 *) PulseOut__CTL)
/* Drive Modes */
#define PulseOut_DM0                    (* (reg8 *) PulseOut__DM0) 
#define PulseOut_DM1                    (* (reg8 *) PulseOut__DM1)
#define PulseOut_DM2                    (* (reg8 *) PulseOut__DM2) 
/* Input Buffer Disable Override */
#define PulseOut_INP_DIS                (* (reg8 *) PulseOut__INP_DIS)
/* LCD Common or Segment Drive */
#define PulseOut_LCD_COM_SEG            (* (reg8 *) PulseOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define PulseOut_LCD_EN                 (* (reg8 *) PulseOut__LCD_EN)
/* Slew Rate Control */
#define PulseOut_SLW                    (* (reg8 *) PulseOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PulseOut_PRTDSI__CAPS_SEL       (* (reg8 *) PulseOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PulseOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PulseOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PulseOut_PRTDSI__OE_SEL0        (* (reg8 *) PulseOut__PRTDSI__OE_SEL0) 
#define PulseOut_PRTDSI__OE_SEL1        (* (reg8 *) PulseOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PulseOut_PRTDSI__OUT_SEL0       (* (reg8 *) PulseOut__PRTDSI__OUT_SEL0) 
#define PulseOut_PRTDSI__OUT_SEL1       (* (reg8 *) PulseOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PulseOut_PRTDSI__SYNC_OUT       (* (reg8 *) PulseOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PulseOut__SIO_CFG)
    #define PulseOut_SIO_HYST_EN        (* (reg8 *) PulseOut__SIO_HYST_EN)
    #define PulseOut_SIO_REG_HIFREQ     (* (reg8 *) PulseOut__SIO_REG_HIFREQ)
    #define PulseOut_SIO_CFG            (* (reg8 *) PulseOut__SIO_CFG)
    #define PulseOut_SIO_DIFF           (* (reg8 *) PulseOut__SIO_DIFF)
#endif /* (PulseOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(PulseOut__INTSTAT)
    #define PulseOut_INTSTAT            (* (reg8 *) PulseOut__INTSTAT)
    #define PulseOut_SNAP               (* (reg8 *) PulseOut__SNAP)
    
	#define PulseOut_0_INTTYPE_REG 		(* (reg8 *) PulseOut__0__INTTYPE)
#endif /* (PulseOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PulseOut_H */


/* [] END OF FILE */
