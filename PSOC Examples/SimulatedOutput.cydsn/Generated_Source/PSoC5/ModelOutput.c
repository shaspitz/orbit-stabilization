/*******************************************************************************
* File Name: ModelOutput.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "ModelOutput.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 ModelOutput_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 ModelOutput_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static ModelOutput_backupStruct ModelOutput_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: ModelOutput_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_Init(void) 
{
    ModelOutput_CR0 = (ModelOutput_MODE_V );

    /* Set default data source */
    #if(ModelOutput_DEFAULT_DATA_SRC != 0 )
        ModelOutput_CR1 = (ModelOutput_DEFAULT_CNTL | ModelOutput_DACBUS_ENABLE) ;
    #else
        ModelOutput_CR1 = (ModelOutput_DEFAULT_CNTL | ModelOutput_DACBUS_DISABLE) ;
    #endif /* (ModelOutput_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(ModelOutput_DEFAULT_STRB != 0)
        ModelOutput_Strobe |= ModelOutput_STRB_EN ;
    #endif/* (ModelOutput_DEFAULT_STRB != 0) */

    /* Set default range */
    ModelOutput_SetRange(ModelOutput_DEFAULT_RANGE); 

    /* Set default speed */
    ModelOutput_SetSpeed(ModelOutput_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: ModelOutput_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_Enable(void) 
{
    ModelOutput_PWRMGR |= ModelOutput_ACT_PWR_EN;
    ModelOutput_STBY_PWRMGR |= ModelOutput_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(ModelOutput_restoreVal == 1u) 
        {
             ModelOutput_CR0 = ModelOutput_backup.data_value;
             ModelOutput_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ModelOutput_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  ModelOutput_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ModelOutput_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(ModelOutput_initVar == 0u)
    { 
        ModelOutput_Init();
        ModelOutput_initVar = 1u;
    }

    /* Enable power to DAC */
    ModelOutput_Enable();

    /* Set default value */
    ModelOutput_SetValue(ModelOutput_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: ModelOutput_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_Stop(void) 
{
    /* Disble power to DAC */
    ModelOutput_PWRMGR &= (uint8)(~ModelOutput_ACT_PWR_EN);
    ModelOutput_STBY_PWRMGR &= (uint8)(~ModelOutput_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        ModelOutput_backup.data_value = ModelOutput_CR0;
        ModelOutput_CR0 = ModelOutput_CUR_MODE_OUT_OFF;
        ModelOutput_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ModelOutput_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    ModelOutput_CR0 &= (uint8)(~ModelOutput_HS_MASK);
    ModelOutput_CR0 |=  (speed & ModelOutput_HS_MASK);
}


/*******************************************************************************
* Function Name: ModelOutput_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_SetRange(uint8 range) 
{
    ModelOutput_CR0 &= (uint8)(~ModelOutput_RANGE_MASK);      /* Clear existing mode */
    ModelOutput_CR0 |= (range & ModelOutput_RANGE_MASK);      /*  Set Range  */
    ModelOutput_DacTrim();
}


/*******************************************************************************
* Function Name: ModelOutput_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 ModelOutput_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    ModelOutput_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        ModelOutput_Data = value;
        CyExitCriticalSection(ModelOutput_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: ModelOutput_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void ModelOutput_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((ModelOutput_CR0 & ModelOutput_RANGE_MASK) >> 2) + ModelOutput_TRIM_M7_1V_RNG_OFFSET;
    ModelOutput_TR = CY_GET_XTND_REG8((uint8 *)(ModelOutput_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
