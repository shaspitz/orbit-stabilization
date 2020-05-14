/*******************************************************************************
* File Name: PulseTrigger_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PulseTrigger.h"

/* Check for removal by optimization */
#if !defined(PulseTrigger_Sync_ctrl_reg__REMOVED)

static PulseTrigger_BACKUP_STRUCT  PulseTrigger_backup = {0u};

    
/*******************************************************************************
* Function Name: PulseTrigger_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PulseTrigger_SaveConfig(void) 
{
    PulseTrigger_backup.controlState = PulseTrigger_Control;
}


/*******************************************************************************
* Function Name: PulseTrigger_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void PulseTrigger_RestoreConfig(void) 
{
     PulseTrigger_Control = PulseTrigger_backup.controlState;
}


/*******************************************************************************
* Function Name: PulseTrigger_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PulseTrigger_Sleep(void) 
{
    PulseTrigger_SaveConfig();
}


/*******************************************************************************
* Function Name: PulseTrigger_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PulseTrigger_Wakeup(void)  
{
    PulseTrigger_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
