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
    UART_2_Start();
    
    
    VDAC8_1_Start();
    Comp_1_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    transmitbuffer[0] = 0xae;  // first byte of no_checksum_sync (little endian -> least-significant byte first)
    transmitbuffer[1] = 0xc1;  // second byte of no_checksum_sync
    transmitbuffer[2] = 0x0e;  // this is the version request type
    transmitbuffer[3] = 0x00;  // data_length is 0

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  
    while(1)
    {
        UART_2_PutArray(transmitbuffer, 0x04);
    
        for(i=0;i<22;i++)
        {
            while(UART_2_ReadRxStatus() != UART_2_RX_STS_FIFO_NOTEMPTY);
        
            Data[i] = UART_2_GetChar();
        }
    CyDelayUs(1500);
    }
    for(;;)
    {
        /* Place your application code here. */
        UART_2_WriteTxData(0xae);
        UART_2_WriteTxData(0xc1);
        UART_2_WriteTxData(0x0e);
        UART_2_WriteTxData(0x0a);
        
       
        for(i=0;i<12;i++)
        {
            
            Status = UART_2_ReadRxStatus();
            Rcount = UART_2_GetRxBufferSize();
            Data[i] = UART_2_ReadRxData();
        }
        i=0;
        Rcount = UART_2_GetRxBufferSize();
        while(Rcount != 0)
        {
            
            i++;
            Rcount = UART_2_GetRxBufferSize();
        }
    
    }
}

/* [] END OF FILE */
