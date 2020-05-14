/*******************************************************************************
* File Name: Foil_VDAC8_PM.c  
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

#include "Foil_VDAC8.h"

static Foil_VDAC8_backupStruct Foil_VDAC8_backup;


/*******************************************************************************
* Function Name: Foil_VDAC8_SaveConfig
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
void Foil_VDAC8_SaveConfig(void) 
{
    if (!((Foil_VDAC8_CR1 & Foil_VDAC8_SRC_MASK) == Foil_VDAC8_SRC_UDB))
    {
        Foil_VDAC8_backup.data_value = Foil_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Foil_VDAC8_RestoreConfig
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
void Foil_VDAC8_RestoreConfig(void) 
{
    if (!((Foil_VDAC8_CR1 & Foil_VDAC8_SRC_MASK) == Foil_VDAC8_SRC_UDB))
    {
        if((Foil_VDAC8_Strobe & Foil_VDAC8_STRB_MASK) == Foil_VDAC8_STRB_EN)
        {
            Foil_VDAC8_Strobe &= (uint8)(~Foil_VDAC8_STRB_MASK);
            Foil_VDAC8_Data = Foil_VDAC8_backup.data_value;
            Foil_VDAC8_Strobe |= Foil_VDAC8_STRB_EN;
        }
        else
        {
            Foil_VDAC8_Data = Foil_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Foil_VDAC8_Sleep
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
*  Foil_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Foil_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Foil_VDAC8_ACT_PWR_EN == (Foil_VDAC8_PWRMGR & Foil_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Foil_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Foil_VDAC8_backup.enableState = 0u;
    }
    
    Foil_VDAC8_Stop();
    Foil_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Foil_VDAC8_Wakeup
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
*  Foil_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Foil_VDAC8_Wakeup(void) 
{
    Foil_VDAC8_RestoreConfig();
    
    if(Foil_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Foil_VDAC8_Enable();

        /* Restore the data register */
        Foil_VDAC8_SetValue(Foil_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
