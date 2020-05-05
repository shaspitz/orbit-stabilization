/*******************************************************************************
* File Name: Shunt.h  
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

#if !defined(CY_WaveDAC8_Shunt_H) 
#define CY_WaveDAC8_Shunt_H

#include "cytypes.h"
#include "cyfitter.h"
#include <Shunt_Wave1_DMA_dma.h>
#include <Shunt_Wave2_DMA_dma.h>
#include <Shunt_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define Shunt_WAVE1_TYPE     (2u)     /* Waveform for wave1 */
#define Shunt_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define Shunt_SINE_WAVE      (0u)
#define Shunt_SQUARE_WAVE    (1u)
#define Shunt_TRIANGLE_WAVE  (2u)
#define Shunt_SAWTOOTH_WAVE  (3u)
#define Shunt_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define Shunt_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define Shunt_WAVE1_LENGTH   (4000u)   /* Length for wave1 */
#define Shunt_WAVE2_LENGTH   (100u)   /* Length for wave2 */
	
#define Shunt_DEFAULT_RANGE    (0u) /* Default DAC range */
#define Shunt_DAC_RANGE_1V     (0u)
#define Shunt_DAC_RANGE_1V_BUF (16u)
#define Shunt_DAC_RANGE_4V     (1u)
#define Shunt_DAC_RANGE_4V_BUF (17u)
#define Shunt_VOLT_MODE        (0u)
#define Shunt_CURRENT_MODE     (1u)
#define Shunt_DAC_MODE         (((Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_1V) || \
									  (Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_4V) || \
							  		  (Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_1V_BUF) || \
									  (Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_4V_BUF)) ? \
									   Shunt_VOLT_MODE : Shunt_CURRENT_MODE)

#define Shunt_DACMODE Shunt_DAC_MODE /* legacy definition for backward compatibility */

#define Shunt_DIRECT_MODE (0u)
#define Shunt_BUFFER_MODE (1u)
#define Shunt_OUT_MODE    (((Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_1V_BUF) || \
								 (Shunt_DEFAULT_RANGE == Shunt_DAC_RANGE_4V_BUF)) ? \
								  Shunt_BUFFER_MODE : Shunt_DIRECT_MODE)

#if(Shunt_OUT_MODE == Shunt_BUFFER_MODE)
    #include <Shunt_BuffAmp.h>
#endif /* Shunt_OUT_MODE == Shunt_BUFFER_MODE */

#define Shunt_CLOCK_INT      (1u)
#define Shunt_CLOCK_EXT      (0u)
#define Shunt_CLOCK_SRC      (1u)

#if(Shunt_CLOCK_SRC == Shunt_CLOCK_INT)  
	#include <Shunt_DacClk.h>
	#if defined(Shunt_DacClk_PHASE)
		#define Shunt_CLK_PHASE_0nS (1u)
	#endif /* defined(Shunt_DacClk_PHASE) */
#endif /* Shunt_CLOCK_SRC == Shunt_CLOCK_INT */

#if (CY_PSOC3)
	#define Shunt_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define Shunt_Wave1_DMA_BYTES_PER_BURST      (1u)
#define Shunt_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define Shunt_Wave2_DMA_BYTES_PER_BURST      (1u)
#define Shunt_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}Shunt_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void Shunt_Start(void)             ;
void Shunt_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void Shunt_Init(void)              ;
void Shunt_Enable(void)            ;
void Shunt_Stop(void)              ;

void Shunt_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void Shunt_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void Shunt_Sleep(void)             ;
void Shunt_Wakeup(void)            ;

#define Shunt_SetSpeed       Shunt_VDAC8_SetSpeed
#define Shunt_SetRange       Shunt_VDAC8_SetRange
#define Shunt_SetValue       Shunt_VDAC8_SetValue
#define Shunt_DacTrim        Shunt_VDAC8_DacTrim
#define Shunt_SaveConfig     Shunt_VDAC8_SaveConfig
#define Shunt_RestoreConfig  Shunt_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 Shunt_initVar;

extern const uint8 CYCODE Shunt_wave1[Shunt_WAVE1_LENGTH];
extern const uint8 CYCODE Shunt_wave2[Shunt_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(Shunt_DAC_MODE == Shunt_VOLT_MODE)
    #define Shunt_RANGE_1V       (0x00u)
    #define Shunt_RANGE_4V       (0x04u)
#else /* current mode */
    #define Shunt_RANGE_32uA     (0x00u)
    #define Shunt_RANGE_255uA    (0x04u)
    #define Shunt_RANGE_2mA      (0x08u)
    #define Shunt_RANGE_2048uA   Shunt_RANGE_2mA
#endif /* Shunt_DAC_MODE == Shunt_VOLT_MODE */

/* Power setting for SetSpeed API */
#define Shunt_LOWSPEED       (0x00u)
#define Shunt_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define Shunt_DAC8__D Shunt_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define Shunt_HS_MASK        (0x02u)
#define Shunt_HS_LOWPOWER    (0x00u)
#define Shunt_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define Shunt_MODE_MASK      (0x10u)
#define Shunt_MODE_V         (0x00u)
#define Shunt_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define Shunt_RANGE_MASK     (0x0Cu)
#define Shunt_RANGE_0        (0x00u)
#define Shunt_RANGE_1        (0x04u)
#define Shunt_RANGE_2        (0x08u)
#define Shunt_RANGE_3        (0x0Cu)
#define Shunt_IDIR_MASK      (0x04u)

#define Shunt_DAC_RANGE      ((uint8)(0u << 2u) & Shunt_RANGE_MASK)
#define Shunt_DAC_POL        ((uint8)(0u >> 1u) & Shunt_IDIR_MASK)


#endif /* CY_WaveDAC8_Shunt_H  */

/* [] END OF FILE */
