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
#ifndef PING_SENSOR_H
#define PING_SENSOR_H
    
#include "project.h"
    
// Based on datasheet
#define MAX_CM      400
#define MAX_MM      4000
#define MAX_IN      158
    
// Scaling values for converting the uS count to a
// distance measurement
#define MM_SCALE    (5.8f)
#define CM_SCALE    (58.0f)
#define IN_SCALE    (148.0f)
    
// Flag for peripheral init status
extern int8 initStatus;
    
// Sensors available
typedef enum {
    SENSOR_ONE,
    SENSOR_TWO,
    SENSOR_THREE,
    SENSOR_FOUR,
    MAX_SENSOR_NUM = SENSOR_FOUR
} SensorNum_t;

typedef enum {
    INCHES,
    MILLIMETER,
    CENTIMETER
} DistanceUnit_t;

// Public API
void initPingSensors(void);
uint16 getPingDistance(SensorNum_t sensorNum, DistanceUnit_t unit);
uint16 getPingMillimeters(SensorNum_t sensorNum);
uint16 getPingInches(SensorNum_t sensorNum);
void getMultiPing(uint16 *distBuf, uint8 numSensors, DistanceUnit_t units);

#endif
/* [] END OF FILE */
