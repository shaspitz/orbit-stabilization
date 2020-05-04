/*******************************************************************************
* File Name: simulatedForce.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "simulatedForce.h"

/* Error message for removed <resource> through optimization */
#ifdef simulatedForce_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* simulatedForce_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 simulatedForce_initVar = 0u;


/*******************************************************************************
* Function Name: simulatedForce_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  simulatedForce_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void simulatedForce_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(simulatedForce_initVar == 0u)
    {
        simulatedForce_Init();
        simulatedForce_initVar = 1u;
    }
    simulatedForce_Enable();

}


/*******************************************************************************
* Function Name: simulatedForce_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  simulatedForce_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void simulatedForce_Init(void) 
{
    #if (simulatedForce_UsingFixedFunction || simulatedForce_UseControl)
        uint8 ctrl;
    #endif /* (simulatedForce_UsingFixedFunction || simulatedForce_UseControl) */

    #if(!simulatedForce_UsingFixedFunction)
        #if(simulatedForce_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 simulatedForce_interruptState;
        #endif /* (simulatedForce_UseStatus) */
    #endif /* (!simulatedForce_UsingFixedFunction) */

    #if (simulatedForce_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        simulatedForce_CONTROL |= simulatedForce_CFG0_MODE;
        #if (simulatedForce_DeadBand2_4)
            simulatedForce_CONTROL |= simulatedForce_CFG0_DB;
        #endif /* (simulatedForce_DeadBand2_4) */

        ctrl = simulatedForce_CONTROL3 & ((uint8 )(~simulatedForce_CTRL_CMPMODE1_MASK));
        simulatedForce_CONTROL3 = ctrl | simulatedForce_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        simulatedForce_RT1 &= ((uint8)(~simulatedForce_RT1_MASK));
        simulatedForce_RT1 |= simulatedForce_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        simulatedForce_RT1 &= ((uint8)(~simulatedForce_SYNCDSI_MASK));
        simulatedForce_RT1 |= simulatedForce_SYNCDSI_EN;

    #elif (simulatedForce_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = simulatedForce_CONTROL & ((uint8)(~simulatedForce_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~simulatedForce_CTRL_CMPMODE1_MASK));
        simulatedForce_CONTROL = ctrl | simulatedForce_DEFAULT_COMPARE2_MODE |
                                   simulatedForce_DEFAULT_COMPARE1_MODE;
    #endif /* (simulatedForce_UsingFixedFunction) */

    #if (!simulatedForce_UsingFixedFunction)
        #if (simulatedForce_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            simulatedForce_AUX_CONTROLDP0 |= (simulatedForce_AUX_CTRL_FIFO0_CLR);
        #else /* (simulatedForce_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            simulatedForce_AUX_CONTROLDP0 |= (simulatedForce_AUX_CTRL_FIFO0_CLR);
            simulatedForce_AUX_CONTROLDP1 |= (simulatedForce_AUX_CTRL_FIFO0_CLR);
        #endif /* (simulatedForce_Resolution == 8) */

        simulatedForce_WriteCounter(simulatedForce_INIT_PERIOD_VALUE);
    #endif /* (!simulatedForce_UsingFixedFunction) */

    simulatedForce_WritePeriod(simulatedForce_INIT_PERIOD_VALUE);

        #if (simulatedForce_UseOneCompareMode)
            simulatedForce_WriteCompare(simulatedForce_INIT_COMPARE_VALUE1);
        #else
            simulatedForce_WriteCompare1(simulatedForce_INIT_COMPARE_VALUE1);
            simulatedForce_WriteCompare2(simulatedForce_INIT_COMPARE_VALUE2);
        #endif /* (simulatedForce_UseOneCompareMode) */

        #if (simulatedForce_KillModeMinTime)
            simulatedForce_WriteKillTime(simulatedForce_MinimumKillTime);
        #endif /* (simulatedForce_KillModeMinTime) */

        #if (simulatedForce_DeadBandUsed)
            simulatedForce_WriteDeadTime(simulatedForce_INIT_DEAD_TIME);
        #endif /* (simulatedForce_DeadBandUsed) */

    #if (simulatedForce_UseStatus || simulatedForce_UsingFixedFunction)
        simulatedForce_SetInterruptMode(simulatedForce_INIT_INTERRUPTS_MODE);
    #endif /* (simulatedForce_UseStatus || simulatedForce_UsingFixedFunction) */

    #if (simulatedForce_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        simulatedForce_GLOBAL_ENABLE |= simulatedForce_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        simulatedForce_CONTROL2 |= simulatedForce_CTRL2_IRQ_SEL;
    #else
        #if(simulatedForce_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            simulatedForce_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            simulatedForce_STATUS_AUX_CTRL |= simulatedForce_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(simulatedForce_interruptState);

            /* Clear the FIFO to enable the simulatedForce_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            simulatedForce_ClearFIFO();
        #endif /* (simulatedForce_UseStatus) */
    #endif /* (simulatedForce_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: simulatedForce_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void simulatedForce_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (simulatedForce_UsingFixedFunction)
        simulatedForce_GLOBAL_ENABLE |= simulatedForce_BLOCK_EN_MASK;
        simulatedForce_GLOBAL_STBY_ENABLE |= simulatedForce_BLOCK_STBY_EN_MASK;
    #endif /* (simulatedForce_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (simulatedForce_UseControl || simulatedForce_UsingFixedFunction)
        simulatedForce_CONTROL |= simulatedForce_CTRL_ENABLE;
    #endif /* (simulatedForce_UseControl || simulatedForce_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: simulatedForce_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void simulatedForce_Stop(void) 
{
    #if (simulatedForce_UseControl || simulatedForce_UsingFixedFunction)
        simulatedForce_CONTROL &= ((uint8)(~simulatedForce_CTRL_ENABLE));
    #endif /* (simulatedForce_UseControl || simulatedForce_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (simulatedForce_UsingFixedFunction)
        simulatedForce_GLOBAL_ENABLE &= ((uint8)(~simulatedForce_BLOCK_EN_MASK));
        simulatedForce_GLOBAL_STBY_ENABLE &= ((uint8)(~simulatedForce_BLOCK_STBY_EN_MASK));
    #endif /* (simulatedForce_UsingFixedFunction) */
}

#if (simulatedForce_UseOneCompareMode)
    #if (simulatedForce_CompareMode1SW)


        /*******************************************************************************
        * Function Name: simulatedForce_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void simulatedForce_SetCompareMode(uint8 comparemode) 
        {
            #if(simulatedForce_UsingFixedFunction)

                #if(0 != simulatedForce_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << simulatedForce_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != simulatedForce_CTRL_CMPMODE1_SHIFT) */

                simulatedForce_CONTROL3 &= ((uint8)(~simulatedForce_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                simulatedForce_CONTROL3 |= comparemodemasked;

            #elif (simulatedForce_UseControl)

                #if(0 != simulatedForce_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << simulatedForce_CTRL_CMPMODE1_SHIFT)) &
                                                simulatedForce_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & simulatedForce_CTRL_CMPMODE1_MASK;
                #endif /* (0 != simulatedForce_CTRL_CMPMODE1_SHIFT) */

                #if(0 != simulatedForce_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << simulatedForce_CTRL_CMPMODE2_SHIFT)) &
                                               simulatedForce_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & simulatedForce_CTRL_CMPMODE2_MASK;
                #endif /* (0 != simulatedForce_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                simulatedForce_CONTROL &= ((uint8)(~(simulatedForce_CTRL_CMPMODE1_MASK |
                                            simulatedForce_CTRL_CMPMODE2_MASK)));
                simulatedForce_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (simulatedForce_UsingFixedFunction) */
        }
    #endif /* simulatedForce_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (simulatedForce_CompareMode1SW)


        /*******************************************************************************
        * Function Name: simulatedForce_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void simulatedForce_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != simulatedForce_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << simulatedForce_CTRL_CMPMODE1_SHIFT)) &
                                           simulatedForce_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & simulatedForce_CTRL_CMPMODE1_MASK;
            #endif /* (0 != simulatedForce_CTRL_CMPMODE1_SHIFT) */

            #if (simulatedForce_UseControl)
                simulatedForce_CONTROL &= ((uint8)(~simulatedForce_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                simulatedForce_CONTROL |= comparemodemasked;
            #endif /* (simulatedForce_UseControl) */
        }
    #endif /* simulatedForce_CompareMode1SW */

#if (simulatedForce_CompareMode2SW)


    /*******************************************************************************
    * Function Name: simulatedForce_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != simulatedForce_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << simulatedForce_CTRL_CMPMODE2_SHIFT)) &
                                                 simulatedForce_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & simulatedForce_CTRL_CMPMODE2_MASK;
        #endif /* (0 != simulatedForce_CTRL_CMPMODE2_SHIFT) */

        #if (simulatedForce_UseControl)
            simulatedForce_CONTROL &= ((uint8)(~simulatedForce_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            simulatedForce_CONTROL |= comparemodemasked;
        #endif /* (simulatedForce_UseControl) */
    }
    #endif /*simulatedForce_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!simulatedForce_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: simulatedForce_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void simulatedForce_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(simulatedForce_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: simulatedForce_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 simulatedForce_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(simulatedForce_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(simulatedForce_CAPTURE_LSB_PTR));
    }

    #if (simulatedForce_UseStatus)


        /*******************************************************************************
        * Function Name: simulatedForce_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void simulatedForce_ClearFIFO(void) 
        {
            while(0u != (simulatedForce_ReadStatusRegister() & simulatedForce_STATUS_FIFONEMPTY))
            {
                (void)simulatedForce_ReadCapture();
            }
        }

    #endif /* simulatedForce_UseStatus */

#endif /* !simulatedForce_UsingFixedFunction */


/*******************************************************************************
* Function Name: simulatedForce_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void simulatedForce_WritePeriod(uint16 period) 
{
    #if(simulatedForce_UsingFixedFunction)
        CY_SET_REG16(simulatedForce_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(simulatedForce_PERIOD_LSB_PTR, period);
    #endif /* (simulatedForce_UsingFixedFunction) */
}

#if (simulatedForce_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: simulatedForce_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void simulatedForce_WriteCompare(uint16 compare) \
                                       
    {
        #if(simulatedForce_UsingFixedFunction)
            CY_SET_REG16(simulatedForce_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(simulatedForce_COMPARE1_LSB_PTR, compare);
        #endif /* (simulatedForce_UsingFixedFunction) */

        #if (simulatedForce_PWMMode == simulatedForce__B_PWM__DITHER)
            #if(simulatedForce_UsingFixedFunction)
                CY_SET_REG16(simulatedForce_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(simulatedForce_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (simulatedForce_UsingFixedFunction) */
        #endif /* (simulatedForce_PWMMode == simulatedForce__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: simulatedForce_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_WriteCompare1(uint16 compare) \
                                        
    {
        #if(simulatedForce_UsingFixedFunction)
            CY_SET_REG16(simulatedForce_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(simulatedForce_COMPARE1_LSB_PTR, compare);
        #endif /* (simulatedForce_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: simulatedForce_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_WriteCompare2(uint16 compare) \
                                        
    {
        #if(simulatedForce_UsingFixedFunction)
            CY_SET_REG16(simulatedForce_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(simulatedForce_COMPARE2_LSB_PTR, compare);
        #endif /* (simulatedForce_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (simulatedForce_DeadBandUsed)


    /*******************************************************************************
    * Function Name: simulatedForce_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!simulatedForce_DeadBand2_4)
            CY_SET_REG8(simulatedForce_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            simulatedForce_DEADBAND_COUNT &= ((uint8)(~simulatedForce_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(simulatedForce_DEADBAND_COUNT_SHIFT)
                simulatedForce_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << simulatedForce_DEADBAND_COUNT_SHIFT)) &
                                                    simulatedForce_DEADBAND_COUNT_MASK;
            #else
                simulatedForce_DEADBAND_COUNT |= deadtime & simulatedForce_DEADBAND_COUNT_MASK;
            #endif /* (simulatedForce_DEADBAND_COUNT_SHIFT) */

        #endif /* (!simulatedForce_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: simulatedForce_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 simulatedForce_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!simulatedForce_DeadBand2_4)
            return (CY_GET_REG8(simulatedForce_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(simulatedForce_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(simulatedForce_DEADBAND_COUNT & simulatedForce_DEADBAND_COUNT_MASK)) >>
                                                                           simulatedForce_DEADBAND_COUNT_SHIFT));
            #else
                return (simulatedForce_DEADBAND_COUNT & simulatedForce_DEADBAND_COUNT_MASK);
            #endif /* (simulatedForce_DEADBAND_COUNT_SHIFT) */
        #endif /* (!simulatedForce_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (simulatedForce_UseStatus || simulatedForce_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: simulatedForce_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(simulatedForce_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: simulatedForce_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 simulatedForce_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(simulatedForce_STATUS_PTR));
    }

#endif /* (simulatedForce_UseStatus || simulatedForce_UsingFixedFunction) */


#if (simulatedForce_UseControl)


    /*******************************************************************************
    * Function Name: simulatedForce_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 simulatedForce_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(simulatedForce_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: simulatedForce_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(simulatedForce_CONTROL_PTR, control);
    }

#endif /* (simulatedForce_UseControl) */


#if (!simulatedForce_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: simulatedForce_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 simulatedForce_ReadCapture(void) 
    {
        return (CY_GET_REG16(simulatedForce_CAPTURE_LSB_PTR));
    }

#endif /* (!simulatedForce_UsingFixedFunction) */


#if (simulatedForce_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: simulatedForce_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 simulatedForce_ReadCompare(void) 
    {
        #if(simulatedForce_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(simulatedForce_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(simulatedForce_COMPARE1_LSB_PTR));
        #endif /* (simulatedForce_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: simulatedForce_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 simulatedForce_ReadCompare1(void) 
    {
        return (CY_GET_REG16(simulatedForce_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: simulatedForce_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 simulatedForce_ReadCompare2(void) 
    {
        return (CY_GET_REG16(simulatedForce_COMPARE2_LSB_PTR));
    }

#endif /* (simulatedForce_UseOneCompareMode) */


/*******************************************************************************
* Function Name: simulatedForce_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 simulatedForce_ReadPeriod(void) 
{
    #if(simulatedForce_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(simulatedForce_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(simulatedForce_PERIOD_LSB_PTR));
    #endif /* (simulatedForce_UsingFixedFunction) */
}

#if ( simulatedForce_KillModeMinTime)


    /*******************************************************************************
    * Function Name: simulatedForce_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void simulatedForce_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(simulatedForce_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: simulatedForce_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 simulatedForce_ReadKillTime(void) 
    {
        return (CY_GET_REG8(simulatedForce_KILLMODEMINTIME_PTR));
    }

#endif /* ( simulatedForce_KillModeMinTime) */

/* [] END OF FILE */
