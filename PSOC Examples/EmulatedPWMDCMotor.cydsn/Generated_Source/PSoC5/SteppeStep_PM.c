/*******************************************************************************
* File Name: SteppeStep_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SteppeStep.h"

static SteppeStep_backupStruct SteppeStep_backup;


/*******************************************************************************
* Function Name: SteppeStep_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SteppeStep_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SteppeStep_SaveConfig(void) 
{
    #if (!SteppeStep_UsingFixedFunction)
        SteppeStep_backup.TimerUdb = SteppeStep_ReadCounter();
        SteppeStep_backup.InterruptMaskValue = SteppeStep_STATUS_MASK;
        #if (SteppeStep_UsingHWCaptureCounter)
            SteppeStep_backup.TimerCaptureCounter = SteppeStep_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SteppeStep_UDB_CONTROL_REG_REMOVED)
            SteppeStep_backup.TimerControlRegister = SteppeStep_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SteppeStep_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SteppeStep_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SteppeStep_RestoreConfig(void) 
{   
    #if (!SteppeStep_UsingFixedFunction)

        SteppeStep_WriteCounter(SteppeStep_backup.TimerUdb);
        SteppeStep_STATUS_MASK =SteppeStep_backup.InterruptMaskValue;
        #if (SteppeStep_UsingHWCaptureCounter)
            SteppeStep_SetCaptureCount(SteppeStep_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SteppeStep_UDB_CONTROL_REG_REMOVED)
            SteppeStep_WriteControlRegister(SteppeStep_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SteppeStep_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SteppeStep_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SteppeStep_Sleep(void) 
{
    #if(!SteppeStep_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SteppeStep_CTRL_ENABLE == (SteppeStep_CONTROL & SteppeStep_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SteppeStep_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SteppeStep_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SteppeStep_Stop();
    SteppeStep_SaveConfig();
}


/*******************************************************************************
* Function Name: SteppeStep_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SteppeStep_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SteppeStep_Wakeup(void) 
{
    SteppeStep_RestoreConfig();
    #if(!SteppeStep_UDB_CONTROL_REG_REMOVED)
        if(SteppeStep_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SteppeStep_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
