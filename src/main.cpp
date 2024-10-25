#include <Arduino.h>
#include <MotorControl.h>
#include "wifiMQTT.h"
#include "IMU6050_v2.h"
#include <encoder.h>
#include <VelocityController.h>

unsigned int count = 0;
unsigned long prevTimeCount = micros();
unsigned int countTiltPID = 0;
unsigned long prevLoop = micros();
float targetAngle = 0;

int pwm;

void setup() {
  Serial.begin(115200);
  setUpPWM();
  MQTTSetup();
  IMU6050setup();
  Serial.println("setup over");
}

void loop()
{
  MQTTLoop();

  if (countTiltPID == 4) {
    targetAngle = CalcTargetAngle(0, getTotalTicks(), getTickRate());
    countTiltPID = 0;
  }

  if (IMU6050loop()) {
  pwm = CalcMotorPower(targetAngle,pitchV2,pitchRateV2);
  setPWM(pwm);
  countTiltPID++;
  }
  
  if (micros() - prevTimeCount > 1000000) 
  {
    Serial.print("Hz: ");
    Serial.println(count);
    Serial.print("Pitch: ");
    Serial.println(pitchV2);
    Serial.print("Rate: ");
    Serial.println(pitchRateV2);
    Serial.print("PWM: ");
    Serial.println(pwm);
    count = 0;
    prevTimeCount = micros();
  }
  count++;
}
