/*******************************************************************************
* File Name: Foil.h  
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

#if !defined(CY_WaveDAC8_Foil_H) 
#define CY_WaveDAC8_Foil_H

#include "cytypes.h"
#include "cyfitter.h"
#include <Foil_Wave1_DMA_dma.h>
#include <Foil_Wave2_DMA_dma.h>
#include <Foil_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define Foil_WAVE1_TYPE     (3u)     /* Waveform for wave1 */
#define Foil_WAVE2_TYPE     (2u)     /* Waveform for wave2 */
#define Foil_SINE_WAVE      (0u)
#define Foil_SQUARE_WAVE    (1u)
#define Foil_TRIANGLE_WAVE  (2u)
#define Foil_SAWTOOTH_WAVE  (3u)
#define Foil_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define Foil_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define Foil_WAVE1_LENGTH   (4000u)   /* Length for wave1 */
#define Foil_WAVE2_LENGTH   (100u)   /* Length for wave2 */
	
#define Foil_DEFAULT_RANGE    (0u) /* Default DAC range */
#define Foil_DAC_RANGE_1V     (0u)
#define Foil_DAC_RANGE_1V_BUF (16u)
#define Foil_DAC_RANGE_4V     (1u)
#define Foil_DAC_RANGE_4V_BUF (17u)
#define Foil_VOLT_MODE        (0u)
#define Foil_CURRENT_MODE     (1u)
#define Foil_DAC_MODE         (((Foil_DEFAULT_RANGE == Foil_DAC_RANGE_1V) || \
									  (Foil_DEFAULT_RANGE == Foil_DAC_RANGE_4V) || \
							  		  (Foil_DEFAULT_RANGE == Foil_DAC_RANGE_1V_BUF) || \
									  (Foil_DEFAULT_RANGE == Foil_DAC_RANGE_4V_BUF)) ? \
									   Foil_VOLT_MODE : Foil_CURRENT_MODE)

#define Foil_DACMODE Foil_DAC_MODE /* legacy definition for backward compatibility */

#define Foil_DIRECT_MODE (0u)
#define Foil_BUFFER_MODE (1u)
#define Foil_OUT_MODE    (((Foil_DEFAULT_RANGE == Foil_DAC_RANGE_1V_BUF) || \
								 (Foil_DEFAULT_RANGE == Foil_DAC_RANGE_4V_BUF)) ? \
								  Foil_BUFFER_MODE : Foil_DIRECT_MODE)

#if(Foil_OUT_MODE == Foil_BUFFER_MODE)
    #include <Foil_BuffAmp.h>
#endif /* Foil_OUT_MODE == Foil_BUFFER_MODE */

#define Foil_CLOCK_INT      (1u)
#define Foil_CLOCK_EXT      (0u)
#define Foil_CLOCK_SRC      (1u)

#if(Foil_CLOCK_SRC == Foil_CLOCK_INT)  
	#include <Foil_DacClk.h>
	#if defined(Foil_DacClk_PHASE)
		#define Foil_CLK_PHASE_0nS (1u)
	#endif /* defined(Foil_DacClk_PHASE) */
#endif /* Foil_CLOCK_SRC == Foil_CLOCK_INT */

#if (CY_PSOC3)
	#define Foil_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define Foil_Wave1_DMA_BYTES_PER_BURST      (1u)
#define Foil_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define Foil_Wave2_DMA_BYTES_PER_BURST      (1u)
#define Foil_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}Foil_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void Foil_Start(void)             ;
void Foil_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void Foil_Init(void)              ;
void Foil_Enable(void)            ;
void Foil_Stop(void)              ;

void Foil_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void Foil_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void Foil_Sleep(void)             ;
void Foil_Wakeup(void)            ;

#define Foil_SetSpeed       Foil_VDAC8_SetSpeed
#define Foil_SetRange       Foil_VDAC8_SetRange
#define Foil_SetValue       Foil_VDAC8_SetValue
#define Foil_DacTrim        Foil_VDAC8_DacTrim
#define Foil_SaveConfig     Foil_VDAC8_SaveConfig
#define Foil_RestoreConfig  Foil_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 Foil_initVar;

extern const uint8 CYCODE Foil_wave1[Foil_WAVE1_LENGTH];
extern const uint8 CYCODE Foil_wave2[Foil_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(Foil_DAC_MODE == Foil_VOLT_MODE)
    #define Foil_RANGE_1V       (0x00u)
    #define Foil_RANGE_4V       (0x04u)
#else /* current mode */
    #define Foil_RANGE_32uA     (0x00u)
    #define Foil_RANGE_255uA    (0x04u)
    #define Foil_RANGE_2mA      (0x08u)
    #define Foil_RANGE_2048uA   Foil_RANGE_2mA
#endif /* Foil_DAC_MODE == Foil_VOLT_MODE */

/* Power setting for SetSpeed API */
#define Foil_LOWSPEED       (0x00u)
#define Foil_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define Foil_DAC8__D Foil_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define Foil_HS_MASK        (0x02u)
#define Foil_HS_LOWPOWER    (0x00u)
#define Foil_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define Foil_MODE_MASK      (0x10u)
#define Foil_MODE_V         (0x00u)
#define Foil_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define Foil_RANGE_MASK     (0x0Cu)
#define Foil_RANGE_0        (0x00u)
#define Foil_RANGE_1        (0x04u)
#define Foil_RANGE_2        (0x08u)
#define Foil_RANGE_3        (0x0Cu)
#define Foil_IDIR_MASK      (0x04u)

#define Foil_DAC_RANGE      ((uint8)(0u << 2u) & Foil_RANGE_MASK)
#define Foil_DAC_POL        ((uint8)(0u >> 1u) & Foil_IDIR_MASK)


#endif /* CY_WaveDAC8_Foil_H  */

/* [] END OF FILE */
