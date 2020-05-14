/*******************************************************************************
* File Name: UARTReset_PM.c
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

#include "UARTReset.h"

/* Check for removal by optimization */
#if !defined(UARTReset_Sync_ctrl_reg__REMOVED)

static UARTReset_BACKUP_STRUCT  UARTReset_backup = {0u};

    
/*******************************************************************************
* Function Name: UARTReset_SaveConfig
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
void UARTReset_SaveConfig(void) 
{
    UARTReset_backup.controlState = UARTReset_Control;
}


/*******************************************************************************
* Function Name: UARTReset_RestoreConfig
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
void UARTReset_RestoreConfig(void) 
{
     UARTReset_Control = UARTReset_backup.controlState;
}


/*******************************************************************************
* Function Name: UARTReset_Sleep
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
void UARTReset_Sleep(void) 
{
    UARTReset_SaveConfig();
}


/*******************************************************************************
* Function Name: UARTReset_Wakeup
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
void UARTReset_Wakeup(void)  
{
    UARTReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
