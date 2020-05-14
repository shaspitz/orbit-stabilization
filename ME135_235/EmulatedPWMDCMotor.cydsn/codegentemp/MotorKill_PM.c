/*******************************************************************************
* File Name: MotorKill_PM.c
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

#include "MotorKill.h"

/* Check for removal by optimization */
#if !defined(MotorKill_Sync_ctrl_reg__REMOVED)

static MotorKill_BACKUP_STRUCT  MotorKill_backup = {0u};

    
/*******************************************************************************
* Function Name: MotorKill_SaveConfig
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
void MotorKill_SaveConfig(void) 
{
    MotorKill_backup.controlState = MotorKill_Control;
}


/*******************************************************************************
* Function Name: MotorKill_RestoreConfig
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
void MotorKill_RestoreConfig(void) 
{
     MotorKill_Control = MotorKill_backup.controlState;
}


/*******************************************************************************
* Function Name: MotorKill_Sleep
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
void MotorKill_Sleep(void) 
{
    MotorKill_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorKill_Wakeup
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
void MotorKill_Wakeup(void)  
{
    MotorKill_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
