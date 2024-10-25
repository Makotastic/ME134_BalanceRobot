#ifndef VELOCITYCONTROLER_H
#define VELOCITYCONTROLER_H

void SetVelGains(float kp, float ki, float kd);

float CalcTargetAngle(int TargetTicks, int ticks, float encoderRate);

#endif