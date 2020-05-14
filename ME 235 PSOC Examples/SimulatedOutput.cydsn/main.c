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

uint8 y[2];

int16 Force = 0;

CY_ISR(SampleInterrupt)
{
    PulseTrigger_Write(0);
    ModelOutput_SetValue(255+y[0]);
    UltraSonic_WriteCompare(255+y[0]);
    Force = ForceInput_Read();
    
    if(Force == 1)
    {
        Force = 3;
    }
    else
    {
        Force = -3;
    }
    
    y[1] = y[0] + Force;
    y[0] = y[1];
    
    SampleTime_ReadStatusRegister();
}

int main(void)
{
    simulatedForce_Start();
    
    ModelOutput_Start();
    ModelOutput_SetValue(128);
    
    UltraSonic_Start();
    UltraSonic_WriteCompare(0);
    
    PulseTrigger_Write(1);
    
    
    SampleInterrupt_Start();
    SampleInterrupt_Disable();
    
    SampleInterrupt_StartEx(SampleInterrupt);
    
    SampleTime_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
