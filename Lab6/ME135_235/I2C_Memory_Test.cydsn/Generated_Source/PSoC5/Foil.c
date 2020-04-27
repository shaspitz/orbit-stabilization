/*******************************************************************************
* File Name: Foil.c
* Version 2.10
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Foil.h"

uint8  Foil_initVar = 0u;

const uint8 CYCODE Foil_wave1[Foil_WAVE1_LENGTH] = { 0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,1u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,2u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,4u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,5u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,6u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,7u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,8u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,9u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,10u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,11u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,12u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,13u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,14u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,15u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,16u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,17u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,18u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,19u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,20u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,21u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,22u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,23u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,24u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,25u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,26u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,27u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,28u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,29u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,30u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,31u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,32u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,33u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,34u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,35u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,36u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,37u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,38u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,39u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,40u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,41u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,42u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,43u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,44u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,45u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,46u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,47u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,48u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,49u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,50u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,51u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,52u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,53u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,54u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,55u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,56u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,57u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,58u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,59u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,60u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,61u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,62u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,63u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,64u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,65u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,66u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,67u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,68u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,69u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,70u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,71u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,72u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,73u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,75u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,76u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,77u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,78u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,79u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,80u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,81u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,82u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,83u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,84u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,85u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,86u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,87u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,88u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,89u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,90u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,91u,92u };
const uint8 CYCODE Foil_wave2[Foil_WAVE2_LENGTH] = { 128u,132u,138u,143u,148u,152u,158u,162u,168u,172u,178u,182u,188u,192u,198u,202u,208u,213u,218u,222u,228u,232u,238u,242u,248u,252u,248u,242u,238u,232u,228u,222u,218u,212u,208u,202u,198u,192u,188u,182u,178u,173u,168u,162u,158u,152u,148u,143u,138u,132u,128u,122u,118u,112u,107u,102u,97u,93u,88u,83u,78u,73u,68u,62u,57u,52u,47u,42u,37u,33u,28u,23u,18u,13u,8u,3u,8u,13u,18u,23u,28u,33u,37u,42u,47u,52u,57u,62u,68u,73u,78u,83u,88u,93u,97u,102u,107u,112u,118u,122u };

static uint8  Foil_Wave1Chan;
static uint8  Foil_Wave2Chan;
static uint8  Foil_Wave1TD;
static uint8  Foil_Wave2TD;


/*******************************************************************************
* Function Name: Foil_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void Foil_Init(void) 
{
	Foil_VDAC8_Init();
	Foil_VDAC8_SetSpeed(Foil_HIGHSPEED);
	Foil_VDAC8_SetRange(Foil_DAC_RANGE);

	#if(Foil_DAC_MODE == Foil_CURRENT_MODE)
		Foil_IDAC8_SetPolarity(Foil_DAC_POL);
	#endif /* Foil_DAC_MODE == Foil_CURRENT_MODE */

	#if(Foil_OUT_MODE == Foil_BUFFER_MODE)
	   Foil_BuffAmp_Init();
	#endif /* Foil_OUT_MODE == Foil_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	Foil_Wave1TD = CyDmaTdAllocate();
	Foil_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	Foil_Wave1Setup(Foil_wave1, Foil_WAVE1_LENGTH) ;
	Foil_Wave2Setup(Foil_wave2, Foil_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(Foil_DacClk_PHASE)
	   Foil_DacClk_SetPhase(Foil_CLK_PHASE_0nS);
	#endif /* defined(Foil_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: Foil_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void Foil_Enable(void) 
{
	Foil_VDAC8_Enable();

	#if(Foil_OUT_MODE == Foil_BUFFER_MODE)
	   Foil_BuffAmp_Enable();
	#endif /* Foil_OUT_MODE == Foil_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(Foil_Wave1Chan, 1u);
	(void)CyDmaChEnable(Foil_Wave2Chan, 1u);
	
	/* set the initial value */
	Foil_SetValue(0u);
	
	#if(Foil_CLOCK_SRC == Foil_CLOCK_INT)  	
	   Foil_DacClk_Start();
	#endif /* Foil_CLOCK_SRC == Foil_CLOCK_INT */
}


/*******************************************************************************
* Function Name: Foil_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void Foil_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(Foil_initVar == 0u)
	{
		Foil_Init();
		Foil_initVar = 1u;
	}
	
	Foil_Enable();
}


/*******************************************************************************
* Function Name: Foil_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void Foil_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	Foil_Wave1Setup(wavePtr1, sampleSize1);
	Foil_Wave2Setup(wavePtr2, sampleSize2);
	Foil_Start();
}


/*******************************************************************************
* Function Name: Foil_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void Foil_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(Foil_CLOCK_SRC == Foil_CLOCK_INT)  	
	   Foil_DacClk_Stop();
	#endif /* Foil_CLOCK_SRC == Foil_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(Foil_Wave1Chan);
	(void)CyDmaChDisable(Foil_Wave2Chan);

	/* Disable power to DAC */
	Foil_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: Foil_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void Foil_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (Foil_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		Foil_Wave1Chan = Foil_Wave1_DMA_DmaInitialize(
		Foil_Wave1_DMA_BYTES_PER_BURST, Foil_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		Foil_Wave1Chan = Foil_Wave1_DMA_DmaInitialize(
		Foil_Wave1_DMA_BYTES_PER_BURST, Foil_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(Foil_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(Foil_Wave1TD, sampleSize, Foil_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)Foil_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(Foil_Wave1TD, LO16((uint32)wavePtr), LO16(Foil_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(Foil_Wave1Chan, Foil_Wave1TD);
}


/*******************************************************************************
* Function Name: Foil_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void Foil_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (Foil_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		Foil_Wave2Chan = Foil_Wave2_DMA_DmaInitialize(
		Foil_Wave2_DMA_BYTES_PER_BURST, Foil_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		Foil_Wave2Chan = Foil_Wave2_DMA_DmaInitialize(
		Foil_Wave2_DMA_BYTES_PER_BURST, Foil_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(Foil_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(Foil_Wave2TD, sampleSize, Foil_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)Foil_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(Foil_Wave2TD, LO16((uint32)wavePtr), LO16(Foil_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(Foil_Wave2Chan, Foil_Wave2TD);
}


/* [] END OF FILE */
