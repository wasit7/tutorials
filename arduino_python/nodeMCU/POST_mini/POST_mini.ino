#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

//    USE_SERIAL.println();
//    USE_SERIAL.println();
//    USE_SERIAL.println();

//    for(uint8_t t = 4; t > 0; t--) {
//        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
//        USE_SERIAL.flush();
//        delay(1000);
//    }
    delay(5000);
    WiFiMulti.addAP("gayeway", "pythonday");
    USE_SERIAL.println("Connected IP address: ");   
    USE_SERIAL.println(WiFi.localIP());
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        const char * headerkeys[] = {"User-Agent","Set-Cookie","Cookie","Date","Content-Type","Connection"} ;
        size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
        String PostData = "usr=esp8266&msg= ["+String(millis())+"] analog:"+String(analogRead(A0));
      
        http.begin("http://pythonday-1191.appspot.com/");
        http.setReuse(true);
        http.setUserAgent("esp8266"); 
        http.addHeader("Content-type","application/x-www-form-urlencoded");

        http.collectHeaders(headerkeys,headerkeyssize);
        int code = http.POST(PostData);
//        Serial.printf("[HTTP] POST... code: %d\r\n", code);
        String res = http.getString();        
//        Serial.printf("Header count: %d\r\n", http.headers());
//        for (int i=0; i < http.headers(); i++) {
//          Serial.printf("%s = %s\r\n", http.headerName(i).c_str(), http.header(i).c_str());
//        }
        //Serial.printf("Cookie: %s\r\n", http.header("Cookie").c_str());
        //Serial.printf("Set-Cookie: %s\r\n", http.header("Set-Cookie").c_str());
        
        USE_SERIAL.printf("%s :: %s\n",  http.header("Date").c_str(), res.c_str());
    }
    
    delay(5000);
}

