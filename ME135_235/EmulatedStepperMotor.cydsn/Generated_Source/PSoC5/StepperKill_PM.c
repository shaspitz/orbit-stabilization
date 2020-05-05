/*******************************************************************************
* File Name: StepperKill_PM.c
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

#include "StepperKill.h"

/* Check for removal by optimization */
#if !defined(StepperKill_Sync_ctrl_reg__REMOVED)

static StepperKill_BACKUP_STRUCT  StepperKill_backup = {0u};

    
/*******************************************************************************
* Function Name: StepperKill_SaveConfig
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
void StepperKill_SaveConfig(void) 
{
    StepperKill_backup.controlState = StepperKill_Control;
}


/*******************************************************************************
* Function Name: StepperKill_RestoreConfig
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
void StepperKill_RestoreConfig(void) 
{
     StepperKill_Control = StepperKill_backup.controlState;
}


/*******************************************************************************
* Function Name: StepperKill_Sleep
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
void StepperKill_Sleep(void) 
{
    StepperKill_SaveConfig();
}


/*******************************************************************************
* Function Name: StepperKill_Wakeup
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
void StepperKill_Wakeup(void)  
{
    StepperKill_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
