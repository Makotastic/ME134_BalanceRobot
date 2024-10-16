#include <Arduino.h>
#include <math.h>
#include "TiltController.h"

const int PWM_MAX_VAL = 255;
float k_p;
float k_d;
float k_i;
float sumError;
int pastTime;

void SetGains(float kp, float ki, float kd) {
    k_p = kp;
    k_d = ki;
    k_i = kd;
}

int CalcMotorPower(float target_angle, float measured_angle, float angluar_velocity) {
    int currentTime = micros();
    float error = (target_angle - measured_angle);
    sumError += error * (currentTime - pastTime);
    float PWM = (k_p * error) + (k_i * sumError) + (k_d * angluar_velocity);
    if (PWM > PWM_MAX_VAL) {
        PWM = 255;
    }
    if (PWM < 0) {
        PWM  = 0;
    }
    pastTime = currentTime;
    return round(PWM);
}