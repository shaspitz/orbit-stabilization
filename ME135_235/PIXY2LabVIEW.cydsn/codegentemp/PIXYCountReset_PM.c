/*******************************************************************************
* File Name: PIXYCountReset_PM.c
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

#include "PIXYCountReset.h"

/* Check for removal by optimization */
#if !defined(PIXYCountReset_Sync_ctrl_reg__REMOVED)

static PIXYCountReset_BACKUP_STRUCT  PIXYCountReset_backup = {0u};

    
/*******************************************************************************
* Function Name: PIXYCountReset_SaveConfig
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
void PIXYCountReset_SaveConfig(void) 
{
    PIXYCountReset_backup.controlState = PIXYCountReset_Control;
}


/*******************************************************************************
* Function Name: PIXYCountReset_RestoreConfig
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
void PIXYCountReset_RestoreConfig(void) 
{
     PIXYCountReset_Control = PIXYCountReset_backup.controlState;
}


/*******************************************************************************
* Function Name: PIXYCountReset_Sleep
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
void PIXYCountReset_Sleep(void) 
{
    PIXYCountReset_SaveConfig();
}


/*******************************************************************************
* Function Name: PIXYCountReset_Wakeup
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
void PIXYCountReset_Wakeup(void)  
{
    PIXYCountReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
