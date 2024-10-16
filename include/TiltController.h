#include <Arduino.h>
#include <math.h>

void SetGains(float kp, float ki, float kd);
int CalcMotorPower(float target_angle, float measured_angle, float angluar_velocity);