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

uint8 transmitbuffer[16];
uint8 Data[128];
uint8 i=0;
uint16 Rcount;

uint8 Status;

int main(void)
{
    SPIM_1_Start();
    SPIM_1_EnableRxInt();
    SPIM_1_EnableTxInt();
    
    Status = SPIM_1_ReadRxStatus();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    transmitbuffer[0] = 0xae;  // first byte of no_checksum_sync (little endian -> least-significant byte first)
    transmitbuffer[1] = 0xc1;  // second byte of no_checksum_sync
    transmitbuffer[2] = 0x0e;  // this is the version request type
    transmitbuffer[3] = 0x00;  // data_length is 0

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    for(;;)
    {
        /* Place your application code here. */
        SPIM_1_WriteTxData(0xae);
        SPIM_1_WriteTxData(0xc1);
        SPIM_1_WriteTxData(0x0e);
        SPIM_1_WriteTxData(0x0a);
        
//        SPIM_1_PutArray(transmitbuffer, 0x04);
//        CyDelayUs(1000);
        
        for(i=0;i<12;i++)
        {
            
            Status = SPIM_1_ReadRxStatus();
            Rcount = SPIM_1_GetRxBufferSize();
            Data[i] = SPIM_1_ReadRxData();
        }
        i=0;
        Rcount = SPIM_1_GetRxBufferSize();
        while(Rcount != 0)
        {
            
            i++;
            Rcount = SPIM_1_GetRxBufferSize();
        }
    
    }
}

/* [] END OF FILE */
