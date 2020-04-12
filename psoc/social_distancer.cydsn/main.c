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
#include "project.h"
#include "pingSensor.h"
#include "millisCounter.h"
#include <stdio.h>

#define NUM_SENSORS     2
#define DEPTH_OF_AVG    10  // We will run an average of the last 10 readingss
#define EVER            ;;
#define SOCIAL_DISTANCE_IN      72

// File private protos
void updateSensorAverages(uint16 *avgDistBuf, DistanceUnit_t units);
uint8 bubbleViolated(uint16 *distance, uint8 sensorCount);
void initSensorReadings(uint16 *distanceBuffer, DistanceUnit_t units);

int main(void) {
    uint16 distance[NUM_SENSORS] = {0};
    char distUartStr[256] = {0};
    uint64 curMs = 0;
    uint64 lastPingScanMs = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    oneMsIsr_Start();
    msTimer_Start();
    ledPwm_Start();
    
    // Fill our reading buffer
    initSensorReadings(distance, INCHES);

    for(EVER) {
        curMs = getCurMs();
        
        if ((curMs - lastPingScanMs) >= 100) {
            updateSensorAverages(distance, INCHES);
            lastPingScanMs = curMs;
        }
        
        // PIR sensor is triggered AND
        // (PING sensor 1 is less than 72 inches OR
        //  PING sensor 2 is less than 72 inches)
        if (pirInput_Read() && bubbleViolated(distance, NUM_SENSORS)) {
            alarmOut_Write(1);
            ledPwm_WriteCompare(250);
        } else {
            alarmOut_Write(0);
            ledPwm_WriteCompare(0);
        }
    }
}


/** Calculate a running average of the last 10 sensor readings
 *
 *  Using a static (runtime global) buffer, read in the latest reading
 *  while maintaining the previous nine (ring buffer).  Then average the 10 values
 *  and update the provide buffer with the average value for each sensor.
 */
void updateSensorAverages(uint16 *avgDistBuf, DistanceUnit_t units) {
    static uint16 readingBuffer[DEPTH_OF_AVG][NUM_SENSORS] = {0};
    static uint8 curReadingIdx = 0;
    uint16 curSum = 0;
    
    getMultiPing(readingBuffer[curReadingIdx], NUM_SENSORS, units);
    
    for (uint8 sensorIdx = 0; sensorIdx < NUM_SENSORS; sensorIdx++) {
        for (uint8 sampleIdx = 0; sampleIdx < DEPTH_OF_AVG; sampleIdx++) {
            curSum += readingBuffer[sampleIdx][sensorIdx];
        }
        
        uint16 avg = (curSum / DEPTH_OF_AVG);
        avgDistBuf[sensorIdx] = avg;
        curSum = 0;
    }
        
    curReadingIdx++;
    
    if (curReadingIdx >= DEPTH_OF_AVG) {
        curReadingIdx = 0;
    }
}


/// Check whether or not someone/something is within 6'
uint8 bubbleViolated(uint16 *distance, uint8 sensorCount) {
    for (uint8 i = 0; i < sensorCount; i++) {
        if (distance[i] < SOCIAL_DISTANCE_IN) {
            return 1;
        }
    }
    
    // No sensor is reading less that the safe distance
    return 0;
}


/// Fill our averaging buffer with enough readings to stabalize an initial distance reading
void initSensorReadings(uint16 *distanceBuffer, DistanceUnit_t units) {
    for (uint8 i = 0; i < DEPTH_OF_AVG; i++) {
        updateSensorAverages(distanceBuffer, units);
        CyDelay(10);    //  If the distance is very short we need to pause between readings
    }
}
/* [] END OF FILE */
