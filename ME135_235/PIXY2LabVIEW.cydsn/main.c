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

uint8 ByteCount = 0;

uint8 firstbyte = 0;
uint8 CommandReady = 0;
uint8 Count = 0;
uint8 Status;

uint8 ReceivedBuffer[66];
uint8 TransmitBuffer[66];

uint8 PIXY2TxBuffer[32];
uint8 PIXY2RxBuffer[32];

uint8 PIXY2_ByteCount = 0;

uint8 PIXY2_firstbyte = 0;
uint8 PIXY2_CommandReady = 0;
uint8 PIXY2_Count = 0;
uint8 PIXY2_Status;


struct command_protocol
{
    uint8 packet_size;
    uint8 command;
    uint8 buffer[64];
} Command_Packet;

struct command_protocol Transmit_Packet;

struct PIXY2_protocol
{
    uint16 sync;
    uint8  type;
    uint8 datalength;
    uint16 checksum;
    uint8 buffer[16];
} PIXY2_Packet;

struct PIXY2_protocol PIXY2_Transmit;
struct PIXY2_protocol PIXY2_Receive;

struct command_protocol Transmit_Packet;

CY_ISR(PIXY2Received)
{ 
    
    PIXY2RxBuffer[PIXY2_ByteCount++] = (uint8) (PIXY2UART_GetByte()&0x00ff);
    if(PIXY2_ByteCount == 4)
    {
        PIXY2PacketCount_WriteCompare(PIXY2RxBuffer[3]+6);
    }
    PIXY2_Count = PIXY2PacketCount_ReadCounter();
    Status = PIXY2PacketCount_ReadStatusRegister();
    
}

CY_ISR(PIXY2Packet)
{
    uint8 i;
    
    if(PIXY2_CommandReady == 0)
    {
        PIXY2_Receive.sync =  (PIXY2RxBuffer[1]<< 8)|(PIXY2RxBuffer[0]&0xFF);
        PIXY2_Receive.type = PIXY2RxBuffer[2];
        PIXY2_Receive.datalength = PIXY2RxBuffer[3];
        PIXY2_Receive.checksum = (PIXY2RxBuffer[5]<< 8)|(PIXY2RxBuffer[4]&0xFF);
    
        for(i=0;i<(PIXY2_Receive.datalength);i++)
        {
            PIXY2_Receive.buffer[i] =  PIXY2RxBuffer[i+6];
        }
    
        PIXY2_CommandReady = 1;
        PIXY2_ByteCount = 0;
    }
    PIXY2PacketCount_ReadStatusRegister();
    
}



CY_ISR(ByteReceived)
{ 
    LEDDrive_Write(1);
    ReceivedBuffer[ByteCount++] = (uint8) (LabVIEW_UART_GetByte()&0x00ff);
    if(firstbyte == 0)
    {
        ByteCounter_WriteCompare(ReceivedBuffer[0]);
        firstbyte = 1;
   
    }
    Count = ByteCounter_ReadCounter();
    Status = ByteCounter_ReadStatusRegister();
    LEDDrive_Write(0);
}

CY_ISR(CommandReceived)
{
    uint8 i;
    
    if(CommandReady == 0)
    {
        Command_Packet.packet_size = ReceivedBuffer[0];
        Command_Packet.command = ReceivedBuffer[1];
    
        for(i=0;i<(Command_Packet.packet_size - 2);i++)
        {
            Command_Packet.buffer[i] =  ReceivedBuffer[i+2];
        }
    
        firstbyte = 0;
        CommandReady = 1;
        ByteCount = 0;
    }
    ByteCounter_ReadStatusRegister();
    LEDDrive_Write(0);
}

int main(void)
{
    uint8 i;
    
    UARTReset_Write(0);
    ByteCountReset_Write(0);
    
    PIXY2UARTReset_Write(0);
    PIXYCountReset_Write(0);
    
    LabVIEW_UART_Start();
    PIXY2UART_Start();
    
    VDAC8_1_Start();
    Comp_1_Start();
    
    ByteCounter_Start();
    ByteCounter_Enable();
    ByteCounter_SetInterruptMode(ByteCounter_STATUS_CMP_INT_EN_MASK);
    
    PIXY2PacketCount_Start();
    PIXY2PacketCount_Enable();
    PIXY2PacketCount_SetInterruptMode(PIXY2PacketCount_STATUS_CMP_INT_EN_MASK);
       
    ByteReceived_Start();
    ByteReceived_StartEx(ByteReceived);
    ByteReceived_Enable();
    
    PIXY2Received_Start();
    PIXY2Received_StartEx(PIXY2Received);
    PIXY2Received_Enable();
    
    CommandReceived_Start();
    CommandReceived_StartEx(CommandReceived);
    CommandReceived_Enable();
    
    PIXY2Packet_Start();
    PIXY2Packet_StartEx(PIXY2Packet);
    PIXY2Packet_Enable();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //LabVIEW_UART_PutString("PSOC Started\r\n");
    
    
    
    
    for(;;)
    {
        /* Place your application code here. */
        
        if(CommandReady)
        {   Transmit_Packet.command = Command_Packet.command;
            TransmitBuffer[1] = Transmit_Packet.command;
            Transmit_Packet.packet_size = Command_Packet.packet_size;
            TransmitBuffer[0] = Transmit_Packet.packet_size;
            
            switch(Command_Packet.command)
            {
                case 0: // getVersion
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    PIXY2_Transmit.sync = 0xC1AE;
                    PIXY2_Transmit.type = 0x0E;
                    PIXY2_Transmit.datalength = 0x00;
                    
                    PIXY2UART_PutArray((uint8*)&PIXY2_Transmit, 0x04);

                    while(PIXY2_CommandReady == 0);
                    
                    TransmitBuffer[2] = (uint8)(PIXY2_Receive.sync & 0xFF);
                    TransmitBuffer[3] = (uint8)(PIXY2_Receive.sync >> 8);
                    TransmitBuffer[4] =  PIXY2_Receive.type;
                    TransmitBuffer[5] =  PIXY2_Receive.datalength;
                    TransmitBuffer[6] =  (uint8)(PIXY2_Receive.checksum & 0xFF);
                    TransmitBuffer[7] =  (uint8)(PIXY2_Receive.checksum >> 8);
                    
                    for(i=0;i<(PIXY2_Receive.datalength);i++)
                    {
                        TransmitBuffer[i+8] = PIXY2_Receive.buffer[i];
                    }
                    
                    TransmitBuffer[0] = PIXY2_Receive.datalength + 8;
                    PIXY2_CommandReady = 0;
                break;
                case 1: // getFPS
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    PIXY2_Transmit.sync = 0xC1AE;
                    PIXY2_Transmit.type = 0x18;
                    PIXY2_Transmit.datalength = 0x00;
                    
                    PIXY2UART_PutArray((uint8*)&PIXY2_Transmit, 0x04);

                    while(PIXY2_CommandReady == 0);
                    
                    TransmitBuffer[2] = (uint8)(PIXY2_Receive.sync & 0xFF);
                    TransmitBuffer[3] = (uint8)(PIXY2_Receive.sync >> 8);
                    TransmitBuffer[4] =  PIXY2_Receive.type;
                    TransmitBuffer[5] =  PIXY2_Receive.datalength;
                    TransmitBuffer[6] =  (uint8)(PIXY2_Receive.checksum & 0xFF);
                    TransmitBuffer[7] =  (uint8)(PIXY2_Receive.checksum >> 8);
                    
                    for(i=0;i<(PIXY2_Receive.datalength);i++)
                    {
                        TransmitBuffer[i+8] = PIXY2_Receive.buffer[i];
                    }
                    
                    TransmitBuffer[0] = PIXY2_Receive.datalength + 8;
                    PIXY2_CommandReady = 0;
                break;
                case 2: // getResolution
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    PIXY2_Transmit.sync = 0xC1AE;
                    PIXY2_Transmit.type = 0x0C;
                    PIXY2_Transmit.datalength = 0x01;
                    PIXY2_Transmit.buffer[0] = 0x00;
                    
                    PIXY2UART_PutArray((uint8*)&PIXY2_Transmit, 0x05);

                    while(PIXY2_CommandReady == 0);
                    
                    TransmitBuffer[2] = (uint8)(PIXY2_Receive.sync & 0xFF);
                    TransmitBuffer[3] = (uint8)(PIXY2_Receive.sync >> 8);
                    TransmitBuffer[4] =  PIXY2_Receive.type;
                    TransmitBuffer[5] =  PIXY2_Receive.datalength;
                    TransmitBuffer[6] =  (uint8)(PIXY2_Receive.checksum & 0xFF);
                    TransmitBuffer[7] =  (uint8)(PIXY2_Receive.checksum >> 8);
                    
                    for(i=0;i<(PIXY2_Receive.datalength);i++)
                    {
                        TransmitBuffer[i+8] = PIXY2_Receive.buffer[i];
                    }
                    
                    TransmitBuffer[0] = PIXY2_Receive.datalength + 8;
                    PIXY2_CommandReady = 0;
                break;
                default:
                break;
            }
            LabVIEW_UART_PutArray(TransmitBuffer,TransmitBuffer[0]);
        }
        
                        
    }
}

/* [] END OF FILE */
