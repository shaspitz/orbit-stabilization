/*******************************************************************************
* File Name: PIXY2UART_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PIXY2UART.h"


/***************************************
* Local data allocation
***************************************/

static PIXY2UART_BACKUP_STRUCT  PIXY2UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: PIXY2UART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the PIXY2UART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PIXY2UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PIXY2UART_SaveConfig(void)
{
    #if(PIXY2UART_CONTROL_REG_REMOVED == 0u)
        PIXY2UART_backup.cr = PIXY2UART_CONTROL_REG;
    #endif /* End PIXY2UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: PIXY2UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PIXY2UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling PIXY2UART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void PIXY2UART_RestoreConfig(void)
{
    #if(PIXY2UART_CONTROL_REG_REMOVED == 0u)
        PIXY2UART_CONTROL_REG = PIXY2UART_backup.cr;
    #endif /* End PIXY2UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: PIXY2UART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The PIXY2UART_Sleep() API saves the current component state. Then it
*  calls the PIXY2UART_Stop() function and calls 
*  PIXY2UART_SaveConfig() to save the hardware configuration.
*  Call the PIXY2UART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PIXY2UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PIXY2UART_Sleep(void)
{
    #if(PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED)
        if((PIXY2UART_RXSTATUS_ACTL_REG  & PIXY2UART_INT_ENABLE) != 0u)
        {
            PIXY2UART_backup.enableState = 1u;
        }
        else
        {
            PIXY2UART_backup.enableState = 0u;
        }
    #else
        if((PIXY2UART_TXSTATUS_ACTL_REG  & PIXY2UART_INT_ENABLE) !=0u)
        {
            PIXY2UART_backup.enableState = 1u;
        }
        else
        {
            PIXY2UART_backup.enableState = 0u;
        }
    #endif /* End PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED*/

    PIXY2UART_Stop();
    PIXY2UART_SaveConfig();
}


/*******************************************************************************
* Function Name: PIXY2UART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  PIXY2UART_Sleep() was called. The PIXY2UART_Wakeup() function
*  calls the PIXY2UART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  PIXY2UART_Sleep() function was called, the PIXY2UART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  PIXY2UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void PIXY2UART_Wakeup(void)
{
    PIXY2UART_RestoreConfig();
    #if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )
        PIXY2UART_ClearRxBuffer();
    #endif /* End (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */
    #if(PIXY2UART_TX_ENABLED || PIXY2UART_HD_ENABLED)
        PIXY2UART_ClearTxBuffer();
    #endif /* End PIXY2UART_TX_ENABLED || PIXY2UART_HD_ENABLED */

    if(PIXY2UART_backup.enableState != 0u)
    {
        PIXY2UART_Enable();
    }
}


/* [] END OF FILE */
