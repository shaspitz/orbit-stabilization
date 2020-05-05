/*******************************************************************************
* File Name: TimerInterrupt.h
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
#if !defined(CY_ISR_TimerInterrupt_H)
#define CY_ISR_TimerInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TimerInterrupt_Start(void);
void TimerInterrupt_StartEx(cyisraddress address);
void TimerInterrupt_Stop(void);

CY_ISR_PROTO(TimerInterrupt_Interrupt);

void TimerInterrupt_SetVector(cyisraddress address);
cyisraddress TimerInterrupt_GetVector(void);

void TimerInterrupt_SetPriority(uint8 priority);
uint8 TimerInterrupt_GetPriority(void);

void TimerInterrupt_Enable(void);
uint8 TimerInterrupt_GetState(void);
void TimerInterrupt_Disable(void);

void TimerInterrupt_SetPending(void);
void TimerInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TimerInterrupt ISR. */
#define TimerInterrupt_INTC_VECTOR            ((reg32 *) TimerInterrupt__INTC_VECT)

/* Address of the TimerInterrupt ISR priority. */
#define TimerInterrupt_INTC_PRIOR             ((reg8 *) TimerInterrupt__INTC_PRIOR_REG)

/* Priority of the TimerInterrupt interrupt. */
#define TimerInterrupt_INTC_PRIOR_NUMBER      TimerInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TimerInterrupt interrupt. */
#define TimerInterrupt_INTC_SET_EN            ((reg32 *) TimerInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TimerInterrupt interrupt. */
#define TimerInterrupt_INTC_CLR_EN            ((reg32 *) TimerInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TimerInterrupt interrupt state to pending. */
#define TimerInterrupt_INTC_SET_PD            ((reg32 *) TimerInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TimerInterrupt interrupt. */
#define TimerInterrupt_INTC_CLR_PD            ((reg32 *) TimerInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_TimerInterrupt_H */


/* [] END OF FILE */
