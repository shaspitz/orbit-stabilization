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

uint8 i;

uint8 LEDState = 0;
int16 LEDPeriod = 1;

uint8 ByteCount = 0;

uint8 firstbyte = 0;
uint8 CommandReady = 0;
uint8 Count = 0;
uint8 Status;

uint8 ReceivedBuffer[66];
uint8 TransmitBuffer[66];

int32  DataI32[16];
uint16 DataU16[32];




struct command_protocol
{
    uint8 packet_size;
    uint8 command;
    uint8 buffer[64];
} Command_Packet;

struct command_protocol Transmit_Packet;

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



CY_ISR(TimerInterrupt)
{
    LEDDrive_Write((LEDState++)&0x01);
    Timer_1_ReadStatusRegister();
}
    

int main(void)
{
    
    UARTReset_Write(0);
    ByteCountReset_Write(0);
    
    LabVIEW_UART_Start();
    
    
    TimerReset_Write(0);
    Timer_1_Start();
    TimerReset_Write(1);
    
    TimerInterrupt_Start();
    TimerInterrupt_StartEx(TimerInterrupt);
    
    Timer_1_Stop();
    
    ByteCounter_Start();
    ByteCounter_Enable();
    ByteCounter_SetInterruptMode(ByteCounter_STATUS_CMP_INT_EN_MASK);
    
    ByteReceived_Start();
    ByteReceived_StartEx(ByteReceived);
    ByteReceived_Enable();
    
    CommandReceived_Start();
    CommandReceived_StartEx(CommandReceived);
    CommandReceived_Enable();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
    if(CommandReady)
        {
            Transmit_Packet.command = Command_Packet.command;
            TransmitBuffer[1] = Transmit_Packet.command;
            Transmit_Packet.packet_size = Command_Packet.packet_size;
            TransmitBuffer[0] = Transmit_Packet.packet_size;
            
            switch(Command_Packet.command)
            {
                case 0: // Start Timer
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    TimerReset_Write(0);
                    Timer_1_Start();
                   
                break;
                case 1: // Store I32
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    for(i=0;i<16;i++)
                    {
                        DataI32[i] =  (int32) ((Command_Packet.buffer[4*i+3] <<8)|(Command_Packet.buffer[4*i+2] & 0xFF)|(Command_Packet.buffer[4*i+1] <<8)|(Command_Packet.buffer[4*i] & 0xFF));
                    }
                    
                    
                break;
                case 2: // Store U16
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    for(i=0;i<32;i++)
                    {
                        DataU16[i] =  (uint16) ((Command_Packet.buffer[2*i+1] <<8)|(Command_Packet.buffer[2*i] & 0xFF));
                    }
                break;
                case 3: // Store single I16
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    LEDPeriod = (int16)((Command_Packet.buffer[1] <<8)|(Command_Packet.buffer[1] & 0xFF));
                    
                    Timer_1_WritePeriod(LEDPeriod);
                    
                break;
                case 4: // Stop Timer
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                    
                    Timer_1_Stop();
                    TimerReset_Write(0);
    
               break;
               default:
                break;
            }
            LabVIEW_UART_PutArray(TransmitBuffer,TransmitBuffer[0]);
        }
      
    }
}

/* [] END OF FILE */
