#include <HardwareSerial.h>
#include <PZEM004T.h>

/*
   An example on how to use ESP32 hardware serial with PZEM004T
*/

HardwareSerial Serial2(2);     // Use hwserial UART2 at pins IO-16 (RX2) and IO-17 (TX2)
PZEM004T pzem(&Serial2);
IPAddress ip(192,168,1,1);

void setup() {
   Serial.begin(115200);
   while (true) {
      Serial.println("Connecting to PZEM...");
      if(pzem.setAddress(ip))
        break;
      delay(1000);
   }
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

  delay(3000);
}