/*******************************************************************************
* File Name: ByteCounter.c  
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

#include "ByteCounter.h"

uint8 ByteCounter_initVar = 0u;


/*******************************************************************************
* Function Name: ByteCounter_Init
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
void ByteCounter_Init(void) 
{
        #if (!ByteCounter_UsingFixedFunction && !ByteCounter_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!ByteCounter_UsingFixedFunction && !ByteCounter_ControlRegRemoved) */
        
        #if(!ByteCounter_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 ByteCounter_interruptState;
        #endif /* (!ByteCounter_UsingFixedFunction) */
        
        #if (ByteCounter_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            ByteCounter_CONTROL &= ByteCounter_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                ByteCounter_CONTROL2 &= ((uint8)(~ByteCounter_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                ByteCounter_CONTROL3 &= ((uint8)(~ByteCounter_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (ByteCounter_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                ByteCounter_CONTROL |= ByteCounter_ONESHOT;
            #endif /* (ByteCounter_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            ByteCounter_CONTROL2 |= ByteCounter_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            ByteCounter_RT1 &= ((uint8)(~ByteCounter_RT1_MASK));
            ByteCounter_RT1 |= ByteCounter_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            ByteCounter_RT1 &= ((uint8)(~ByteCounter_SYNCDSI_MASK));
            ByteCounter_RT1 |= ByteCounter_SYNCDSI_EN;

        #else
            #if(!ByteCounter_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = ByteCounter_CONTROL & ((uint8)(~ByteCounter_CTRL_CMPMODE_MASK));
            ByteCounter_CONTROL = ctrl | ByteCounter_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = ByteCounter_CONTROL & ((uint8)(~ByteCounter_CTRL_CAPMODE_MASK));
            
            #if( 0 != ByteCounter_CAPTURE_MODE_CONF)
                ByteCounter_CONTROL = ctrl | ByteCounter_DEFAULT_CAPTURE_MODE;
            #else
                ByteCounter_CONTROL = ctrl;
            #endif /* 0 != ByteCounter_CAPTURE_MODE */ 
            
            #endif /* (!ByteCounter_ControlRegRemoved) */
        #endif /* (ByteCounter_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!ByteCounter_UsingFixedFunction)
            ByteCounter_ClearFIFO();
        #endif /* (!ByteCounter_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        ByteCounter_WritePeriod(ByteCounter_INIT_PERIOD_VALUE);
        #if (!(ByteCounter_UsingFixedFunction && (CY_PSOC5A)))
            ByteCounter_WriteCounter(ByteCounter_INIT_COUNTER_VALUE);
        #endif /* (!(ByteCounter_UsingFixedFunction && (CY_PSOC5A))) */
        ByteCounter_SetInterruptMode(ByteCounter_INIT_INTERRUPTS_MASK);
        
        #if (!ByteCounter_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)ByteCounter_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            ByteCounter_WriteCompare(ByteCounter_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            ByteCounter_interruptState = CyEnterCriticalSection();
            
            ByteCounter_STATUS_AUX_CTRL |= ByteCounter_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(ByteCounter_interruptState);
            
        #endif /* (!ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_Enable
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
void ByteCounter_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (ByteCounter_UsingFixedFunction)
        ByteCounter_GLOBAL_ENABLE |= ByteCounter_BLOCK_EN_MASK;
        ByteCounter_GLOBAL_STBY_ENABLE |= ByteCounter_BLOCK_STBY_EN_MASK;
    #endif /* (ByteCounter_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!ByteCounter_ControlRegRemoved || ByteCounter_UsingFixedFunction)
        ByteCounter_CONTROL |= ByteCounter_CTRL_ENABLE;                
    #endif /* (!ByteCounter_ControlRegRemoved || ByteCounter_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: ByteCounter_Start
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
*  ByteCounter_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void ByteCounter_Start(void) 
{
    if(ByteCounter_initVar == 0u)
    {
        ByteCounter_Init();
        
        ByteCounter_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    ByteCounter_Enable();        
}


/*******************************************************************************
* Function Name: ByteCounter_Stop
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
void ByteCounter_Stop(void) 
{
    /* Disable Counter */
    #if(!ByteCounter_ControlRegRemoved || ByteCounter_UsingFixedFunction)
        ByteCounter_CONTROL &= ((uint8)(~ByteCounter_CTRL_ENABLE));        
    #endif /* (!ByteCounter_ControlRegRemoved || ByteCounter_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (ByteCounter_UsingFixedFunction)
        ByteCounter_GLOBAL_ENABLE &= ((uint8)(~ByteCounter_BLOCK_EN_MASK));
        ByteCounter_GLOBAL_STBY_ENABLE &= ((uint8)(~ByteCounter_BLOCK_STBY_EN_MASK));
    #endif /* (ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_SetInterruptMode
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
void ByteCounter_SetInterruptMode(uint8 interruptsMask) 
{
    ByteCounter_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: ByteCounter_ReadStatusRegister
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
uint8   ByteCounter_ReadStatusRegister(void) 
{
    return ByteCounter_STATUS;
}


#if(!ByteCounter_ControlRegRemoved)
/*******************************************************************************
* Function Name: ByteCounter_ReadControlRegister
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
uint8   ByteCounter_ReadControlRegister(void) 
{
    return ByteCounter_CONTROL;
}


/*******************************************************************************
* Function Name: ByteCounter_WriteControlRegister
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
void    ByteCounter_WriteControlRegister(uint8 control) 
{
    ByteCounter_CONTROL = control;
}

#endif  /* (!ByteCounter_ControlRegRemoved) */


#if (!(ByteCounter_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: ByteCounter_WriteCounter
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
void ByteCounter_WriteCounter(uint8 counter) \
                                   
{
    #if(ByteCounter_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (ByteCounter_GLOBAL_ENABLE & ByteCounter_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        ByteCounter_GLOBAL_ENABLE |= ByteCounter_BLOCK_EN_MASK;
        CY_SET_REG16(ByteCounter_COUNTER_LSB_PTR, (uint16)counter);
        ByteCounter_GLOBAL_ENABLE &= ((uint8)(~ByteCounter_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(ByteCounter_COUNTER_LSB_PTR, counter);
    #endif /* (ByteCounter_UsingFixedFunction) */
}
#endif /* (!(ByteCounter_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: ByteCounter_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 ByteCounter_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(ByteCounter_UsingFixedFunction)
		(void)CY_GET_REG16(ByteCounter_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(ByteCounter_COUNTER_LSB_PTR_8BIT);
	#endif/* (ByteCounter_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(ByteCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 ByteCounter_ReadCapture(void) 
{
    #if(ByteCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCounter_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCounter_STATICCOUNT_LSB_PTR));
    #endif /* (ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void ByteCounter_WritePeriod(uint8 period) 
{
    #if(ByteCounter_UsingFixedFunction)
        CY_SET_REG16(ByteCounter_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(ByteCounter_PERIOD_LSB_PTR, period);
    #endif /* (ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 ByteCounter_ReadPeriod(void) 
{
    #if(ByteCounter_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(ByteCounter_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(ByteCounter_PERIOD_LSB_PTR));
    #endif /* (ByteCounter_UsingFixedFunction) */
}


#if (!ByteCounter_UsingFixedFunction)
/*******************************************************************************
* Function Name: ByteCounter_WriteCompare
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
void ByteCounter_WriteCompare(uint8 compare) \
                                   
{
    #if(ByteCounter_UsingFixedFunction)
        CY_SET_REG16(ByteCounter_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(ByteCounter_COMPARE_LSB_PTR, compare);
    #endif /* (ByteCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ByteCounter_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 ByteCounter_ReadCompare(void) 
{
    return (CY_GET_REG8(ByteCounter_COMPARE_LSB_PTR));
}


#if (ByteCounter_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ByteCounter_SetCompareMode
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
void ByteCounter_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    ByteCounter_CONTROL &= ((uint8)(~ByteCounter_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    ByteCounter_CONTROL |= compareMode;
}
#endif  /* (ByteCounter_COMPARE_MODE_SOFTWARE) */


#if (ByteCounter_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: ByteCounter_SetCaptureMode
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
void ByteCounter_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    ByteCounter_CONTROL &= ((uint8)(~ByteCounter_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    ByteCounter_CONTROL |= ((uint8)((uint8)captureMode << ByteCounter_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (ByteCounter_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: ByteCounter_ClearFIFO
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
void ByteCounter_ClearFIFO(void) 
{

    while(0u != (ByteCounter_ReadStatusRegister() & ByteCounter_STATUS_FIFONEMP))
    {
        (void)ByteCounter_ReadCapture();
    }

}
#endif  /* (!ByteCounter_UsingFixedFunction) */


/* [] END OF FILE */

