/*******************************************************************************
* File Name: Shunt_PM.c  
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

#include "Shunt.h"

static Shunt_BACKUP_STRUCT  Shunt_backup;


/*******************************************************************************
* Function Name: Shunt_Sleep
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
*  Shunt_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Shunt_Sleep(void) 
{
	/* Save DAC8's enable state */

	Shunt_backup.enableState = (Shunt_VDAC8_ACT_PWR_EN == 
		(Shunt_VDAC8_PWRMGR_REG & Shunt_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	Shunt_Stop();
	Shunt_SaveConfig();
}


/*******************************************************************************
* Function Name: Shunt_Wakeup
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
*  Shunt_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Shunt_Wakeup(void) 
{
	Shunt_RestoreConfig();

	if(Shunt_backup.enableState == 1u)
	{
		Shunt_Enable();
	}
}


/* [] END OF FILE */
