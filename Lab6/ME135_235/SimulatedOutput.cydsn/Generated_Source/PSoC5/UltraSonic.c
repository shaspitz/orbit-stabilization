/*******************************************************************************
* File Name: UltraSonic.c
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

#include "UltraSonic.h"

/* Error message for removed <resource> through optimization */
#ifdef UltraSonic_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* UltraSonic_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 UltraSonic_initVar = 0u;


/*******************************************************************************
* Function Name: UltraSonic_Start
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
*  UltraSonic_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void UltraSonic_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(UltraSonic_initVar == 0u)
    {
        UltraSonic_Init();
        UltraSonic_initVar = 1u;
    }
    UltraSonic_Enable();

}


/*******************************************************************************
* Function Name: UltraSonic_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  UltraSonic_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UltraSonic_Init(void) 
{
    #if (UltraSonic_UsingFixedFunction || UltraSonic_UseControl)
        uint8 ctrl;
    #endif /* (UltraSonic_UsingFixedFunction || UltraSonic_UseControl) */

    #if(!UltraSonic_UsingFixedFunction)
        #if(UltraSonic_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 UltraSonic_interruptState;
        #endif /* (UltraSonic_UseStatus) */
    #endif /* (!UltraSonic_UsingFixedFunction) */

    #if (UltraSonic_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        UltraSonic_CONTROL |= UltraSonic_CFG0_MODE;
        #if (UltraSonic_DeadBand2_4)
            UltraSonic_CONTROL |= UltraSonic_CFG0_DB;
        #endif /* (UltraSonic_DeadBand2_4) */

        ctrl = UltraSonic_CONTROL3 & ((uint8 )(~UltraSonic_CTRL_CMPMODE1_MASK));
        UltraSonic_CONTROL3 = ctrl | UltraSonic_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        UltraSonic_RT1 &= ((uint8)(~UltraSonic_RT1_MASK));
        UltraSonic_RT1 |= UltraSonic_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        UltraSonic_RT1 &= ((uint8)(~UltraSonic_SYNCDSI_MASK));
        UltraSonic_RT1 |= UltraSonic_SYNCDSI_EN;

    #elif (UltraSonic_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = UltraSonic_CONTROL & ((uint8)(~UltraSonic_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~UltraSonic_CTRL_CMPMODE1_MASK));
        UltraSonic_CONTROL = ctrl | UltraSonic_DEFAULT_COMPARE2_MODE |
                                   UltraSonic_DEFAULT_COMPARE1_MODE;
    #endif /* (UltraSonic_UsingFixedFunction) */

    #if (!UltraSonic_UsingFixedFunction)
        #if (UltraSonic_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            UltraSonic_AUX_CONTROLDP0 |= (UltraSonic_AUX_CTRL_FIFO0_CLR);
        #else /* (UltraSonic_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            UltraSonic_AUX_CONTROLDP0 |= (UltraSonic_AUX_CTRL_FIFO0_CLR);
            UltraSonic_AUX_CONTROLDP1 |= (UltraSonic_AUX_CTRL_FIFO0_CLR);
        #endif /* (UltraSonic_Resolution == 8) */

        UltraSonic_WriteCounter(UltraSonic_INIT_PERIOD_VALUE);
    #endif /* (!UltraSonic_UsingFixedFunction) */

    UltraSonic_WritePeriod(UltraSonic_INIT_PERIOD_VALUE);

        #if (UltraSonic_UseOneCompareMode)
            UltraSonic_WriteCompare(UltraSonic_INIT_COMPARE_VALUE1);
        #else
            UltraSonic_WriteCompare1(UltraSonic_INIT_COMPARE_VALUE1);
            UltraSonic_WriteCompare2(UltraSonic_INIT_COMPARE_VALUE2);
        #endif /* (UltraSonic_UseOneCompareMode) */

        #if (UltraSonic_KillModeMinTime)
            UltraSonic_WriteKillTime(UltraSonic_MinimumKillTime);
        #endif /* (UltraSonic_KillModeMinTime) */

        #if (UltraSonic_DeadBandUsed)
            UltraSonic_WriteDeadTime(UltraSonic_INIT_DEAD_TIME);
        #endif /* (UltraSonic_DeadBandUsed) */

    #if (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction)
        UltraSonic_SetInterruptMode(UltraSonic_INIT_INTERRUPTS_MODE);
    #endif /* (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction) */

    #if (UltraSonic_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        UltraSonic_GLOBAL_ENABLE |= UltraSonic_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        UltraSonic_CONTROL2 |= UltraSonic_CTRL2_IRQ_SEL;
    #else
        #if(UltraSonic_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            UltraSonic_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            UltraSonic_STATUS_AUX_CTRL |= UltraSonic_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(UltraSonic_interruptState);

            /* Clear the FIFO to enable the UltraSonic_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            UltraSonic_ClearFIFO();
        #endif /* (UltraSonic_UseStatus) */
    #endif /* (UltraSonic_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: UltraSonic_Enable
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
void UltraSonic_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (UltraSonic_UsingFixedFunction)
        UltraSonic_GLOBAL_ENABLE |= UltraSonic_BLOCK_EN_MASK;
        UltraSonic_GLOBAL_STBY_ENABLE |= UltraSonic_BLOCK_STBY_EN_MASK;
    #endif /* (UltraSonic_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (UltraSonic_UseControl || UltraSonic_UsingFixedFunction)
        UltraSonic_CONTROL |= UltraSonic_CTRL_ENABLE;
    #endif /* (UltraSonic_UseControl || UltraSonic_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: UltraSonic_Stop
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
void UltraSonic_Stop(void) 
{
    #if (UltraSonic_UseControl || UltraSonic_UsingFixedFunction)
        UltraSonic_CONTROL &= ((uint8)(~UltraSonic_CTRL_ENABLE));
    #endif /* (UltraSonic_UseControl || UltraSonic_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (UltraSonic_UsingFixedFunction)
        UltraSonic_GLOBAL_ENABLE &= ((uint8)(~UltraSonic_BLOCK_EN_MASK));
        UltraSonic_GLOBAL_STBY_ENABLE &= ((uint8)(~UltraSonic_BLOCK_STBY_EN_MASK));
    #endif /* (UltraSonic_UsingFixedFunction) */
}

#if (UltraSonic_UseOneCompareMode)
    #if (UltraSonic_CompareMode1SW)


        /*******************************************************************************
        * Function Name: UltraSonic_SetCompareMode
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
        void UltraSonic_SetCompareMode(uint8 comparemode) 
        {
            #if(UltraSonic_UsingFixedFunction)

                #if(0 != UltraSonic_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << UltraSonic_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != UltraSonic_CTRL_CMPMODE1_SHIFT) */

                UltraSonic_CONTROL3 &= ((uint8)(~UltraSonic_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                UltraSonic_CONTROL3 |= comparemodemasked;

            #elif (UltraSonic_UseControl)

                #if(0 != UltraSonic_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << UltraSonic_CTRL_CMPMODE1_SHIFT)) &
                                                UltraSonic_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & UltraSonic_CTRL_CMPMODE1_MASK;
                #endif /* (0 != UltraSonic_CTRL_CMPMODE1_SHIFT) */

                #if(0 != UltraSonic_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << UltraSonic_CTRL_CMPMODE2_SHIFT)) &
                                               UltraSonic_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & UltraSonic_CTRL_CMPMODE2_MASK;
                #endif /* (0 != UltraSonic_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                UltraSonic_CONTROL &= ((uint8)(~(UltraSonic_CTRL_CMPMODE1_MASK |
                                            UltraSonic_CTRL_CMPMODE2_MASK)));
                UltraSonic_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (UltraSonic_UsingFixedFunction) */
        }
    #endif /* UltraSonic_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (UltraSonic_CompareMode1SW)


        /*******************************************************************************
        * Function Name: UltraSonic_SetCompareMode1
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
        void UltraSonic_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != UltraSonic_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << UltraSonic_CTRL_CMPMODE1_SHIFT)) &
                                           UltraSonic_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & UltraSonic_CTRL_CMPMODE1_MASK;
            #endif /* (0 != UltraSonic_CTRL_CMPMODE1_SHIFT) */

            #if (UltraSonic_UseControl)
                UltraSonic_CONTROL &= ((uint8)(~UltraSonic_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                UltraSonic_CONTROL |= comparemodemasked;
            #endif /* (UltraSonic_UseControl) */
        }
    #endif /* UltraSonic_CompareMode1SW */

#if (UltraSonic_CompareMode2SW)


    /*******************************************************************************
    * Function Name: UltraSonic_SetCompareMode2
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
    void UltraSonic_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != UltraSonic_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << UltraSonic_CTRL_CMPMODE2_SHIFT)) &
                                                 UltraSonic_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & UltraSonic_CTRL_CMPMODE2_MASK;
        #endif /* (0 != UltraSonic_CTRL_CMPMODE2_SHIFT) */

        #if (UltraSonic_UseControl)
            UltraSonic_CONTROL &= ((uint8)(~UltraSonic_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            UltraSonic_CONTROL |= comparemodemasked;
        #endif /* (UltraSonic_UseControl) */
    }
    #endif /*UltraSonic_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!UltraSonic_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: UltraSonic_WriteCounter
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
    void UltraSonic_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(UltraSonic_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: UltraSonic_ReadCounter
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
    uint16 UltraSonic_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(UltraSonic_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(UltraSonic_CAPTURE_LSB_PTR));
    }

    #if (UltraSonic_UseStatus)


        /*******************************************************************************
        * Function Name: UltraSonic_ClearFIFO
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
        void UltraSonic_ClearFIFO(void) 
        {
            while(0u != (UltraSonic_ReadStatusRegister() & UltraSonic_STATUS_FIFONEMPTY))
            {
                (void)UltraSonic_ReadCapture();
            }
        }

    #endif /* UltraSonic_UseStatus */

#endif /* !UltraSonic_UsingFixedFunction */


/*******************************************************************************
* Function Name: UltraSonic_WritePeriod
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
void UltraSonic_WritePeriod(uint16 period) 
{
    #if(UltraSonic_UsingFixedFunction)
        CY_SET_REG16(UltraSonic_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(UltraSonic_PERIOD_LSB_PTR, period);
    #endif /* (UltraSonic_UsingFixedFunction) */
}

#if (UltraSonic_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: UltraSonic_WriteCompare
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
    void UltraSonic_WriteCompare(uint16 compare) \
                                       
    {
        #if(UltraSonic_UsingFixedFunction)
            CY_SET_REG16(UltraSonic_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(UltraSonic_COMPARE1_LSB_PTR, compare);
        #endif /* (UltraSonic_UsingFixedFunction) */

        #if (UltraSonic_PWMMode == UltraSonic__B_PWM__DITHER)
            #if(UltraSonic_UsingFixedFunction)
                CY_SET_REG16(UltraSonic_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(UltraSonic_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (UltraSonic_UsingFixedFunction) */
        #endif /* (UltraSonic_PWMMode == UltraSonic__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: UltraSonic_WriteCompare1
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
    void UltraSonic_WriteCompare1(uint16 compare) \
                                        
    {
        #if(UltraSonic_UsingFixedFunction)
            CY_SET_REG16(UltraSonic_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(UltraSonic_COMPARE1_LSB_PTR, compare);
        #endif /* (UltraSonic_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: UltraSonic_WriteCompare2
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
    void UltraSonic_WriteCompare2(uint16 compare) \
                                        
    {
        #if(UltraSonic_UsingFixedFunction)
            CY_SET_REG16(UltraSonic_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(UltraSonic_COMPARE2_LSB_PTR, compare);
        #endif /* (UltraSonic_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (UltraSonic_DeadBandUsed)


    /*******************************************************************************
    * Function Name: UltraSonic_WriteDeadTime
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
    void UltraSonic_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!UltraSonic_DeadBand2_4)
            CY_SET_REG8(UltraSonic_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            UltraSonic_DEADBAND_COUNT &= ((uint8)(~UltraSonic_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(UltraSonic_DEADBAND_COUNT_SHIFT)
                UltraSonic_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << UltraSonic_DEADBAND_COUNT_SHIFT)) &
                                                    UltraSonic_DEADBAND_COUNT_MASK;
            #else
                UltraSonic_DEADBAND_COUNT |= deadtime & UltraSonic_DEADBAND_COUNT_MASK;
            #endif /* (UltraSonic_DEADBAND_COUNT_SHIFT) */

        #endif /* (!UltraSonic_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: UltraSonic_ReadDeadTime
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
    uint8 UltraSonic_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!UltraSonic_DeadBand2_4)
            return (CY_GET_REG8(UltraSonic_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(UltraSonic_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(UltraSonic_DEADBAND_COUNT & UltraSonic_DEADBAND_COUNT_MASK)) >>
                                                                           UltraSonic_DEADBAND_COUNT_SHIFT));
            #else
                return (UltraSonic_DEADBAND_COUNT & UltraSonic_DEADBAND_COUNT_MASK);
            #endif /* (UltraSonic_DEADBAND_COUNT_SHIFT) */
        #endif /* (!UltraSonic_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: UltraSonic_SetInterruptMode
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
    void UltraSonic_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(UltraSonic_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: UltraSonic_ReadStatusRegister
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
    uint8 UltraSonic_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(UltraSonic_STATUS_PTR));
    }

#endif /* (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction) */


#if (UltraSonic_UseControl)


    /*******************************************************************************
    * Function Name: UltraSonic_ReadControlRegister
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
    uint8 UltraSonic_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(UltraSonic_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: UltraSonic_WriteControlRegister
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
    void UltraSonic_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(UltraSonic_CONTROL_PTR, control);
    }

#endif /* (UltraSonic_UseControl) */


#if (!UltraSonic_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: UltraSonic_ReadCapture
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
    uint16 UltraSonic_ReadCapture(void) 
    {
        return (CY_GET_REG16(UltraSonic_CAPTURE_LSB_PTR));
    }

#endif /* (!UltraSonic_UsingFixedFunction) */


#if (UltraSonic_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: UltraSonic_ReadCompare
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
    uint16 UltraSonic_ReadCompare(void) 
    {
        #if(UltraSonic_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(UltraSonic_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(UltraSonic_COMPARE1_LSB_PTR));
        #endif /* (UltraSonic_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: UltraSonic_ReadCompare1
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
    uint16 UltraSonic_ReadCompare1(void) 
    {
        return (CY_GET_REG16(UltraSonic_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: UltraSonic_ReadCompare2
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
    uint16 UltraSonic_ReadCompare2(void) 
    {
        return (CY_GET_REG16(UltraSonic_COMPARE2_LSB_PTR));
    }

#endif /* (UltraSonic_UseOneCompareMode) */


/*******************************************************************************
* Function Name: UltraSonic_ReadPeriod
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
uint16 UltraSonic_ReadPeriod(void) 
{
    #if(UltraSonic_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(UltraSonic_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(UltraSonic_PERIOD_LSB_PTR));
    #endif /* (UltraSonic_UsingFixedFunction) */
}

#if ( UltraSonic_KillModeMinTime)


    /*******************************************************************************
    * Function Name: UltraSonic_WriteKillTime
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
    void UltraSonic_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(UltraSonic_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: UltraSonic_ReadKillTime
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
    uint8 UltraSonic_ReadKillTime(void) 
    {
        return (CY_GET_REG8(UltraSonic_KILLMODEMINTIME_PTR));
    }

#endif /* ( UltraSonic_KillModeMinTime) */

/* [] END OF FILE */
