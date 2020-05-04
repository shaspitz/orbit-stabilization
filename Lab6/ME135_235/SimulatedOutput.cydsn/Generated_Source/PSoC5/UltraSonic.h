/*******************************************************************************
* File Name: UltraSonic.h
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

#if !defined(CY_PWM_UltraSonic_H)
#define CY_PWM_UltraSonic_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 UltraSonic_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define UltraSonic_Resolution                     (16u)
#define UltraSonic_UsingFixedFunction             (0u)
#define UltraSonic_DeadBandMode                   (0u)
#define UltraSonic_KillModeMinTime                (0u)
#define UltraSonic_KillMode                       (0u)
#define UltraSonic_PWMMode                        (0u)
#define UltraSonic_PWMModeIsCenterAligned         (0u)
#define UltraSonic_DeadBandUsed                   (0u)
#define UltraSonic_DeadBand2_4                    (0u)

#if !defined(UltraSonic_PWMUDB_genblk8_stsreg__REMOVED)
    #define UltraSonic_UseStatus                  (1u)
#else
    #define UltraSonic_UseStatus                  (0u)
#endif /* !defined(UltraSonic_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(UltraSonic_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define UltraSonic_UseControl                 (1u)
#else
    #define UltraSonic_UseControl                 (0u)
#endif /* !defined(UltraSonic_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define UltraSonic_UseOneCompareMode              (1u)
#define UltraSonic_MinimumKillTime                (1u)
#define UltraSonic_EnableMode                     (0u)

#define UltraSonic_CompareMode1SW                 (0u)
#define UltraSonic_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define UltraSonic__B_PWM__DISABLED 0
#define UltraSonic__B_PWM__ASYNCHRONOUS 1
#define UltraSonic__B_PWM__SINGLECYCLE 2
#define UltraSonic__B_PWM__LATCHED 3
#define UltraSonic__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define UltraSonic__B_PWM__DBMDISABLED 0
#define UltraSonic__B_PWM__DBM_2_4_CLOCKS 1
#define UltraSonic__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define UltraSonic__B_PWM__ONE_OUTPUT 0
#define UltraSonic__B_PWM__TWO_OUTPUTS 1
#define UltraSonic__B_PWM__DUAL_EDGE 2
#define UltraSonic__B_PWM__CENTER_ALIGN 3
#define UltraSonic__B_PWM__DITHER 5
#define UltraSonic__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define UltraSonic__B_PWM__LESS_THAN 1
#define UltraSonic__B_PWM__LESS_THAN_OR_EQUAL 2
#define UltraSonic__B_PWM__GREATER_THAN 3
#define UltraSonic__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define UltraSonic__B_PWM__EQUAL 0
#define UltraSonic__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!UltraSonic_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!UltraSonic_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!UltraSonic_PWMModeIsCenterAligned) */
        #if (UltraSonic_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (UltraSonic_UseStatus) */

        /* Backup for Deadband parameters */
        #if(UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_256_CLOCKS || \
            UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(UltraSonic_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (UltraSonic_KillModeMinTime) */

        /* Backup control register */
        #if(UltraSonic_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (UltraSonic_UseControl) */

    #endif /* (!UltraSonic_UsingFixedFunction) */

}UltraSonic_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    UltraSonic_Start(void) ;
void    UltraSonic_Stop(void) ;

#if (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction)
    void  UltraSonic_SetInterruptMode(uint8 interruptMode) ;
    uint8 UltraSonic_ReadStatusRegister(void) ;
#endif /* (UltraSonic_UseStatus || UltraSonic_UsingFixedFunction) */

#define UltraSonic_GetInterruptSource() UltraSonic_ReadStatusRegister()

#if (UltraSonic_UseControl)
    uint8 UltraSonic_ReadControlRegister(void) ;
    void  UltraSonic_WriteControlRegister(uint8 control)
          ;
#endif /* (UltraSonic_UseControl) */

#if (UltraSonic_UseOneCompareMode)
   #if (UltraSonic_CompareMode1SW)
       void    UltraSonic_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (UltraSonic_CompareMode1SW) */
#else
    #if (UltraSonic_CompareMode1SW)
        void    UltraSonic_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (UltraSonic_CompareMode1SW) */
    #if (UltraSonic_CompareMode2SW)
        void    UltraSonic_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (UltraSonic_CompareMode2SW) */
#endif /* (UltraSonic_UseOneCompareMode) */

#if (!UltraSonic_UsingFixedFunction)
    uint16   UltraSonic_ReadCounter(void) ;
    uint16 UltraSonic_ReadCapture(void) ;

    #if (UltraSonic_UseStatus)
            void UltraSonic_ClearFIFO(void) ;
    #endif /* (UltraSonic_UseStatus) */

    void    UltraSonic_WriteCounter(uint16 counter)
            ;
#endif /* (!UltraSonic_UsingFixedFunction) */

void    UltraSonic_WritePeriod(uint16 period)
        ;
uint16 UltraSonic_ReadPeriod(void) ;

#if (UltraSonic_UseOneCompareMode)
    void    UltraSonic_WriteCompare(uint16 compare)
            ;
    uint16 UltraSonic_ReadCompare(void) ;
#else
    void    UltraSonic_WriteCompare1(uint16 compare)
            ;
    uint16 UltraSonic_ReadCompare1(void) ;
    void    UltraSonic_WriteCompare2(uint16 compare)
            ;
    uint16 UltraSonic_ReadCompare2(void) ;
#endif /* (UltraSonic_UseOneCompareMode) */


#if (UltraSonic_DeadBandUsed)
    void    UltraSonic_WriteDeadTime(uint8 deadtime) ;
    uint8   UltraSonic_ReadDeadTime(void) ;
#endif /* (UltraSonic_DeadBandUsed) */

#if ( UltraSonic_KillModeMinTime)
    void UltraSonic_WriteKillTime(uint8 killtime) ;
    uint8 UltraSonic_ReadKillTime(void) ;
#endif /* ( UltraSonic_KillModeMinTime) */

void UltraSonic_Init(void) ;
void UltraSonic_Enable(void) ;
void UltraSonic_Sleep(void) ;
void UltraSonic_Wakeup(void) ;
void UltraSonic_SaveConfig(void) ;
void UltraSonic_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define UltraSonic_INIT_PERIOD_VALUE          (1000u)
#define UltraSonic_INIT_COMPARE_VALUE1        (127u)
#define UltraSonic_INIT_COMPARE_VALUE2        (63u)
#define UltraSonic_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    UltraSonic_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    UltraSonic_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    UltraSonic_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    UltraSonic_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define UltraSonic_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  UltraSonic_CTRL_CMPMODE2_SHIFT)
#define UltraSonic_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  UltraSonic_CTRL_CMPMODE1_SHIFT)
#define UltraSonic_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (UltraSonic_UsingFixedFunction)
   #define UltraSonic_PERIOD_LSB              (*(reg16 *) UltraSonic_PWMHW__PER0)
   #define UltraSonic_PERIOD_LSB_PTR          ( (reg16 *) UltraSonic_PWMHW__PER0)
   #define UltraSonic_COMPARE1_LSB            (*(reg16 *) UltraSonic_PWMHW__CNT_CMP0)
   #define UltraSonic_COMPARE1_LSB_PTR        ( (reg16 *) UltraSonic_PWMHW__CNT_CMP0)
   #define UltraSonic_COMPARE2_LSB            (0x00u)
   #define UltraSonic_COMPARE2_LSB_PTR        (0x00u)
   #define UltraSonic_COUNTER_LSB             (*(reg16 *) UltraSonic_PWMHW__CNT_CMP0)
   #define UltraSonic_COUNTER_LSB_PTR         ( (reg16 *) UltraSonic_PWMHW__CNT_CMP0)
   #define UltraSonic_CAPTURE_LSB             (*(reg16 *) UltraSonic_PWMHW__CAP0)
   #define UltraSonic_CAPTURE_LSB_PTR         ( (reg16 *) UltraSonic_PWMHW__CAP0)
   #define UltraSonic_RT1                     (*(reg8 *)  UltraSonic_PWMHW__RT1)
   #define UltraSonic_RT1_PTR                 ( (reg8 *)  UltraSonic_PWMHW__RT1)

#else
   #if (UltraSonic_Resolution == 8u) /* 8bit - PWM */

       #if(UltraSonic_PWMModeIsCenterAligned)
           #define UltraSonic_PERIOD_LSB      (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define UltraSonic_PERIOD_LSB_PTR  ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define UltraSonic_PERIOD_LSB      (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define UltraSonic_PERIOD_LSB_PTR  ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (UltraSonic_PWMModeIsCenterAligned) */

       #define UltraSonic_COMPARE1_LSB        (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define UltraSonic_COMPARE1_LSB_PTR    ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define UltraSonic_COMPARE2_LSB        (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define UltraSonic_COMPARE2_LSB_PTR    ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define UltraSonic_COUNTERCAP_LSB      (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define UltraSonic_COUNTERCAP_LSB_PTR  ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define UltraSonic_COUNTER_LSB         (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define UltraSonic_COUNTER_LSB_PTR     ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define UltraSonic_CAPTURE_LSB         (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define UltraSonic_CAPTURE_LSB_PTR     ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(UltraSonic_PWMModeIsCenterAligned)
               #define UltraSonic_PERIOD_LSB      (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define UltraSonic_PERIOD_LSB_PTR  ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define UltraSonic_PERIOD_LSB      (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define UltraSonic_PERIOD_LSB_PTR  ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (UltraSonic_PWMModeIsCenterAligned) */

            #define UltraSonic_COMPARE1_LSB       (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define UltraSonic_COMPARE1_LSB_PTR   ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define UltraSonic_COMPARE2_LSB       (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define UltraSonic_COMPARE2_LSB_PTR   ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define UltraSonic_COUNTERCAP_LSB     (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define UltraSonic_COUNTERCAP_LSB_PTR ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define UltraSonic_COUNTER_LSB        (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define UltraSonic_COUNTER_LSB_PTR    ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define UltraSonic_CAPTURE_LSB        (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define UltraSonic_CAPTURE_LSB_PTR    ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(UltraSonic_PWMModeIsCenterAligned)
               #define UltraSonic_PERIOD_LSB      (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define UltraSonic_PERIOD_LSB_PTR  ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define UltraSonic_PERIOD_LSB      (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define UltraSonic_PERIOD_LSB_PTR  ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (UltraSonic_PWMModeIsCenterAligned) */

            #define UltraSonic_COMPARE1_LSB       (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define UltraSonic_COMPARE1_LSB_PTR   ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define UltraSonic_COMPARE2_LSB       (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define UltraSonic_COMPARE2_LSB_PTR   ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define UltraSonic_COUNTERCAP_LSB     (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define UltraSonic_COUNTERCAP_LSB_PTR ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define UltraSonic_COUNTER_LSB        (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define UltraSonic_COUNTER_LSB_PTR    ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define UltraSonic_CAPTURE_LSB        (*(reg16 *) UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define UltraSonic_CAPTURE_LSB_PTR    ((reg16 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define UltraSonic_AUX_CONTROLDP1          (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define UltraSonic_AUX_CONTROLDP1_PTR      ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (UltraSonic_Resolution == 8) */

   #define UltraSonic_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define UltraSonic_AUX_CONTROLDP0          (*(reg8 *)  UltraSonic_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define UltraSonic_AUX_CONTROLDP0_PTR      ((reg8 *)   UltraSonic_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (UltraSonic_UsingFixedFunction) */

#if(UltraSonic_KillModeMinTime )
    #define UltraSonic_KILLMODEMINTIME        (*(reg8 *)  UltraSonic_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define UltraSonic_KILLMODEMINTIME_PTR    ((reg8 *)   UltraSonic_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (UltraSonic_KillModeMinTime ) */

#if(UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_256_CLOCKS)
    #define UltraSonic_DEADBAND_COUNT         (*(reg8 *)  UltraSonic_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define UltraSonic_DEADBAND_COUNT_PTR     ((reg8 *)   UltraSonic_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define UltraSonic_DEADBAND_LSB_PTR       ((reg8 *)   UltraSonic_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define UltraSonic_DEADBAND_LSB           (*(reg8 *)  UltraSonic_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (UltraSonic_UsingFixedFunction)
        #define UltraSonic_DEADBAND_COUNT         (*(reg8 *)  UltraSonic_PWMHW__CFG0)
        #define UltraSonic_DEADBAND_COUNT_PTR     ((reg8 *)   UltraSonic_PWMHW__CFG0)
        #define UltraSonic_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << UltraSonic_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define UltraSonic_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define UltraSonic_DEADBAND_COUNT         (*(reg8 *)  UltraSonic_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define UltraSonic_DEADBAND_COUNT_PTR     ((reg8 *)   UltraSonic_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define UltraSonic_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << UltraSonic_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define UltraSonic_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (UltraSonic_UsingFixedFunction) */
#endif /* (UltraSonic_DeadBandMode == UltraSonic__B_PWM__DBM_256_CLOCKS) */



#if (UltraSonic_UsingFixedFunction)
    #define UltraSonic_STATUS                 (*(reg8 *) UltraSonic_PWMHW__SR0)
    #define UltraSonic_STATUS_PTR             ((reg8 *) UltraSonic_PWMHW__SR0)
    #define UltraSonic_STATUS_MASK            (*(reg8 *) UltraSonic_PWMHW__SR0)
    #define UltraSonic_STATUS_MASK_PTR        ((reg8 *) UltraSonic_PWMHW__SR0)
    #define UltraSonic_CONTROL                (*(reg8 *) UltraSonic_PWMHW__CFG0)
    #define UltraSonic_CONTROL_PTR            ((reg8 *) UltraSonic_PWMHW__CFG0)
    #define UltraSonic_CONTROL2               (*(reg8 *) UltraSonic_PWMHW__CFG1)
    #define UltraSonic_CONTROL3               (*(reg8 *) UltraSonic_PWMHW__CFG2)
    #define UltraSonic_GLOBAL_ENABLE          (*(reg8 *) UltraSonic_PWMHW__PM_ACT_CFG)
    #define UltraSonic_GLOBAL_ENABLE_PTR      ( (reg8 *) UltraSonic_PWMHW__PM_ACT_CFG)
    #define UltraSonic_GLOBAL_STBY_ENABLE     (*(reg8 *) UltraSonic_PWMHW__PM_STBY_CFG)
    #define UltraSonic_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) UltraSonic_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define UltraSonic_BLOCK_EN_MASK          (UltraSonic_PWMHW__PM_ACT_MSK)
    #define UltraSonic_BLOCK_STBY_EN_MASK     (UltraSonic_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define UltraSonic_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define UltraSonic_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define UltraSonic_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define UltraSonic_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define UltraSonic_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define UltraSonic_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define UltraSonic_CTRL_ENABLE            (uint8)((uint8)0x01u << UltraSonic_CTRL_ENABLE_SHIFT)
    #define UltraSonic_CTRL_RESET             (uint8)((uint8)0x01u << UltraSonic_CTRL_RESET_SHIFT)
    #define UltraSonic_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << UltraSonic_CTRL_CMPMODE2_SHIFT)
    #define UltraSonic_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << UltraSonic_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define UltraSonic_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define UltraSonic_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << UltraSonic_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define UltraSonic_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define UltraSonic_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define UltraSonic_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define UltraSonic_STATUS_TC_INT_EN_MASK_SHIFT            (UltraSonic_STATUS_TC_SHIFT - 4u)
    #define UltraSonic_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define UltraSonic_STATUS_CMP1_INT_EN_MASK_SHIFT          (UltraSonic_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define UltraSonic_STATUS_TC              (uint8)((uint8)0x01u << UltraSonic_STATUS_TC_SHIFT)
    #define UltraSonic_STATUS_CMP1            (uint8)((uint8)0x01u << UltraSonic_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define UltraSonic_STATUS_TC_INT_EN_MASK              (uint8)((uint8)UltraSonic_STATUS_TC >> 4u)
    #define UltraSonic_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)UltraSonic_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define UltraSonic_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define UltraSonic_RT1_MASK              (uint8)((uint8)0x03u << UltraSonic_RT1_SHIFT)
    #define UltraSonic_SYNC                  (uint8)((uint8)0x03u << UltraSonic_RT1_SHIFT)
    #define UltraSonic_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define UltraSonic_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << UltraSonic_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define UltraSonic_SYNCDSI_EN            (uint8)((uint8)0x0Fu << UltraSonic_SYNCDSI_SHIFT)


#else
    #define UltraSonic_STATUS                (*(reg8 *)   UltraSonic_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define UltraSonic_STATUS_PTR            ((reg8 *)    UltraSonic_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define UltraSonic_STATUS_MASK           (*(reg8 *)   UltraSonic_PWMUDB_genblk8_stsreg__MASK_REG)
    #define UltraSonic_STATUS_MASK_PTR       ((reg8 *)    UltraSonic_PWMUDB_genblk8_stsreg__MASK_REG)
    #define UltraSonic_STATUS_AUX_CTRL       (*(reg8 *)   UltraSonic_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define UltraSonic_CONTROL               (*(reg8 *)   UltraSonic_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define UltraSonic_CONTROL_PTR           ((reg8 *)    UltraSonic_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define UltraSonic_CTRL_ENABLE_SHIFT      (0x07u)
    #define UltraSonic_CTRL_RESET_SHIFT       (0x06u)
    #define UltraSonic_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define UltraSonic_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define UltraSonic_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define UltraSonic_CTRL_ENABLE            (uint8)((uint8)0x01u << UltraSonic_CTRL_ENABLE_SHIFT)
    #define UltraSonic_CTRL_RESET             (uint8)((uint8)0x01u << UltraSonic_CTRL_RESET_SHIFT)
    #define UltraSonic_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << UltraSonic_CTRL_CMPMODE2_SHIFT)
    #define UltraSonic_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << UltraSonic_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define UltraSonic_STATUS_KILL_SHIFT          (0x05u)
    #define UltraSonic_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define UltraSonic_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define UltraSonic_STATUS_TC_SHIFT            (0x02u)
    #define UltraSonic_STATUS_CMP2_SHIFT          (0x01u)
    #define UltraSonic_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define UltraSonic_STATUS_KILL_INT_EN_MASK_SHIFT          (UltraSonic_STATUS_KILL_SHIFT)
    #define UltraSonic_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (UltraSonic_STATUS_FIFONEMPTY_SHIFT)
    #define UltraSonic_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (UltraSonic_STATUS_FIFOFULL_SHIFT)
    #define UltraSonic_STATUS_TC_INT_EN_MASK_SHIFT            (UltraSonic_STATUS_TC_SHIFT)
    #define UltraSonic_STATUS_CMP2_INT_EN_MASK_SHIFT          (UltraSonic_STATUS_CMP2_SHIFT)
    #define UltraSonic_STATUS_CMP1_INT_EN_MASK_SHIFT          (UltraSonic_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define UltraSonic_STATUS_KILL            (uint8)((uint8)0x00u << UltraSonic_STATUS_KILL_SHIFT )
    #define UltraSonic_STATUS_FIFOFULL        (uint8)((uint8)0x01u << UltraSonic_STATUS_FIFOFULL_SHIFT)
    #define UltraSonic_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << UltraSonic_STATUS_FIFONEMPTY_SHIFT)
    #define UltraSonic_STATUS_TC              (uint8)((uint8)0x01u << UltraSonic_STATUS_TC_SHIFT)
    #define UltraSonic_STATUS_CMP2            (uint8)((uint8)0x01u << UltraSonic_STATUS_CMP2_SHIFT)
    #define UltraSonic_STATUS_CMP1            (uint8)((uint8)0x01u << UltraSonic_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define UltraSonic_STATUS_KILL_INT_EN_MASK            (UltraSonic_STATUS_KILL)
    #define UltraSonic_STATUS_FIFOFULL_INT_EN_MASK        (UltraSonic_STATUS_FIFOFULL)
    #define UltraSonic_STATUS_FIFONEMPTY_INT_EN_MASK      (UltraSonic_STATUS_FIFONEMPTY)
    #define UltraSonic_STATUS_TC_INT_EN_MASK              (UltraSonic_STATUS_TC)
    #define UltraSonic_STATUS_CMP2_INT_EN_MASK            (UltraSonic_STATUS_CMP2)
    #define UltraSonic_STATUS_CMP1_INT_EN_MASK            (UltraSonic_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define UltraSonic_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define UltraSonic_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define UltraSonic_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define UltraSonic_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define UltraSonic_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* UltraSonic_UsingFixedFunction */

#endif  /* CY_PWM_UltraSonic_H */


/* [] END OF FILE */
