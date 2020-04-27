/*******************************************************************************
* File Name: StepCountReset_PM.c
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

#include "StepCountReset.h"

/* Check for removal by optimization */
#if !defined(StepCountReset_Sync_ctrl_reg__REMOVED)

static StepCountReset_BACKUP_STRUCT  StepCountReset_backup = {0u};

    
/*******************************************************************************
* Function Name: StepCountReset_SaveConfig
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
void StepCountReset_SaveConfig(void) 
{
    StepCountReset_backup.controlState = StepCountReset_Control;
}


/*******************************************************************************
* Function Name: StepCountReset_RestoreConfig
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
void StepCountReset_RestoreConfig(void) 
{
     StepCountReset_Control = StepCountReset_backup.controlState;
}


/*******************************************************************************
* Function Name: StepCountReset_Sleep
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
void StepCountReset_Sleep(void) 
{
    StepCountReset_SaveConfig();
}


/*******************************************************************************
* Function Name: StepCountReset_Wakeup
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
void StepCountReset_Wakeup(void)  
{
    StepCountReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
