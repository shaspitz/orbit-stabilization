/*******************************************************************************
* File Name: Marker2_PM.c
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

#include "Marker2.h"

/* Check for removal by optimization */
#if !defined(Marker2_Sync_ctrl_reg__REMOVED)

static Marker2_BACKUP_STRUCT  Marker2_backup = {0u};

    
/*******************************************************************************
* Function Name: Marker2_SaveConfig
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
void Marker2_SaveConfig(void) 
{
    Marker2_backup.controlState = Marker2_Control;
}


/*******************************************************************************
* Function Name: Marker2_RestoreConfig
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
void Marker2_RestoreConfig(void) 
{
     Marker2_Control = Marker2_backup.controlState;
}


/*******************************************************************************
* Function Name: Marker2_Sleep
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
void Marker2_Sleep(void) 
{
    Marker2_SaveConfig();
}


/*******************************************************************************
* Function Name: Marker2_Wakeup
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
void Marker2_Wakeup(void)  
{
    Marker2_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
