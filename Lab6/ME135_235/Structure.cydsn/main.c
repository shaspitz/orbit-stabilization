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

struct sensorset
{
    uint32 Xaccel;
    uint32 Yaccel;
    uint32 Zaccel;
    uint8 Error;
}Axis[4];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        
        Axis[1].Xaccel = 1;
        Axis[1].Yaccel = 2;
        Axis[1].Zaccel = 5;
        Axis[1].Error = 0xFF;
        
        CyDelay(100);
    }
}

/* [] END OF FILE */
