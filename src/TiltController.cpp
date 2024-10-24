#include <Arduino.h>
#include <math.h>
#include "TiltController.h"

const int PWM_MAX_VAL = 255;
const int maxIntegral = 2000;
float k_p = 0;
float k_d = 0;
float k_i = 0;
float sumError;
int pastTime;

//k_d negative

void SetGains(float kp, float ki, float kd) {
    k_p = kp;
    k_i = ki;
    k_d = kd;

    Serial.print("Setting Gains: ");
    Serial.print(k_p);
    Serial.print(k_i);
    Serial.print(k_d);
}

float GetErrorSum() {
    return sumError;
}

int CalcMotorPower(float target_angle, float measured_angle, float angular_velocity) {
    float mNormAngle = measured_angle;
    // if (measured_angle > 180) {
    //     mNormAngle = measured_angle - 360;
    // }
    // else {
    //     mNormAngle = measured_angle;
    // }

    int currentTime = micros();
    float dt = (currentTime - pastTime) / 1000000.0;

    float error = (target_angle - mNormAngle);
    sumError += error * dt;

    //if (sumError > maxIntegral) sumError = maxIntegral;
    //if (sumError < -maxIntegral) sumError = -maxIntegral;

    float PWM = (k_p * error) + (k_i * sumError) + (k_d * angular_velocity);

    PWM = constrain(PWM, -1 * PWM_MAX_VAL, PWM_MAX_VAL);
    
    pastTime = currentTime;
    return round(PWM);
}

void resetI() {
    sumError = 0;
}