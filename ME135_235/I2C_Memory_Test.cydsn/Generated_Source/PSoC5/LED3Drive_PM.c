/*******************************************************************************
* File Name: LED3Drive_PM.c
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

#include "LED3Drive.h"

/* Check for removal by optimization */
#if !defined(LED3Drive_Sync_ctrl_reg__REMOVED)

static LED3Drive_BACKUP_STRUCT  LED3Drive_backup = {0u};

    
/*******************************************************************************
* Function Name: LED3Drive_SaveConfig
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
void LED3Drive_SaveConfig(void) 
{
    LED3Drive_backup.controlState = LED3Drive_Control;
}


/*******************************************************************************
* Function Name: LED3Drive_RestoreConfig
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
void LED3Drive_RestoreConfig(void) 
{
     LED3Drive_Control = LED3Drive_backup.controlState;
}


/*******************************************************************************
* Function Name: LED3Drive_Sleep
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
void LED3Drive_Sleep(void) 
{
    LED3Drive_SaveConfig();
}


/*******************************************************************************
* Function Name: LED3Drive_Wakeup
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
void LED3Drive_Wakeup(void)  
{
    LED3Drive_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
