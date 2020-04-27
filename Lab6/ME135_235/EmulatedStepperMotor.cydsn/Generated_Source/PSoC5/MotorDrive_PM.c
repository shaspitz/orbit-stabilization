/*******************************************************************************
* File Name: MotorDrive_PM.c
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

#include "MotorDrive.h"

static MotorDrive_backupStruct MotorDrive_backup;


/*******************************************************************************
* Function Name: MotorDrive_SaveConfig
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
*  MotorDrive_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MotorDrive_SaveConfig(void) 
{

    #if(!MotorDrive_UsingFixedFunction)
        #if(!MotorDrive_PWMModeIsCenterAligned)
            MotorDrive_backup.PWMPeriod = MotorDrive_ReadPeriod();
        #endif /* (!MotorDrive_PWMModeIsCenterAligned) */
        MotorDrive_backup.PWMUdb = MotorDrive_ReadCounter();
        #if (MotorDrive_UseStatus)
            MotorDrive_backup.InterruptMaskValue = MotorDrive_STATUS_MASK;
        #endif /* (MotorDrive_UseStatus) */

        #if(MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_256_CLOCKS || \
            MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_2_4_CLOCKS)
            MotorDrive_backup.PWMdeadBandValue = MotorDrive_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(MotorDrive_KillModeMinTime)
             MotorDrive_backup.PWMKillCounterPeriod = MotorDrive_ReadKillTime();
        #endif /* (MotorDrive_KillModeMinTime) */

        #if(MotorDrive_UseControl)
            MotorDrive_backup.PWMControlRegister = MotorDrive_ReadControlRegister();
        #endif /* (MotorDrive_UseControl) */
    #endif  /* (!MotorDrive_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: MotorDrive_RestoreConfig
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
*  MotorDrive_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MotorDrive_RestoreConfig(void) 
{
        #if(!MotorDrive_UsingFixedFunction)
            #if(!MotorDrive_PWMModeIsCenterAligned)
                MotorDrive_WritePeriod(MotorDrive_backup.PWMPeriod);
            #endif /* (!MotorDrive_PWMModeIsCenterAligned) */

            MotorDrive_WriteCounter(MotorDrive_backup.PWMUdb);

            #if (MotorDrive_UseStatus)
                MotorDrive_STATUS_MASK = MotorDrive_backup.InterruptMaskValue;
            #endif /* (MotorDrive_UseStatus) */

            #if(MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_256_CLOCKS || \
                MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_2_4_CLOCKS)
                MotorDrive_WriteDeadTime(MotorDrive_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(MotorDrive_KillModeMinTime)
                MotorDrive_WriteKillTime(MotorDrive_backup.PWMKillCounterPeriod);
            #endif /* (MotorDrive_KillModeMinTime) */

            #if(MotorDrive_UseControl)
                MotorDrive_WriteControlRegister(MotorDrive_backup.PWMControlRegister);
            #endif /* (MotorDrive_UseControl) */
        #endif  /* (!MotorDrive_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: MotorDrive_Sleep
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
*  MotorDrive_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void MotorDrive_Sleep(void) 
{
    #if(MotorDrive_UseControl)
        if(MotorDrive_CTRL_ENABLE == (MotorDrive_CONTROL & MotorDrive_CTRL_ENABLE))
        {
            /*Component is enabled */
            MotorDrive_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            MotorDrive_backup.PWMEnableState = 0u;
        }
    #endif /* (MotorDrive_UseControl) */

    /* Stop component */
    MotorDrive_Stop();

    /* Save registers configuration */
    MotorDrive_SaveConfig();
}


/*******************************************************************************
* Function Name: MotorDrive_Wakeup
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
*  MotorDrive_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MotorDrive_Wakeup(void) 
{
     /* Restore registers values */
    MotorDrive_RestoreConfig();

    if(MotorDrive_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        MotorDrive_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
