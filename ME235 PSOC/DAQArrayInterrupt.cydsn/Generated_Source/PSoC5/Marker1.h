/*******************************************************************************
* File Name: Marker1.h  
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

#if !defined(CY_PINS_Marker1_H) /* Pins Marker1_H */
#define CY_PINS_Marker1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Marker1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Marker1__PORT == 15 && ((Marker1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Marker1_Write(uint8 value);
void    Marker1_SetDriveMode(uint8 mode);
uint8   Marker1_ReadDataReg(void);
uint8   Marker1_Read(void);
void    Marker1_SetInterruptMode(uint16 position, uint16 mode);
uint8   Marker1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Marker1_SetDriveMode() function.
     *  @{
     */
        #define Marker1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Marker1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Marker1_DM_RES_UP          PIN_DM_RES_UP
        #define Marker1_DM_RES_DWN         PIN_DM_RES_DWN
        #define Marker1_DM_OD_LO           PIN_DM_OD_LO
        #define Marker1_DM_OD_HI           PIN_DM_OD_HI
        #define Marker1_DM_STRONG          PIN_DM_STRONG
        #define Marker1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Marker1_MASK               Marker1__MASK
#define Marker1_SHIFT              Marker1__SHIFT
#define Marker1_WIDTH              1u

/* Interrupt constants */
#if defined(Marker1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Marker1_SetInterruptMode() function.
     *  @{
     */
        #define Marker1_INTR_NONE      (uint16)(0x0000u)
        #define Marker1_INTR_RISING    (uint16)(0x0001u)
        #define Marker1_INTR_FALLING   (uint16)(0x0002u)
        #define Marker1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Marker1_INTR_MASK      (0x01u) 
#endif /* (Marker1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Marker1_PS                     (* (reg8 *) Marker1__PS)
/* Data Register */
#define Marker1_DR                     (* (reg8 *) Marker1__DR)
/* Port Number */
#define Marker1_PRT_NUM                (* (reg8 *) Marker1__PRT) 
/* Connect to Analog Globals */                                                  
#define Marker1_AG                     (* (reg8 *) Marker1__AG)                       
/* Analog MUX bux enable */
#define Marker1_AMUX                   (* (reg8 *) Marker1__AMUX) 
/* Bidirectional Enable */                                                        
#define Marker1_BIE                    (* (reg8 *) Marker1__BIE)
/* Bit-mask for Aliased Register Access */
#define Marker1_BIT_MASK               (* (reg8 *) Marker1__BIT_MASK)
/* Bypass Enable */
#define Marker1_BYP                    (* (reg8 *) Marker1__BYP)
/* Port wide control signals */                                                   
#define Marker1_CTL                    (* (reg8 *) Marker1__CTL)
/* Drive Modes */
#define Marker1_DM0                    (* (reg8 *) Marker1__DM0) 
#define Marker1_DM1                    (* (reg8 *) Marker1__DM1)
#define Marker1_DM2                    (* (reg8 *) Marker1__DM2) 
/* Input Buffer Disable Override */
#define Marker1_INP_DIS                (* (reg8 *) Marker1__INP_DIS)
/* LCD Common or Segment Drive */
#define Marker1_LCD_COM_SEG            (* (reg8 *) Marker1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Marker1_LCD_EN                 (* (reg8 *) Marker1__LCD_EN)
/* Slew Rate Control */
#define Marker1_SLW                    (* (reg8 *) Marker1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Marker1_PRTDSI__CAPS_SEL       (* (reg8 *) Marker1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Marker1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Marker1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Marker1_PRTDSI__OE_SEL0        (* (reg8 *) Marker1__PRTDSI__OE_SEL0) 
#define Marker1_PRTDSI__OE_SEL1        (* (reg8 *) Marker1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Marker1_PRTDSI__OUT_SEL0       (* (reg8 *) Marker1__PRTDSI__OUT_SEL0) 
#define Marker1_PRTDSI__OUT_SEL1       (* (reg8 *) Marker1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Marker1_PRTDSI__SYNC_OUT       (* (reg8 *) Marker1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Marker1__SIO_CFG)
    #define Marker1_SIO_HYST_EN        (* (reg8 *) Marker1__SIO_HYST_EN)
    #define Marker1_SIO_REG_HIFREQ     (* (reg8 *) Marker1__SIO_REG_HIFREQ)
    #define Marker1_SIO_CFG            (* (reg8 *) Marker1__SIO_CFG)
    #define Marker1_SIO_DIFF           (* (reg8 *) Marker1__SIO_DIFF)
#endif /* (Marker1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Marker1__INTSTAT)
    #define Marker1_INTSTAT            (* (reg8 *) Marker1__INTSTAT)
    #define Marker1_SNAP               (* (reg8 *) Marker1__SNAP)
    
	#define Marker1_0_INTTYPE_REG 		(* (reg8 *) Marker1__0__INTTYPE)
#endif /* (Marker1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Marker1_H */


/* [] END OF FILE */
