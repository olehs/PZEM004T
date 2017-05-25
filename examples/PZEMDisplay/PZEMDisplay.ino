#include <SoftwareSerial.h> // Arduino IDE <1.6.6
#include <PZEM004T.h>


//https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
//* RX is digital pin 10 (connect to TX of other device)
//* TX is digital pin 11 (connect to RX of other device)
PZEM004T pzem(10,11);  // RX,TX
IPAddress ip(192,168,1,1);

void setup() {
  Serial.begin(9600);
  pzem.setAddress(ip);
}

void loop() {
  float v = pzem.voltage(ip);
  if (v > 0.0) {Serial.print(v);Serial.print("V; "); }

  float i = pzem.current(ip);
  if(i >= 0.0){ Serial.print(i);Serial.print("A; "); }
  
  float p = pzem.power(ip);
  if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }
  
  float e = pzem.energy(ip);
  if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }

  Serial.println();

  //delay(1000);
}
