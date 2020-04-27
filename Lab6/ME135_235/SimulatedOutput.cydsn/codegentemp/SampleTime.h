/*******************************************************************************
* File Name: SampleTime.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_SampleTime_H)
#define CY_TIMER_SampleTime_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 SampleTime_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SampleTime_Resolution                 16u
#define SampleTime_UsingFixedFunction         1u
#define SampleTime_UsingHWCaptureCounter      0u
#define SampleTime_SoftwareCaptureMode        0u
#define SampleTime_SoftwareTriggerMode        0u
#define SampleTime_UsingHWEnable              0u
#define SampleTime_EnableTriggerMode          0u
#define SampleTime_InterruptOnCaptureCount    0u
#define SampleTime_RunModeUsed                0u
#define SampleTime_ControlRegRemoved          0u

#if defined(SampleTime_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define SampleTime_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (SampleTime_UsingFixedFunction)
    #define SampleTime_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define SampleTime_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End SampleTime_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!SampleTime_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (SampleTime_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!SampleTime_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}SampleTime_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SampleTime_Start(void) ;
void    SampleTime_Stop(void) ;

void    SampleTime_SetInterruptMode(uint8 interruptMode) ;
uint8   SampleTime_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SampleTime_GetInterruptSource() SampleTime_ReadStatusRegister()

#if(!SampleTime_UDB_CONTROL_REG_REMOVED)
    uint8   SampleTime_ReadControlRegister(void) ;
    void    SampleTime_WriteControlRegister(uint8 control) ;
#endif /* (!SampleTime_UDB_CONTROL_REG_REMOVED) */

uint16  SampleTime_ReadPeriod(void) ;
void    SampleTime_WritePeriod(uint16 period) ;
uint16  SampleTime_ReadCounter(void) ;
void    SampleTime_WriteCounter(uint16 counter) ;
uint16  SampleTime_ReadCapture(void) ;
void    SampleTime_SoftwareCapture(void) ;

#if(!SampleTime_UsingFixedFunction) /* UDB Prototypes */
    #if (SampleTime_SoftwareCaptureMode)
        void    SampleTime_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SampleTime_UsingFixedFunction) */

    #if (SampleTime_SoftwareTriggerMode)
        void    SampleTime_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SampleTime_SoftwareTriggerMode) */

    #if (SampleTime_EnableTriggerMode)
        void    SampleTime_EnableTrigger(void) ;
        void    SampleTime_DisableTrigger(void) ;
    #endif /* (SampleTime_EnableTriggerMode) */


    #if(SampleTime_InterruptOnCaptureCount)
        void    SampleTime_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (SampleTime_InterruptOnCaptureCount) */

    #if (SampleTime_UsingHWCaptureCounter)
        void    SampleTime_SetCaptureCount(uint8 captureCount) ;
        uint8   SampleTime_ReadCaptureCount(void) ;
    #endif /* (SampleTime_UsingHWCaptureCounter) */

    void SampleTime_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SampleTime_Init(void)          ;
void SampleTime_Enable(void)        ;
void SampleTime_SaveConfig(void)    ;
void SampleTime_RestoreConfig(void) ;
void SampleTime_Sleep(void)         ;
void SampleTime_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SampleTime__B_TIMER__CM_NONE 0
#define SampleTime__B_TIMER__CM_RISINGEDGE 1
#define SampleTime__B_TIMER__CM_FALLINGEDGE 2
#define SampleTime__B_TIMER__CM_EITHEREDGE 3
#define SampleTime__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SampleTime__B_TIMER__TM_NONE 0x00u
#define SampleTime__B_TIMER__TM_RISINGEDGE 0x04u
#define SampleTime__B_TIMER__TM_FALLINGEDGE 0x08u
#define SampleTime__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SampleTime__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SampleTime_INIT_PERIOD             23999u
#define SampleTime_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << SampleTime_CTRL_CAP_MODE_SHIFT))
#define SampleTime_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << SampleTime_CTRL_TRIG_MODE_SHIFT))
#if (SampleTime_UsingFixedFunction)
    #define SampleTime_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SampleTime_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << SampleTime_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define SampleTime_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << SampleTime_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SampleTime_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SampleTime_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (SampleTime_UsingFixedFunction) */
#define SampleTime_INIT_CAPTURE_COUNT      (2u)
#define SampleTime_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << SampleTime_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (SampleTime_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SampleTime_STATUS         (*(reg8 *) SampleTime_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SampleTime_STATUS_MASK    (*(reg8 *) SampleTime_TimerHW__SR0 )
    #define SampleTime_CONTROL        (*(reg8 *) SampleTime_TimerHW__CFG0)
    #define SampleTime_CONTROL2       (*(reg8 *) SampleTime_TimerHW__CFG1)
    #define SampleTime_CONTROL2_PTR   ( (reg8 *) SampleTime_TimerHW__CFG1)
    #define SampleTime_RT1            (*(reg8 *) SampleTime_TimerHW__RT1)
    #define SampleTime_RT1_PTR        ( (reg8 *) SampleTime_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SampleTime_CONTROL3       (*(reg8 *) SampleTime_TimerHW__CFG2)
        #define SampleTime_CONTROL3_PTR   ( (reg8 *) SampleTime_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SampleTime_GLOBAL_ENABLE  (*(reg8 *) SampleTime_TimerHW__PM_ACT_CFG)
    #define SampleTime_GLOBAL_STBY_ENABLE  (*(reg8 *) SampleTime_TimerHW__PM_STBY_CFG)

    #define SampleTime_CAPTURE_LSB         (* (reg16 *) SampleTime_TimerHW__CAP0 )
    #define SampleTime_CAPTURE_LSB_PTR       ((reg16 *) SampleTime_TimerHW__CAP0 )
    #define SampleTime_PERIOD_LSB          (* (reg16 *) SampleTime_TimerHW__PER0 )
    #define SampleTime_PERIOD_LSB_PTR        ((reg16 *) SampleTime_TimerHW__PER0 )
    #define SampleTime_COUNTER_LSB         (* (reg16 *) SampleTime_TimerHW__CNT_CMP0 )
    #define SampleTime_COUNTER_LSB_PTR       ((reg16 *) SampleTime_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SampleTime_BLOCK_EN_MASK                     SampleTime_TimerHW__PM_ACT_MSK
    #define SampleTime_BLOCK_STBY_EN_MASK                SampleTime_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SampleTime_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SampleTime_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SampleTime_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SampleTime_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SampleTime_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SampleTime_CTRL_ENABLE                        ((uint8)((uint8)0x01u << SampleTime_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SampleTime_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SampleTime_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << SampleTime_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SampleTime_CTRL_MODE_SHIFT                 0x01u
        #define SampleTime_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << SampleTime_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SampleTime_CTRL_RCOD_SHIFT        0x02u
        #define SampleTime_CTRL_ENBL_SHIFT        0x00u
        #define SampleTime_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SampleTime_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << SampleTime_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define SampleTime_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << SampleTime_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define SampleTime_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << SampleTime_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define SampleTime_CTRL_RCOD       ((uint8)((uint8)0x03u << SampleTime_CTRL_RCOD_SHIFT))
        #define SampleTime_CTRL_ENBL       ((uint8)((uint8)0x80u << SampleTime_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SampleTime_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SampleTime_RT1_MASK                        ((uint8)((uint8)0x03u << SampleTime_RT1_SHIFT))
    #define SampleTime_SYNC                            ((uint8)((uint8)0x03u << SampleTime_RT1_SHIFT))
    #define SampleTime_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SampleTime_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << SampleTime_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define SampleTime_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << SampleTime_SYNCDSI_SHIFT))

    #define SampleTime_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << SampleTime_CTRL_MODE_SHIFT))
    #define SampleTime_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << SampleTime_CTRL_MODE_SHIFT))
    #define SampleTime_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << SampleTime_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SampleTime_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SampleTime_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SampleTime_STATUS_TC_INT_MASK_SHIFT        (SampleTime_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SampleTime_STATUS_CAPTURE_INT_MASK_SHIFT   (SampleTime_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define SampleTime_STATUS_TC                       ((uint8)((uint8)0x01u << SampleTime_STATUS_TC_SHIFT))
    #define SampleTime_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << SampleTime_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SampleTime_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << SampleTime_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SampleTime_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << SampleTime_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SampleTime_STATUS              (* (reg8 *) SampleTime_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SampleTime_STATUS_MASK         (* (reg8 *) SampleTime_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SampleTime_STATUS_AUX_CTRL     (* (reg8 *) SampleTime_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SampleTime_CONTROL             (* (reg8 *) SampleTime_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(SampleTime_Resolution <= 8u) /* 8-bit Timer */
        #define SampleTime_CAPTURE_LSB         (* (reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SampleTime_CAPTURE_LSB_PTR       ((reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SampleTime_PERIOD_LSB          (* (reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SampleTime_PERIOD_LSB_PTR        ((reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SampleTime_COUNTER_LSB         (* (reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define SampleTime_COUNTER_LSB_PTR       ((reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(SampleTime_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define SampleTime_CAPTURE_LSB         (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SampleTime_CAPTURE_LSB_PTR       ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SampleTime_PERIOD_LSB          (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SampleTime_PERIOD_LSB_PTR        ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SampleTime_COUNTER_LSB         (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define SampleTime_COUNTER_LSB_PTR       ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define SampleTime_CAPTURE_LSB         (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define SampleTime_CAPTURE_LSB_PTR       ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define SampleTime_PERIOD_LSB          (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define SampleTime_PERIOD_LSB_PTR        ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define SampleTime_COUNTER_LSB         (* (reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define SampleTime_COUNTER_LSB_PTR       ((reg16 *) SampleTime_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(SampleTime_Resolution <= 24u)/* 24-bit Timer */
        #define SampleTime_CAPTURE_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SampleTime_CAPTURE_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define SampleTime_PERIOD_LSB          (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SampleTime_PERIOD_LSB_PTR        ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define SampleTime_COUNTER_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define SampleTime_COUNTER_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define SampleTime_CAPTURE_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SampleTime_CAPTURE_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define SampleTime_PERIOD_LSB          (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SampleTime_PERIOD_LSB_PTR        ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define SampleTime_COUNTER_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define SampleTime_COUNTER_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define SampleTime_CAPTURE_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define SampleTime_CAPTURE_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define SampleTime_PERIOD_LSB          (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define SampleTime_PERIOD_LSB_PTR        ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define SampleTime_COUNTER_LSB         (* (reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define SampleTime_COUNTER_LSB_PTR       ((reg32 *) SampleTime_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define SampleTime_COUNTER_LSB_PTR_8BIT       ((reg8 *) SampleTime_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (SampleTime_UsingHWCaptureCounter)
        #define SampleTime_CAP_COUNT              (*(reg8 *) SampleTime_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SampleTime_CAP_COUNT_PTR          ( (reg8 *) SampleTime_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SampleTime_CAPTURE_COUNT_CTRL     (*(reg8 *) SampleTime_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SampleTime_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SampleTime_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SampleTime_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SampleTime_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SampleTime_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SampleTime_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SampleTime_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SampleTime_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SampleTime_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << SampleTime_CTRL_INTCNT_SHIFT))
    #define SampleTime_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << SampleTime_CTRL_TRIG_MODE_SHIFT))
    #define SampleTime_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << SampleTime_CTRL_TRIG_EN_SHIFT))
    #define SampleTime_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << SampleTime_CTRL_CAP_MODE_SHIFT))
    #define SampleTime_CTRL_ENABLE                    ((uint8)((uint8)0x01u << SampleTime_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SampleTime_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SampleTime_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SampleTime_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SampleTime_STATUS_TC_INT_MASK_SHIFT       SampleTime_STATUS_TC_SHIFT
    #define SampleTime_STATUS_CAPTURE_INT_MASK_SHIFT  SampleTime_STATUS_CAPTURE_SHIFT
    #define SampleTime_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SampleTime_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SampleTime_STATUS_FIFOFULL_INT_MASK_SHIFT SampleTime_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SampleTime_STATUS_TC                      ((uint8)((uint8)0x01u << SampleTime_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define SampleTime_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << SampleTime_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SampleTime_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << SampleTime_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SampleTime_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << SampleTime_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SampleTime_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << SampleTime_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SampleTime_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << SampleTime_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SampleTime_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << SampleTime_STATUS_FIFOFULL_SHIFT))

    #define SampleTime_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SampleTime_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SampleTime_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SampleTime_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SampleTime_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SampleTime_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_SampleTime_H */


/* [] END OF FILE */
