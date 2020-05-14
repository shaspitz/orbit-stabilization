/*******************************************************************************
* File Name: JapanSensor_VDAC8_PM.c  
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

#include "JapanSensor_VDAC8.h"

static JapanSensor_VDAC8_backupStruct JapanSensor_VDAC8_backup;


/*******************************************************************************
* Function Name: JapanSensor_VDAC8_SaveConfig
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
void JapanSensor_VDAC8_SaveConfig(void) 
{
    if (!((JapanSensor_VDAC8_CR1 & JapanSensor_VDAC8_SRC_MASK) == JapanSensor_VDAC8_SRC_UDB))
    {
        JapanSensor_VDAC8_backup.data_value = JapanSensor_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: JapanSensor_VDAC8_RestoreConfig
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
void JapanSensor_VDAC8_RestoreConfig(void) 
{
    if (!((JapanSensor_VDAC8_CR1 & JapanSensor_VDAC8_SRC_MASK) == JapanSensor_VDAC8_SRC_UDB))
    {
        if((JapanSensor_VDAC8_Strobe & JapanSensor_VDAC8_STRB_MASK) == JapanSensor_VDAC8_STRB_EN)
        {
            JapanSensor_VDAC8_Strobe &= (uint8)(~JapanSensor_VDAC8_STRB_MASK);
            JapanSensor_VDAC8_Data = JapanSensor_VDAC8_backup.data_value;
            JapanSensor_VDAC8_Strobe |= JapanSensor_VDAC8_STRB_EN;
        }
        else
        {
            JapanSensor_VDAC8_Data = JapanSensor_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: JapanSensor_VDAC8_Sleep
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
*  JapanSensor_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void JapanSensor_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(JapanSensor_VDAC8_ACT_PWR_EN == (JapanSensor_VDAC8_PWRMGR & JapanSensor_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        JapanSensor_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        JapanSensor_VDAC8_backup.enableState = 0u;
    }
    
    JapanSensor_VDAC8_Stop();
    JapanSensor_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: JapanSensor_VDAC8_Wakeup
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
*  JapanSensor_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void JapanSensor_VDAC8_Wakeup(void) 
{
    JapanSensor_VDAC8_RestoreConfig();
    
    if(JapanSensor_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        JapanSensor_VDAC8_Enable();

        /* Restore the data register */
        JapanSensor_VDAC8_SetValue(JapanSensor_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
