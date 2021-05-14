#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "creds.h"

WiFiClient wifiClient = new WiFiClient();
PubSubClient homeAssistMQTT(wifiClient);

#define sensorPin 5
#define switchPin 18
void connectToWifi(){
    WiFi.begin(SSID,PWD);
    while(WiFi.status() != WL_CONNECTED){
        Serial.println("---");
        delay(500);
    }
    Serial.println("Connected to "+SSID);
}
void connectToHA(){
    homeAssistMQTT.setServer(HA_ENDPOINT,1883);
    homeAssistMQTT.setCallback(callback);
    Serial.println("Connecting to HA MQTT");
    homeAssistMQTT.connect(DeviceName,HA_USERNAME,HA_PASSWORD);
    
    while (!homeAssistMQTT.connected()) {
      Serial.println("Connecting to  HA MQTT....Retry");
      homeAssistMQTT.connect(DeviceName,HA_USERNAME,HA_PASSWORD);
      delay(5000);
    }
    Serial.println("HA MQTT Connected");
    homeAssistMQTT.subscribe(CommandTopic);
}
void setup()
{
    Serial.begin(115200);
	pinMode(sensorPin, INPUT);
    pinMode(switchPin, INPUT);
    connectToWifi();
}

int status= LOW;
void loop()
{
	status = digitalRead(sensorPin);
    if(status == HIGH){
        Serial.println("Person Detected");
    }
}
