#ifndef _IMU6050V2_H_
#define _IMU6050V2_H_

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

extern float pitchV2;
extern float pitchRateV2;

void IMU6050setup();

bool IMU6050loop();

#endif