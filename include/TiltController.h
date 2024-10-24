#ifndef TILTCONTROLLER_H
#define TILTCONTROLLER_H

#include <Arduino.h>
#include <math.h>

void SetGains(float kp, float ki, float kd);
float GetErrorSum();
void resetI();
int CalcMotorPower(float target_angle, float measured_angle, float angluar_velocity);

#endif 