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


uint8 Output[1024];

uint16 DataReady = 0;

uint8 Ch;

uint16 i;


CY_ISR(WaveDone)
{
    Marker1Drive_Write(1);
    i=0;
    DataReady = 1;
    Marker1Drive_Write(0);
}

CY_ISR(ADCInterrupt)
{
    if(DataReady == 0)
    {
    Output[i] = ADC_DelSig_1_GetResult8();
    i=(i+1)&0x03FF;
    }
 }

int main(void)
{
    i = 0;
    
    WaveDAC8_1_Start();
    
    WaveDone_Start();
    WaveDone_StartEx(WaveDone);
    
    WaveDone_Enable();
    
    ADC_DelSig_1_Start();
    
    ADCInterrupt_Start();
    ADCInterrupt_StartEx(ADCInterrupt);
    
    ADCInterrupt_Enable();
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    ADC_DelSig_1_StartConvert();
    
   UART_1_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        Ch = UART_1_GetChar();
        
        switch(Ch)
        {
            case 0:
                
                break;
            case 'C':
            case 'c':
                
                break;
            case 'S':
            case 's':
               
                break;
            case 'X':
            case 'x':
                
                break;
            case 'E':
            case 'e':
            
                while(DataReady == 0);
                
                WaveDone_Disable();
                LEDDrive_Write(1);
                UART_1_PutArray((uint8 *)Output,64);
                LEDDrive_Write(0);
                DataReady = 0;
                WaveDone_Enable();
                break;
            default:
                
                break;    
        }
        
 /*    if(DataReady == 1)
      {          
                
                LEDDrive_Write(1);
                UART_1_PutArray((uint8 *)Output,64);
                LEDDrive_Write(0);
                DataReady = 0;
                   
      }  
*/        
    }
}

/* [] END OF FILE */
