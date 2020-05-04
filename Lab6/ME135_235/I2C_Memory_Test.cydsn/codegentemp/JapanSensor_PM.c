/*******************************************************************************
* File Name: JapanSensor_PM.c  
* Version 2.10
*
* Description:
*  This file provides the power manager source code to the API for 
*  the WaveDAC8 component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "JapanSensor.h"

static JapanSensor_BACKUP_STRUCT  JapanSensor_backup;


/*******************************************************************************
* Function Name: JapanSensor_Sleep
********************************************************************************
*
* Summary:
*  Stops the component and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  JapanSensor_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void JapanSensor_Sleep(void) 
{
	/* Save DAC8's enable state */

	JapanSensor_backup.enableState = (JapanSensor_VDAC8_ACT_PWR_EN == 
		(JapanSensor_VDAC8_PWRMGR_REG & JapanSensor_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	JapanSensor_Stop();
	JapanSensor_SaveConfig();
}


/*******************************************************************************
* Function Name: JapanSensor_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  JapanSensor_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void JapanSensor_Wakeup(void) 
{
	JapanSensor_RestoreConfig();

	if(JapanSensor_backup.enableState == 1u)
	{
		JapanSensor_Enable();
	}
}


/* [] END OF FILE */
