/*******************************************************************************
* File Name: PIXY2UARTINT.c
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

#include "PIXY2UART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (PIXY2UART_RX_INTERRUPT_ENABLED && (PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: PIXY2UART_RXISR
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
    *  PIXY2UART_rxBuffer - RAM buffer pointer for save received data.
    *  PIXY2UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  PIXY2UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  PIXY2UART_rxBufferOverflow - software overflow flag. Set to one
    *     when PIXY2UART_rxBufferWrite index overtakes
    *     PIXY2UART_rxBufferRead index.
    *  PIXY2UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when PIXY2UART_rxBufferWrite is equal to
    *    PIXY2UART_rxBufferRead
    *  PIXY2UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  PIXY2UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(PIXY2UART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef PIXY2UART_RXISR_ENTRY_CALLBACK
        PIXY2UART_RXISR_EntryCallback();
    #endif /* PIXY2UART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START PIXY2UART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = PIXY2UART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in PIXY2UART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (PIXY2UART_RX_STS_BREAK | 
                            PIXY2UART_RX_STS_PAR_ERROR |
                            PIXY2UART_RX_STS_STOP_ERROR | 
                            PIXY2UART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                PIXY2UART_errorStatus |= readStatus & ( PIXY2UART_RX_STS_BREAK | 
                                                            PIXY2UART_RX_STS_PAR_ERROR | 
                                                            PIXY2UART_RX_STS_STOP_ERROR | 
                                                            PIXY2UART_RX_STS_OVERRUN);
                /* `#START PIXY2UART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef PIXY2UART_RXISR_ERROR_CALLBACK
                PIXY2UART_RXISR_ERROR_Callback();
            #endif /* PIXY2UART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & PIXY2UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = PIXY2UART_RXDATA_REG;
            #if (PIXY2UART_RXHW_ADDRESS_ENABLED)
                if(PIXY2UART_rxAddressMode == (uint8)PIXY2UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & PIXY2UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & PIXY2UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            PIXY2UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            PIXY2UART_rxAddressDetected = 0u;
                        }
                    }
                    if(PIXY2UART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        PIXY2UART_rxBuffer[PIXY2UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    PIXY2UART_rxBuffer[PIXY2UART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                PIXY2UART_rxBuffer[PIXY2UART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (PIXY2UART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(PIXY2UART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        PIXY2UART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    PIXY2UART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(PIXY2UART_rxBufferWrite >= PIXY2UART_RX_BUFFER_SIZE)
                    {
                        PIXY2UART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(PIXY2UART_rxBufferWrite == PIXY2UART_rxBufferRead)
                    {
                        PIXY2UART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (PIXY2UART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            PIXY2UART_RXSTATUS_MASK_REG  &= (uint8)~PIXY2UART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(PIXY2UART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (PIXY2UART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & PIXY2UART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START PIXY2UART_RXISR_END` */

        /* `#END` */

    #ifdef PIXY2UART_RXISR_EXIT_CALLBACK
        PIXY2UART_RXISR_ExitCallback();
    #endif /* PIXY2UART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (PIXY2UART_RX_INTERRUPT_ENABLED && (PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED)) */


#if (PIXY2UART_TX_INTERRUPT_ENABLED && PIXY2UART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: PIXY2UART_TXISR
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
    *  PIXY2UART_txBuffer - RAM buffer pointer for transmit data from.
    *  PIXY2UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  PIXY2UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(PIXY2UART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef PIXY2UART_TXISR_ENTRY_CALLBACK
        PIXY2UART_TXISR_EntryCallback();
    #endif /* PIXY2UART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START PIXY2UART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((PIXY2UART_txBufferRead != PIXY2UART_txBufferWrite) &&
             ((PIXY2UART_TXSTATUS_REG & PIXY2UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(PIXY2UART_txBufferRead >= PIXY2UART_TX_BUFFER_SIZE)
            {
                PIXY2UART_txBufferRead = 0u;
            }

            PIXY2UART_TXDATA_REG = PIXY2UART_txBuffer[PIXY2UART_txBufferRead];

            /* Set next pointer */
            PIXY2UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START PIXY2UART_TXISR_END` */

        /* `#END` */

    #ifdef PIXY2UART_TXISR_EXIT_CALLBACK
        PIXY2UART_TXISR_ExitCallback();
    #endif /* PIXY2UART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (PIXY2UART_TX_INTERRUPT_ENABLED && PIXY2UART_TX_ENABLED) */


/* [] END OF FILE */
