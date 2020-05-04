/*******************************************************************************
* File Name: StepperDirection_PM.c
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

#include "StepperDirection.h"

/* Check for removal by optimization */
#if !defined(StepperDirection_Sync_ctrl_reg__REMOVED)

static StepperDirection_BACKUP_STRUCT  StepperDirection_backup = {0u};

    
/*******************************************************************************
* Function Name: StepperDirection_SaveConfig
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
void StepperDirection_SaveConfig(void) 
{
    StepperDirection_backup.controlState = StepperDirection_Control;
}


/*******************************************************************************
* Function Name: StepperDirection_RestoreConfig
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
void StepperDirection_RestoreConfig(void) 
{
     StepperDirection_Control = StepperDirection_backup.controlState;
}


/*******************************************************************************
* Function Name: StepperDirection_Sleep
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
void StepperDirection_Sleep(void) 
{
    StepperDirection_SaveConfig();
}


/*******************************************************************************
* Function Name: StepperDirection_Wakeup
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
void StepperDirection_Wakeup(void)  
{
    StepperDirection_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
