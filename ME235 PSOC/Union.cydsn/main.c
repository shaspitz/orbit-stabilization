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


union SPIset
{
    uint8 data[4];
    int32 number;
} SPI_data;

union SPIset RTD_data;

uint8 byte0;
uint8 byte1;
uint8 byte2;
uint8 byte3;





int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        
        RTD_data.number = RTD_data.number + 255;
        
        CyDelay(100);
        
        byte0 = RTD_data.data[0];
        byte1 = RTD_data.data[1];
        byte2 = RTD_data.data[2];
        byte3 = RTD_data.data[3];
    }
}

/* [] END OF FILE */
