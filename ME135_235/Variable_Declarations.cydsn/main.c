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

static uint8 xbyte = 255;
static int8  ybyte = -1;

static uint16 xuint = 0xFFFF;
static int16 yint = -1;

static uint32 xlong = 0x12345678;
static int32  ylong = 0x12345678;

static float xfloat = 5.2;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        CyDelay(1000);
        
        xbyte++;
        ybyte++;

        xuint++;
        yint++;

        xlong++;
        ylong++;
        xfloat+= 1.0;
        
        
    }
}

/* [] END OF FILE */
