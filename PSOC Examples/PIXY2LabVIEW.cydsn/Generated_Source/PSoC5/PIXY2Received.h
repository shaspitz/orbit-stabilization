/*******************************************************************************
* File Name: PIXY2Received.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_PIXY2Received_H)
#define CY_ISR_PIXY2Received_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PIXY2Received_Start(void);
void PIXY2Received_StartEx(cyisraddress address);
void PIXY2Received_Stop(void);

CY_ISR_PROTO(PIXY2Received_Interrupt);

void PIXY2Received_SetVector(cyisraddress address);
cyisraddress PIXY2Received_GetVector(void);

void PIXY2Received_SetPriority(uint8 priority);
uint8 PIXY2Received_GetPriority(void);

void PIXY2Received_Enable(void);
uint8 PIXY2Received_GetState(void);
void PIXY2Received_Disable(void);

void PIXY2Received_SetPending(void);
void PIXY2Received_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PIXY2Received ISR. */
#define PIXY2Received_INTC_VECTOR            ((reg32 *) PIXY2Received__INTC_VECT)

/* Address of the PIXY2Received ISR priority. */
#define PIXY2Received_INTC_PRIOR             ((reg8 *) PIXY2Received__INTC_PRIOR_REG)

/* Priority of the PIXY2Received interrupt. */
#define PIXY2Received_INTC_PRIOR_NUMBER      PIXY2Received__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PIXY2Received interrupt. */
#define PIXY2Received_INTC_SET_EN            ((reg32 *) PIXY2Received__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PIXY2Received interrupt. */
#define PIXY2Received_INTC_CLR_EN            ((reg32 *) PIXY2Received__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PIXY2Received interrupt state to pending. */
#define PIXY2Received_INTC_SET_PD            ((reg32 *) PIXY2Received__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PIXY2Received interrupt. */
#define PIXY2Received_INTC_CLR_PD            ((reg32 *) PIXY2Received__INTC_CLR_PD_REG)


#endif /* CY_ISR_PIXY2Received_H */


/* [] END OF FILE */
