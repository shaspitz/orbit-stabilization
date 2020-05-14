/*******************************************************************************
* File Name: SampleTime_PM.c
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

#include "SampleTime.h"

static SampleTime_backupStruct SampleTime_backup;


/*******************************************************************************
* Function Name: SampleTime_SaveConfig
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
*  SampleTime_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SampleTime_SaveConfig(void) 
{
    #if (!SampleTime_UsingFixedFunction)
        SampleTime_backup.TimerUdb = SampleTime_ReadCounter();
        SampleTime_backup.InterruptMaskValue = SampleTime_STATUS_MASK;
        #if (SampleTime_UsingHWCaptureCounter)
            SampleTime_backup.TimerCaptureCounter = SampleTime_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SampleTime_UDB_CONTROL_REG_REMOVED)
            SampleTime_backup.TimerControlRegister = SampleTime_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SampleTime_RestoreConfig
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
*  SampleTime_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SampleTime_RestoreConfig(void) 
{   
    #if (!SampleTime_UsingFixedFunction)

        SampleTime_WriteCounter(SampleTime_backup.TimerUdb);
        SampleTime_STATUS_MASK =SampleTime_backup.InterruptMaskValue;
        #if (SampleTime_UsingHWCaptureCounter)
            SampleTime_SetCaptureCount(SampleTime_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SampleTime_UDB_CONTROL_REG_REMOVED)
            SampleTime_WriteControlRegister(SampleTime_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SampleTime_Sleep
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
*  SampleTime_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SampleTime_Sleep(void) 
{
    #if(!SampleTime_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SampleTime_CTRL_ENABLE == (SampleTime_CONTROL & SampleTime_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SampleTime_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SampleTime_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SampleTime_Stop();
    SampleTime_SaveConfig();
}


/*******************************************************************************
* Function Name: SampleTime_Wakeup
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
*  SampleTime_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SampleTime_Wakeup(void) 
{
    SampleTime_RestoreConfig();
    #if(!SampleTime_UDB_CONTROL_REG_REMOVED)
        if(SampleTime_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SampleTime_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
