/*******************************************************************************
* File Name: MoorPWM.h  
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

#if !defined(CY_PINS_MoorPWM_H) /* Pins MoorPWM_H */
#define CY_PINS_MoorPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MoorPWM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MoorPWM__PORT == 15 && ((MoorPWM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MoorPWM_Write(uint8 value);
void    MoorPWM_SetDriveMode(uint8 mode);
uint8   MoorPWM_ReadDataReg(void);
uint8   MoorPWM_Read(void);
void    MoorPWM_SetInterruptMode(uint16 position, uint16 mode);
uint8   MoorPWM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MoorPWM_SetDriveMode() function.
     *  @{
     */
        #define MoorPWM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MoorPWM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MoorPWM_DM_RES_UP          PIN_DM_RES_UP
        #define MoorPWM_DM_RES_DWN         PIN_DM_RES_DWN
        #define MoorPWM_DM_OD_LO           PIN_DM_OD_LO
        #define MoorPWM_DM_OD_HI           PIN_DM_OD_HI
        #define MoorPWM_DM_STRONG          PIN_DM_STRONG
        #define MoorPWM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MoorPWM_MASK               MoorPWM__MASK
#define MoorPWM_SHIFT              MoorPWM__SHIFT
#define MoorPWM_WIDTH              1u

/* Interrupt constants */
#if defined(MoorPWM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MoorPWM_SetInterruptMode() function.
     *  @{
     */
        #define MoorPWM_INTR_NONE      (uint16)(0x0000u)
        #define MoorPWM_INTR_RISING    (uint16)(0x0001u)
        #define MoorPWM_INTR_FALLING   (uint16)(0x0002u)
        #define MoorPWM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MoorPWM_INTR_MASK      (0x01u) 
#endif /* (MoorPWM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MoorPWM_PS                     (* (reg8 *) MoorPWM__PS)
/* Data Register */
#define MoorPWM_DR                     (* (reg8 *) MoorPWM__DR)
/* Port Number */
#define MoorPWM_PRT_NUM                (* (reg8 *) MoorPWM__PRT) 
/* Connect to Analog Globals */                                                  
#define MoorPWM_AG                     (* (reg8 *) MoorPWM__AG)                       
/* Analog MUX bux enable */
#define MoorPWM_AMUX                   (* (reg8 *) MoorPWM__AMUX) 
/* Bidirectional Enable */                                                        
#define MoorPWM_BIE                    (* (reg8 *) MoorPWM__BIE)
/* Bit-mask for Aliased Register Access */
#define MoorPWM_BIT_MASK               (* (reg8 *) MoorPWM__BIT_MASK)
/* Bypass Enable */
#define MoorPWM_BYP                    (* (reg8 *) MoorPWM__BYP)
/* Port wide control signals */                                                   
#define MoorPWM_CTL                    (* (reg8 *) MoorPWM__CTL)
/* Drive Modes */
#define MoorPWM_DM0                    (* (reg8 *) MoorPWM__DM0) 
#define MoorPWM_DM1                    (* (reg8 *) MoorPWM__DM1)
#define MoorPWM_DM2                    (* (reg8 *) MoorPWM__DM2) 
/* Input Buffer Disable Override */
#define MoorPWM_INP_DIS                (* (reg8 *) MoorPWM__INP_DIS)
/* LCD Common or Segment Drive */
#define MoorPWM_LCD_COM_SEG            (* (reg8 *) MoorPWM__LCD_COM_SEG)
/* Enable Segment LCD */
#define MoorPWM_LCD_EN                 (* (reg8 *) MoorPWM__LCD_EN)
/* Slew Rate Control */
#define MoorPWM_SLW                    (* (reg8 *) MoorPWM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MoorPWM_PRTDSI__CAPS_SEL       (* (reg8 *) MoorPWM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MoorPWM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MoorPWM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MoorPWM_PRTDSI__OE_SEL0        (* (reg8 *) MoorPWM__PRTDSI__OE_SEL0) 
#define MoorPWM_PRTDSI__OE_SEL1        (* (reg8 *) MoorPWM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MoorPWM_PRTDSI__OUT_SEL0       (* (reg8 *) MoorPWM__PRTDSI__OUT_SEL0) 
#define MoorPWM_PRTDSI__OUT_SEL1       (* (reg8 *) MoorPWM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MoorPWM_PRTDSI__SYNC_OUT       (* (reg8 *) MoorPWM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MoorPWM__SIO_CFG)
    #define MoorPWM_SIO_HYST_EN        (* (reg8 *) MoorPWM__SIO_HYST_EN)
    #define MoorPWM_SIO_REG_HIFREQ     (* (reg8 *) MoorPWM__SIO_REG_HIFREQ)
    #define MoorPWM_SIO_CFG            (* (reg8 *) MoorPWM__SIO_CFG)
    #define MoorPWM_SIO_DIFF           (* (reg8 *) MoorPWM__SIO_DIFF)
#endif /* (MoorPWM__SIO_CFG) */

/* Interrupt Registers */
#if defined(MoorPWM__INTSTAT)
    #define MoorPWM_INTSTAT            (* (reg8 *) MoorPWM__INTSTAT)
    #define MoorPWM_SNAP               (* (reg8 *) MoorPWM__SNAP)
    
	#define MoorPWM_0_INTTYPE_REG 		(* (reg8 *) MoorPWM__0__INTTYPE)
#endif /* (MoorPWM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MoorPWM_H */


/* [] END OF FILE */
