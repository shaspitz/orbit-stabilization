/*******************************************************************************
* File Name: StepperCount.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StepperCount.h"

uint8 StepperCount_initVar = 0u;


/*******************************************************************************
* Function Name: StepperCount_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void StepperCount_Init(void) 
{
        #if (!StepperCount_UsingFixedFunction && !StepperCount_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!StepperCount_UsingFixedFunction && !StepperCount_ControlRegRemoved) */
        
        #if(!StepperCount_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 StepperCount_interruptState;
        #endif /* (!StepperCount_UsingFixedFunction) */
        
        #if (StepperCount_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            StepperCount_CONTROL &= StepperCount_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                StepperCount_CONTROL2 &= ((uint8)(~StepperCount_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                StepperCount_CONTROL3 &= ((uint8)(~StepperCount_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (StepperCount_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                StepperCount_CONTROL |= StepperCount_ONESHOT;
            #endif /* (StepperCount_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            StepperCount_CONTROL2 |= StepperCount_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            StepperCount_RT1 &= ((uint8)(~StepperCount_RT1_MASK));
            StepperCount_RT1 |= StepperCount_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            StepperCount_RT1 &= ((uint8)(~StepperCount_SYNCDSI_MASK));
            StepperCount_RT1 |= StepperCount_SYNCDSI_EN;

        #else
            #if(!StepperCount_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = StepperCount_CONTROL & ((uint8)(~StepperCount_CTRL_CMPMODE_MASK));
            StepperCount_CONTROL = ctrl | StepperCount_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = StepperCount_CONTROL & ((uint8)(~StepperCount_CTRL_CAPMODE_MASK));
            
            #if( 0 != StepperCount_CAPTURE_MODE_CONF)
                StepperCount_CONTROL = ctrl | StepperCount_DEFAULT_CAPTURE_MODE;
            #else
                StepperCount_CONTROL = ctrl;
            #endif /* 0 != StepperCount_CAPTURE_MODE */ 
            
            #endif /* (!StepperCount_ControlRegRemoved) */
        #endif /* (StepperCount_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!StepperCount_UsingFixedFunction)
            StepperCount_ClearFIFO();
        #endif /* (!StepperCount_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        StepperCount_WritePeriod(StepperCount_INIT_PERIOD_VALUE);
        #if (!(StepperCount_UsingFixedFunction && (CY_PSOC5A)))
            StepperCount_WriteCounter(StepperCount_INIT_COUNTER_VALUE);
        #endif /* (!(StepperCount_UsingFixedFunction && (CY_PSOC5A))) */
        StepperCount_SetInterruptMode(StepperCount_INIT_INTERRUPTS_MASK);
        
        #if (!StepperCount_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)StepperCount_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            StepperCount_WriteCompare(StepperCount_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            StepperCount_interruptState = CyEnterCriticalSection();
            
            StepperCount_STATUS_AUX_CTRL |= StepperCount_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(StepperCount_interruptState);
            
        #endif /* (!StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void StepperCount_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (StepperCount_UsingFixedFunction)
        StepperCount_GLOBAL_ENABLE |= StepperCount_BLOCK_EN_MASK;
        StepperCount_GLOBAL_STBY_ENABLE |= StepperCount_BLOCK_STBY_EN_MASK;
    #endif /* (StepperCount_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!StepperCount_ControlRegRemoved || StepperCount_UsingFixedFunction)
        StepperCount_CONTROL |= StepperCount_CTRL_ENABLE;                
    #endif /* (!StepperCount_ControlRegRemoved || StepperCount_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: StepperCount_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  StepperCount_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void StepperCount_Start(void) 
{
    if(StepperCount_initVar == 0u)
    {
        StepperCount_Init();
        
        StepperCount_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    StepperCount_Enable();        
}


/*******************************************************************************
* Function Name: StepperCount_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void StepperCount_Stop(void) 
{
    /* Disable Counter */
    #if(!StepperCount_ControlRegRemoved || StepperCount_UsingFixedFunction)
        StepperCount_CONTROL &= ((uint8)(~StepperCount_CTRL_ENABLE));        
    #endif /* (!StepperCount_ControlRegRemoved || StepperCount_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (StepperCount_UsingFixedFunction)
        StepperCount_GLOBAL_ENABLE &= ((uint8)(~StepperCount_BLOCK_EN_MASK));
        StepperCount_GLOBAL_STBY_ENABLE &= ((uint8)(~StepperCount_BLOCK_STBY_EN_MASK));
    #endif /* (StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void StepperCount_SetInterruptMode(uint8 interruptsMask) 
{
    StepperCount_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: StepperCount_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   StepperCount_ReadStatusRegister(void) 
{
    return StepperCount_STATUS;
}


#if(!StepperCount_ControlRegRemoved)
/*******************************************************************************
* Function Name: StepperCount_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   StepperCount_ReadControlRegister(void) 
{
    return StepperCount_CONTROL;
}


/*******************************************************************************
* Function Name: StepperCount_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    StepperCount_WriteControlRegister(uint8 control) 
{
    StepperCount_CONTROL = control;
}

#endif  /* (!StepperCount_ControlRegRemoved) */


#if (!(StepperCount_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: StepperCount_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void StepperCount_WriteCounter(uint32 counter) \
                                   
{
    #if(StepperCount_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (StepperCount_GLOBAL_ENABLE & StepperCount_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        StepperCount_GLOBAL_ENABLE |= StepperCount_BLOCK_EN_MASK;
        CY_SET_REG16(StepperCount_COUNTER_LSB_PTR, (uint16)counter);
        StepperCount_GLOBAL_ENABLE &= ((uint8)(~StepperCount_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(StepperCount_COUNTER_LSB_PTR, counter);
    #endif /* (StepperCount_UsingFixedFunction) */
}
#endif /* (!(StepperCount_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: StepperCount_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 StepperCount_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(StepperCount_UsingFixedFunction)
		(void)CY_GET_REG16(StepperCount_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(StepperCount_COUNTER_LSB_PTR_8BIT);
	#endif/* (StepperCount_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(StepperCount_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(StepperCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(StepperCount_STATICCOUNT_LSB_PTR));
    #endif /* (StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 StepperCount_ReadCapture(void) 
{
    #if(StepperCount_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(StepperCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(StepperCount_STATICCOUNT_LSB_PTR));
    #endif /* (StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void StepperCount_WritePeriod(uint32 period) 
{
    #if(StepperCount_UsingFixedFunction)
        CY_SET_REG16(StepperCount_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(StepperCount_PERIOD_LSB_PTR, period);
    #endif /* (StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 StepperCount_ReadPeriod(void) 
{
    #if(StepperCount_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(StepperCount_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(StepperCount_PERIOD_LSB_PTR));
    #endif /* (StepperCount_UsingFixedFunction) */
}


#if (!StepperCount_UsingFixedFunction)
/*******************************************************************************
* Function Name: StepperCount_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void StepperCount_WriteCompare(uint32 compare) \
                                   
{
    #if(StepperCount_UsingFixedFunction)
        CY_SET_REG16(StepperCount_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(StepperCount_COMPARE_LSB_PTR, compare);
    #endif /* (StepperCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: StepperCount_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 StepperCount_ReadCompare(void) 
{
    return (CY_GET_REG32(StepperCount_COMPARE_LSB_PTR));
}


#if (StepperCount_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: StepperCount_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void StepperCount_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    StepperCount_CONTROL &= ((uint8)(~StepperCount_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    StepperCount_CONTROL |= compareMode;
}
#endif  /* (StepperCount_COMPARE_MODE_SOFTWARE) */


#if (StepperCount_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: StepperCount_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void StepperCount_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    StepperCount_CONTROL &= ((uint8)(~StepperCount_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    StepperCount_CONTROL |= ((uint8)((uint8)captureMode << StepperCount_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (StepperCount_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: StepperCount_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void StepperCount_ClearFIFO(void) 
{

    while(0u != (StepperCount_ReadStatusRegister() & StepperCount_STATUS_FIFONEMP))
    {
        (void)StepperCount_ReadCapture();
    }

}
#endif  /* (!StepperCount_UsingFixedFunction) */


/* [] END OF FILE */

