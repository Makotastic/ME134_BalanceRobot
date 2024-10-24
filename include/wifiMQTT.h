#ifndef WIFIMQTT_H
#define WIFIMQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <TiltController.h>
#include <ArduinoJson.h>
#include <WiFi.h>

void callback(char* topic, byte* payload, unsigned int length);
void MQTTSetup();
void MQTTLoop();
void sendIntegralSum();
void logs(char* data);

#endif