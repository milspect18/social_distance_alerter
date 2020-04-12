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
#include "pingSensor.h"


int8 initStatus = -1;


/// Start up the requires internal peripherals
void initPingSensors(void) {
    echoCounter_Start();
    timeout_Start();
    
    initStatus = 1;
}


/// Internal method for reading the echo pulse width in us
uint16 readPingDistance(SensorNum_t sensorNum) {
    // We need to init the hardware if it hasn't already been done
    if (initStatus == -1) {
        initPingSensors();
    }
    
    // Set the ctl register to address the mux/de-mux
    sensorSelRegister_Write((uint8)sensorNum);
    
    // Send the trig pulse via the trigger ctl register
    triggerRegister_Write(1);
    CyDelayUs(10);
    triggerRegister_Write(0);
    
    
    // Wait for the front (rising edge) of the echo pulse
    while (!echoRegister_Read()) {
        // We wait up to 1ms then timeout and bail
        if ((timeout_ReadStatusRegister() & timeout_STATUS_TC) != 0) {
            return 0xFFFF;
        }
    }
    
    // wait for back (falling edge) of echo pulse
    while (echoRegister_Read()) {}
    
    // return raw us counter val
    return echoCounter_ReadCounter();
}


/// Public function for getting a single sensor distance in the specified units
uint16 getPingDistance(SensorNum_t sensorNum, DistanceUnit_t unit) {
    switch (unit) {
        case INCHES:
            return readPingDistance(sensorNum) / IN_SCALE;
        case MILLIMETER:
            return readPingDistance(sensorNum) / MM_SCALE;
        case CENTIMETER:
            return readPingDistance(sensorNum) / CM_SCALE;
        default:
            return 0xFFFF;
    }
}


/// Public function for reading multiple ping sensor values into a buffer
void getMultiPing(uint16 *distBuf, uint8 numSensors, DistanceUnit_t units) {
    if (numSensors == 0) {
        return;
    }
    
    if (numSensors > (uint8)MAX_SENSOR_NUM) {
        numSensors = (uint8)MAX_SENSOR_NUM;
    }
    
    for (uint8 i = 0; i < numSensors; i++) {
        distBuf[i] = getPingDistance(i, units);
    }
}
/* [] END OF FILE */
