/*******************************************************************************
* File Name: SampleInterrupt.h
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
#if !defined(CY_ISR_SampleInterrupt_H)
#define CY_ISR_SampleInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SampleInterrupt_Start(void);
void SampleInterrupt_StartEx(cyisraddress address);
void SampleInterrupt_Stop(void);

CY_ISR_PROTO(SampleInterrupt_Interrupt);

void SampleInterrupt_SetVector(cyisraddress address);
cyisraddress SampleInterrupt_GetVector(void);

void SampleInterrupt_SetPriority(uint8 priority);
uint8 SampleInterrupt_GetPriority(void);

void SampleInterrupt_Enable(void);
uint8 SampleInterrupt_GetState(void);
void SampleInterrupt_Disable(void);

void SampleInterrupt_SetPending(void);
void SampleInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SampleInterrupt ISR. */
#define SampleInterrupt_INTC_VECTOR            ((reg32 *) SampleInterrupt__INTC_VECT)

/* Address of the SampleInterrupt ISR priority. */
#define SampleInterrupt_INTC_PRIOR             ((reg8 *) SampleInterrupt__INTC_PRIOR_REG)

/* Priority of the SampleInterrupt interrupt. */
#define SampleInterrupt_INTC_PRIOR_NUMBER      SampleInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SampleInterrupt interrupt. */
#define SampleInterrupt_INTC_SET_EN            ((reg32 *) SampleInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SampleInterrupt interrupt. */
#define SampleInterrupt_INTC_CLR_EN            ((reg32 *) SampleInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SampleInterrupt interrupt state to pending. */
#define SampleInterrupt_INTC_SET_PD            ((reg32 *) SampleInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SampleInterrupt interrupt. */
#define SampleInterrupt_INTC_CLR_PD            ((reg32 *) SampleInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_SampleInterrupt_H */


/* [] END OF FILE */
