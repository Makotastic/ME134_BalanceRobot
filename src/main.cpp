#include <Arduino.h>
#include <PubSubClient.h>
#include <IMU9250.h>
#include <SPI.h>
#include <WiFi.h>

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
}

WiFiClient Wifi_Client;
PubSubClient client(server, 1883, callback, Wifi_Client);

void setup() {
  Serial.begin(115200);
 //Setup Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);

  Serial.println("Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  if (client.connect("arduinoClient", "testuser", "testpass")) {
    client.publish("outTopic","hello world");
    client.subscribe("inTopic");
    Serial.println("SUCCESSFUL");
  }
  IMU9250_Setup();
  Serial.println("setup over");
}

void loop()
{
    IMU9250_loop();
    client.loop();
}
