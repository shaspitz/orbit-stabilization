/*******************************************************************************
* File Name: LED_Drive_PM.c
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

#include "LED_Drive.h"

/* Check for removal by optimization */
#if !defined(LED_Drive_Sync_ctrl_reg__REMOVED)

static LED_Drive_BACKUP_STRUCT  LED_Drive_backup = {0u};

    
/*******************************************************************************
* Function Name: LED_Drive_SaveConfig
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
void LED_Drive_SaveConfig(void) 
{
    LED_Drive_backup.controlState = LED_Drive_Control;
}


/*******************************************************************************
* Function Name: LED_Drive_RestoreConfig
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
void LED_Drive_RestoreConfig(void) 
{
     LED_Drive_Control = LED_Drive_backup.controlState;
}


/*******************************************************************************
* Function Name: LED_Drive_Sleep
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
void LED_Drive_Sleep(void) 
{
    LED_Drive_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_Drive_Wakeup
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
void LED_Drive_Wakeup(void)  
{
    LED_Drive_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
