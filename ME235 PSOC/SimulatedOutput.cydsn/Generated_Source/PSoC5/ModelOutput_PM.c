/*******************************************************************************
* File Name: ModelOutput_PM.c  
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

#include "ModelOutput.h"

static ModelOutput_backupStruct ModelOutput_backup;


/*******************************************************************************
* Function Name: ModelOutput_SaveConfig
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
void ModelOutput_SaveConfig(void) 
{
    if (!((ModelOutput_CR1 & ModelOutput_SRC_MASK) == ModelOutput_SRC_UDB))
    {
        ModelOutput_backup.data_value = ModelOutput_Data;
    }
}


/*******************************************************************************
* Function Name: ModelOutput_RestoreConfig
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
void ModelOutput_RestoreConfig(void) 
{
    if (!((ModelOutput_CR1 & ModelOutput_SRC_MASK) == ModelOutput_SRC_UDB))
    {
        if((ModelOutput_Strobe & ModelOutput_STRB_MASK) == ModelOutput_STRB_EN)
        {
            ModelOutput_Strobe &= (uint8)(~ModelOutput_STRB_MASK);
            ModelOutput_Data = ModelOutput_backup.data_value;
            ModelOutput_Strobe |= ModelOutput_STRB_EN;
        }
        else
        {
            ModelOutput_Data = ModelOutput_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: ModelOutput_Sleep
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
*  ModelOutput_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void ModelOutput_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(ModelOutput_ACT_PWR_EN == (ModelOutput_PWRMGR & ModelOutput_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        ModelOutput_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        ModelOutput_backup.enableState = 0u;
    }
    
    ModelOutput_Stop();
    ModelOutput_SaveConfig();
}


/*******************************************************************************
* Function Name: ModelOutput_Wakeup
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
*  ModelOutput_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ModelOutput_Wakeup(void) 
{
    ModelOutput_RestoreConfig();
    
    if(ModelOutput_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        ModelOutput_Enable();

        /* Restore the data register */
        ModelOutput_SetValue(ModelOutput_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
