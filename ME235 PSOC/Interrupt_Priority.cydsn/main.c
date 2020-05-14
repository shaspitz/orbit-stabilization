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

uint8 LEDState = 0;

uint16 data;

CY_ISR(ADC_Interrupt)
{
    data = ADC_DelSig_1_GetResult16();
}

CY_ISR(Timer_Interrupt)
{
    
      LED_Drive_Write(1);
      
      CyDelay(20);
    
     Timer_ReadStatusRegister();
     LED_Drive_Write(0);
 }

CY_ISR(Timer2_Interrupt)
  {
    
      Marker2_Write(1);
      CyDelay(1);
    
      Timer2_ReadStatusRegister();
      Marker2_Write(0);
     
 }  

int main(void)
{
    ADC_DelSig_1_Start();
    
    ADC_Interrupt_Start();
    ADC_Interrupt_StartEx(ADC_Interrupt);
    ADC_Interrupt_Enable();
    
    ADC_DelSig_1_StartConvert();
    
    
    Timer_Start();
    
    Timer_Interrupt_Start();
    Timer_Interrupt_StartEx(Timer_Interrupt);
    Timer_Interrupt_Enable();
    
    Timer2_Start();
    
    Timer2_Interrupt_Start();
    Timer2_Interrupt_StartEx(Timer2_Interrupt);
    Timer2_Interrupt_Enable();
    
    
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
