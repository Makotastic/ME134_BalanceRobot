#include <Arduino.h>
#include <math.h>
#include <VelocityController.h>

const int MAX_ANGLE = 20;
const int maxIntegral = 2000;
float k_p = 0;
float k_d = 0;
float k_i = 0;
float sumError = 0;
//int pastTime;

void SetVelGains(float kp, float ki, float kd) {
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

float CalcTargetAngle(int TargetTicks, int ticks, float encoderRate) {

    // int currentTime = micros();
    //float dt = (currentTime - pastTime) / 1000000.0;

    float error = (TargetTicks - ticks);
    //sumError += error * dt;

    //if (sumError > maxIntegral) sumError = maxIntegral;
    //if (sumError < -maxIntegral) sumError = -maxIntegral;

    float angle = (k_p * error) + (k_i * sumError) + (k_d * encoderRate);

    angle = constrain(angle, -1 * MAX_ANGLE, MAX_ANGLE);
    
    //pastTime = currentTime;
    return angle;
}

void resetI() {
    sumError = 0;
}