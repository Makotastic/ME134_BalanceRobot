#include <Arduino.h>
#include <MotorControl.h>
#include "wifiMQTT.h"
#include "IMU6050_v2.h"
#include "IMU9250_v2.h"

int count = 0;
unsigned long prevTimeCount = micros();

unsigned long prevLoop = micros();

bool imu9250 = false;
bool imu6050 = false;

float deadrec = 0;
int pwm;

void setup() {
  Serial.begin(115200);
  MQTTSetup();
  IMU9250setup();
  IMU6050setup();
  setUpPWM();
  Serial.println("setup over");
}

void loop()
{
  MQTTLoop();

  imu6050 = IMU6050loop();
  imu9250 = IMU9250loop();
  
  // if (imu6050 && !imu9250) {
  //   deadrec = rollRate / 1000000 * (float)(micros() - prevLoop);
  //   pwm = CalcMotorPower(0,deadrec,rollRate);
  // }
  // else if (imu6050 && imu9250) {
  //   pwm = CalcMotorPower(0,pitch,rollRate);
  //   deadrec = pitch;
  // }
  // else if (!imu6050 && imu9250) {
  //   pwm = CalcMotorPower(0,pitch,rollRate);
  //   deadrec = pitch;
  // }

  // if( imu6050 || imu9250 ){
  //   setPWM(pwm);
  // }

  pwm = CalcMotorPower(0,pitch,rollRate);
  setPWM(pwm);
  
  if (micros() - prevTimeCount > 1000000) 
  {
    Serial.print("Hz: ");
    Serial.println(count);
    Serial.print("Roll: ");
    Serial.println(pitch);
    Serial.println(rollRate);
    Serial.print("PWM: ");
    Serial.println(pwm);
    count = 0;
    prevTimeCount = micros();
  }
  count++;
}
