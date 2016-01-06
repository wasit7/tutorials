#include <SPI.h>
#include <Ethernet.h>
#include <RF24Network.h>
#include <RF24.h>

//////////////////ethernet setting
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xE0
};

//IPAddress ip(192, 168, 1, 177);
//int port = 5000;
//char server[] = "192.168.1.3";
int port = 80;
char server[] = "www.scituweather.appspot.com";
//IPAddress server(192,168,1,2);
//IPAddress myDns(8, 8, 8, 8);
EthernetClient client;

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 1000L; // delay between updates, in milliseconds

//////////////////nrf24 setting
RF24 radio(7,8);                // nRF24L01(+) radio attached using Getting Started board 
RF24Network network(radio);      // Network uses that radio
const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format

struct payload_t {                  // Structure of our payload
  unsigned int nodeID;
  float temp;
  float humi;
  int israin;
};
payload_t payload;



void setup() {
  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // give the ethernet module time to boot up:
  delay(1000);
  
  // start the Ethernet connection using a fixed IP address and DNS server:
  //Ethernet.begin(mac, ip, myDns);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print the Ethernet board/shield's IP address:
  printIPAddress();

  ////////////////nrf24
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void loop() {
  ///////////////nrf24
  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:
      listenRF24();
      break;

  }  
  


}

void listenRF24(){
  network.update();                  // Check the network regularly  
  while ( network.available() ) {     // Is there anything ready for us?
    RF24NetworkHeader header;        // If so, grab it and print it out
    network.read(header,&payload,sizeof(payload));
    Serial.print("Received packet from");
    httpRequest(payload);
    
    Serial.print(payload.nodeID);
    Serial.print("temp: ");
    Serial.print(payload.temp);
    Serial.print("humi: ");
    Serial.print(payload.humi);
    Serial.print("israin: ");
    Serial.println(payload.israin);   
  }
  
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
}

void printIPAddress()
{
  Serial.print("IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }

  Serial.println();
}

// this method makes a HTTP connection to the server:
void httpRequest(payload_t& payload) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, port)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET /?");
    client.print("temp=");client.print(payload.temp);
    client.print("&humi=");client.print(payload.humi);
    client.print("&israin=");client.print(payload.israin);
    client.println(" HTTP/1.1");
    client.print("Host: ");client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


