/*******************************************************************************
* File Name: simulatedForce_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "simulatedForce.h"

static simulatedForce_backupStruct simulatedForce_backup;


/*******************************************************************************
* Function Name: simulatedForce_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  simulatedForce_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void simulatedForce_SaveConfig(void) 
{

    #if(!simulatedForce_UsingFixedFunction)
        #if(!simulatedForce_PWMModeIsCenterAligned)
            simulatedForce_backup.PWMPeriod = simulatedForce_ReadPeriod();
        #endif /* (!simulatedForce_PWMModeIsCenterAligned) */
        simulatedForce_backup.PWMUdb = simulatedForce_ReadCounter();
        #if (simulatedForce_UseStatus)
            simulatedForce_backup.InterruptMaskValue = simulatedForce_STATUS_MASK;
        #endif /* (simulatedForce_UseStatus) */

        #if(simulatedForce_DeadBandMode == simulatedForce__B_PWM__DBM_256_CLOCKS || \
            simulatedForce_DeadBandMode == simulatedForce__B_PWM__DBM_2_4_CLOCKS)
            simulatedForce_backup.PWMdeadBandValue = simulatedForce_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(simulatedForce_KillModeMinTime)
             simulatedForce_backup.PWMKillCounterPeriod = simulatedForce_ReadKillTime();
        #endif /* (simulatedForce_KillModeMinTime) */

        #if(simulatedForce_UseControl)
            simulatedForce_backup.PWMControlRegister = simulatedForce_ReadControlRegister();
        #endif /* (simulatedForce_UseControl) */
    #endif  /* (!simulatedForce_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: simulatedForce_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  simulatedForce_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void simulatedForce_RestoreConfig(void) 
{
        #if(!simulatedForce_UsingFixedFunction)
            #if(!simulatedForce_PWMModeIsCenterAligned)
                simulatedForce_WritePeriod(simulatedForce_backup.PWMPeriod);
            #endif /* (!simulatedForce_PWMModeIsCenterAligned) */

            simulatedForce_WriteCounter(simulatedForce_backup.PWMUdb);

            #if (simulatedForce_UseStatus)
                simulatedForce_STATUS_MASK = simulatedForce_backup.InterruptMaskValue;
            #endif /* (simulatedForce_UseStatus) */

            #if(simulatedForce_DeadBandMode == simulatedForce__B_PWM__DBM_256_CLOCKS || \
                simulatedForce_DeadBandMode == simulatedForce__B_PWM__DBM_2_4_CLOCKS)
                simulatedForce_WriteDeadTime(simulatedForce_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(simulatedForce_KillModeMinTime)
                simulatedForce_WriteKillTime(simulatedForce_backup.PWMKillCounterPeriod);
            #endif /* (simulatedForce_KillModeMinTime) */

            #if(simulatedForce_UseControl)
                simulatedForce_WriteControlRegister(simulatedForce_backup.PWMControlRegister);
            #endif /* (simulatedForce_UseControl) */
        #endif  /* (!simulatedForce_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: simulatedForce_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  simulatedForce_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void simulatedForce_Sleep(void) 
{
    #if(simulatedForce_UseControl)
        if(simulatedForce_CTRL_ENABLE == (simulatedForce_CONTROL & simulatedForce_CTRL_ENABLE))
        {
            /*Component is enabled */
            simulatedForce_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            simulatedForce_backup.PWMEnableState = 0u;
        }
    #endif /* (simulatedForce_UseControl) */

    /* Stop component */
    simulatedForce_Stop();

    /* Save registers configuration */
    simulatedForce_SaveConfig();
}


/*******************************************************************************
* Function Name: simulatedForce_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  simulatedForce_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void simulatedForce_Wakeup(void) 
{
     /* Restore registers values */
    simulatedForce_RestoreConfig();

    if(simulatedForce_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        simulatedForce_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
