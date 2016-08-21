
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "DHT.h"
#define ISRAINPIN 3
#define DHTPIN 2
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

RF24 radio(7,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 01;        // Address of our node in Octal format
const uint16_t gateway_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct payload_t {                  // Structure of our payload
  unsigned int nodeID;
  float temp;
  float humi;
  unsigned int israin;
};

payload_t payload{this_node,0.0f,0.0f,0};
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Uno DHT22 NRF24L01");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);

  ///DHT
  dht.begin();

  pinMode(ISRAINPIN, INPUT); 
}

void loop() {
  payload.temp = dht.readTemperature();// Read temperature as Celsius (the default)
  payload.humi = dht.readHumidity();
  payload.israin= digitalRead(ISRAINPIN)==0;  
  if(payload.temp==payload.temp && payload.humi==payload.humi){
    bool ok=0;
    Serial.println("Sending the package!!");
    do{
      network.update();                          // Check the network regularly
      RF24NetworkHeader header(gateway_node);
      ok=network.write(header,&payload,sizeof(payload));
      Serial.print("send from: ");
      
      Serial.print(payload.nodeID);
      Serial.print(" temp: ");
      Serial.print(payload.temp);
      Serial.print(" humi: ");
      Serial.print(payload.humi);
      Serial.print(" israin: ");
      Serial.print(payload.israin);
      
      Serial.print(" ok:");
      Serial.println(ok);
      delay(1000);
    }while(!ok);
    delay(300000);
  }
  else{
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
}


