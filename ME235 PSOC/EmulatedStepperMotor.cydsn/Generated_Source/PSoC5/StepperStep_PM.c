/*******************************************************************************
* File Name: StepperStep_PM.c
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

#include "StepperStep.h"

static StepperStep_backupStruct StepperStep_backup;


/*******************************************************************************
* Function Name: StepperStep_SaveConfig
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
*  StepperStep_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void StepperStep_SaveConfig(void) 
{
    #if (!StepperStep_UsingFixedFunction)
        StepperStep_backup.TimerUdb = StepperStep_ReadCounter();
        StepperStep_backup.InterruptMaskValue = StepperStep_STATUS_MASK;
        #if (StepperStep_UsingHWCaptureCounter)
            StepperStep_backup.TimerCaptureCounter = StepperStep_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!StepperStep_UDB_CONTROL_REG_REMOVED)
            StepperStep_backup.TimerControlRegister = StepperStep_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: StepperStep_RestoreConfig
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
*  StepperStep_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void StepperStep_RestoreConfig(void) 
{   
    #if (!StepperStep_UsingFixedFunction)

        StepperStep_WriteCounter(StepperStep_backup.TimerUdb);
        StepperStep_STATUS_MASK =StepperStep_backup.InterruptMaskValue;
        #if (StepperStep_UsingHWCaptureCounter)
            StepperStep_SetCaptureCount(StepperStep_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!StepperStep_UDB_CONTROL_REG_REMOVED)
            StepperStep_WriteControlRegister(StepperStep_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: StepperStep_Sleep
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
*  StepperStep_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void StepperStep_Sleep(void) 
{
    #if(!StepperStep_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(StepperStep_CTRL_ENABLE == (StepperStep_CONTROL & StepperStep_CTRL_ENABLE))
        {
            /* Timer is enabled */
            StepperStep_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            StepperStep_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    StepperStep_Stop();
    StepperStep_SaveConfig();
}


/*******************************************************************************
* Function Name: StepperStep_Wakeup
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
*  StepperStep_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepperStep_Wakeup(void) 
{
    StepperStep_RestoreConfig();
    #if(!StepperStep_UDB_CONTROL_REG_REMOVED)
        if(StepperStep_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                StepperStep_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
