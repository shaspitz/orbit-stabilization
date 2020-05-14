/*******************************************************************************
* File Name: Shunt_VDAC8_PM.c  
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

#include "Shunt_VDAC8.h"

static Shunt_VDAC8_backupStruct Shunt_VDAC8_backup;


/*******************************************************************************
* Function Name: Shunt_VDAC8_SaveConfig
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
void Shunt_VDAC8_SaveConfig(void) 
{
    if (!((Shunt_VDAC8_CR1 & Shunt_VDAC8_SRC_MASK) == Shunt_VDAC8_SRC_UDB))
    {
        Shunt_VDAC8_backup.data_value = Shunt_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Shunt_VDAC8_RestoreConfig
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
void Shunt_VDAC8_RestoreConfig(void) 
{
    if (!((Shunt_VDAC8_CR1 & Shunt_VDAC8_SRC_MASK) == Shunt_VDAC8_SRC_UDB))
    {
        if((Shunt_VDAC8_Strobe & Shunt_VDAC8_STRB_MASK) == Shunt_VDAC8_STRB_EN)
        {
            Shunt_VDAC8_Strobe &= (uint8)(~Shunt_VDAC8_STRB_MASK);
            Shunt_VDAC8_Data = Shunt_VDAC8_backup.data_value;
            Shunt_VDAC8_Strobe |= Shunt_VDAC8_STRB_EN;
        }
        else
        {
            Shunt_VDAC8_Data = Shunt_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Shunt_VDAC8_Sleep
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
*  Shunt_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Shunt_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Shunt_VDAC8_ACT_PWR_EN == (Shunt_VDAC8_PWRMGR & Shunt_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Shunt_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Shunt_VDAC8_backup.enableState = 0u;
    }
    
    Shunt_VDAC8_Stop();
    Shunt_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Shunt_VDAC8_Wakeup
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
*  Shunt_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Shunt_VDAC8_Wakeup(void) 
{
    Shunt_VDAC8_RestoreConfig();
    
    if(Shunt_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Shunt_VDAC8_Enable();

        /* Restore the data register */
        Shunt_VDAC8_SetValue(Shunt_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
