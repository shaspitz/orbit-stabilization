/*******************************************************************************
* File Name: JapanSensor.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_JapanSensor_H) 
#define CY_WaveDAC8_JapanSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include <JapanSensor_Wave1_DMA_dma.h>
#include <JapanSensor_Wave2_DMA_dma.h>
#include <JapanSensor_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define JapanSensor_WAVE1_TYPE     (3u)     /* Waveform for wave1 */
#define JapanSensor_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define JapanSensor_SINE_WAVE      (0u)
#define JapanSensor_SQUARE_WAVE    (1u)
#define JapanSensor_TRIANGLE_WAVE  (2u)
#define JapanSensor_SAWTOOTH_WAVE  (3u)
#define JapanSensor_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define JapanSensor_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define JapanSensor_WAVE1_LENGTH   (4000u)   /* Length for wave1 */
#define JapanSensor_WAVE2_LENGTH   (100u)   /* Length for wave2 */
	
#define JapanSensor_DEFAULT_RANGE    (0u) /* Default DAC range */
#define JapanSensor_DAC_RANGE_1V     (0u)
#define JapanSensor_DAC_RANGE_1V_BUF (16u)
#define JapanSensor_DAC_RANGE_4V     (1u)
#define JapanSensor_DAC_RANGE_4V_BUF (17u)
#define JapanSensor_VOLT_MODE        (0u)
#define JapanSensor_CURRENT_MODE     (1u)
#define JapanSensor_DAC_MODE         (((JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_1V) || \
									  (JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_4V) || \
							  		  (JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_1V_BUF) || \
									  (JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_4V_BUF)) ? \
									   JapanSensor_VOLT_MODE : JapanSensor_CURRENT_MODE)

#define JapanSensor_DACMODE JapanSensor_DAC_MODE /* legacy definition for backward compatibility */

#define JapanSensor_DIRECT_MODE (0u)
#define JapanSensor_BUFFER_MODE (1u)
#define JapanSensor_OUT_MODE    (((JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_1V_BUF) || \
								 (JapanSensor_DEFAULT_RANGE == JapanSensor_DAC_RANGE_4V_BUF)) ? \
								  JapanSensor_BUFFER_MODE : JapanSensor_DIRECT_MODE)

#if(JapanSensor_OUT_MODE == JapanSensor_BUFFER_MODE)
    #include <JapanSensor_BuffAmp.h>
#endif /* JapanSensor_OUT_MODE == JapanSensor_BUFFER_MODE */

#define JapanSensor_CLOCK_INT      (1u)
#define JapanSensor_CLOCK_EXT      (0u)
#define JapanSensor_CLOCK_SRC      (1u)

#if(JapanSensor_CLOCK_SRC == JapanSensor_CLOCK_INT)  
	#include <JapanSensor_DacClk.h>
	#if defined(JapanSensor_DacClk_PHASE)
		#define JapanSensor_CLK_PHASE_0nS (1u)
	#endif /* defined(JapanSensor_DacClk_PHASE) */
#endif /* JapanSensor_CLOCK_SRC == JapanSensor_CLOCK_INT */

#if (CY_PSOC3)
	#define JapanSensor_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define JapanSensor_Wave1_DMA_BYTES_PER_BURST      (1u)
#define JapanSensor_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define JapanSensor_Wave2_DMA_BYTES_PER_BURST      (1u)
#define JapanSensor_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}JapanSensor_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void JapanSensor_Start(void)             ;
void JapanSensor_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void JapanSensor_Init(void)              ;
void JapanSensor_Enable(void)            ;
void JapanSensor_Stop(void)              ;

void JapanSensor_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void JapanSensor_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void JapanSensor_Sleep(void)             ;
void JapanSensor_Wakeup(void)            ;

#define JapanSensor_SetSpeed       JapanSensor_VDAC8_SetSpeed
#define JapanSensor_SetRange       JapanSensor_VDAC8_SetRange
#define JapanSensor_SetValue       JapanSensor_VDAC8_SetValue
#define JapanSensor_DacTrim        JapanSensor_VDAC8_DacTrim
#define JapanSensor_SaveConfig     JapanSensor_VDAC8_SaveConfig
#define JapanSensor_RestoreConfig  JapanSensor_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 JapanSensor_initVar;

extern const uint8 CYCODE JapanSensor_wave1[JapanSensor_WAVE1_LENGTH];
extern const uint8 CYCODE JapanSensor_wave2[JapanSensor_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(JapanSensor_DAC_MODE == JapanSensor_VOLT_MODE)
    #define JapanSensor_RANGE_1V       (0x00u)
    #define JapanSensor_RANGE_4V       (0x04u)
#else /* current mode */
    #define JapanSensor_RANGE_32uA     (0x00u)
    #define JapanSensor_RANGE_255uA    (0x04u)
    #define JapanSensor_RANGE_2mA      (0x08u)
    #define JapanSensor_RANGE_2048uA   JapanSensor_RANGE_2mA
#endif /* JapanSensor_DAC_MODE == JapanSensor_VOLT_MODE */

/* Power setting for SetSpeed API */
#define JapanSensor_LOWSPEED       (0x00u)
#define JapanSensor_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define JapanSensor_DAC8__D JapanSensor_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define JapanSensor_HS_MASK        (0x02u)
#define JapanSensor_HS_LOWPOWER    (0x00u)
#define JapanSensor_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define JapanSensor_MODE_MASK      (0x10u)
#define JapanSensor_MODE_V         (0x00u)
#define JapanSensor_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define JapanSensor_RANGE_MASK     (0x0Cu)
#define JapanSensor_RANGE_0        (0x00u)
#define JapanSensor_RANGE_1        (0x04u)
#define JapanSensor_RANGE_2        (0x08u)
#define JapanSensor_RANGE_3        (0x0Cu)
#define JapanSensor_IDIR_MASK      (0x04u)

#define JapanSensor_DAC_RANGE      ((uint8)(0u << 2u) & JapanSensor_RANGE_MASK)
#define JapanSensor_DAC_POL        ((uint8)(0u >> 1u) & JapanSensor_IDIR_MASK)


#endif /* CY_WaveDAC8_JapanSensor_H  */

/* [] END OF FILE */
