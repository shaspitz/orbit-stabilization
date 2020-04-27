/*******************************************************************************
* File Name: Foil_PM.c  
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

#include "Foil.h"

static Foil_BACKUP_STRUCT  Foil_backup;


/*******************************************************************************
* Function Name: Foil_Sleep
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
*  Foil_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Foil_Sleep(void) 
{
	/* Save DAC8's enable state */

	Foil_backup.enableState = (Foil_VDAC8_ACT_PWR_EN == 
		(Foil_VDAC8_PWRMGR_REG & Foil_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	Foil_Stop();
	Foil_SaveConfig();
}


/*******************************************************************************
* Function Name: Foil_Wakeup
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
*  Foil_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Foil_Wakeup(void) 
{
	Foil_RestoreConfig();

	if(Foil_backup.enableState == 1u)
	{
		Foil_Enable();
	}
}


/* [] END OF FILE */
