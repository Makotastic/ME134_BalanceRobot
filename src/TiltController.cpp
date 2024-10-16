#include <Arduino.h>
#include <math.h>
#include "TiltController.h"

const int PWM_MAX_VAL = 255;
const int maxIntegral = 2000;
float k_p;
float k_d;
float k_i;
float sumError;
int pastTime;

void SetGains(float kp, float ki, float kd) {
    k_p = kp;
    k_i = ki;
    k_d = kd;
}

float GetErrorSum() {
    return sumError;
}

int CalcMotorPower(float target_angle, float measured_angle, float angular_velocity) {
    int currentTime = micros();
    float dt = (currentTime - pastTime) / 1000000.0;

    float error = (target_angle - measured_angle);
    sumError += error * dt;

    if (sumError > maxIntegral) sumError = maxIntegral;
    if (sumError < -maxIntegral) sumError = -maxIntegral;

    float PWM = (k_p * error) + (k_i * sumError) + (k_d * angular_velocity);

    PWM = constrain(PWM, 0, PWM_MAX_VAL);
    
    pastTime = currentTime;
    return round(PWM);
}