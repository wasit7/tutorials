#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
void sendAlarm();
void setup() {
    pinMode(4, INPUT);
    USE_SERIAL.begin(115200);
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    WiFiMulti.addAP("acesspointid", "key");
    Serial.println(WiFi.localIP());
}

    int previousRead = 0;
    int currentRead = 0;
void loop() {
    currentRead = digitalRead(4);
    if(previousRead == 0 && currentRead == 1){
      printf("Alarm");
      sendAlarm();
      }
     previousRead = currentRead;
}

void sendAlarm() {
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        http.begin("http://192.168.1.36:5000/alarm");
        int httpCode = http.GET();
        
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode > 0) {
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        }
        http.end();
    }
    delay(1000);
  }
