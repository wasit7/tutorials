unsigned long time;
int analogPin = 3;     // potentiometer wiper (middle terminal) connected to analog pin 3
int v1 = 0;           // outside leads to ground and +5V                 
void setup(){
  Serial.begin(9600);
}
void loop(){
  
  time = millis();
  v1 = analogRead(analogPin);    // read the input pin
  //prints time since program started
  Serial.print(time);
  Serial.print(",");
  Serial.print(v1);
  Serial.print(",");
  Serial.println(200);
  // wait a second so as not to send massive amounts of data
  delay(100);
}
