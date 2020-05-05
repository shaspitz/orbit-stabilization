/*******************************************************************************
* File Name: PIXY2PacketCount_PM.c  
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

#include "PIXY2PacketCount.h"

static PIXY2PacketCount_backupStruct PIXY2PacketCount_backup;


/*******************************************************************************
* Function Name: PIXY2PacketCount_SaveConfig
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
*  PIXY2PacketCount_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PIXY2PacketCount_SaveConfig(void) 
{
    #if (!PIXY2PacketCount_UsingFixedFunction)

        PIXY2PacketCount_backup.CounterUdb = PIXY2PacketCount_ReadCounter();

        #if(!PIXY2PacketCount_ControlRegRemoved)
            PIXY2PacketCount_backup.CounterControlRegister = PIXY2PacketCount_ReadControlRegister();
        #endif /* (!PIXY2PacketCount_ControlRegRemoved) */

    #endif /* (!PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_RestoreConfig
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
*  PIXY2PacketCount_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PIXY2PacketCount_RestoreConfig(void) 
{      
    #if (!PIXY2PacketCount_UsingFixedFunction)

       PIXY2PacketCount_WriteCounter(PIXY2PacketCount_backup.CounterUdb);

        #if(!PIXY2PacketCount_ControlRegRemoved)
            PIXY2PacketCount_WriteControlRegister(PIXY2PacketCount_backup.CounterControlRegister);
        #endif /* (!PIXY2PacketCount_ControlRegRemoved) */

    #endif /* (!PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_Sleep
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
*  PIXY2PacketCount_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PIXY2PacketCount_Sleep(void) 
{
    #if(!PIXY2PacketCount_ControlRegRemoved)
        /* Save Counter's enable state */
        if(PIXY2PacketCount_CTRL_ENABLE == (PIXY2PacketCount_CONTROL & PIXY2PacketCount_CTRL_ENABLE))
        {
            /* Counter is enabled */
            PIXY2PacketCount_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            PIXY2PacketCount_backup.CounterEnableState = 0u;
        }
    #else
        PIXY2PacketCount_backup.CounterEnableState = 1u;
        if(PIXY2PacketCount_backup.CounterEnableState != 0u)
        {
            PIXY2PacketCount_backup.CounterEnableState = 0u;
        }
    #endif /* (!PIXY2PacketCount_ControlRegRemoved) */
    
    PIXY2PacketCount_Stop();
    PIXY2PacketCount_SaveConfig();
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_Wakeup
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
*  PIXY2PacketCount_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PIXY2PacketCount_Wakeup(void) 
{
    PIXY2PacketCount_RestoreConfig();
    #if(!PIXY2PacketCount_ControlRegRemoved)
        if(PIXY2PacketCount_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            PIXY2PacketCount_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!PIXY2PacketCount_ControlRegRemoved) */
    
}


/* [] END OF FILE */
