#include <ESP8266WiFi.h>
const char* ssid     = "gateway";//enter your network ssid
const char* password = "pythonday"; //password of the network
void setup(){
    Serial.begin(115200);   //an esp8266 uses 115200 bit rate by default 
    delay(100);             //some small delay the get the serial connection ready 
    
    //attempting to connect the network and aquiring IP from a DHCP server
    Serial.print("Connecting to netwok");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    //waiting for connection
    while (WiFi.status() != WL_CONNECTED){
            delay(500);
            Serial.print(".");
    }
    //show connection details
    Serial.println("Connected IP address: ");   
    Serial.println(WiFi.localIP());
}
void loop() {}
