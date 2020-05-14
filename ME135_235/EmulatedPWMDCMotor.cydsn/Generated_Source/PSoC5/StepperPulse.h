/*******************************************************************************
* File Name: StepperPulse.h
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
#if !defined(CY_ISR_StepperPulse_H)
#define CY_ISR_StepperPulse_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StepperPulse_Start(void);
void StepperPulse_StartEx(cyisraddress address);
void StepperPulse_Stop(void);

CY_ISR_PROTO(StepperPulse_Interrupt);

void StepperPulse_SetVector(cyisraddress address);
cyisraddress StepperPulse_GetVector(void);

void StepperPulse_SetPriority(uint8 priority);
uint8 StepperPulse_GetPriority(void);

void StepperPulse_Enable(void);
uint8 StepperPulse_GetState(void);
void StepperPulse_Disable(void);

void StepperPulse_SetPending(void);
void StepperPulse_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StepperPulse ISR. */
#define StepperPulse_INTC_VECTOR            ((reg32 *) StepperPulse__INTC_VECT)

/* Address of the StepperPulse ISR priority. */
#define StepperPulse_INTC_PRIOR             ((reg8 *) StepperPulse__INTC_PRIOR_REG)

/* Priority of the StepperPulse interrupt. */
#define StepperPulse_INTC_PRIOR_NUMBER      StepperPulse__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StepperPulse interrupt. */
#define StepperPulse_INTC_SET_EN            ((reg32 *) StepperPulse__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StepperPulse interrupt. */
#define StepperPulse_INTC_CLR_EN            ((reg32 *) StepperPulse__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StepperPulse interrupt state to pending. */
#define StepperPulse_INTC_SET_PD            ((reg32 *) StepperPulse__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StepperPulse interrupt. */
#define StepperPulse_INTC_CLR_PD            ((reg32 *) StepperPulse__INTC_CLR_PD_REG)


#endif /* CY_ISR_StepperPulse_H */


/* [] END OF FILE */
