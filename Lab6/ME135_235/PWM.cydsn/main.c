/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

uint32 distance;

uint16 PWMvalue;

CY_ISR(isr_1)
{
    CyDelayUs(10);
}

CY_ISR(isr_2)
{
    CyDelayUs(10);
    
    distance = Timer_1_ReadCounter();

    TimerReset_Write(1);
    CyDelayUs(50);
    TimerReset_Write(0);
}

int main(void)
{
    PWM_1_Start();
    Timer_1_Start();
    
    isr_1_Start();
    isr_1_StartEx(isr_1);
    isr_1_Enable();
    
    isr_2_Start();
    isr_2_StartEx(isr_2);
    isr_2_Enable();
    
    Timer_1_EnableTrigger();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    PWMvalue = 0;
    for(;;)
    {
        /* Place your application code here. */
        
        PWMvalue = (PWMvalue+1024);
        
        PWM_1_WriteCompare(PWMvalue/2 + 2048);
        
        CyDelay(100);
    }
}

/* [] END OF FILE */
