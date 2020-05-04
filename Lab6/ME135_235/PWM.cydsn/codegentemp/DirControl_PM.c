/*******************************************************************************
* File Name: DirControl_PM.c
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

#include "DirControl.h"

/* Check for removal by optimization */
#if !defined(DirControl_Sync_ctrl_reg__REMOVED)

static DirControl_BACKUP_STRUCT  DirControl_backup = {0u};

    
/*******************************************************************************
* Function Name: DirControl_SaveConfig
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
void DirControl_SaveConfig(void) 
{
    DirControl_backup.controlState = DirControl_Control;
}


/*******************************************************************************
* Function Name: DirControl_RestoreConfig
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
void DirControl_RestoreConfig(void) 
{
     DirControl_Control = DirControl_backup.controlState;
}


/*******************************************************************************
* Function Name: DirControl_Sleep
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
void DirControl_Sleep(void) 
{
    DirControl_SaveConfig();
}


/*******************************************************************************
* Function Name: DirControl_Wakeup
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
void DirControl_Wakeup(void)  
{
    DirControl_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
