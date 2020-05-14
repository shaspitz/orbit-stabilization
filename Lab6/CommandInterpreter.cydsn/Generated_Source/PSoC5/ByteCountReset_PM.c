/*******************************************************************************
* File Name: ByteCountReset_PM.c
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

#include "ByteCountReset.h"

/* Check for removal by optimization */
#if !defined(ByteCountReset_Sync_ctrl_reg__REMOVED)

static ByteCountReset_BACKUP_STRUCT  ByteCountReset_backup = {0u};

    
/*******************************************************************************
* Function Name: ByteCountReset_SaveConfig
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
void ByteCountReset_SaveConfig(void) 
{
    ByteCountReset_backup.controlState = ByteCountReset_Control;
}


/*******************************************************************************
* Function Name: ByteCountReset_RestoreConfig
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
void ByteCountReset_RestoreConfig(void) 
{
     ByteCountReset_Control = ByteCountReset_backup.controlState;
}


/*******************************************************************************
* Function Name: ByteCountReset_Sleep
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
void ByteCountReset_Sleep(void) 
{
    ByteCountReset_SaveConfig();
}


/*******************************************************************************
* Function Name: ByteCountReset_Wakeup
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
void ByteCountReset_Wakeup(void)  
{
    ByteCountReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
