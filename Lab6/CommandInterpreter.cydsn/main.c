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
int32 problem3a_array[16];
uint16 problem3b_array[32];
int16 problem3c_var;

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
    LEDDrive_Write(!LEDDrive_Read());
    Timer_1_ReadStatusRegister();
}

int main(void)
{
    uint8 i;
    
    UARTReset_Write(0);
    ByteCountReset_Write(0);
    
    LabVIEW_UART_Start();
    
    
    ByteCounter_Start();
    ByteCounter_Enable();
    ByteCounter_SetInterruptMode(ByteCounter_STATUS_CMP_INT_EN_MASK);
       
    ByteReceived_Start();
    ByteReceived_StartEx(ByteReceived);
    ByteReceived_Enable();
    
    CommandReceived_Start();
    CommandReceived_StartEx(CommandReceived);
    CommandReceived_Enable();
    
    Timer_1_Start();
    TimerInterrupt_Start();
    TimerInterrupt_StartEx(TimerInterrupt);
    TimerInterrupt_Enable();
    // Default period is fast for testing
    int16 period = 5000;
    Timer_1_WritePeriod(period);
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //LabVIEW_UART_PutString("PSOC Started\r\n");
    
    for(;;)
    {
        /* Place your application code here. */
        
        if(CommandReady)
        {
            switch(Command_Packet.command)
            {
                case 5:
                    Transmit_Packet.command = Command_Packet.command;
                    TransmitBuffer[1] = Transmit_Packet.command;
                    Transmit_Packet.packet_size = Command_Packet.packet_size;
                    TransmitBuffer[0] = Transmit_Packet.packet_size;
                    for(i=0;i<Transmit_Packet.packet_size;i++)
                    {
                            Transmit_Packet.buffer[i+2] = Command_Packet.buffer[i];
                            TransmitBuffer[i+2] = Transmit_Packet.buffer[i+2];
                    }
                    CommandReady = 0;
                break;
                
                case 1:
                    for (i=0;i<Command_Packet.packet_size/4;++i)
                    {
                        /*
                        Have pointer of type int32 point to head of 4 byte sequence
                        in the command packet buffer representing that int32 number.
                        Then dereference pointer to place int32 value in new array.
                        */
                        
                        //Array decays to pointer itself, no need for '&'
                        int32 *ptr = Command_Packet.buffer[4*i]; 
                        problem3a_array[i] = *ptr;                        
                    }
                    break;
                
                case 2:
                    for (i=0;i<Command_Packet.packet_size/2;++i)
                    {
                        /*
                        Have pointer of type uint16 point to head of 2 byte sequence
                        in the command packet buffer representing that uint16 number.
                        Then dereference pointer to place uint16 value in new array.
                        */
                        
                        //Array decays to pointer itself, no need for '&'
                        uint16 *ptr = Command_Packet.buffer[2*i]; 
                        problem3b_array[i] = *ptr;
                    }
                    break;
                     
                case 3:
                    
                    for (i=0;i<Command_Packet.packet_size/2;++i)
                    {   
                        /*
                        Have pointer of type int16 point to head of 2 byte sequence
                        in the command packet buffer representing that int16 number.
                        Then dereference pointer to place int16 value in new variable.
                        That int16 variable then updates the timer interrupt period
                        that toggles the LED light flashing.
                        */
                        
                        //Array decays to pointer itself, no need for '&'
                        int16 *ptr = Command_Packet.buffer[i];
                        problem3c_var = *ptr;
                    }
                      
                    Timer_1_WritePeriod(problem3c_var);
                    break;
                    
                default:
                break;
            }
            LabVIEW_UART_PutArray(TransmitBuffer,Transmit_Packet.packet_size);
        }
        
                        
    }
}

/* [] END OF FILE */
