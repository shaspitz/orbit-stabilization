/*******************************************************************************
* File Name: StepperStep.h
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

#if !defined(CY_TIMER_StepperStep_H)
#define CY_TIMER_StepperStep_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 StepperStep_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define StepperStep_Resolution                 32u
#define StepperStep_UsingFixedFunction         0u
#define StepperStep_UsingHWCaptureCounter      0u
#define StepperStep_SoftwareCaptureMode        0u
#define StepperStep_SoftwareTriggerMode        0u
#define StepperStep_UsingHWEnable              1u
#define StepperStep_EnableTriggerMode          0u
#define StepperStep_InterruptOnCaptureCount    0u
#define StepperStep_RunModeUsed                0u
#define StepperStep_ControlRegRemoved          1u

#if defined(StepperStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define StepperStep_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (StepperStep_UsingFixedFunction)
    #define StepperStep_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define StepperStep_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End StepperStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!StepperStep_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (StepperStep_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!StepperStep_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}StepperStep_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    StepperStep_Start(void) ;
void    StepperStep_Stop(void) ;

void    StepperStep_SetInterruptMode(uint8 interruptMode) ;
uint8   StepperStep_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define StepperStep_GetInterruptSource() StepperStep_ReadStatusRegister()

#if(!StepperStep_UDB_CONTROL_REG_REMOVED)
    uint8   StepperStep_ReadControlRegister(void) ;
    void    StepperStep_WriteControlRegister(uint8 control) ;
#endif /* (!StepperStep_UDB_CONTROL_REG_REMOVED) */

uint32  StepperStep_ReadPeriod(void) ;
void    StepperStep_WritePeriod(uint32 period) ;
uint32  StepperStep_ReadCounter(void) ;
void    StepperStep_WriteCounter(uint32 counter) ;
uint32  StepperStep_ReadCapture(void) ;
void    StepperStep_SoftwareCapture(void) ;

#if(!StepperStep_UsingFixedFunction) /* UDB Prototypes */
    #if (StepperStep_SoftwareCaptureMode)
        void    StepperStep_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!StepperStep_UsingFixedFunction) */

    #if (StepperStep_SoftwareTriggerMode)
        void    StepperStep_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (StepperStep_SoftwareTriggerMode) */

    #if (StepperStep_EnableTriggerMode)
        void    StepperStep_EnableTrigger(void) ;
        void    StepperStep_DisableTrigger(void) ;
    #endif /* (StepperStep_EnableTriggerMode) */


    #if(StepperStep_InterruptOnCaptureCount)
        void    StepperStep_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (StepperStep_InterruptOnCaptureCount) */

    #if (StepperStep_UsingHWCaptureCounter)
        void    StepperStep_SetCaptureCount(uint8 captureCount) ;
        uint8   StepperStep_ReadCaptureCount(void) ;
    #endif /* (StepperStep_UsingHWCaptureCounter) */

    void StepperStep_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void StepperStep_Init(void)          ;
void StepperStep_Enable(void)        ;
void StepperStep_SaveConfig(void)    ;
void StepperStep_RestoreConfig(void) ;
void StepperStep_Sleep(void)         ;
void StepperStep_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define StepperStep__B_TIMER__CM_NONE 0
#define StepperStep__B_TIMER__CM_RISINGEDGE 1
#define StepperStep__B_TIMER__CM_FALLINGEDGE 2
#define StepperStep__B_TIMER__CM_EITHEREDGE 3
#define StepperStep__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define StepperStep__B_TIMER__TM_NONE 0x00u
#define StepperStep__B_TIMER__TM_RISINGEDGE 0x04u
#define StepperStep__B_TIMER__TM_FALLINGEDGE 0x08u
#define StepperStep__B_TIMER__TM_EITHEREDGE 0x0Cu
#define StepperStep__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define StepperStep_INIT_PERIOD             4294967295u
#define StepperStep_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << StepperStep_CTRL_CAP_MODE_SHIFT))
#define StepperStep_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << StepperStep_CTRL_TRIG_MODE_SHIFT))
#if (StepperStep_UsingFixedFunction)
    #define StepperStep_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << StepperStep_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << StepperStep_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define StepperStep_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << StepperStep_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << StepperStep_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << StepperStep_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (StepperStep_UsingFixedFunction) */
#define StepperStep_INIT_CAPTURE_COUNT      (2u)
#define StepperStep_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << StepperStep_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (StepperStep_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define StepperStep_STATUS         (*(reg8 *) StepperStep_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define StepperStep_STATUS_MASK    (*(reg8 *) StepperStep_TimerHW__SR0 )
    #define StepperStep_CONTROL        (*(reg8 *) StepperStep_TimerHW__CFG0)
    #define StepperStep_CONTROL2       (*(reg8 *) StepperStep_TimerHW__CFG1)
    #define StepperStep_CONTROL2_PTR   ( (reg8 *) StepperStep_TimerHW__CFG1)
    #define StepperStep_RT1            (*(reg8 *) StepperStep_TimerHW__RT1)
    #define StepperStep_RT1_PTR        ( (reg8 *) StepperStep_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define StepperStep_CONTROL3       (*(reg8 *) StepperStep_TimerHW__CFG2)
        #define StepperStep_CONTROL3_PTR   ( (reg8 *) StepperStep_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define StepperStep_GLOBAL_ENABLE  (*(reg8 *) StepperStep_TimerHW__PM_ACT_CFG)
    #define StepperStep_GLOBAL_STBY_ENABLE  (*(reg8 *) StepperStep_TimerHW__PM_STBY_CFG)

    #define StepperStep_CAPTURE_LSB         (* (reg16 *) StepperStep_TimerHW__CAP0 )
    #define StepperStep_CAPTURE_LSB_PTR       ((reg16 *) StepperStep_TimerHW__CAP0 )
    #define StepperStep_PERIOD_LSB          (* (reg16 *) StepperStep_TimerHW__PER0 )
    #define StepperStep_PERIOD_LSB_PTR        ((reg16 *) StepperStep_TimerHW__PER0 )
    #define StepperStep_COUNTER_LSB         (* (reg16 *) StepperStep_TimerHW__CNT_CMP0 )
    #define StepperStep_COUNTER_LSB_PTR       ((reg16 *) StepperStep_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define StepperStep_BLOCK_EN_MASK                     StepperStep_TimerHW__PM_ACT_MSK
    #define StepperStep_BLOCK_STBY_EN_MASK                StepperStep_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define StepperStep_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define StepperStep_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define StepperStep_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define StepperStep_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define StepperStep_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define StepperStep_CTRL_ENABLE                        ((uint8)((uint8)0x01u << StepperStep_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define StepperStep_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define StepperStep_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << StepperStep_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define StepperStep_CTRL_MODE_SHIFT                 0x01u
        #define StepperStep_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << StepperStep_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define StepperStep_CTRL_RCOD_SHIFT        0x02u
        #define StepperStep_CTRL_ENBL_SHIFT        0x00u
        #define StepperStep_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define StepperStep_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << StepperStep_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define StepperStep_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << StepperStep_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define StepperStep_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << StepperStep_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define StepperStep_CTRL_RCOD       ((uint8)((uint8)0x03u << StepperStep_CTRL_RCOD_SHIFT))
        #define StepperStep_CTRL_ENBL       ((uint8)((uint8)0x80u << StepperStep_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define StepperStep_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define StepperStep_RT1_MASK                        ((uint8)((uint8)0x03u << StepperStep_RT1_SHIFT))
    #define StepperStep_SYNC                            ((uint8)((uint8)0x03u << StepperStep_RT1_SHIFT))
    #define StepperStep_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define StepperStep_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << StepperStep_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define StepperStep_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << StepperStep_SYNCDSI_SHIFT))

    #define StepperStep_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << StepperStep_CTRL_MODE_SHIFT))
    #define StepperStep_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << StepperStep_CTRL_MODE_SHIFT))
    #define StepperStep_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << StepperStep_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define StepperStep_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define StepperStep_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define StepperStep_STATUS_TC_INT_MASK_SHIFT        (StepperStep_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define StepperStep_STATUS_CAPTURE_INT_MASK_SHIFT   (StepperStep_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define StepperStep_STATUS_TC                       ((uint8)((uint8)0x01u << StepperStep_STATUS_TC_SHIFT))
    #define StepperStep_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << StepperStep_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define StepperStep_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << StepperStep_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define StepperStep_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << StepperStep_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define StepperStep_STATUS              (* (reg8 *) StepperStep_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define StepperStep_STATUS_MASK         (* (reg8 *) StepperStep_TimerUDB_rstSts_stsreg__MASK_REG)
    #define StepperStep_STATUS_AUX_CTRL     (* (reg8 *) StepperStep_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define StepperStep_CONTROL             (* (reg8 *) StepperStep_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(StepperStep_Resolution <= 8u) /* 8-bit Timer */
        #define StepperStep_CAPTURE_LSB         (* (reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define StepperStep_CAPTURE_LSB_PTR       ((reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define StepperStep_PERIOD_LSB          (* (reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define StepperStep_PERIOD_LSB_PTR        ((reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define StepperStep_COUNTER_LSB         (* (reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define StepperStep_COUNTER_LSB_PTR       ((reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    #elif(StepperStep_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define StepperStep_CAPTURE_LSB         (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define StepperStep_CAPTURE_LSB_PTR       ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define StepperStep_PERIOD_LSB          (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define StepperStep_PERIOD_LSB_PTR        ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define StepperStep_COUNTER_LSB         (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define StepperStep_COUNTER_LSB_PTR       ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define StepperStep_CAPTURE_LSB         (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define StepperStep_CAPTURE_LSB_PTR       ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_F0_REG )
            #define StepperStep_PERIOD_LSB          (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define StepperStep_PERIOD_LSB_PTR        ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_D0_REG )
            #define StepperStep_COUNTER_LSB         (* (reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
            #define StepperStep_COUNTER_LSB_PTR       ((reg16 *) StepperStep_TimerUDB_sT32_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(StepperStep_Resolution <= 24u)/* 24-bit Timer */
        #define StepperStep_CAPTURE_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define StepperStep_CAPTURE_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
        #define StepperStep_PERIOD_LSB          (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define StepperStep_PERIOD_LSB_PTR        ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
        #define StepperStep_COUNTER_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #define StepperStep_COUNTER_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define StepperStep_CAPTURE_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define StepperStep_CAPTURE_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__F0_REG )
            #define StepperStep_PERIOD_LSB          (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define StepperStep_PERIOD_LSB_PTR        ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__D0_REG )
            #define StepperStep_COUNTER_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
            #define StepperStep_COUNTER_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define StepperStep_CAPTURE_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define StepperStep_CAPTURE_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_F0_REG )
            #define StepperStep_PERIOD_LSB          (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define StepperStep_PERIOD_LSB_PTR        ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_D0_REG )
            #define StepperStep_COUNTER_LSB         (* (reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
            #define StepperStep_COUNTER_LSB_PTR       ((reg32 *) StepperStep_TimerUDB_sT32_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define StepperStep_COUNTER_LSB_PTR_8BIT       ((reg8 *) StepperStep_TimerUDB_sT32_timerdp_u0__A0_REG )
    
    #if (StepperStep_UsingHWCaptureCounter)
        #define StepperStep_CAP_COUNT              (*(reg8 *) StepperStep_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define StepperStep_CAP_COUNT_PTR          ( (reg8 *) StepperStep_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define StepperStep_CAPTURE_COUNT_CTRL     (*(reg8 *) StepperStep_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define StepperStep_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) StepperStep_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (StepperStep_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define StepperStep_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define StepperStep_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define StepperStep_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define StepperStep_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define StepperStep_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define StepperStep_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << StepperStep_CTRL_INTCNT_SHIFT))
    #define StepperStep_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << StepperStep_CTRL_TRIG_MODE_SHIFT))
    #define StepperStep_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << StepperStep_CTRL_TRIG_EN_SHIFT))
    #define StepperStep_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << StepperStep_CTRL_CAP_MODE_SHIFT))
    #define StepperStep_CTRL_ENABLE                    ((uint8)((uint8)0x01u << StepperStep_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define StepperStep_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define StepperStep_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define StepperStep_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define StepperStep_STATUS_TC_INT_MASK_SHIFT       StepperStep_STATUS_TC_SHIFT
    #define StepperStep_STATUS_CAPTURE_INT_MASK_SHIFT  StepperStep_STATUS_CAPTURE_SHIFT
    #define StepperStep_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define StepperStep_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define StepperStep_STATUS_FIFOFULL_INT_MASK_SHIFT StepperStep_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define StepperStep_STATUS_TC                      ((uint8)((uint8)0x01u << StepperStep_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define StepperStep_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << StepperStep_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define StepperStep_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << StepperStep_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define StepperStep_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << StepperStep_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define StepperStep_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << StepperStep_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define StepperStep_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << StepperStep_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define StepperStep_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << StepperStep_STATUS_FIFOFULL_SHIFT))

    #define StepperStep_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define StepperStep_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define StepperStep_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define StepperStep_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define StepperStep_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define StepperStep_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_StepperStep_H */


/* [] END OF FILE */
