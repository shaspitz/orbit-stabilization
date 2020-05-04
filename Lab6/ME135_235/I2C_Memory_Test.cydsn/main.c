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

uint8 EEPROM_data[256];
uint8 test_data[256];

uint8 EEPROM_Write_Page(uint8 Slave_Address, uint8 Page_Address, uint8 *Test_Byte)
{
    
    uint8 dataout[17];
    uint8 datain[16];
   volatile uint8 error;
    uint8 i;
    
    
    
    dataout[0] = Page_Address&0x00FF;
    for(i=1;i<17;i++)
    {
        dataout[i] = Test_Byte[i-1];
    }
    error = I2C_1_MasterWriteBuf(Slave_Address, dataout, 17, I2C_1_MODE_COMPLETE_XFER);
    
    CyDelayUs(5010);
    
    error = error + I2C_1_MasterWriteBuf(Slave_Address, dataout, 1, I2C_1_MODE_NO_STOP);
    CyDelayUs(100);
    error = error + I2C_1_MasterReadBuf(Slave_Address, datain, 16, I2C_1_MODE_REPEAT_START);
    CyDelayUs(1000);
    
    for(i=0;i<16;i++)
    {
        error = error + (datain[0] - dataout[1]);
    }
    return(error);
}

uint8 EEPROM_Read_Page(uint8 Slave_Address, uint8 Page_Address, uint8 *Test_Byte)
{
    
    uint8 error;
          
    error = I2C_1_MasterWriteBuf(Slave_Address, &Page_Address , 1, I2C_1_MODE_NO_STOP);
    CyDelayUs(100);
    error = error + I2C_1_MasterReadBuf(Slave_Address, Test_Byte, 16, I2C_1_MODE_REPEAT_START);
    CyDelayUs(1000);
    
    return(error);
}

int main(void)
{
    uint8 j;
    uint8 error = 0;
    
    uint16 i;
        
    CyGlobalIntEnable; /* Enable global interrupts. */

    I2C_1_Start();
    
    JapanSensor_Start();
    Supply_Start();
    Shunt_Start();
    PWM_1_Start();
    
    
    
    
    for(i=0;i<256;i++)
    {
        test_data[i] = (uint8)(i&0x00FF);
    }
   
    for(j=0;j<16;j++)
    {
        
        error = error + EEPROM_Write_Page(0x50, (j<<4),(uint8 *) &test_data[j*16]);
       
    }
    LED3Drive_Write(0);
    for(j=0;j<16;j++)
    {
        LED3Drive_Write(1);
        error = error + EEPROM_Read_Page(0x50, (j<<4), (uint8 *)&EEPROM_data[j*16]);
        LED3Drive_Write(0);
    }
     
    CyDelayUs(1000);
    
    
    return(error);
}

/* [] END OF FILE */
