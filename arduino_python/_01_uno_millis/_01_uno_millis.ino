unsigned long time;

void setup(){
  Serial.begin(9600);
}
void loop(){
  
  time = millis();
  //prints time since program started
  Serial.print(time);
  Serial.print(",");
  Serial.print(100);
  Serial.print(",");
  Serial.println(200);
  // wait a second so as not to send massive amounts of data
  delay(1000);
}
