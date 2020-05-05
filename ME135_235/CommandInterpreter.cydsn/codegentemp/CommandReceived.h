/*******************************************************************************
* File Name: CommandReceived.h
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
#if !defined(CY_ISR_CommandReceived_H)
#define CY_ISR_CommandReceived_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CommandReceived_Start(void);
void CommandReceived_StartEx(cyisraddress address);
void CommandReceived_Stop(void);

CY_ISR_PROTO(CommandReceived_Interrupt);

void CommandReceived_SetVector(cyisraddress address);
cyisraddress CommandReceived_GetVector(void);

void CommandReceived_SetPriority(uint8 priority);
uint8 CommandReceived_GetPriority(void);

void CommandReceived_Enable(void);
uint8 CommandReceived_GetState(void);
void CommandReceived_Disable(void);

void CommandReceived_SetPending(void);
void CommandReceived_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CommandReceived ISR. */
#define CommandReceived_INTC_VECTOR            ((reg32 *) CommandReceived__INTC_VECT)

/* Address of the CommandReceived ISR priority. */
#define CommandReceived_INTC_PRIOR             ((reg8 *) CommandReceived__INTC_PRIOR_REG)

/* Priority of the CommandReceived interrupt. */
#define CommandReceived_INTC_PRIOR_NUMBER      CommandReceived__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CommandReceived interrupt. */
#define CommandReceived_INTC_SET_EN            ((reg32 *) CommandReceived__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CommandReceived interrupt. */
#define CommandReceived_INTC_CLR_EN            ((reg32 *) CommandReceived__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CommandReceived interrupt state to pending. */
#define CommandReceived_INTC_SET_PD            ((reg32 *) CommandReceived__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CommandReceived interrupt. */
#define CommandReceived_INTC_CLR_PD            ((reg32 *) CommandReceived__INTC_CLR_PD_REG)


#endif /* CY_ISR_CommandReceived_H */


/* [] END OF FILE */
