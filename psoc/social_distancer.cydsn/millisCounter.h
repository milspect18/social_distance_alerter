/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef MILLIS_COUNTER_H
#define MILLIS_COUNTER_H
    
#include "project.h"
    
extern uint64 curMs;
    
void msTickCallback(void);
uint64 getCurMs(void);
    
#endif
/* [] END OF FILE */
