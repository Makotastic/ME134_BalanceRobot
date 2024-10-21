#include <Arduino.h>
#include <test.h>
#include <MotorControl.h>
#include "wifiMQTT.h"

int count = 0;
unsigned long prevTime = micros();

void setup() {
  Serial.begin(115200);
  MQTTSetup();
  IMUsetup();
  setUpPWM();
  Serial.println("setup over");
}

void loop()
{
  MQTTLoop();
  //if ()
  IMUloop();
  int pwm = CalcMotorPower(0,roll,gX);
  setPWM(pwm);
  if (micros() - prevTime > 1000000) 
  {
    Serial.print("Hz: ");
    Serial.println(count);
    Serial.print("Roll: ");
    Serial.println(roll);
    Serial.println(gX);
    Serial.print("PWM: ");
    Serial.println(pwm);
    count = 0;
    prevTime = micros();
  }
  count++;
}
