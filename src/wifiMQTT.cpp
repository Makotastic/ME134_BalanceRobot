#include <Arduino.h>
#include <PubSubClient.h>
#include <TiltController.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "wifiMQTT.h"

const char* ssid = "Tufts_Robot";
const char* pass = "";

IPAddress server(10, 243, 124, 44);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.println(topic);
    // Print the message (payload)
    Serial.print("Message: ");
    // The payload is an array of bytes, so we need to convert it to a string
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();  // New line after printing the message

    if (strcmp(topic,"Gains")) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        SetGains(doc["k_p"], doc["k_i"], doc["k_d"]); 
    }

    if (strcmp(topic,"TargetPosition")) {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
        //setTarget
    }
}

WiFiClient Wifi_Client;
PubSubClient client(server, 1883, callback, Wifi_Client);

void MQTTSetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid);

    Serial.println("Wifi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());

    if (client.connect("ESP32Client", "testuser", "testpass")) {
        Serial.println("MQTT CONNECTED");
        client.subscribe("Gains");
        client.subscribe("TargetPosition");
        client.publish("StartUp","POWERUP");
    }
}

void MQTTLoop() {
    client.loop();
}