/*
 * Simple example to show using the https://github.com/plerup/espsoftwareserial software 
 * serial library on an ESP8266 with pins GPIO14 (RX) and GPIO12 (TX). 
 */

#include <SoftwareSerial.h> 
#include <PZEM004T.h>

SoftwareSerial swSer;  
PZEM004T pzem(&swSer);      //Using https://github.com/plerup/espsoftwareserial library
IPAddress ip(192,168,1,1);


void setup() {
  swSer.begin(9600, SWSERIAL_8N1, 14, 12, false, 95, 11);
  Serial.begin(9600);
  pzem.setAddress(ip);
}

void loop() {
  float v = pzem.voltage(ip);
  if (v < 0.0) v = 0.0;
  Serial.print(v);Serial.print("V; ");

  float i = pzem.current(ip);
  if(i >= 0.0){ Serial.print(i);Serial.print("A; "); }
  
  float p = pzem.power(ip);
  if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }
  
  float e = pzem.energy(ip);
  if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }

  Serial.println();

  delay(1000);
}
