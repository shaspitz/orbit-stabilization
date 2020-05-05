/*******************************************************************************
* File Name: Supply_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Supply.h"

static Supply_backupStruct Supply_backup;


/*******************************************************************************
* Function Name: Supply_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Supply_SaveConfig(void) 
{
    if (!((Supply_CR1 & Supply_SRC_MASK) == Supply_SRC_UDB))
    {
        Supply_backup.data_value = Supply_Data;
    }
}


/*******************************************************************************
* Function Name: Supply_RestoreConfig
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
*******************************************************************************/
void Supply_RestoreConfig(void) 
{
    if (!((Supply_CR1 & Supply_SRC_MASK) == Supply_SRC_UDB))
    {
        if((Supply_Strobe & Supply_STRB_MASK) == Supply_STRB_EN)
        {
            Supply_Strobe &= (uint8)(~Supply_STRB_MASK);
            Supply_Data = Supply_backup.data_value;
            Supply_Strobe |= Supply_STRB_EN;
        }
        else
        {
            Supply_Data = Supply_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Supply_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Supply_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Supply_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Supply_ACT_PWR_EN == (Supply_PWRMGR & Supply_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Supply_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Supply_backup.enableState = 0u;
    }
    
    Supply_Stop();
    Supply_SaveConfig();
}


/*******************************************************************************
* Function Name: Supply_Wakeup
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
*  Supply_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Supply_Wakeup(void) 
{
    Supply_RestoreConfig();
    
    if(Supply_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Supply_Enable();

        /* Restore the data register */
        Supply_SetValue(Supply_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
