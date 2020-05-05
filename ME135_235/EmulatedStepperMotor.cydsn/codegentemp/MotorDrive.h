/*******************************************************************************
* File Name: MotorDrive.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_MotorDrive_H)
#define CY_PWM_MotorDrive_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MotorDrive_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define MotorDrive_Resolution                     (16u)
#define MotorDrive_UsingFixedFunction             (0u)
#define MotorDrive_DeadBandMode                   (0u)
#define MotorDrive_KillModeMinTime                (0u)
#define MotorDrive_KillMode                       (1u)
#define MotorDrive_PWMMode                        (0u)
#define MotorDrive_PWMModeIsCenterAligned         (0u)
#define MotorDrive_DeadBandUsed                   (0u)
#define MotorDrive_DeadBand2_4                    (0u)

#if !defined(MotorDrive_PWMUDB_genblk8_stsreg__REMOVED)
    #define MotorDrive_UseStatus                  (1u)
#else
    #define MotorDrive_UseStatus                  (0u)
#endif /* !defined(MotorDrive_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(MotorDrive_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define MotorDrive_UseControl                 (1u)
#else
    #define MotorDrive_UseControl                 (0u)
#endif /* !defined(MotorDrive_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define MotorDrive_UseOneCompareMode              (1u)
#define MotorDrive_MinimumKillTime                (1u)
#define MotorDrive_EnableMode                     (0u)

#define MotorDrive_CompareMode1SW                 (0u)
#define MotorDrive_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define MotorDrive__B_PWM__DISABLED 0
#define MotorDrive__B_PWM__ASYNCHRONOUS 1
#define MotorDrive__B_PWM__SINGLECYCLE 2
#define MotorDrive__B_PWM__LATCHED 3
#define MotorDrive__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define MotorDrive__B_PWM__DBMDISABLED 0
#define MotorDrive__B_PWM__DBM_2_4_CLOCKS 1
#define MotorDrive__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define MotorDrive__B_PWM__ONE_OUTPUT 0
#define MotorDrive__B_PWM__TWO_OUTPUTS 1
#define MotorDrive__B_PWM__DUAL_EDGE 2
#define MotorDrive__B_PWM__CENTER_ALIGN 3
#define MotorDrive__B_PWM__DITHER 5
#define MotorDrive__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define MotorDrive__B_PWM__LESS_THAN 1
#define MotorDrive__B_PWM__LESS_THAN_OR_EQUAL 2
#define MotorDrive__B_PWM__GREATER_THAN 3
#define MotorDrive__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define MotorDrive__B_PWM__EQUAL 0
#define MotorDrive__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!MotorDrive_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!MotorDrive_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!MotorDrive_PWMModeIsCenterAligned) */
        #if (MotorDrive_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (MotorDrive_UseStatus) */

        /* Backup for Deadband parameters */
        #if(MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_256_CLOCKS || \
            MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(MotorDrive_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (MotorDrive_KillModeMinTime) */

        /* Backup control register */
        #if(MotorDrive_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (MotorDrive_UseControl) */

    #endif /* (!MotorDrive_UsingFixedFunction) */

}MotorDrive_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    MotorDrive_Start(void) ;
void    MotorDrive_Stop(void) ;

#if (MotorDrive_UseStatus || MotorDrive_UsingFixedFunction)
    void  MotorDrive_SetInterruptMode(uint8 interruptMode) ;
    uint8 MotorDrive_ReadStatusRegister(void) ;
#endif /* (MotorDrive_UseStatus || MotorDrive_UsingFixedFunction) */

#define MotorDrive_GetInterruptSource() MotorDrive_ReadStatusRegister()

#if (MotorDrive_UseControl)
    uint8 MotorDrive_ReadControlRegister(void) ;
    void  MotorDrive_WriteControlRegister(uint8 control)
          ;
#endif /* (MotorDrive_UseControl) */

#if (MotorDrive_UseOneCompareMode)
   #if (MotorDrive_CompareMode1SW)
       void    MotorDrive_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (MotorDrive_CompareMode1SW) */
#else
    #if (MotorDrive_CompareMode1SW)
        void    MotorDrive_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (MotorDrive_CompareMode1SW) */
    #if (MotorDrive_CompareMode2SW)
        void    MotorDrive_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (MotorDrive_CompareMode2SW) */
#endif /* (MotorDrive_UseOneCompareMode) */

#if (!MotorDrive_UsingFixedFunction)
    uint16   MotorDrive_ReadCounter(void) ;
    uint16 MotorDrive_ReadCapture(void) ;

    #if (MotorDrive_UseStatus)
            void MotorDrive_ClearFIFO(void) ;
    #endif /* (MotorDrive_UseStatus) */

    void    MotorDrive_WriteCounter(uint16 counter)
            ;
#endif /* (!MotorDrive_UsingFixedFunction) */

void    MotorDrive_WritePeriod(uint16 period)
        ;
uint16 MotorDrive_ReadPeriod(void) ;

#if (MotorDrive_UseOneCompareMode)
    void    MotorDrive_WriteCompare(uint16 compare)
            ;
    uint16 MotorDrive_ReadCompare(void) ;
#else
    void    MotorDrive_WriteCompare1(uint16 compare)
            ;
    uint16 MotorDrive_ReadCompare1(void) ;
    void    MotorDrive_WriteCompare2(uint16 compare)
            ;
    uint16 MotorDrive_ReadCompare2(void) ;
#endif /* (MotorDrive_UseOneCompareMode) */


#if (MotorDrive_DeadBandUsed)
    void    MotorDrive_WriteDeadTime(uint8 deadtime) ;
    uint8   MotorDrive_ReadDeadTime(void) ;
#endif /* (MotorDrive_DeadBandUsed) */

#if ( MotorDrive_KillModeMinTime)
    void MotorDrive_WriteKillTime(uint8 killtime) ;
    uint8 MotorDrive_ReadKillTime(void) ;
#endif /* ( MotorDrive_KillModeMinTime) */

void MotorDrive_Init(void) ;
void MotorDrive_Enable(void) ;
void MotorDrive_Sleep(void) ;
void MotorDrive_Wakeup(void) ;
void MotorDrive_SaveConfig(void) ;
void MotorDrive_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define MotorDrive_INIT_PERIOD_VALUE          (1200u)
#define MotorDrive_INIT_COMPARE_VALUE1        (1000u)
#define MotorDrive_INIT_COMPARE_VALUE2        (63u)
#define MotorDrive_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(1u <<   \
                                                    MotorDrive_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorDrive_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorDrive_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    MotorDrive_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define MotorDrive_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  MotorDrive_CTRL_CMPMODE2_SHIFT)
#define MotorDrive_DEFAULT_COMPARE1_MODE      (uint8)((uint8)2u <<  MotorDrive_CTRL_CMPMODE1_SHIFT)
#define MotorDrive_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (MotorDrive_UsingFixedFunction)
   #define MotorDrive_PERIOD_LSB              (*(reg16 *) MotorDrive_PWMHW__PER0)
   #define MotorDrive_PERIOD_LSB_PTR          ( (reg16 *) MotorDrive_PWMHW__PER0)
   #define MotorDrive_COMPARE1_LSB            (*(reg16 *) MotorDrive_PWMHW__CNT_CMP0)
   #define MotorDrive_COMPARE1_LSB_PTR        ( (reg16 *) MotorDrive_PWMHW__CNT_CMP0)
   #define MotorDrive_COMPARE2_LSB            (0x00u)
   #define MotorDrive_COMPARE2_LSB_PTR        (0x00u)
   #define MotorDrive_COUNTER_LSB             (*(reg16 *) MotorDrive_PWMHW__CNT_CMP0)
   #define MotorDrive_COUNTER_LSB_PTR         ( (reg16 *) MotorDrive_PWMHW__CNT_CMP0)
   #define MotorDrive_CAPTURE_LSB             (*(reg16 *) MotorDrive_PWMHW__CAP0)
   #define MotorDrive_CAPTURE_LSB_PTR         ( (reg16 *) MotorDrive_PWMHW__CAP0)
   #define MotorDrive_RT1                     (*(reg8 *)  MotorDrive_PWMHW__RT1)
   #define MotorDrive_RT1_PTR                 ( (reg8 *)  MotorDrive_PWMHW__RT1)

#else
   #if (MotorDrive_Resolution == 8u) /* 8bit - PWM */

       #if(MotorDrive_PWMModeIsCenterAligned)
           #define MotorDrive_PERIOD_LSB      (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define MotorDrive_PERIOD_LSB_PTR  ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define MotorDrive_PERIOD_LSB      (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define MotorDrive_PERIOD_LSB_PTR  ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (MotorDrive_PWMModeIsCenterAligned) */

       #define MotorDrive_COMPARE1_LSB        (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define MotorDrive_COMPARE1_LSB_PTR    ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define MotorDrive_COMPARE2_LSB        (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define MotorDrive_COMPARE2_LSB_PTR    ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define MotorDrive_COUNTERCAP_LSB      (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define MotorDrive_COUNTERCAP_LSB_PTR  ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define MotorDrive_COUNTER_LSB         (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define MotorDrive_COUNTER_LSB_PTR     ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define MotorDrive_CAPTURE_LSB         (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define MotorDrive_CAPTURE_LSB_PTR     ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(MotorDrive_PWMModeIsCenterAligned)
               #define MotorDrive_PERIOD_LSB      (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define MotorDrive_PERIOD_LSB_PTR  ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define MotorDrive_PERIOD_LSB      (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define MotorDrive_PERIOD_LSB_PTR  ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (MotorDrive_PWMModeIsCenterAligned) */

            #define MotorDrive_COMPARE1_LSB       (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define MotorDrive_COMPARE1_LSB_PTR   ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define MotorDrive_COMPARE2_LSB       (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define MotorDrive_COMPARE2_LSB_PTR   ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define MotorDrive_COUNTERCAP_LSB     (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define MotorDrive_COUNTERCAP_LSB_PTR ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define MotorDrive_COUNTER_LSB        (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define MotorDrive_COUNTER_LSB_PTR    ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define MotorDrive_CAPTURE_LSB        (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define MotorDrive_CAPTURE_LSB_PTR    ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(MotorDrive_PWMModeIsCenterAligned)
               #define MotorDrive_PERIOD_LSB      (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define MotorDrive_PERIOD_LSB_PTR  ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define MotorDrive_PERIOD_LSB      (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define MotorDrive_PERIOD_LSB_PTR  ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (MotorDrive_PWMModeIsCenterAligned) */

            #define MotorDrive_COMPARE1_LSB       (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define MotorDrive_COMPARE1_LSB_PTR   ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define MotorDrive_COMPARE2_LSB       (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define MotorDrive_COMPARE2_LSB_PTR   ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define MotorDrive_COUNTERCAP_LSB     (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define MotorDrive_COUNTERCAP_LSB_PTR ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define MotorDrive_COUNTER_LSB        (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define MotorDrive_COUNTER_LSB_PTR    ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define MotorDrive_CAPTURE_LSB        (*(reg16 *) MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define MotorDrive_CAPTURE_LSB_PTR    ((reg16 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define MotorDrive_AUX_CONTROLDP1          (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define MotorDrive_AUX_CONTROLDP1_PTR      ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (MotorDrive_Resolution == 8) */

   #define MotorDrive_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define MotorDrive_AUX_CONTROLDP0          (*(reg8 *)  MotorDrive_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define MotorDrive_AUX_CONTROLDP0_PTR      ((reg8 *)   MotorDrive_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (MotorDrive_UsingFixedFunction) */

#if(MotorDrive_KillModeMinTime )
    #define MotorDrive_KILLMODEMINTIME        (*(reg8 *)  MotorDrive_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define MotorDrive_KILLMODEMINTIME_PTR    ((reg8 *)   MotorDrive_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (MotorDrive_KillModeMinTime ) */

#if(MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_256_CLOCKS)
    #define MotorDrive_DEADBAND_COUNT         (*(reg8 *)  MotorDrive_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorDrive_DEADBAND_COUNT_PTR     ((reg8 *)   MotorDrive_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define MotorDrive_DEADBAND_LSB_PTR       ((reg8 *)   MotorDrive_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define MotorDrive_DEADBAND_LSB           (*(reg8 *)  MotorDrive_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (MotorDrive_UsingFixedFunction)
        #define MotorDrive_DEADBAND_COUNT         (*(reg8 *)  MotorDrive_PWMHW__CFG0)
        #define MotorDrive_DEADBAND_COUNT_PTR     ((reg8 *)   MotorDrive_PWMHW__CFG0)
        #define MotorDrive_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorDrive_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define MotorDrive_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define MotorDrive_DEADBAND_COUNT         (*(reg8 *)  MotorDrive_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorDrive_DEADBAND_COUNT_PTR     ((reg8 *)   MotorDrive_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define MotorDrive_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << MotorDrive_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define MotorDrive_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (MotorDrive_UsingFixedFunction) */
#endif /* (MotorDrive_DeadBandMode == MotorDrive__B_PWM__DBM_256_CLOCKS) */



#if (MotorDrive_UsingFixedFunction)
    #define MotorDrive_STATUS                 (*(reg8 *) MotorDrive_PWMHW__SR0)
    #define MotorDrive_STATUS_PTR             ((reg8 *) MotorDrive_PWMHW__SR0)
    #define MotorDrive_STATUS_MASK            (*(reg8 *) MotorDrive_PWMHW__SR0)
    #define MotorDrive_STATUS_MASK_PTR        ((reg8 *) MotorDrive_PWMHW__SR0)
    #define MotorDrive_CONTROL                (*(reg8 *) MotorDrive_PWMHW__CFG0)
    #define MotorDrive_CONTROL_PTR            ((reg8 *) MotorDrive_PWMHW__CFG0)
    #define MotorDrive_CONTROL2               (*(reg8 *) MotorDrive_PWMHW__CFG1)
    #define MotorDrive_CONTROL3               (*(reg8 *) MotorDrive_PWMHW__CFG2)
    #define MotorDrive_GLOBAL_ENABLE          (*(reg8 *) MotorDrive_PWMHW__PM_ACT_CFG)
    #define MotorDrive_GLOBAL_ENABLE_PTR      ( (reg8 *) MotorDrive_PWMHW__PM_ACT_CFG)
    #define MotorDrive_GLOBAL_STBY_ENABLE     (*(reg8 *) MotorDrive_PWMHW__PM_STBY_CFG)
    #define MotorDrive_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) MotorDrive_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define MotorDrive_BLOCK_EN_MASK          (MotorDrive_PWMHW__PM_ACT_MSK)
    #define MotorDrive_BLOCK_STBY_EN_MASK     (MotorDrive_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define MotorDrive_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define MotorDrive_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define MotorDrive_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define MotorDrive_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define MotorDrive_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define MotorDrive_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define MotorDrive_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorDrive_CTRL_ENABLE_SHIFT)
    #define MotorDrive_CTRL_RESET             (uint8)((uint8)0x01u << MotorDrive_CTRL_RESET_SHIFT)
    #define MotorDrive_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorDrive_CTRL_CMPMODE2_SHIFT)
    #define MotorDrive_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorDrive_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MotorDrive_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define MotorDrive_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << MotorDrive_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define MotorDrive_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define MotorDrive_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define MotorDrive_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorDrive_STATUS_TC_INT_EN_MASK_SHIFT            (MotorDrive_STATUS_TC_SHIFT - 4u)
    #define MotorDrive_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define MotorDrive_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorDrive_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define MotorDrive_STATUS_TC              (uint8)((uint8)0x01u << MotorDrive_STATUS_TC_SHIFT)
    #define MotorDrive_STATUS_CMP1            (uint8)((uint8)0x01u << MotorDrive_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define MotorDrive_STATUS_TC_INT_EN_MASK              (uint8)((uint8)MotorDrive_STATUS_TC >> 4u)
    #define MotorDrive_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)MotorDrive_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define MotorDrive_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define MotorDrive_RT1_MASK              (uint8)((uint8)0x03u << MotorDrive_RT1_SHIFT)
    #define MotorDrive_SYNC                  (uint8)((uint8)0x03u << MotorDrive_RT1_SHIFT)
    #define MotorDrive_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define MotorDrive_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << MotorDrive_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define MotorDrive_SYNCDSI_EN            (uint8)((uint8)0x0Fu << MotorDrive_SYNCDSI_SHIFT)


#else
    #define MotorDrive_STATUS                (*(reg8 *)   MotorDrive_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorDrive_STATUS_PTR            ((reg8 *)    MotorDrive_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define MotorDrive_STATUS_MASK           (*(reg8 *)   MotorDrive_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorDrive_STATUS_MASK_PTR       ((reg8 *)    MotorDrive_PWMUDB_genblk8_stsreg__MASK_REG)
    #define MotorDrive_STATUS_AUX_CTRL       (*(reg8 *)   MotorDrive_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define MotorDrive_CONTROL               (*(reg8 *)   MotorDrive_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define MotorDrive_CONTROL_PTR           ((reg8 *)    MotorDrive_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define MotorDrive_CTRL_ENABLE_SHIFT      (0x07u)
    #define MotorDrive_CTRL_RESET_SHIFT       (0x06u)
    #define MotorDrive_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define MotorDrive_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define MotorDrive_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define MotorDrive_CTRL_ENABLE            (uint8)((uint8)0x01u << MotorDrive_CTRL_ENABLE_SHIFT)
    #define MotorDrive_CTRL_RESET             (uint8)((uint8)0x01u << MotorDrive_CTRL_RESET_SHIFT)
    #define MotorDrive_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << MotorDrive_CTRL_CMPMODE2_SHIFT)
    #define MotorDrive_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << MotorDrive_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define MotorDrive_STATUS_KILL_SHIFT          (0x05u)
    #define MotorDrive_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define MotorDrive_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define MotorDrive_STATUS_TC_SHIFT            (0x02u)
    #define MotorDrive_STATUS_CMP2_SHIFT          (0x01u)
    #define MotorDrive_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define MotorDrive_STATUS_KILL_INT_EN_MASK_SHIFT          (MotorDrive_STATUS_KILL_SHIFT)
    #define MotorDrive_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (MotorDrive_STATUS_FIFONEMPTY_SHIFT)
    #define MotorDrive_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (MotorDrive_STATUS_FIFOFULL_SHIFT)
    #define MotorDrive_STATUS_TC_INT_EN_MASK_SHIFT            (MotorDrive_STATUS_TC_SHIFT)
    #define MotorDrive_STATUS_CMP2_INT_EN_MASK_SHIFT          (MotorDrive_STATUS_CMP2_SHIFT)
    #define MotorDrive_STATUS_CMP1_INT_EN_MASK_SHIFT          (MotorDrive_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define MotorDrive_STATUS_KILL            (uint8)((uint8)0x00u << MotorDrive_STATUS_KILL_SHIFT )
    #define MotorDrive_STATUS_FIFOFULL        (uint8)((uint8)0x01u << MotorDrive_STATUS_FIFOFULL_SHIFT)
    #define MotorDrive_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << MotorDrive_STATUS_FIFONEMPTY_SHIFT)
    #define MotorDrive_STATUS_TC              (uint8)((uint8)0x01u << MotorDrive_STATUS_TC_SHIFT)
    #define MotorDrive_STATUS_CMP2            (uint8)((uint8)0x01u << MotorDrive_STATUS_CMP2_SHIFT)
    #define MotorDrive_STATUS_CMP1            (uint8)((uint8)0x01u << MotorDrive_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define MotorDrive_STATUS_KILL_INT_EN_MASK            (MotorDrive_STATUS_KILL)
    #define MotorDrive_STATUS_FIFOFULL_INT_EN_MASK        (MotorDrive_STATUS_FIFOFULL)
    #define MotorDrive_STATUS_FIFONEMPTY_INT_EN_MASK      (MotorDrive_STATUS_FIFONEMPTY)
    #define MotorDrive_STATUS_TC_INT_EN_MASK              (MotorDrive_STATUS_TC)
    #define MotorDrive_STATUS_CMP2_INT_EN_MASK            (MotorDrive_STATUS_CMP2)
    #define MotorDrive_STATUS_CMP1_INT_EN_MASK            (MotorDrive_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define MotorDrive_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define MotorDrive_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define MotorDrive_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define MotorDrive_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define MotorDrive_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* MotorDrive_UsingFixedFunction */

#endif  /* CY_PWM_MotorDrive_H */


/* [] END OF FILE */
