/*******************************************************************************
* File Name: UltraSonic_PM.c
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

#include "UltraSonic.h"

static UltraSonic_backupStruct UltraSonic_backup;


/*******************************************************************************
* Function Name: UltraSonic_SaveConfig
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
*  UltraSonic_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void UltraSonic_SaveConfig(void) 
{

    #if(!UltraSonic_UsingFixedFunction)
        #if(!UltraSonic_PWMModeIsCenterAligned)
            UltraSonic_backup.PWMPeriod = UltraSonic_ReadPeriod();
        #endif /* (!UltraSonic_PWMModeIsCenterAligned) */
        UltraSonic_backup.PWMUdb = UltraSonic_ReadCounter();
        #if (UltraSonic_UseStatus)
            UltraSonic_backup.InterruptMaskValue = UltraSonic_STATUS_MASK;
        #endif /* (UltraSonic_UseStatus) */

        #if(UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_256_CLOCKS || \
            UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_2_4_CLOCKS)
            UltraSonic_backup.PWMdeadBandValue = UltraSonic_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(UltraSonic_KillModeMinTime)
             UltraSonic_backup.PWMKillCounterPeriod = UltraSonic_ReadKillTime();
        #endif /* (UltraSonic_KillModeMinTime) */

        #if(UltraSonic_UseControl)
            UltraSonic_backup.PWMControlRegister = UltraSonic_ReadControlRegister();
        #endif /* (UltraSonic_UseControl) */
    #endif  /* (!UltraSonic_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: UltraSonic_RestoreConfig
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
*  UltraSonic_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void UltraSonic_RestoreConfig(void) 
{
        #if(!UltraSonic_UsingFixedFunction)
            #if(!UltraSonic_PWMModeIsCenterAligned)
                UltraSonic_WritePeriod(UltraSonic_backup.PWMPeriod);
            #endif /* (!UltraSonic_PWMModeIsCenterAligned) */

            UltraSonic_WriteCounter(UltraSonic_backup.PWMUdb);

            #if (UltraSonic_UseStatus)
                UltraSonic_STATUS_MASK = UltraSonic_backup.InterruptMaskValue;
            #endif /* (UltraSonic_UseStatus) */

            #if(UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_256_CLOCKS || \
                UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_2_4_CLOCKS)
                UltraSonic_WriteDeadTime(UltraSonic_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(UltraSonic_KillModeMinTime)
                UltraSonic_WriteKillTime(UltraSonic_backup.PWMKillCounterPeriod);
            #endif /* (UltraSonic_KillModeMinTime) */

            #if(UltraSonic_UseControl)
                UltraSonic_WriteControlRegister(UltraSonic_backup.PWMControlRegister);
            #endif /* (UltraSonic_UseControl) */
        #endif  /* (!UltraSonic_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: UltraSonic_Sleep
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
*  UltraSonic_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void UltraSonic_Sleep(void) 
{
    #if(UltraSonic_UseControl)
        if(UltraSonic_CTRL_ENABLE == (UltraSonic_CONTROL & UltraSonic_CTRL_ENABLE))
        {
            /*Component is enabled */
            UltraSonic_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            UltraSonic_backup.PWMEnableState = 0u;
        }
    #endif /* (UltraSonic_UseControl) */

    /* Stop component */
    UltraSonic_Stop();

    /* Save registers configuration */
    UltraSonic_SaveConfig();
}


/*******************************************************************************
* Function Name: UltraSonic_Wakeup
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
*  UltraSonic_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void UltraSonic_Wakeup(void) 
{
     /* Restore registers values */
    UltraSonic_RestoreConfig();

    if(UltraSonic_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        UltraSonic_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
