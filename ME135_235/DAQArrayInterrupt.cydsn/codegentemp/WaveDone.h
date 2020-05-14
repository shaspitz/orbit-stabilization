/*******************************************************************************
* File Name: WaveDone.h
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
#if !defined(CY_ISR_WaveDone_H)
#define CY_ISR_WaveDone_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void WaveDone_Start(void);
void WaveDone_StartEx(cyisraddress address);
void WaveDone_Stop(void);

CY_ISR_PROTO(WaveDone_Interrupt);

void WaveDone_SetVector(cyisraddress address);
cyisraddress WaveDone_GetVector(void);

void WaveDone_SetPriority(uint8 priority);
uint8 WaveDone_GetPriority(void);

void WaveDone_Enable(void);
uint8 WaveDone_GetState(void);
void WaveDone_Disable(void);

void WaveDone_SetPending(void);
void WaveDone_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the WaveDone ISR. */
#define WaveDone_INTC_VECTOR            ((reg32 *) WaveDone__INTC_VECT)

/* Address of the WaveDone ISR priority. */
#define WaveDone_INTC_PRIOR             ((reg8 *) WaveDone__INTC_PRIOR_REG)

/* Priority of the WaveDone interrupt. */
#define WaveDone_INTC_PRIOR_NUMBER      WaveDone__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable WaveDone interrupt. */
#define WaveDone_INTC_SET_EN            ((reg32 *) WaveDone__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the WaveDone interrupt. */
#define WaveDone_INTC_CLR_EN            ((reg32 *) WaveDone__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the WaveDone interrupt state to pending. */
#define WaveDone_INTC_SET_PD            ((reg32 *) WaveDone__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the WaveDone interrupt. */
#define WaveDone_INTC_CLR_PD            ((reg32 *) WaveDone__INTC_CLR_PD_REG)


#endif /* CY_ISR_WaveDone_H */


/* [] END OF FILE */
