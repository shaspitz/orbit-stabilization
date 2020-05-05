/*******************************************************************************
* File Name: PIXY2UART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_PIXY2UART_H)
#define CY_UART_PIXY2UART_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define PIXY2UART_RX_ENABLED                     (1u)
#define PIXY2UART_TX_ENABLED                     (1u)
#define PIXY2UART_HD_ENABLED                     (0u)
#define PIXY2UART_RX_INTERRUPT_ENABLED           (0u)
#define PIXY2UART_TX_INTERRUPT_ENABLED           (0u)
#define PIXY2UART_INTERNAL_CLOCK_USED            (1u)
#define PIXY2UART_RXHW_ADDRESS_ENABLED           (0u)
#define PIXY2UART_OVER_SAMPLE_COUNT              (8u)
#define PIXY2UART_PARITY_TYPE                    (0u)
#define PIXY2UART_PARITY_TYPE_SW                 (0u)
#define PIXY2UART_BREAK_DETECT                   (0u)
#define PIXY2UART_BREAK_BITS_TX                  (13u)
#define PIXY2UART_BREAK_BITS_RX                  (13u)
#define PIXY2UART_TXCLKGEN_DP                    (1u)
#define PIXY2UART_USE23POLLING                   (1u)
#define PIXY2UART_FLOW_CONTROL                   (0u)
#define PIXY2UART_CLK_FREQ                       (0u)
#define PIXY2UART_TX_BUFFER_SIZE                 (4u)
#define PIXY2UART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define PIXY2UART_CONTROL_REG_REMOVED            (0u)
#else
    #define PIXY2UART_CONTROL_REG_REMOVED            (1u)
#endif /* End PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct PIXY2UART_backupStruct_
{
    uint8 enableState;

    #if(PIXY2UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End PIXY2UART_CONTROL_REG_REMOVED */

} PIXY2UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void PIXY2UART_Start(void) ;
void PIXY2UART_Stop(void) ;
uint8 PIXY2UART_ReadControlRegister(void) ;
void PIXY2UART_WriteControlRegister(uint8 control) ;

void PIXY2UART_Init(void) ;
void PIXY2UART_Enable(void) ;
void PIXY2UART_SaveConfig(void) ;
void PIXY2UART_RestoreConfig(void) ;
void PIXY2UART_Sleep(void) ;
void PIXY2UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )

    #if (PIXY2UART_RX_INTERRUPT_ENABLED)
        #define PIXY2UART_EnableRxInt()  CyIntEnable (PIXY2UART_RX_VECT_NUM)
        #define PIXY2UART_DisableRxInt() CyIntDisable(PIXY2UART_RX_VECT_NUM)
        CY_ISR_PROTO(PIXY2UART_RXISR);
    #endif /* PIXY2UART_RX_INTERRUPT_ENABLED */

    void PIXY2UART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void PIXY2UART_SetRxAddress1(uint8 address) ;
    void PIXY2UART_SetRxAddress2(uint8 address) ;

    void  PIXY2UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 PIXY2UART_ReadRxData(void) ;
    uint8 PIXY2UART_ReadRxStatus(void) ;
    uint8 PIXY2UART_GetChar(void) ;
    uint16 PIXY2UART_GetByte(void) ;
    uint8 PIXY2UART_GetRxBufferSize(void)
                                                            ;
    void PIXY2UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define PIXY2UART_GetRxInterruptSource   PIXY2UART_ReadRxStatus

#endif /* End (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(PIXY2UART_TX_ENABLED || PIXY2UART_HD_ENABLED)

    #if(PIXY2UART_TX_INTERRUPT_ENABLED)
        #define PIXY2UART_EnableTxInt()  CyIntEnable (PIXY2UART_TX_VECT_NUM)
        #define PIXY2UART_DisableTxInt() CyIntDisable(PIXY2UART_TX_VECT_NUM)
        #define PIXY2UART_SetPendingTxInt() CyIntSetPending(PIXY2UART_TX_VECT_NUM)
        #define PIXY2UART_ClearPendingTxInt() CyIntClearPending(PIXY2UART_TX_VECT_NUM)
        CY_ISR_PROTO(PIXY2UART_TXISR);
    #endif /* PIXY2UART_TX_INTERRUPT_ENABLED */

    void PIXY2UART_SetTxInterruptMode(uint8 intSrc) ;
    void PIXY2UART_WriteTxData(uint8 txDataByte) ;
    uint8 PIXY2UART_ReadTxStatus(void) ;
    void PIXY2UART_PutChar(uint8 txDataByte) ;
    void PIXY2UART_PutString(const char8 string[]) ;
    void PIXY2UART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void PIXY2UART_PutCRLF(uint8 txDataByte) ;
    void PIXY2UART_ClearTxBuffer(void) ;
    void PIXY2UART_SetTxAddressMode(uint8 addressMode) ;
    void PIXY2UART_SendBreak(uint8 retMode) ;
    uint8 PIXY2UART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define PIXY2UART_PutStringConst         PIXY2UART_PutString
    #define PIXY2UART_PutArrayConst          PIXY2UART_PutArray
    #define PIXY2UART_GetTxInterruptSource   PIXY2UART_ReadTxStatus

#endif /* End PIXY2UART_TX_ENABLED || PIXY2UART_HD_ENABLED */

#if(PIXY2UART_HD_ENABLED)
    void PIXY2UART_LoadRxConfig(void) ;
    void PIXY2UART_LoadTxConfig(void) ;
#endif /* End PIXY2UART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PIXY2UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    PIXY2UART_CyBtldrCommStart(void) CYSMALL ;
    void    PIXY2UART_CyBtldrCommStop(void) CYSMALL ;
    void    PIXY2UART_CyBtldrCommReset(void) CYSMALL ;
    cystatus PIXY2UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus PIXY2UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PIXY2UART)
        #define CyBtldrCommStart    PIXY2UART_CyBtldrCommStart
        #define CyBtldrCommStop     PIXY2UART_CyBtldrCommStop
        #define CyBtldrCommReset    PIXY2UART_CyBtldrCommReset
        #define CyBtldrCommWrite    PIXY2UART_CyBtldrCommWrite
        #define CyBtldrCommRead     PIXY2UART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_PIXY2UART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define PIXY2UART_BYTE2BYTE_TIME_OUT (25u)
    #define PIXY2UART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define PIXY2UART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define PIXY2UART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define PIXY2UART_SET_SPACE      (0x00u)
#define PIXY2UART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (PIXY2UART_TX_ENABLED) || (PIXY2UART_HD_ENABLED) )
    #if(PIXY2UART_TX_INTERRUPT_ENABLED)
        #define PIXY2UART_TX_VECT_NUM            (uint8)PIXY2UART_TXInternalInterrupt__INTC_NUMBER
        #define PIXY2UART_TX_PRIOR_NUM           (uint8)PIXY2UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PIXY2UART_TX_INTERRUPT_ENABLED */

    #define PIXY2UART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define PIXY2UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define PIXY2UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(PIXY2UART_TX_ENABLED)
        #define PIXY2UART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (PIXY2UART_HD_ENABLED) */
        #define PIXY2UART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (PIXY2UART_TX_ENABLED) */

    #define PIXY2UART_TX_STS_COMPLETE            (uint8)(0x01u << PIXY2UART_TX_STS_COMPLETE_SHIFT)
    #define PIXY2UART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << PIXY2UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define PIXY2UART_TX_STS_FIFO_FULL           (uint8)(0x01u << PIXY2UART_TX_STS_FIFO_FULL_SHIFT)
    #define PIXY2UART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << PIXY2UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (PIXY2UART_TX_ENABLED) || (PIXY2UART_HD_ENABLED)*/

#if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )
    #if(PIXY2UART_RX_INTERRUPT_ENABLED)
        #define PIXY2UART_RX_VECT_NUM            (uint8)PIXY2UART_RXInternalInterrupt__INTC_NUMBER
        #define PIXY2UART_RX_PRIOR_NUM           (uint8)PIXY2UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* PIXY2UART_RX_INTERRUPT_ENABLED */
    #define PIXY2UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define PIXY2UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define PIXY2UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define PIXY2UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define PIXY2UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define PIXY2UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define PIXY2UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define PIXY2UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define PIXY2UART_RX_STS_MRKSPC           (uint8)(0x01u << PIXY2UART_RX_STS_MRKSPC_SHIFT)
    #define PIXY2UART_RX_STS_BREAK            (uint8)(0x01u << PIXY2UART_RX_STS_BREAK_SHIFT)
    #define PIXY2UART_RX_STS_PAR_ERROR        (uint8)(0x01u << PIXY2UART_RX_STS_PAR_ERROR_SHIFT)
    #define PIXY2UART_RX_STS_STOP_ERROR       (uint8)(0x01u << PIXY2UART_RX_STS_STOP_ERROR_SHIFT)
    #define PIXY2UART_RX_STS_OVERRUN          (uint8)(0x01u << PIXY2UART_RX_STS_OVERRUN_SHIFT)
    #define PIXY2UART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << PIXY2UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define PIXY2UART_RX_STS_ADDR_MATCH       (uint8)(0x01u << PIXY2UART_RX_STS_ADDR_MATCH_SHIFT)
    #define PIXY2UART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << PIXY2UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define PIXY2UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */

/* Control Register definitions */
#define PIXY2UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define PIXY2UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define PIXY2UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define PIXY2UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define PIXY2UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define PIXY2UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define PIXY2UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define PIXY2UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define PIXY2UART_CTRL_HD_SEND               (uint8)(0x01u << PIXY2UART_CTRL_HD_SEND_SHIFT)
#define PIXY2UART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << PIXY2UART_CTRL_HD_SEND_BREAK_SHIFT)
#define PIXY2UART_CTRL_MARK                  (uint8)(0x01u << PIXY2UART_CTRL_MARK_SHIFT)
#define PIXY2UART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << PIXY2UART_CTRL_PARITY_TYPE0_SHIFT)
#define PIXY2UART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << PIXY2UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define PIXY2UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define PIXY2UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define PIXY2UART_SEND_BREAK                         (0x00u)
#define PIXY2UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define PIXY2UART_REINIT                             (0x02u)
#define PIXY2UART_SEND_WAIT_REINIT                   (0x03u)

#define PIXY2UART_OVER_SAMPLE_8                      (8u)
#define PIXY2UART_OVER_SAMPLE_16                     (16u)

#define PIXY2UART_BIT_CENTER                         (PIXY2UART_OVER_SAMPLE_COUNT - 2u)

#define PIXY2UART_FIFO_LENGTH                        (4u)
#define PIXY2UART_NUMBER_OF_START_BIT                (1u)
#define PIXY2UART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define PIXY2UART_TXBITCTR_BREAKBITS8X   ((PIXY2UART_BREAK_BITS_TX * PIXY2UART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define PIXY2UART_TXBITCTR_BREAKBITS ((PIXY2UART_BREAK_BITS_TX * PIXY2UART_OVER_SAMPLE_COUNT) - 1u)

#define PIXY2UART_HALF_BIT_COUNT   \
                            (((PIXY2UART_OVER_SAMPLE_COUNT / 2u) + (PIXY2UART_USE23POLLING * 1u)) - 2u)
#if (PIXY2UART_OVER_SAMPLE_COUNT == PIXY2UART_OVER_SAMPLE_8)
    #define PIXY2UART_HD_TXBITCTR_INIT   (((PIXY2UART_BREAK_BITS_TX + \
                            PIXY2UART_NUMBER_OF_START_BIT) * PIXY2UART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define PIXY2UART_RXBITCTR_INIT  ((((PIXY2UART_BREAK_BITS_RX + PIXY2UART_NUMBER_OF_START_BIT) \
                            * PIXY2UART_OVER_SAMPLE_COUNT) + PIXY2UART_HALF_BIT_COUNT) - 1u)

#else /* PIXY2UART_OVER_SAMPLE_COUNT == PIXY2UART_OVER_SAMPLE_16 */
    #define PIXY2UART_HD_TXBITCTR_INIT   ((8u * PIXY2UART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define PIXY2UART_RXBITCTR_INIT      (((7u * PIXY2UART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      PIXY2UART_HALF_BIT_COUNT)
#endif /* End PIXY2UART_OVER_SAMPLE_COUNT */

#define PIXY2UART_HD_RXBITCTR_INIT                   PIXY2UART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 PIXY2UART_initVar;
#if (PIXY2UART_TX_INTERRUPT_ENABLED && PIXY2UART_TX_ENABLED)
    extern volatile uint8 PIXY2UART_txBuffer[PIXY2UART_TX_BUFFER_SIZE];
    extern volatile uint8 PIXY2UART_txBufferRead;
    extern uint8 PIXY2UART_txBufferWrite;
#endif /* (PIXY2UART_TX_INTERRUPT_ENABLED && PIXY2UART_TX_ENABLED) */
#if (PIXY2UART_RX_INTERRUPT_ENABLED && (PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED))
    extern uint8 PIXY2UART_errorStatus;
    extern volatile uint8 PIXY2UART_rxBuffer[PIXY2UART_RX_BUFFER_SIZE];
    extern volatile uint8 PIXY2UART_rxBufferRead;
    extern volatile uint8 PIXY2UART_rxBufferWrite;
    extern volatile uint8 PIXY2UART_rxBufferLoopDetect;
    extern volatile uint8 PIXY2UART_rxBufferOverflow;
    #if (PIXY2UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 PIXY2UART_rxAddressMode;
        extern volatile uint8 PIXY2UART_rxAddressDetected;
    #endif /* (PIXY2UART_RXHW_ADDRESS_ENABLED) */
#endif /* (PIXY2UART_RX_INTERRUPT_ENABLED && (PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define PIXY2UART__B_UART__AM_SW_BYTE_BYTE 1
#define PIXY2UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define PIXY2UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define PIXY2UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define PIXY2UART__B_UART__AM_NONE 0

#define PIXY2UART__B_UART__NONE_REVB 0
#define PIXY2UART__B_UART__EVEN_REVB 1
#define PIXY2UART__B_UART__ODD_REVB 2
#define PIXY2UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define PIXY2UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define PIXY2UART_NUMBER_OF_STOP_BITS    (1u)

#if (PIXY2UART_RXHW_ADDRESS_ENABLED)
    #define PIXY2UART_RX_ADDRESS_MODE    (0u)
    #define PIXY2UART_RX_HW_ADDRESS1     (0u)
    #define PIXY2UART_RX_HW_ADDRESS2     (0u)
#endif /* (PIXY2UART_RXHW_ADDRESS_ENABLED) */

#define PIXY2UART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << PIXY2UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << PIXY2UART_RX_STS_OVERRUN_SHIFT))

#define PIXY2UART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << PIXY2UART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << PIXY2UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << PIXY2UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << PIXY2UART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define PIXY2UART_CONTROL_REG \
                            (* (reg8 *) PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define PIXY2UART_CONTROL_PTR \
                            (  (reg8 *) PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(PIXY2UART_TX_ENABLED)
    #define PIXY2UART_TXDATA_REG          (* (reg8 *) PIXY2UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define PIXY2UART_TXDATA_PTR          (  (reg8 *) PIXY2UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define PIXY2UART_TXDATA_AUX_CTL_REG  (* (reg8 *) PIXY2UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PIXY2UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) PIXY2UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define PIXY2UART_TXSTATUS_REG        (* (reg8 *) PIXY2UART_BUART_sTX_TxSts__STATUS_REG)
    #define PIXY2UART_TXSTATUS_PTR        (  (reg8 *) PIXY2UART_BUART_sTX_TxSts__STATUS_REG)
    #define PIXY2UART_TXSTATUS_MASK_REG   (* (reg8 *) PIXY2UART_BUART_sTX_TxSts__MASK_REG)
    #define PIXY2UART_TXSTATUS_MASK_PTR   (  (reg8 *) PIXY2UART_BUART_sTX_TxSts__MASK_REG)
    #define PIXY2UART_TXSTATUS_ACTL_REG   (* (reg8 *) PIXY2UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define PIXY2UART_TXSTATUS_ACTL_PTR   (  (reg8 *) PIXY2UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(PIXY2UART_TXCLKGEN_DP)
        #define PIXY2UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PIXY2UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define PIXY2UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define PIXY2UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define PIXY2UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PIXY2UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define PIXY2UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PIXY2UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define PIXY2UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define PIXY2UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) PIXY2UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* PIXY2UART_TXCLKGEN_DP */

#endif /* End PIXY2UART_TX_ENABLED */

#if(PIXY2UART_HD_ENABLED)

    #define PIXY2UART_TXDATA_REG             (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define PIXY2UART_TXDATA_PTR             (  (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define PIXY2UART_TXDATA_AUX_CTL_REG     (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define PIXY2UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PIXY2UART_TXSTATUS_REG           (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_REG )
    #define PIXY2UART_TXSTATUS_PTR           (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_REG )
    #define PIXY2UART_TXSTATUS_MASK_REG      (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__MASK_REG )
    #define PIXY2UART_TXSTATUS_MASK_PTR      (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__MASK_REG )
    #define PIXY2UART_TXSTATUS_ACTL_REG      (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PIXY2UART_TXSTATUS_ACTL_PTR      (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End PIXY2UART_HD_ENABLED */

#if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )
    #define PIXY2UART_RXDATA_REG             (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define PIXY2UART_RXDATA_PTR             (  (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define PIXY2UART_RXADDRESS1_REG         (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define PIXY2UART_RXADDRESS1_PTR         (  (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define PIXY2UART_RXADDRESS2_REG         (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define PIXY2UART_RXADDRESS2_PTR         (  (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define PIXY2UART_RXDATA_AUX_CTL_REG     (* (reg8 *) PIXY2UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define PIXY2UART_RXBITCTR_PERIOD_REG    (* (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PIXY2UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define PIXY2UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PIXY2UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define PIXY2UART_RXBITCTR_COUNTER_REG   (* (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define PIXY2UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) PIXY2UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define PIXY2UART_RXSTATUS_REG           (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_REG )
    #define PIXY2UART_RXSTATUS_PTR           (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_REG )
    #define PIXY2UART_RXSTATUS_MASK_REG      (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__MASK_REG )
    #define PIXY2UART_RXSTATUS_MASK_PTR      (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__MASK_REG )
    #define PIXY2UART_RXSTATUS_ACTL_REG      (* (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define PIXY2UART_RXSTATUS_ACTL_PTR      (  (reg8 *) PIXY2UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */

#if(PIXY2UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define PIXY2UART_INTCLOCK_CLKEN_REG     (* (reg8 *) PIXY2UART_IntClock__PM_ACT_CFG)
    #define PIXY2UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) PIXY2UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define PIXY2UART_INTCLOCK_CLKEN_MASK    PIXY2UART_IntClock__PM_ACT_MSK
#endif /* End PIXY2UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(PIXY2UART_TX_ENABLED)
    #define PIXY2UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End PIXY2UART_TX_ENABLED */

#if(PIXY2UART_HD_ENABLED)
    #define PIXY2UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End PIXY2UART_HD_ENABLED */

#if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )
    #define PIXY2UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define PIXY2UART_WAIT_1_MS      PIXY2UART_BL_CHK_DELAY_MS   

#define PIXY2UART_TXBUFFERSIZE   PIXY2UART_TX_BUFFER_SIZE
#define PIXY2UART_RXBUFFERSIZE   PIXY2UART_RX_BUFFER_SIZE

#if (PIXY2UART_RXHW_ADDRESS_ENABLED)
    #define PIXY2UART_RXADDRESSMODE  PIXY2UART_RX_ADDRESS_MODE
    #define PIXY2UART_RXHWADDRESS1   PIXY2UART_RX_HW_ADDRESS1
    #define PIXY2UART_RXHWADDRESS2   PIXY2UART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define PIXY2UART_RXAddressMode  PIXY2UART_RXADDRESSMODE
#endif /* (PIXY2UART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define PIXY2UART_initvar                    PIXY2UART_initVar

#define PIXY2UART_RX_Enabled                 PIXY2UART_RX_ENABLED
#define PIXY2UART_TX_Enabled                 PIXY2UART_TX_ENABLED
#define PIXY2UART_HD_Enabled                 PIXY2UART_HD_ENABLED
#define PIXY2UART_RX_IntInterruptEnabled     PIXY2UART_RX_INTERRUPT_ENABLED
#define PIXY2UART_TX_IntInterruptEnabled     PIXY2UART_TX_INTERRUPT_ENABLED
#define PIXY2UART_InternalClockUsed          PIXY2UART_INTERNAL_CLOCK_USED
#define PIXY2UART_RXHW_Address_Enabled       PIXY2UART_RXHW_ADDRESS_ENABLED
#define PIXY2UART_OverSampleCount            PIXY2UART_OVER_SAMPLE_COUNT
#define PIXY2UART_ParityType                 PIXY2UART_PARITY_TYPE

#if( PIXY2UART_TX_ENABLED && (PIXY2UART_TXBUFFERSIZE > PIXY2UART_FIFO_LENGTH))
    #define PIXY2UART_TXBUFFER               PIXY2UART_txBuffer
    #define PIXY2UART_TXBUFFERREAD           PIXY2UART_txBufferRead
    #define PIXY2UART_TXBUFFERWRITE          PIXY2UART_txBufferWrite
#endif /* End PIXY2UART_TX_ENABLED */
#if( ( PIXY2UART_RX_ENABLED || PIXY2UART_HD_ENABLED ) && \
     (PIXY2UART_RXBUFFERSIZE > PIXY2UART_FIFO_LENGTH) )
    #define PIXY2UART_RXBUFFER               PIXY2UART_rxBuffer
    #define PIXY2UART_RXBUFFERREAD           PIXY2UART_rxBufferRead
    #define PIXY2UART_RXBUFFERWRITE          PIXY2UART_rxBufferWrite
    #define PIXY2UART_RXBUFFERLOOPDETECT     PIXY2UART_rxBufferLoopDetect
    #define PIXY2UART_RXBUFFER_OVERFLOW      PIXY2UART_rxBufferOverflow
#endif /* End PIXY2UART_RX_ENABLED */

#ifdef PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define PIXY2UART_CONTROL                PIXY2UART_CONTROL_REG
#endif /* End PIXY2UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(PIXY2UART_TX_ENABLED)
    #define PIXY2UART_TXDATA                 PIXY2UART_TXDATA_REG
    #define PIXY2UART_TXSTATUS               PIXY2UART_TXSTATUS_REG
    #define PIXY2UART_TXSTATUS_MASK          PIXY2UART_TXSTATUS_MASK_REG
    #define PIXY2UART_TXSTATUS_ACTL          PIXY2UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(PIXY2UART_TXCLKGEN_DP)
        #define PIXY2UART_TXBITCLKGEN_CTR        PIXY2UART_TXBITCLKGEN_CTR_REG
        #define PIXY2UART_TXBITCLKTX_COMPLETE    PIXY2UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define PIXY2UART_TXBITCTR_PERIOD        PIXY2UART_TXBITCTR_PERIOD_REG
        #define PIXY2UART_TXBITCTR_CONTROL       PIXY2UART_TXBITCTR_CONTROL_REG
        #define PIXY2UART_TXBITCTR_COUNTER       PIXY2UART_TXBITCTR_COUNTER_REG
    #endif /* PIXY2UART_TXCLKGEN_DP */
#endif /* End PIXY2UART_TX_ENABLED */

#if(PIXY2UART_HD_ENABLED)
    #define PIXY2UART_TXDATA                 PIXY2UART_TXDATA_REG
    #define PIXY2UART_TXSTATUS               PIXY2UART_TXSTATUS_REG
    #define PIXY2UART_TXSTATUS_MASK          PIXY2UART_TXSTATUS_MASK_REG
    #define PIXY2UART_TXSTATUS_ACTL          PIXY2UART_TXSTATUS_ACTL_REG
#endif /* End PIXY2UART_HD_ENABLED */

#if( (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) )
    #define PIXY2UART_RXDATA                 PIXY2UART_RXDATA_REG
    #define PIXY2UART_RXADDRESS1             PIXY2UART_RXADDRESS1_REG
    #define PIXY2UART_RXADDRESS2             PIXY2UART_RXADDRESS2_REG
    #define PIXY2UART_RXBITCTR_PERIOD        PIXY2UART_RXBITCTR_PERIOD_REG
    #define PIXY2UART_RXBITCTR_CONTROL       PIXY2UART_RXBITCTR_CONTROL_REG
    #define PIXY2UART_RXBITCTR_COUNTER       PIXY2UART_RXBITCTR_COUNTER_REG
    #define PIXY2UART_RXSTATUS               PIXY2UART_RXSTATUS_REG
    #define PIXY2UART_RXSTATUS_MASK          PIXY2UART_RXSTATUS_MASK_REG
    #define PIXY2UART_RXSTATUS_ACTL          PIXY2UART_RXSTATUS_ACTL_REG
#endif /* End  (PIXY2UART_RX_ENABLED) || (PIXY2UART_HD_ENABLED) */

#if(PIXY2UART_INTERNAL_CLOCK_USED)
    #define PIXY2UART_INTCLOCK_CLKEN         PIXY2UART_INTCLOCK_CLKEN_REG
#endif /* End PIXY2UART_INTERNAL_CLOCK_USED */

#define PIXY2UART_WAIT_FOR_COMLETE_REINIT    PIXY2UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_PIXY2UART_H */


/* [] END OF FILE */
