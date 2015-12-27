
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 01;        // Address of our node in Octal format
const uint16_t gateway_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct payload_t {                  // Structure of our payload
  unsigned int nodeID;
  unsigned long ms;
};

int pir_pin=3;
payload_t payload{this_node,0};
void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_tx/");
 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);

  ///PIR
  pinMode(pir_pin, INPUT);
  digitalWrite(pir_pin, LOW);
}

void loop() {
  if(digitalRead(pir_pin)){
    bool ok=0;
    
    Serial.println("Alarm!!");
    do{
      network.update();                          // Check the network regularly
      payload.ms = millis();
      RF24NetworkHeader header(gateway_node);
      ok=network.write(header,&payload,sizeof(payload));
      Serial.print("  send from: ");
      Serial.print(payload.nodeID);
      Serial.print("at: ");
      Serial.print(payload.ms);
      Serial.print(" ok:");
      Serial.println(ok);
      delay(1000);
    }while(!ok);
  }
}


