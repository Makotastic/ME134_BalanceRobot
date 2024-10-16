#include <Arduino.h>
#include <IMU9250.h>
#include "wifiMQTT.h"

void setup() {
  Serial.begin(115200);
  MQTTSetup();
  IMU9250_Setup();
  Serial.println("setup over");
}

void loop()
{
  MQTTLoop();
  IMU9250_loop();
}
