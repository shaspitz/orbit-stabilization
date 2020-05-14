/*******************************************************************************
* File Name: Marker1Drive_PM.c
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

#include "Marker1Drive.h"

/* Check for removal by optimization */
#if !defined(Marker1Drive_Sync_ctrl_reg__REMOVED)

static Marker1Drive_BACKUP_STRUCT  Marker1Drive_backup = {0u};

    
/*******************************************************************************
* Function Name: Marker1Drive_SaveConfig
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
void Marker1Drive_SaveConfig(void) 
{
    Marker1Drive_backup.controlState = Marker1Drive_Control;
}


/*******************************************************************************
* Function Name: Marker1Drive_RestoreConfig
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
void Marker1Drive_RestoreConfig(void) 
{
     Marker1Drive_Control = Marker1Drive_backup.controlState;
}


/*******************************************************************************
* Function Name: Marker1Drive_Sleep
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
void Marker1Drive_Sleep(void) 
{
    Marker1Drive_SaveConfig();
}


/*******************************************************************************
* Function Name: Marker1Drive_Wakeup
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
void Marker1Drive_Wakeup(void)  
{
    Marker1Drive_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
