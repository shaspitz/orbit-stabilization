/*******************************************************************************
* File Name: ByteCounter_PM.c  
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

#include "ByteCounter.h"

static ByteCounter_backupStruct ByteCounter_backup;


/*******************************************************************************
* Function Name: ByteCounter_SaveConfig
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
*  ByteCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ByteCounter_SaveConfig(void) 
{
    #if (!ByteCounter_UsingFixedFunction)

        ByteCounter_backup.CounterUdb = ByteCounter_ReadCounter();

        #if(!ByteCounter_ControlRegRemoved)
            ByteCounter_backup.CounterControlRegister = ByteCounter_ReadControlRegister();
        #endif /* (!ByteCounter_ControlRegRemoved) */

    #endif /* (!ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_RestoreConfig
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
*  ByteCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ByteCounter_RestoreConfig(void) 
{      
    #if (!ByteCounter_UsingFixedFunction)

       ByteCounter_WriteCounter(ByteCounter_backup.CounterUdb);

        #if(!ByteCounter_ControlRegRemoved)
            ByteCounter_WriteControlRegister(ByteCounter_backup.CounterControlRegister);
        #endif /* (!ByteCounter_ControlRegRemoved) */

    #endif /* (!ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_Sleep
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
*  ByteCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ByteCounter_Sleep(void) 
{
    #if(!ByteCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ByteCounter_CTRL_ENABLE == (ByteCounter_CONTROL & ByteCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ByteCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ByteCounter_backup.CounterEnableState = 0u;
        }
    #else
        ByteCounter_backup.CounterEnableState = 1u;
        if(ByteCounter_backup.CounterEnableState != 0u)
        {
            ByteCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!ByteCounter_ControlRegRemoved) */
    
    ByteCounter_Stop();
    ByteCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: ByteCounter_Wakeup
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
*  ByteCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ByteCounter_Wakeup(void) 
{
    ByteCounter_RestoreConfig();
    #if(!ByteCounter_ControlRegRemoved)
        if(ByteCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ByteCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ByteCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
