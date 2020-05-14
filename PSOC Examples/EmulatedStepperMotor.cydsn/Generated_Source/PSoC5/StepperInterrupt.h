/*******************************************************************************
* File Name: StepperInterrupt.h
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
#if !defined(CY_ISR_StepperInterrupt_H)
#define CY_ISR_StepperInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StepperInterrupt_Start(void);
void StepperInterrupt_StartEx(cyisraddress address);
void StepperInterrupt_Stop(void);

CY_ISR_PROTO(StepperInterrupt_Interrupt);

void StepperInterrupt_SetVector(cyisraddress address);
cyisraddress StepperInterrupt_GetVector(void);

void StepperInterrupt_SetPriority(uint8 priority);
uint8 StepperInterrupt_GetPriority(void);

void StepperInterrupt_Enable(void);
uint8 StepperInterrupt_GetState(void);
void StepperInterrupt_Disable(void);

void StepperInterrupt_SetPending(void);
void StepperInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StepperInterrupt ISR. */
#define StepperInterrupt_INTC_VECTOR            ((reg32 *) StepperInterrupt__INTC_VECT)

/* Address of the StepperInterrupt ISR priority. */
#define StepperInterrupt_INTC_PRIOR             ((reg8 *) StepperInterrupt__INTC_PRIOR_REG)

/* Priority of the StepperInterrupt interrupt. */
#define StepperInterrupt_INTC_PRIOR_NUMBER      StepperInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StepperInterrupt interrupt. */
#define StepperInterrupt_INTC_SET_EN            ((reg32 *) StepperInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StepperInterrupt interrupt. */
#define StepperInterrupt_INTC_CLR_EN            ((reg32 *) StepperInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StepperInterrupt interrupt state to pending. */
#define StepperInterrupt_INTC_SET_PD            ((reg32 *) StepperInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StepperInterrupt interrupt. */
#define StepperInterrupt_INTC_CLR_PD            ((reg32 *) StepperInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_StepperInterrupt_H */


/* [] END OF FILE */
