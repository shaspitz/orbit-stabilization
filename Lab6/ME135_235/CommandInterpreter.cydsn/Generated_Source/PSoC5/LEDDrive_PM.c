/*******************************************************************************
* File Name: LEDDrive_PM.c
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

#include "LEDDrive.h"

/* Check for removal by optimization */
#if !defined(LEDDrive_Sync_ctrl_reg__REMOVED)

static LEDDrive_BACKUP_STRUCT  LEDDrive_backup = {0u};

    
/*******************************************************************************
* Function Name: LEDDrive_SaveConfig
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
void LEDDrive_SaveConfig(void) 
{
    LEDDrive_backup.controlState = LEDDrive_Control;
}


/*******************************************************************************
* Function Name: LEDDrive_RestoreConfig
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
void LEDDrive_RestoreConfig(void) 
{
     LEDDrive_Control = LEDDrive_backup.controlState;
}


/*******************************************************************************
* Function Name: LEDDrive_Sleep
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
void LEDDrive_Sleep(void) 
{
    LEDDrive_SaveConfig();
}


/*******************************************************************************
* Function Name: LEDDrive_Wakeup
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
void LEDDrive_Wakeup(void)  
{
    LEDDrive_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
