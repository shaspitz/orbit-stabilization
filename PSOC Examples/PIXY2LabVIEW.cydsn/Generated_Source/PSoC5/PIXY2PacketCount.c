/*******************************************************************************
* File Name: PIXY2PacketCount.c  
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

#include "PIXY2PacketCount.h"

uint8 PIXY2PacketCount_initVar = 0u;


/*******************************************************************************
* Function Name: PIXY2PacketCount_Init
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
void PIXY2PacketCount_Init(void) 
{
        #if (!PIXY2PacketCount_UsingFixedFunction && !PIXY2PacketCount_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!PIXY2PacketCount_UsingFixedFunction && !PIXY2PacketCount_ControlRegRemoved) */
        
        #if(!PIXY2PacketCount_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 PIXY2PacketCount_interruptState;
        #endif /* (!PIXY2PacketCount_UsingFixedFunction) */
        
        #if (PIXY2PacketCount_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            PIXY2PacketCount_CONTROL &= PIXY2PacketCount_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                PIXY2PacketCount_CONTROL2 &= ((uint8)(~PIXY2PacketCount_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                PIXY2PacketCount_CONTROL3 &= ((uint8)(~PIXY2PacketCount_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (PIXY2PacketCount_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                PIXY2PacketCount_CONTROL |= PIXY2PacketCount_ONESHOT;
            #endif /* (PIXY2PacketCount_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            PIXY2PacketCount_CONTROL2 |= PIXY2PacketCount_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            PIXY2PacketCount_RT1 &= ((uint8)(~PIXY2PacketCount_RT1_MASK));
            PIXY2PacketCount_RT1 |= PIXY2PacketCount_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            PIXY2PacketCount_RT1 &= ((uint8)(~PIXY2PacketCount_SYNCDSI_MASK));
            PIXY2PacketCount_RT1 |= PIXY2PacketCount_SYNCDSI_EN;

        #else
            #if(!PIXY2PacketCount_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = PIXY2PacketCount_CONTROL & ((uint8)(~PIXY2PacketCount_CTRL_CMPMODE_MASK));
            PIXY2PacketCount_CONTROL = ctrl | PIXY2PacketCount_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = PIXY2PacketCount_CONTROL & ((uint8)(~PIXY2PacketCount_CTRL_CAPMODE_MASK));
            
            #if( 0 != PIXY2PacketCount_CAPTURE_MODE_CONF)
                PIXY2PacketCount_CONTROL = ctrl | PIXY2PacketCount_DEFAULT_CAPTURE_MODE;
            #else
                PIXY2PacketCount_CONTROL = ctrl;
            #endif /* 0 != PIXY2PacketCount_CAPTURE_MODE */ 
            
            #endif /* (!PIXY2PacketCount_ControlRegRemoved) */
        #endif /* (PIXY2PacketCount_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!PIXY2PacketCount_UsingFixedFunction)
            PIXY2PacketCount_ClearFIFO();
        #endif /* (!PIXY2PacketCount_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        PIXY2PacketCount_WritePeriod(PIXY2PacketCount_INIT_PERIOD_VALUE);
        #if (!(PIXY2PacketCount_UsingFixedFunction && (CY_PSOC5A)))
            PIXY2PacketCount_WriteCounter(PIXY2PacketCount_INIT_COUNTER_VALUE);
        #endif /* (!(PIXY2PacketCount_UsingFixedFunction && (CY_PSOC5A))) */
        PIXY2PacketCount_SetInterruptMode(PIXY2PacketCount_INIT_INTERRUPTS_MASK);
        
        #if (!PIXY2PacketCount_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)PIXY2PacketCount_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            PIXY2PacketCount_WriteCompare(PIXY2PacketCount_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PIXY2PacketCount_interruptState = CyEnterCriticalSection();
            
            PIXY2PacketCount_STATUS_AUX_CTRL |= PIXY2PacketCount_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(PIXY2PacketCount_interruptState);
            
        #endif /* (!PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_Enable
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
void PIXY2PacketCount_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PIXY2PacketCount_UsingFixedFunction)
        PIXY2PacketCount_GLOBAL_ENABLE |= PIXY2PacketCount_BLOCK_EN_MASK;
        PIXY2PacketCount_GLOBAL_STBY_ENABLE |= PIXY2PacketCount_BLOCK_STBY_EN_MASK;
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!PIXY2PacketCount_ControlRegRemoved || PIXY2PacketCount_UsingFixedFunction)
        PIXY2PacketCount_CONTROL |= PIXY2PacketCount_CTRL_ENABLE;                
    #endif /* (!PIXY2PacketCount_ControlRegRemoved || PIXY2PacketCount_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_Start
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
*  PIXY2PacketCount_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PIXY2PacketCount_Start(void) 
{
    if(PIXY2PacketCount_initVar == 0u)
    {
        PIXY2PacketCount_Init();
        
        PIXY2PacketCount_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    PIXY2PacketCount_Enable();        
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_Stop
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
void PIXY2PacketCount_Stop(void) 
{
    /* Disable Counter */
    #if(!PIXY2PacketCount_ControlRegRemoved || PIXY2PacketCount_UsingFixedFunction)
        PIXY2PacketCount_CONTROL &= ((uint8)(~PIXY2PacketCount_CTRL_ENABLE));        
    #endif /* (!PIXY2PacketCount_ControlRegRemoved || PIXY2PacketCount_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (PIXY2PacketCount_UsingFixedFunction)
        PIXY2PacketCount_GLOBAL_ENABLE &= ((uint8)(~PIXY2PacketCount_BLOCK_EN_MASK));
        PIXY2PacketCount_GLOBAL_STBY_ENABLE &= ((uint8)(~PIXY2PacketCount_BLOCK_STBY_EN_MASK));
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_SetInterruptMode
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
void PIXY2PacketCount_SetInterruptMode(uint8 interruptsMask) 
{
    PIXY2PacketCount_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadStatusRegister
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
uint8   PIXY2PacketCount_ReadStatusRegister(void) 
{
    return PIXY2PacketCount_STATUS;
}


#if(!PIXY2PacketCount_ControlRegRemoved)
/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadControlRegister
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
uint8   PIXY2PacketCount_ReadControlRegister(void) 
{
    return PIXY2PacketCount_CONTROL;
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_WriteControlRegister
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
void    PIXY2PacketCount_WriteControlRegister(uint8 control) 
{
    PIXY2PacketCount_CONTROL = control;
}

#endif  /* (!PIXY2PacketCount_ControlRegRemoved) */


#if (!(PIXY2PacketCount_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: PIXY2PacketCount_WriteCounter
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
void PIXY2PacketCount_WriteCounter(uint8 counter) \
                                   
{
    #if(PIXY2PacketCount_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (PIXY2PacketCount_GLOBAL_ENABLE & PIXY2PacketCount_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        PIXY2PacketCount_GLOBAL_ENABLE |= PIXY2PacketCount_BLOCK_EN_MASK;
        CY_SET_REG16(PIXY2PacketCount_COUNTER_LSB_PTR, (uint16)counter);
        PIXY2PacketCount_GLOBAL_ENABLE &= ((uint8)(~PIXY2PacketCount_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(PIXY2PacketCount_COUNTER_LSB_PTR, counter);
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}
#endif /* (!(PIXY2PacketCount_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadCounter
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
uint8 PIXY2PacketCount_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(PIXY2PacketCount_UsingFixedFunction)
		(void)CY_GET_REG16(PIXY2PacketCount_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(PIXY2PacketCount_COUNTER_LSB_PTR_8BIT);
	#endif/* (PIXY2PacketCount_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(PIXY2PacketCount_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PIXY2PacketCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PIXY2PacketCount_STATICCOUNT_LSB_PTR));
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadCapture
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
uint8 PIXY2PacketCount_ReadCapture(void) 
{
    #if(PIXY2PacketCount_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PIXY2PacketCount_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(PIXY2PacketCount_STATICCOUNT_LSB_PTR));
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_WritePeriod
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
void PIXY2PacketCount_WritePeriod(uint8 period) 
{
    #if(PIXY2PacketCount_UsingFixedFunction)
        CY_SET_REG16(PIXY2PacketCount_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(PIXY2PacketCount_PERIOD_LSB_PTR, period);
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadPeriod
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
uint8 PIXY2PacketCount_ReadPeriod(void) 
{
    #if(PIXY2PacketCount_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(PIXY2PacketCount_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(PIXY2PacketCount_PERIOD_LSB_PTR));
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


#if (!PIXY2PacketCount_UsingFixedFunction)
/*******************************************************************************
* Function Name: PIXY2PacketCount_WriteCompare
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
void PIXY2PacketCount_WriteCompare(uint8 compare) \
                                   
{
    #if(PIXY2PacketCount_UsingFixedFunction)
        CY_SET_REG16(PIXY2PacketCount_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(PIXY2PacketCount_COMPARE_LSB_PTR, compare);
    #endif /* (PIXY2PacketCount_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PIXY2PacketCount_ReadCompare
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
uint8 PIXY2PacketCount_ReadCompare(void) 
{
    return (CY_GET_REG8(PIXY2PacketCount_COMPARE_LSB_PTR));
}


#if (PIXY2PacketCount_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PIXY2PacketCount_SetCompareMode
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
void PIXY2PacketCount_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    PIXY2PacketCount_CONTROL &= ((uint8)(~PIXY2PacketCount_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    PIXY2PacketCount_CONTROL |= compareMode;
}
#endif  /* (PIXY2PacketCount_COMPARE_MODE_SOFTWARE) */


#if (PIXY2PacketCount_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: PIXY2PacketCount_SetCaptureMode
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
void PIXY2PacketCount_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    PIXY2PacketCount_CONTROL &= ((uint8)(~PIXY2PacketCount_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    PIXY2PacketCount_CONTROL |= ((uint8)((uint8)captureMode << PIXY2PacketCount_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (PIXY2PacketCount_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: PIXY2PacketCount_ClearFIFO
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
void PIXY2PacketCount_ClearFIFO(void) 
{

    while(0u != (PIXY2PacketCount_ReadStatusRegister() & PIXY2PacketCount_STATUS_FIFONEMP))
    {
        (void)PIXY2PacketCount_ReadCapture();
    }

}
#endif  /* (!PIXY2PacketCount_UsingFixedFunction) */


/* [] END OF FILE */

