/*******************************************************************************
* File Name: DoorSensorIn.h  
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

#if !defined(CY_PINS_DoorSensorIn_H) /* Pins DoorSensorIn_H */
#define CY_PINS_DoorSensorIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DoorSensorIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DoorSensorIn__PORT == 15 && ((DoorSensorIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DoorSensorIn_Write(uint8 value);
void    DoorSensorIn_SetDriveMode(uint8 mode);
uint8   DoorSensorIn_ReadDataReg(void);
uint8   DoorSensorIn_Read(void);
void    DoorSensorIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorSensorIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DoorSensorIn_SetDriveMode() function.
     *  @{
     */
        #define DoorSensorIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DoorSensorIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DoorSensorIn_DM_RES_UP          PIN_DM_RES_UP
        #define DoorSensorIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define DoorSensorIn_DM_OD_LO           PIN_DM_OD_LO
        #define DoorSensorIn_DM_OD_HI           PIN_DM_OD_HI
        #define DoorSensorIn_DM_STRONG          PIN_DM_STRONG
        #define DoorSensorIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DoorSensorIn_MASK               DoorSensorIn__MASK
#define DoorSensorIn_SHIFT              DoorSensorIn__SHIFT
#define DoorSensorIn_WIDTH              1u

/* Interrupt constants */
#if defined(DoorSensorIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorSensorIn_SetInterruptMode() function.
     *  @{
     */
        #define DoorSensorIn_INTR_NONE      (uint16)(0x0000u)
        #define DoorSensorIn_INTR_RISING    (uint16)(0x0001u)
        #define DoorSensorIn_INTR_FALLING   (uint16)(0x0002u)
        #define DoorSensorIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DoorSensorIn_INTR_MASK      (0x01u) 
#endif /* (DoorSensorIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DoorSensorIn_PS                     (* (reg8 *) DoorSensorIn__PS)
/* Data Register */
#define DoorSensorIn_DR                     (* (reg8 *) DoorSensorIn__DR)
/* Port Number */
#define DoorSensorIn_PRT_NUM                (* (reg8 *) DoorSensorIn__PRT) 
/* Connect to Analog Globals */                                                  
#define DoorSensorIn_AG                     (* (reg8 *) DoorSensorIn__AG)                       
/* Analog MUX bux enable */
#define DoorSensorIn_AMUX                   (* (reg8 *) DoorSensorIn__AMUX) 
/* Bidirectional Enable */                                                        
#define DoorSensorIn_BIE                    (* (reg8 *) DoorSensorIn__BIE)
/* Bit-mask for Aliased Register Access */
#define DoorSensorIn_BIT_MASK               (* (reg8 *) DoorSensorIn__BIT_MASK)
/* Bypass Enable */
#define DoorSensorIn_BYP                    (* (reg8 *) DoorSensorIn__BYP)
/* Port wide control signals */                                                   
#define DoorSensorIn_CTL                    (* (reg8 *) DoorSensorIn__CTL)
/* Drive Modes */
#define DoorSensorIn_DM0                    (* (reg8 *) DoorSensorIn__DM0) 
#define DoorSensorIn_DM1                    (* (reg8 *) DoorSensorIn__DM1)
#define DoorSensorIn_DM2                    (* (reg8 *) DoorSensorIn__DM2) 
/* Input Buffer Disable Override */
#define DoorSensorIn_INP_DIS                (* (reg8 *) DoorSensorIn__INP_DIS)
/* LCD Common or Segment Drive */
#define DoorSensorIn_LCD_COM_SEG            (* (reg8 *) DoorSensorIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define DoorSensorIn_LCD_EN                 (* (reg8 *) DoorSensorIn__LCD_EN)
/* Slew Rate Control */
#define DoorSensorIn_SLW                    (* (reg8 *) DoorSensorIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DoorSensorIn_PRTDSI__CAPS_SEL       (* (reg8 *) DoorSensorIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DoorSensorIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DoorSensorIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DoorSensorIn_PRTDSI__OE_SEL0        (* (reg8 *) DoorSensorIn__PRTDSI__OE_SEL0) 
#define DoorSensorIn_PRTDSI__OE_SEL1        (* (reg8 *) DoorSensorIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DoorSensorIn_PRTDSI__OUT_SEL0       (* (reg8 *) DoorSensorIn__PRTDSI__OUT_SEL0) 
#define DoorSensorIn_PRTDSI__OUT_SEL1       (* (reg8 *) DoorSensorIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DoorSensorIn_PRTDSI__SYNC_OUT       (* (reg8 *) DoorSensorIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DoorSensorIn__SIO_CFG)
    #define DoorSensorIn_SIO_HYST_EN        (* (reg8 *) DoorSensorIn__SIO_HYST_EN)
    #define DoorSensorIn_SIO_REG_HIFREQ     (* (reg8 *) DoorSensorIn__SIO_REG_HIFREQ)
    #define DoorSensorIn_SIO_CFG            (* (reg8 *) DoorSensorIn__SIO_CFG)
    #define DoorSensorIn_SIO_DIFF           (* (reg8 *) DoorSensorIn__SIO_DIFF)
#endif /* (DoorSensorIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(DoorSensorIn__INTSTAT)
    #define DoorSensorIn_INTSTAT            (* (reg8 *) DoorSensorIn__INTSTAT)
    #define DoorSensorIn_SNAP               (* (reg8 *) DoorSensorIn__SNAP)
    
	#define DoorSensorIn_0_INTTYPE_REG 		(* (reg8 *) DoorSensorIn__0__INTTYPE)
#endif /* (DoorSensorIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DoorSensorIn_H */


/* [] END OF FILE */
