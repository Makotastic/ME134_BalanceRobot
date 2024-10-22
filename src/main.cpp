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
  
  if (imu6050 && !imu9250) {
    deadrec = rollRate / 1000000 * (micros() - prevLoop);
    pwm = CalcMotorPower(0,deadrec,rollRate);
  }
  else if (imu6050 && imu9250) {
    pwm = CalcMotorPower(0,roll,rollRate);
    deadrec = roll;
  }
  else if (!imu6050 && imu9250) {
    pwm = CalcMotorPower(0,roll,rollRate);
    deadrec = roll;
  }

  if( imu6050 || imu9250 ){
    setPWM(pwm);
  }
  
  if (micros() - prevTimeCount > 100000) 
  {
    Serial.print("Hz: ");
    Serial.println(count);
    Serial.print("Roll: ");
    Serial.println(roll);
    Serial.println(rollRate);
    Serial.print("PWM: ");
    Serial.println(pwm);
    count = 0;
    prevTimeCount = micros();
  }
  count++;
}
