/* ========================================
 Author: Shawn Marshall-Spitzbart
(adapted from code written by George Anwar)
 * ========================================
*/
#include "project.h"

// Project Defines
#define FALSE  0
#define TRUE   1

uint8 ByteCount = 0;
uint8 firstbyte = 0;
uint8 CommandReady = 0;
uint8 Count = 0;
uint8 Status;

uint8 ReceivedBuffer[66];
uint8 TransmitBuffer[66];

uint32 Time = 0; //ms
uint32 TimeStart;

double Input1;
double Input2;

struct command_protocol
{
    uint8 packet_size;
    uint8 command;
    uint8 buffer[64];
} Command_Packet;

struct command_protocol Transmit_Packet;

// Interrupts 
CY_ISR(TimerInterrupt)
{
    // Timer interrupt runs at 1000Hz
    ++Time;
    Timer_1_ReadStatusRegister();
}

CY_ISR(ByteReceived)
{ 
    //LEDDrive_Write(1);
    ReceivedBuffer[ByteCount++] = (uint8) (UART1_GetByte()&0x00ff);
    if(firstbyte == 0)
    {
        ByteCounter_WriteCompare(ReceivedBuffer[0]);
        firstbyte = 1;
   
    }
    Count = ByteCounter_ReadCounter();
    Status = ByteCounter_ReadStatusRegister();
    //LEDDrive_Write(0);
    
}

CY_ISR(CommandReceived)
{
    uint8 i;
    //LEDDrive_Write(1);
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
    //LEDDrive_Write(0);
}

int main(void)
{
    uint8 i;
    
    Timer_1_Start();
    TimerInterrupt_Start();
    TimerInterrupt_StartEx(TimerInterrupt);
    TimerInterrupt_Enable();
    
    UARTReset_Write(0);
    ByteCountReset_Write(0);
    
    UART1_Start();
    
    ByteCounter_Start();
    ByteCounter_Enable();
    ByteCounter_SetInterruptMode(ByteCounter_STATUS_CMP_INT_EN_MASK);
       
    ByteReceived_Start();
    ByteReceived_StartEx(ByteReceived);
    ByteReceived_Enable();
    
    CommandReceived_Start();
    CommandReceived_StartEx(CommandReceived);
    CommandReceived_Enable();
    
    CyGlobalIntEnable; //Enable global interrupts

    // Initialize flags
    uint8 ActiveFlag = FALSE;
    uint8 InputFlag = FALSE;
    uint8 MeasFlag = FALSE;
    
    for(;;)
    {        
        if(CommandReady)
        {
            switch(Command_Packet.command)
            {
                case 1:
                    // Relay bytes back to Python (for testing)
                    Transmit_Packet.command = Command_Packet.command;
                    TransmitBuffer[1] = Transmit_Packet.command;
                    Transmit_Packet.packet_size = Command_Packet.packet_size;
                    TransmitBuffer[0] = Transmit_Packet.packet_size;
                    for(i = 0; i < Transmit_Packet.packet_size; ++i)
                    {
                        Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                        TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                break;
                
                case 2:
                    // Start timing for computation alongside Python
                    TimeStart = Time;
                    ActiveFlag = TRUE;
                    CommandReady = 0;
                break;
                
                case 3:
                    LEDDrive_Write(1);
                    // Input requested
                    if (ActiveFlag)
                    {   
                        // Send two double inputs to Python
                        Transmit_Packet.command = Command_Packet.command;
                        TransmitBuffer[1] = Transmit_Packet.command;
                        
                        // Set packet size for sending two doubles
                        Transmit_Packet.packet_size = 18;
                        TransmitBuffer[0] = Transmit_Packet.packet_size;
                        
                        // Values of those doubles (will be LQG eventually)
                        Input1 = 5.678 + (double) Time;
                        Input2 = 9.7834594324234 + (double) Time;
                        
                        // Pointer declaration for sending doubles by byte
                        uint8 *PtrInput1 = &Input1;
                        uint8 *PtrInput2 = &Input2;
                        
                        /*
                        Load bytes representing doubles into transmit buffer via
                        iteration
                        */
                        for (i=0; i < (Transmit_Packet.packet_size-2)/2; ++i)
                        {
                            Transmit_Packet.buffer[i+2] = *PtrInput1;
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                            ++PtrInput1;
                            
                            Transmit_Packet.buffer[i+2+8] = *PtrInput2;
                            TransmitBuffer[i+2+8] = Transmit_Packet.buffer[i+2+8];
                            ++PtrInput2;
                        }
                        CommandReady = 0;
                    }
                break;
                
                case 4:
                    // Incoming measurement data
                    if (ActiveFlag)
                    {
                    }
                    CommandReady = 0;
                break;
                
                case 5:
                    // Store LQG matricies
                break;
                
                default:
                break;
            }
            UART1_PutArray(TransmitBuffer,Transmit_Packet.packet_size);
        }                 
    }
}

// END OF FILE