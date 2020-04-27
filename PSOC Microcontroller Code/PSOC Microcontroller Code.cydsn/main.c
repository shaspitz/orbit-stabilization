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
#define TRANSMIT_BUFFER_SIZE  16


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
uint32 time = 0; //ms
uint time_start;

// Interrupts 
CY_ISR(TimerInterrupt)
{
    // Timer interrupt runs at 1000Hz
    ++time;
    Timer_1_ReadStatusRegister();
}

int main()
{
    Timer_1_Start();
    TimerInterrupt_Start();
    TimerInterrupt_StartEx(TimerInterrupt);
    TimerInterrupt_Enable();
    CyGlobalIntEnable; // Enable global interrupts

    // Variable to store UART received character 
    uint8 Ch;
    // Transmit Buffer 
    char TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    // Start UART
    UART_1_Start();
    // Initialize input flag
    uint8 input_flag = FALSE;
    uint8 active = FALSE;

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
                time_start = time;
                active = TRUE;
            case 'u':
                input_flag = TRUE;
            default:
                // Place error handling code here //
                break;    
        }

        if(input_flag && active)
        {
            uint32 input1 = 101;
            uint32 input2 = 50;
            sprintf(TransmitBuffer, "%lu,%lu,%lu\n", time-time_start, input1, input2);
            // can send to sending array directly by using array command (and activating at top of script!!!)
            UART_1_PutString(TransmitBuffer);
            input_flag = FALSE;
        }
    }
}


/* [] END OF FILE */
