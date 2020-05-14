/*******************************************************************************
* File Name: PWMInterrupt.h
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
#if !defined(CY_ISR_PWMInterrupt_H)
#define CY_ISR_PWMInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PWMInterrupt_Start(void);
void PWMInterrupt_StartEx(cyisraddress address);
void PWMInterrupt_Stop(void);

CY_ISR_PROTO(PWMInterrupt_Interrupt);

void PWMInterrupt_SetVector(cyisraddress address);
cyisraddress PWMInterrupt_GetVector(void);

void PWMInterrupt_SetPriority(uint8 priority);
uint8 PWMInterrupt_GetPriority(void);

void PWMInterrupt_Enable(void);
uint8 PWMInterrupt_GetState(void);
void PWMInterrupt_Disable(void);

void PWMInterrupt_SetPending(void);
void PWMInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PWMInterrupt ISR. */
#define PWMInterrupt_INTC_VECTOR            ((reg32 *) PWMInterrupt__INTC_VECT)

/* Address of the PWMInterrupt ISR priority. */
#define PWMInterrupt_INTC_PRIOR             ((reg8 *) PWMInterrupt__INTC_PRIOR_REG)

/* Priority of the PWMInterrupt interrupt. */
#define PWMInterrupt_INTC_PRIOR_NUMBER      PWMInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PWMInterrupt interrupt. */
#define PWMInterrupt_INTC_SET_EN            ((reg32 *) PWMInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PWMInterrupt interrupt. */
#define PWMInterrupt_INTC_CLR_EN            ((reg32 *) PWMInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PWMInterrupt interrupt state to pending. */
#define PWMInterrupt_INTC_SET_PD            ((reg32 *) PWMInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PWMInterrupt interrupt. */
#define PWMInterrupt_INTC_CLR_PD            ((reg32 *) PWMInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_PWMInterrupt_H */


/* [] END OF FILE */
