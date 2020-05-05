/*******************************************************************************
* File Name: PIXY2UARTReset_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "PIXY2UARTReset.h"

/* Check for removal by optimization */
#if !defined(PIXY2UARTReset_Sync_ctrl_reg__REMOVED)

static PIXY2UARTReset_BACKUP_STRUCT  PIXY2UARTReset_backup = {0u};

    
/*******************************************************************************
* Function Name: PIXY2UARTReset_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIXY2UARTReset_SaveConfig(void) 
{
    PIXY2UARTReset_backup.controlState = PIXY2UARTReset_Control;
}


/*******************************************************************************
* Function Name: PIXY2UARTReset_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void PIXY2UARTReset_RestoreConfig(void) 
{
     PIXY2UARTReset_Control = PIXY2UARTReset_backup.controlState;
}


/*******************************************************************************
* Function Name: PIXY2UARTReset_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIXY2UARTReset_Sleep(void) 
{
    PIXY2UARTReset_SaveConfig();
}


/*******************************************************************************
* Function Name: PIXY2UARTReset_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PIXY2UARTReset_Wakeup(void)  
{
    PIXY2UARTReset_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
