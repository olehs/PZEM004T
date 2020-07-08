#include <PZEM004T.h>

PZEM004T* pzem;
IPAddress ip(192,168,1,1);

void setup() {
  while(!Serial) { }
  Serial.begin(9600);

  while(!Serial1) { }
  pzem = new PZEM004T(&Serial1);
  pzem->setAddress(ip);
}

void loop() {
  float v = pzem->voltage(ip);
  if (v < 0.0) v = 0.0;
  Serial.print(v);Serial.print("V; ");

  float i = pzem->current(ip);
  if(i >= 0.0){ Serial.print(i);Serial.print("A; "); }
  
  float p = pzem->power(ip);
  if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }
  
  float e = pzem->energy(ip);
  if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }

  Serial.println();
}
