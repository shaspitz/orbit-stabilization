/******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description: This is the source code for the ADC and UART code example.
*
* Related Document: CE195277_ADC_and_UART.pdf
*
* Hardware Dependency: See CE195277_ADC_and_UART.pdf
*
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/

#include <project.h>
#include "stdio.h"

/* Project Defines */
#define FALSE  0
#define TRUE   1
#define TRANSMIT_BUFFER_SIZE  64


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main() performs following functions:
...
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
uint32 Time = 0; //ms
uint TimeStart;
uint8 LedState = 0;

// Interrupts 
CY_ISR(TimerInterrupt)
{
    // Timer interrupt runs at 1000Hz
    ++Time;
    Timer_1_ReadStatusRegister();
}

int main()
{
    uint8 i;
    uint8 j;
    
    Timer_1_Start();
    TimerInterrupt_Start();
    TimerInterrupt_StartEx(TimerInterrupt);
    TimerInterrupt_Enable();
    
    // Enable global interrupts
    CyGlobalIntEnable;

    // Variable to store UART received character 
    uint8 Ch;
    
    // Transmit buffer 
    char TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    
    // Measurement buffer
    char MeasBuffer[64];
    
    // Start UART
    UART_1_Start();
    
    // Initialize flags
    uint8 ActiveFlag = FALSE;
    uint8 InputFlag = FALSE;
    uint8 MeasFlag = FALSE;

    for(;;)
    {
        /* Non-blocking call to get the latest data recieved  */
        Ch = UART_1_GetChar();
        
        /* Set flags based on UART command */
        switch(Ch)
        {
            case 0:
                // No new data was recieved 
                break;
            case 's':
                // Start timing for computation alongside Python
                TimeStart = Time;
                ActiveFlag = TRUE;
            case 'u':
                // Input requested
                InputFlag = TRUE;
            case 'm':
                // Incoming measurement data
                MeasFlag = TRUE;
            default:
                // Place error handling code here //
                break;    
        }
        /*
        if(InputFlag && ActiveFlag)
        {
            uint32 Input1 = UART_1_GetRxBufferSize();
            uint32 Input2 = UART_1_GetRxBufferSize();
            sprintf(TransmitBuffer, "%lu,%lu,%lu\n", Time-TimeStart, Input1, Input2);
            UART_1_PutString(TransmitBuffer);
            InputFlag = FALSE;
        }
        */
        
        if (MeasFlag && ActiveFlag)
        {
            //For testing
            /*
            LedState = !LedState;
            LEDDrive_Write(LedState);
            char test = UART_1_ReadRxData();
            sprintf(TransmitBuffer, "UART GetChar not working, testing..see code: %c\n", test);
            UART_1_PutString(TransmitBuffer);
            */
            
            uint8 NumChar = 20;//UART_1_GetRxBufferSize();
            
            for(i=0; i < NumChar; ++i)
            {
                MeasBuffer[i] = UART_1_ReadRxData();
            }
            sprintf(TransmitBuffer, "Testing: %s\n", MeasBuffer);
            UART_1_PutString(TransmitBuffer);
            for(i=0; i < NumChar; ++i)
            {   
                
            }
            MeasFlag = FALSE;
        }
    }
}


/* [] END OF FILE */
