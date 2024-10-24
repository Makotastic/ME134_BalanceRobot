#ifndef _IMU9250V2_H_
#define _IMU9250V2_H_

#include <Arduino.h>
#include <math.h>
#include <MPU9250_RegisterMap.h>
#include <SparkFunMPU9250-DMP.h> // Include SparkFun MPU-9250-DMP library
#include <Wire.h> // Depending on your Arduino version, you may need to include Wire.h

extern float pitch;

void IMU9250setup();
bool IMU9250loop();

#endif