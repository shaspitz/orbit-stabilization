/*******************************************************************************
* File Name: DirControl.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_DirControl_H) /* CY_CONTROL_REG_DirControl_H */
#define CY_CONTROL_REG_DirControl_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} DirControl_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    DirControl_Write(uint8 control) ;
uint8   DirControl_Read(void) ;

void DirControl_SaveConfig(void) ;
void DirControl_RestoreConfig(void) ;
void DirControl_Sleep(void) ; 
void DirControl_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define DirControl_Control        (* (reg8 *) DirControl_Sync_ctrl_reg__CONTROL_REG )
#define DirControl_Control_PTR    (  (reg8 *) DirControl_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_DirControl_H */


/* [] END OF FILE */
