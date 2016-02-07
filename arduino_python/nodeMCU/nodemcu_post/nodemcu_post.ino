#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "gateway";//enter your network ssid
const char* password = "pythonday"; //password of the network
ESP8266WiFiMulti WiFiMulti;
void setup(){
    Serial.begin(115200);   //an esp8266 uses 115200 bit rate by default 
    delay(100);             //some small delay the get the serial connection ready 
    
    //attempting to connect the network and aquiring IP from a DHCP server
    Serial.print("Connecting to netwok");
    Serial.println(ssid);
    //WiFi.begin(ssid, password);
    WiFiMulti.addAP(ssid, password);
    //waiting for connection
    //while (WiFi.status() != WL_CONNECTED){
    while((WiFiMulti.run() != WL_CONNECTED)) {
            delay(500);
            Serial.print(".");
    }
    //show connection details
    Serial.println("Connected IP address: ");   
    Serial.println(WiFi.localIP());
}
void loop() {
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
    String res = http.getString();
    Serial.printf("%s :: %s\n",  http.header("Date").c_str(), res.c_str());
  }
  delay(5000);
}
