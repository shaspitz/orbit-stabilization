/*******************************************************************************
* File Name: LabVIEW_UARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LabVIEW_UART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (LabVIEW_UART_RX_INTERRUPT_ENABLED && (LabVIEW_UART_RX_ENABLED || LabVIEW_UART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: LabVIEW_UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  LabVIEW_UART_rxBuffer - RAM buffer pointer for save received data.
    *  LabVIEW_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  LabVIEW_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  LabVIEW_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when LabVIEW_UART_rxBufferWrite index overtakes
    *     LabVIEW_UART_rxBufferRead index.
    *  LabVIEW_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when LabVIEW_UART_rxBufferWrite is equal to
    *    LabVIEW_UART_rxBufferRead
    *  LabVIEW_UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  LabVIEW_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(LabVIEW_UART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef LabVIEW_UART_RXISR_ENTRY_CALLBACK
        LabVIEW_UART_RXISR_EntryCallback();
    #endif /* LabVIEW_UART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START LabVIEW_UART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = LabVIEW_UART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in LabVIEW_UART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (LabVIEW_UART_RX_STS_BREAK | 
                            LabVIEW_UART_RX_STS_PAR_ERROR |
                            LabVIEW_UART_RX_STS_STOP_ERROR | 
                            LabVIEW_UART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                LabVIEW_UART_errorStatus |= readStatus & ( LabVIEW_UART_RX_STS_BREAK | 
                                                            LabVIEW_UART_RX_STS_PAR_ERROR | 
                                                            LabVIEW_UART_RX_STS_STOP_ERROR | 
                                                            LabVIEW_UART_RX_STS_OVERRUN);
                /* `#START LabVIEW_UART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef LabVIEW_UART_RXISR_ERROR_CALLBACK
                LabVIEW_UART_RXISR_ERROR_Callback();
            #endif /* LabVIEW_UART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & LabVIEW_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = LabVIEW_UART_RXDATA_REG;
            #if (LabVIEW_UART_RXHW_ADDRESS_ENABLED)
                if(LabVIEW_UART_rxAddressMode == (uint8)LabVIEW_UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & LabVIEW_UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & LabVIEW_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            LabVIEW_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            LabVIEW_UART_rxAddressDetected = 0u;
                        }
                    }
                    if(LabVIEW_UART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        LabVIEW_UART_rxBuffer[LabVIEW_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    LabVIEW_UART_rxBuffer[LabVIEW_UART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                LabVIEW_UART_rxBuffer[LabVIEW_UART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (LabVIEW_UART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(LabVIEW_UART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        LabVIEW_UART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    LabVIEW_UART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(LabVIEW_UART_rxBufferWrite >= LabVIEW_UART_RX_BUFFER_SIZE)
                    {
                        LabVIEW_UART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(LabVIEW_UART_rxBufferWrite == LabVIEW_UART_rxBufferRead)
                    {
                        LabVIEW_UART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (LabVIEW_UART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            LabVIEW_UART_RXSTATUS_MASK_REG  &= (uint8)~LabVIEW_UART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(LabVIEW_UART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (LabVIEW_UART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & LabVIEW_UART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START LabVIEW_UART_RXISR_END` */

        /* `#END` */

    #ifdef LabVIEW_UART_RXISR_EXIT_CALLBACK
        LabVIEW_UART_RXISR_ExitCallback();
    #endif /* LabVIEW_UART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (LabVIEW_UART_RX_INTERRUPT_ENABLED && (LabVIEW_UART_RX_ENABLED || LabVIEW_UART_HD_ENABLED)) */


#if (LabVIEW_UART_TX_INTERRUPT_ENABLED && LabVIEW_UART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: LabVIEW_UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  LabVIEW_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  LabVIEW_UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  LabVIEW_UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(LabVIEW_UART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef LabVIEW_UART_TXISR_ENTRY_CALLBACK
        LabVIEW_UART_TXISR_EntryCallback();
    #endif /* LabVIEW_UART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START LabVIEW_UART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((LabVIEW_UART_txBufferRead != LabVIEW_UART_txBufferWrite) &&
             ((LabVIEW_UART_TXSTATUS_REG & LabVIEW_UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(LabVIEW_UART_txBufferRead >= LabVIEW_UART_TX_BUFFER_SIZE)
            {
                LabVIEW_UART_txBufferRead = 0u;
            }

            LabVIEW_UART_TXDATA_REG = LabVIEW_UART_txBuffer[LabVIEW_UART_txBufferRead];

            /* Set next pointer */
            LabVIEW_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START LabVIEW_UART_TXISR_END` */

        /* `#END` */

    #ifdef LabVIEW_UART_TXISR_EXIT_CALLBACK
        LabVIEW_UART_TXISR_ExitCallback();
    #endif /* LabVIEW_UART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (LabVIEW_UART_TX_INTERRUPT_ENABLED && LabVIEW_UART_TX_ENABLED) */


/* [] END OF FILE */
