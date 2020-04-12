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
#include "millisCounter.h"
#include "led.h"

// Private protos
void fiveMsTask();

uint64 curMs = 0;

void msTickCallback() {
    // clear interrupt
    msTimer_ReadStatusRegister();
    
    // Inc Counter
    curMs++;
    
    if ((curMs % 5) == 0) {
        fiveMsTask();
    }
}


/// Public function for getting the current millis since init
uint64 getCurMs() {
    return curMs;   
}


/// Private function for handling tasks every 5ms
void fiveMsTask() {
//    updateLedPwm();
}
/* [] END OF FILE */
