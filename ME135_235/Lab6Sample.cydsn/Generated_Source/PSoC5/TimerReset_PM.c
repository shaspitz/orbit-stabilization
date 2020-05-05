/*******************************************************************************
* File Name: TimerReset_PM.c
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

#include "TimerReset.h"

/* Check for removal by optimization */
#if !defined(TimerReset_Sync_ctrl_reg__REMOVED)

static TimerReset_BACKUP_STRUCT  TimerReset_backup = {0u};

    
/*******************************************************************************
* Function Name: TimerReset_SaveConfig
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
void TimerReset_SaveConfig(void) 
{
    TimerReset_backup.controlState = TimerReset_Control;
}


/*******************************************************************************
* Function Name: TimerReset_RestoreConfig
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
void TimerReset_RestoreConfig(void) 
{
     TimerReset_Control = TimerReset_backup.controlState;
}


/*******************************************************************************
* Function Name: TimerReset_Sleep
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
void TimerReset_Sleep(void) 
{
    TimerReset_SaveConfig();
}


/*******************************************************************************
* Function Name: TimerReset_Wakeup
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
void TimerReset_Wakeup(void)  
{
    TimerReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
