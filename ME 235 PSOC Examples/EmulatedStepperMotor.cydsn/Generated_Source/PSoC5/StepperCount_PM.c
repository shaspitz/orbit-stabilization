/*******************************************************************************
* File Name: StepperCount_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StepperCount.h"

static StepperCount_backupStruct StepperCount_backup;


/*******************************************************************************
* Function Name: StepperCount_SaveConfig
********************************************************************************
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
*  StepperCount_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void StepperCount_SaveConfig(void) 
{
    #if (!StepperCount_UsingFixedFunction)

        StepperCount_backup.CounterUdb = StepperCount_ReadCounter();

        #if(!StepperCount_ControlRegRemoved)
            StepperCount_backup.CounterControlRegister = StepperCount_ReadControlRegister();
        #endif /* (!StepperCount_ControlRegRemoved) */

    #endif /* (!StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_RestoreConfig
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
*  StepperCount_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void StepperCount_RestoreConfig(void) 
{      
    #if (!StepperCount_UsingFixedFunction)

       StepperCount_WriteCounter(StepperCount_backup.CounterUdb);

        #if(!StepperCount_ControlRegRemoved)
            StepperCount_WriteControlRegister(StepperCount_backup.CounterControlRegister);
        #endif /* (!StepperCount_ControlRegRemoved) */

    #endif /* (!StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_Sleep
********************************************************************************
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
*  StepperCount_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void StepperCount_Sleep(void) 
{
    #if(!StepperCount_ControlRegRemoved)
        /* Save Counter's enable state */
        if(StepperCount_CTRL_ENABLE == (StepperCount_CONTROL & StepperCount_CTRL_ENABLE))
        {
            /* Counter is enabled */
            StepperCount_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            StepperCount_backup.CounterEnableState = 0u;
        }
    #else
        StepperCount_backup.CounterEnableState = 1u;
        if(StepperCount_backup.CounterEnableState != 0u)
        {
            StepperCount_backup.CounterEnableState = 0u;
        }
    #endif /* (!StepperCount_ControlRegRemoved) */
    
    StepperCount_Stop();
    StepperCount_SaveConfig();
}


/*******************************************************************************
* Function Name: StepperCount_Wakeup
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
*  StepperCount_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void StepperCount_Wakeup(void) 
{
    StepperCount_RestoreConfig();
    #if(!StepperCount_ControlRegRemoved)
        if(StepperCount_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            StepperCount_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!StepperCount_ControlRegRemoved) */
    
}


/* [] END OF FILE */
