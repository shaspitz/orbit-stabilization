/*******************************************************************************
* File Name: UltraSonicOut.h  
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

#if !defined(CY_PINS_UltraSonicOut_H) /* Pins UltraSonicOut_H */
#define CY_PINS_UltraSonicOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "UltraSonicOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 UltraSonicOut__PORT == 15 && ((UltraSonicOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    UltraSonicOut_Write(uint8 value);
void    UltraSonicOut_SetDriveMode(uint8 mode);
uint8   UltraSonicOut_ReadDataReg(void);
uint8   UltraSonicOut_Read(void);
void    UltraSonicOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   UltraSonicOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the UltraSonicOut_SetDriveMode() function.
     *  @{
     */
        #define UltraSonicOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define UltraSonicOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define UltraSonicOut_DM_RES_UP          PIN_DM_RES_UP
        #define UltraSonicOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define UltraSonicOut_DM_OD_LO           PIN_DM_OD_LO
        #define UltraSonicOut_DM_OD_HI           PIN_DM_OD_HI
        #define UltraSonicOut_DM_STRONG          PIN_DM_STRONG
        #define UltraSonicOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define UltraSonicOut_MASK               UltraSonicOut__MASK
#define UltraSonicOut_SHIFT              UltraSonicOut__SHIFT
#define UltraSonicOut_WIDTH              1u

/* Interrupt constants */
#if defined(UltraSonicOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UltraSonicOut_SetInterruptMode() function.
     *  @{
     */
        #define UltraSonicOut_INTR_NONE      (uint16)(0x0000u)
        #define UltraSonicOut_INTR_RISING    (uint16)(0x0001u)
        #define UltraSonicOut_INTR_FALLING   (uint16)(0x0002u)
        #define UltraSonicOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define UltraSonicOut_INTR_MASK      (0x01u) 
#endif /* (UltraSonicOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define UltraSonicOut_PS                     (* (reg8 *) UltraSonicOut__PS)
/* Data Register */
#define UltraSonicOut_DR                     (* (reg8 *) UltraSonicOut__DR)
/* Port Number */
#define UltraSonicOut_PRT_NUM                (* (reg8 *) UltraSonicOut__PRT) 
/* Connect to Analog Globals */                                                  
#define UltraSonicOut_AG                     (* (reg8 *) UltraSonicOut__AG)                       
/* Analog MUX bux enable */
#define UltraSonicOut_AMUX                   (* (reg8 *) UltraSonicOut__AMUX) 
/* Bidirectional Enable */                                                        
#define UltraSonicOut_BIE                    (* (reg8 *) UltraSonicOut__BIE)
/* Bit-mask for Aliased Register Access */
#define UltraSonicOut_BIT_MASK               (* (reg8 *) UltraSonicOut__BIT_MASK)
/* Bypass Enable */
#define UltraSonicOut_BYP                    (* (reg8 *) UltraSonicOut__BYP)
/* Port wide control signals */                                                   
#define UltraSonicOut_CTL                    (* (reg8 *) UltraSonicOut__CTL)
/* Drive Modes */
#define UltraSonicOut_DM0                    (* (reg8 *) UltraSonicOut__DM0) 
#define UltraSonicOut_DM1                    (* (reg8 *) UltraSonicOut__DM1)
#define UltraSonicOut_DM2                    (* (reg8 *) UltraSonicOut__DM2) 
/* Input Buffer Disable Override */
#define UltraSonicOut_INP_DIS                (* (reg8 *) UltraSonicOut__INP_DIS)
/* LCD Common or Segment Drive */
#define UltraSonicOut_LCD_COM_SEG            (* (reg8 *) UltraSonicOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define UltraSonicOut_LCD_EN                 (* (reg8 *) UltraSonicOut__LCD_EN)
/* Slew Rate Control */
#define UltraSonicOut_SLW                    (* (reg8 *) UltraSonicOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define UltraSonicOut_PRTDSI__CAPS_SEL       (* (reg8 *) UltraSonicOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define UltraSonicOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) UltraSonicOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define UltraSonicOut_PRTDSI__OE_SEL0        (* (reg8 *) UltraSonicOut__PRTDSI__OE_SEL0) 
#define UltraSonicOut_PRTDSI__OE_SEL1        (* (reg8 *) UltraSonicOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define UltraSonicOut_PRTDSI__OUT_SEL0       (* (reg8 *) UltraSonicOut__PRTDSI__OUT_SEL0) 
#define UltraSonicOut_PRTDSI__OUT_SEL1       (* (reg8 *) UltraSonicOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define UltraSonicOut_PRTDSI__SYNC_OUT       (* (reg8 *) UltraSonicOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(UltraSonicOut__SIO_CFG)
    #define UltraSonicOut_SIO_HYST_EN        (* (reg8 *) UltraSonicOut__SIO_HYST_EN)
    #define UltraSonicOut_SIO_REG_HIFREQ     (* (reg8 *) UltraSonicOut__SIO_REG_HIFREQ)
    #define UltraSonicOut_SIO_CFG            (* (reg8 *) UltraSonicOut__SIO_CFG)
    #define UltraSonicOut_SIO_DIFF           (* (reg8 *) UltraSonicOut__SIO_DIFF)
#endif /* (UltraSonicOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(UltraSonicOut__INTSTAT)
    #define UltraSonicOut_INTSTAT            (* (reg8 *) UltraSonicOut__INTSTAT)
    #define UltraSonicOut_SNAP               (* (reg8 *) UltraSonicOut__SNAP)
    
	#define UltraSonicOut_0_INTTYPE_REG 		(* (reg8 *) UltraSonicOut__0__INTTYPE)
#endif /* (UltraSonicOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_UltraSonicOut_H */


/* [] END OF FILE */
