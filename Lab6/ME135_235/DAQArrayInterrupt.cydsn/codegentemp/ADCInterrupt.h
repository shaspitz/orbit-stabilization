/*******************************************************************************
* File Name: ADCInterrupt.h
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
#if !defined(CY_ISR_ADCInterrupt_H)
#define CY_ISR_ADCInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ADCInterrupt_Start(void);
void ADCInterrupt_StartEx(cyisraddress address);
void ADCInterrupt_Stop(void);

CY_ISR_PROTO(ADCInterrupt_Interrupt);

void ADCInterrupt_SetVector(cyisraddress address);
cyisraddress ADCInterrupt_GetVector(void);

void ADCInterrupt_SetPriority(uint8 priority);
uint8 ADCInterrupt_GetPriority(void);

void ADCInterrupt_Enable(void);
uint8 ADCInterrupt_GetState(void);
void ADCInterrupt_Disable(void);

void ADCInterrupt_SetPending(void);
void ADCInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ADCInterrupt ISR. */
#define ADCInterrupt_INTC_VECTOR            ((reg32 *) ADCInterrupt__INTC_VECT)

/* Address of the ADCInterrupt ISR priority. */
#define ADCInterrupt_INTC_PRIOR             ((reg8 *) ADCInterrupt__INTC_PRIOR_REG)

/* Priority of the ADCInterrupt interrupt. */
#define ADCInterrupt_INTC_PRIOR_NUMBER      ADCInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ADCInterrupt interrupt. */
#define ADCInterrupt_INTC_SET_EN            ((reg32 *) ADCInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ADCInterrupt interrupt. */
#define ADCInterrupt_INTC_CLR_EN            ((reg32 *) ADCInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ADCInterrupt interrupt state to pending. */
#define ADCInterrupt_INTC_SET_PD            ((reg32 *) ADCInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ADCInterrupt interrupt. */
#define ADCInterrupt_INTC_CLR_PD            ((reg32 *) ADCInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_ADCInterrupt_H */


/* [] END OF FILE */
