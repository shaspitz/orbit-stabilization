/*******************************************************************************
* File Name: SteppeStep.h
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

#if !defined(CY_TIMER_SteppeStep_H)
#define CY_TIMER_SteppeStep_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 SteppeStep_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SteppeStep_Resolution                 32u
#define SteppeStep_UsingFixedFunction         0u
#define SteppeStep_UsingHWCaptureCounter      0u
#define SteppeStep_SoftwareCaptureMode        0u
#define SteppeStep_SoftwareTriggerMode        0u
#define SteppeStep_UsingHWEnable              1u
#define SteppeStep_EnableTriggerMode          0u
#define SteppeStep_InterruptOnCaptureCount    0u
#define SteppeStep_RunModeUsed                0u
#define SteppeStep_ControlRegRemoved          1u

#if defined(SteppeStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define SteppeStep_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (SteppeStep_UsingFixedFunction)
    #define SteppeStep_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define SteppeStep_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End SteppeStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!SteppeStep_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (SteppeStep_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!SteppeStep_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}SteppeStep_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SteppeStep_Start(void) ;
void    SteppeStep_Stop(void) ;

void    SteppeStep_SetInterruptMode(uint8 interruptMode) ;
uint8   SteppeStep_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SteppeStep_GetInterruptSource() SteppeStep_ReadStatusRegister()

#if(!SteppeStep_UDB_CONTROL_REG_REMOVED)
    uint8   SteppeStep_ReadControlRegister(void) ;
    void    SteppeStep_WriteControlRegister(uint8 control) ;
#endif /* (!SteppeStep_UDB_CONTROL_REG_REMOVED) */

uint32  SteppeStep_ReadPeriod(void) ;
void    SteppeStep_WritePeriod(uint32 period) ;
uint32  SteppeStep_ReadCounter(void) ;
void    SteppeStep_WriteCounter(uint32 counter) ;
uint32  SteppeStep_ReadCapture(void) ;
void    SteppeStep_SoftwareCapture(void) ;

#if(!SteppeStep_UsingFixedFunction) /* UDB Prototypes */
    #if (SteppeStep_SoftwareCaptureMode)
        void    SteppeStep_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SteppeStep_UsingFixedFunction) */

    #if (SteppeStep_SoftwareTriggerMode)
        void    SteppeStep_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SteppeStep_SoftwareTriggerMode) */

    #if (SteppeStep_EnableTriggerMode)
        void    SteppeStep_EnableTrigger(void) ;
        void    SteppeStep_DisableTrigger(void) ;
    #endif /* (SteppeStep_EnableTriggerMode) */


    #if(SteppeStep_InterruptOnCaptureCount)
        void    SteppeStep_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (SteppeStep_InterruptOnCaptureCount) */

    #if (SteppeStep_UsingHWCaptureCounter)
        void    SteppeStep_SetCaptureCount(uint8 captureCount) ;
        uint8   SteppeStep_ReadCaptureCount(void) ;
    #endif /* (SteppeStep_UsingHWCaptureCounter) */

    void SteppeStep_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SteppeStep_Init(void)          ;
void SteppeStep_Enable(void)        ;
void SteppeStep_SaveConfig(void)    ;
void SteppeStep_RestoreConfig(void) ;
void SteppeStep_Sleep(void)         ;
void SteppeStep_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SteppeStep__B_TIMER__CM_NONE 0
#define SteppeStep__B_TIMER__CM_RISINGEDGE 1
#define SteppeStep__B_TIMER__CM_FALLINGEDGE 2
#define SteppeStep__B_TIMER__CM_EITHEREDGE 3
#define SteppeStep__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SteppeStep__B_TIMER__TM_NONE 0x00u
#define SteppeStep__B_TIMER__TM_RISINGEDGE 0x04u
#define SteppeStep__B_TIMER__TM_FALLINGEDGE 0x08u
#define SteppeStep__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SteppeStep__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SteppeStep_INIT_PERIOD             4294967295u
#define SteppeStep_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << SteppeStep_CTRL_CAP_MODE_SHIFT))
#define SteppeStep_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << SteppeStep_CTRL_TRIG_MODE_SHIFT))
#if (SteppeStep_UsingFixedFunction)
    #define SteppeStep_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << SteppeStep_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << SteppeStep_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define SteppeStep_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << SteppeStep_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SteppeStep_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << SteppeStep_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (SteppeStep_UsingFixedFunction) */
#define SteppeStep_INIT_CAPTURE_COUNT      (2u)
#define SteppeStep_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << SteppeStep_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (SteppeStep_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SteppeStep_STATUS         (*(reg8 *) SteppeStep_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SteppeStep_STATUS_MASK    (*(reg8 *) SteppeStep_TimerHW__SR0 )
    #define SteppeStep_CONTROL        (*(reg8 *) SteppeStep_TimerHW__CFG0)
    #define SteppeStep_CONTROL2       (*(reg8 *) SteppeStep_TimerHW__CFG1)
    #define SteppeStep_CONTROL2_PTR   ( (reg8 *) SteppeStep_TimerHW__CFG1)
    #define SteppeStep_RT1            (*(reg8 *) SteppeStep_TimerHW__RT1)
    #define SteppeStep_RT1_PTR        ( (reg8 *) SteppeStep_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SteppeStep_CONTROL3       (*(reg8 *) SteppeStep_TimerHW__CFG2)
        #define SteppeStep_CONTROL3_PTR   ( (reg8 *) SteppeStep_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SteppeStep_GLOBAL_ENABLE  (*(reg8 *) SteppeStep_TimerHW__PM_ACT_CFG)
    #define SteppeStep_GLOBAL_STBY_ENABLE  (*(reg8 *) SteppeStep_TimerHW__PM_STBY_CFG)

    #define SteppeStep_CAPTURE_LSB         (* (reg16 *) SteppeStep_TimerHW__CAP0 )
    #define SteppeStep_CAPTURE_LSB_PTR       ((reg16 *) SteppeStep_TimerHW__CAP0 )
    #define SteppeStep_PERIOD_LSB          (* (reg16 *) SteppeStep_TimerHW__PER0 )
    #define SteppeStep_PERIOD_LSB_PTR        ((reg16 *) SteppeStep_TimerHW__PER0 )
    #define SteppeStep_COUNTER_LSB         (* (reg16 *) SteppeStep_TimerHW__CNT_CMP0 )
    #define SteppeStep_COUNTER_LSB_PTR       ((reg16 *) SteppeStep_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SteppeStep_BLOCK_EN_MASK                     SteppeStep_TimerHW__PM_ACT_MSK
    #define SteppeStep_BLOCK_STBY_EN_MASK                SteppeStep_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SteppeStep_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SteppeStep_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SteppeStep_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SteppeStep_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SteppeStep_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SteppeStep_CTRL_ENABLE                        ((uint8)((uint8)0x01u << SteppeStep_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SteppeStep_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SteppeStep_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << SteppeStep_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SteppeStep_CTRL_MODE_SHIFT                 0x01u
        #define SteppeStep_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << SteppeStep_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SteppeStep_CTRL_RCOD_SHIFT        0x02u
        #define SteppeStep_CTRL_ENBL_SHIFT        0x00u
        #define SteppeStep_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SteppeStep_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << SteppeStep_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define SteppeStep_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << SteppeStep_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define SteppeStep_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << SteppeStep_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define SteppeStep_CTRL_RCOD       ((uint8)((uint8)0x03u << SteppeStep_CTRL_RCOD_SHIFT))
        #define SteppeStep_CTRL_ENBL       ((uint8)((uint8)0x80u << SteppeStep_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SteppeStep_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SteppeStep_RT1_MASK                        ((uint8)((uint8)0x03u << SteppeStep_RT1_SHIFT))
    #define SteppeStep_SYNC                            ((uint8)((uint8)0x03u << SteppeStep_RT1_SHIFT))
    #define SteppeStep_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SteppeStep_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << SteppeStep_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define SteppeStep_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << SteppeStep_SYNCDSI_SHIFT))

    #define SteppeStep_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << SteppeStep_CTRL_MODE_SHIFT))
    #define SteppeStep_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << SteppeStep_CTRL_MODE_SHIFT))
    #define SteppeStep_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << SteppeStep_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SteppeStep_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SteppeStep_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SteppeStep_STATUS_TC_INT_MASK_SHIFT        (SteppeStep_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SteppeStep_STATUS_CAPTURE_INT_MASK_SHIFT   (SteppeStep_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define SteppeStep_STATUS_TC                       ((uint8)((uint8)0x01u << SteppeStep_STATUS_TC_SHIFT))
    #define SteppeStep_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << SteppeStep_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SteppeStep_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << SteppeStep_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SteppeStep_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << SteppeStep_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SteppeStep_STATUS              (* (reg8 *) SteppeStep_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SteppeStep_STATUS_MASK         (* (reg8 *) SteppeStep_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SteppeStep_STATUS_AUX_CTRL     (* (reg8 *) SteppeStep_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SteppeStep_CONTROL             (* (reg8 *) SteppeStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(SteppeStep_Resolution <= 8u) /* 8-bit Timer */
        #define SteppeStep_CAPTURE_LSB         (* (reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define SteppeStep_CAPTURE_LSB_PTR       ((reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define SteppeStep_PERIOD_LSB          (* (reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define SteppeStep_PERIOD_LSB_PTR        ((reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define SteppeStep_COUNTER_LSB         (* (reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define SteppeStep_COUNTER_LSB_PTR       ((reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(SteppeStep_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define SteppeStep_CAPTURE_LSB         (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define SteppeStep_CAPTURE_LSB_PTR       ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define SteppeStep_PERIOD_LSB          (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define SteppeStep_PERIOD_LSB_PTR        ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define SteppeStep_COUNTER_LSB         (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define SteppeStep_COUNTER_LSB_PTR       ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define SteppeStep_CAPTURE_LSB         (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define SteppeStep_CAPTURE_LSB_PTR       ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define SteppeStep_PERIOD_LSB          (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define SteppeStep_PERIOD_LSB_PTR        ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define SteppeStep_COUNTER_LSB         (* (reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define SteppeStep_COUNTER_LSB_PTR       ((reg16 *) SteppeStep_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(SteppeStep_Resolution <= 24u)/* 24-bit Timer */
        #define SteppeStep_CAPTURE_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define SteppeStep_CAPTURE_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define SteppeStep_PERIOD_LSB          (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define SteppeStep_PERIOD_LSB_PTR        ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define SteppeStep_COUNTER_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define SteppeStep_COUNTER_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define SteppeStep_CAPTURE_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define SteppeStep_CAPTURE_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define SteppeStep_PERIOD_LSB          (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define SteppeStep_PERIOD_LSB_PTR        ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define SteppeStep_COUNTER_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define SteppeStep_COUNTER_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define SteppeStep_CAPTURE_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define SteppeStep_CAPTURE_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define SteppeStep_PERIOD_LSB          (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define SteppeStep_PERIOD_LSB_PTR        ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define SteppeStep_COUNTER_LSB         (* (reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define SteppeStep_COUNTER_LSB_PTR       ((reg32 *) SteppeStep_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define SteppeStep_COUNTER_LSB_PTR_8BIT       ((reg8 *) SteppeStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (SteppeStep_UsingHWCaptureCounter)
        #define SteppeStep_CAP_COUNT              (*(reg8 *) SteppeStep_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SteppeStep_CAP_COUNT_PTR          ( (reg8 *) SteppeStep_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SteppeStep_CAPTURE_COUNT_CTRL     (*(reg8 *) SteppeStep_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SteppeStep_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SteppeStep_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SteppeStep_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SteppeStep_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SteppeStep_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SteppeStep_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SteppeStep_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SteppeStep_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SteppeStep_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << SteppeStep_CTRL_INTCNT_SHIFT))
    #define SteppeStep_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << SteppeStep_CTRL_TRIG_MODE_SHIFT))
    #define SteppeStep_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << SteppeStep_CTRL_TRIG_EN_SHIFT))
    #define SteppeStep_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << SteppeStep_CTRL_CAP_MODE_SHIFT))
    #define SteppeStep_CTRL_ENABLE                    ((uint8)((uint8)0x01u << SteppeStep_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SteppeStep_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SteppeStep_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SteppeStep_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SteppeStep_STATUS_TC_INT_MASK_SHIFT       SteppeStep_STATUS_TC_SHIFT
    #define SteppeStep_STATUS_CAPTURE_INT_MASK_SHIFT  SteppeStep_STATUS_CAPTURE_SHIFT
    #define SteppeStep_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SteppeStep_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SteppeStep_STATUS_FIFOFULL_INT_MASK_SHIFT SteppeStep_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SteppeStep_STATUS_TC                      ((uint8)((uint8)0x01u << SteppeStep_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define SteppeStep_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << SteppeStep_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SteppeStep_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << SteppeStep_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SteppeStep_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << SteppeStep_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SteppeStep_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << SteppeStep_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SteppeStep_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << SteppeStep_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define SteppeStep_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << SteppeStep_STATUS_FIFOFULL_SHIFT))

    #define SteppeStep_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SteppeStep_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SteppeStep_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SteppeStep_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SteppeStep_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SteppeStep_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_SteppeStep_H */


/* [] END OF FILE */
