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
#include "led.h"

void updateLedPwm() {
    static uint8 ledCompVal = 0;
    static uint8 goingUp = 1;
    
    // Update the value for this cycle
    goingUp ? ledCompVal++ : ledCompVal--;
    
    // Check if we hit top or bottom and flip direction
    if ((goingUp == 1) && (ledCompVal == ledPwm_ReadPeriod())) {
        goingUp = 0;
    } else if ((goingUp == 0) && (ledCompVal == 0)) {
        goingUp = 1;
    }
    
    // write the new compare value
    ledPwm_WriteCompare(ledCompVal);
}

/* [] END OF FILE */
