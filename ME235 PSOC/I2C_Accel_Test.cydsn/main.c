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

uint8 datain[16];
uint8 dataout[17];

uint8 i;

uint8 error;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    I2C_1_Start();
    
    dataout[0] = 0x00;
    for(i=1;i<17;i++)
    {
        dataout[i] = i*2;
    }

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    error = I2C_1_MasterWriteBuf(0x1D, dataout, 1, I2C_1_MODE_NO_STOP);
    CyDelayUs(200);
    error = I2C_1_MasterReadBuf(0x1D, datain, 1, I2C_1_MODE_REPEAT_START);
    CyDelayUs(250);
    
      

    dataout[0] = 0x32;
    for(;;)
    {
        /* Place your application code here. */
        error = I2C_1_MasterWriteBuf(0x1D, dataout, 1, I2C_1_MODE_NO_STOP);
        CyDelayUs(200);
        error = I2C_1_MasterReadBuf(0x1D, datain, 6, I2C_1_MODE_REPEAT_START);
        CyDelayUs(10000);
    }
}

/* [] END OF FILE */
