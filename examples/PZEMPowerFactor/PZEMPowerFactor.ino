#include <SoftwareSerial.h> // Arduino IDE <1.6.6 
#include <PZEM004T.h>

PZEM004T pzem(10,11);  // RX,TX
IPAddress ip(192,168,1,1);

void setup() {
  Serial.begin(9600);
  pzem.setAddress(ip);
}

void loop() {

/*
    PZEM meter does RMS measurment for voltage and current
    Power factor for active power can be calculated as a simple P / rms(U) / rms(I)
    Tested with:
    - active loads under triac control,
    - switching power supplies without PFC
    - switching power supplies with Active-PFC

    Cons: accuracy
    Just give it a try
*/

    PZEM004T::meter_t meterdata;	// structure for monitor data

    pzem.fetchAll(ip, meterdata);	// fetch all data at once

    Serial.print("Voltage - ");		Serial.println(meterdata.voltage);
    Serial.print("Current - ");		Serial.println(meterdata.current);
    Serial.print("Power - ");		Serial.println(meterdata.power);
    Serial.print("Power Factor - ");	Serial.println(meterdata.pf());
    Serial.print("Energy - ");		Serial.println(meterdata.energy);

    Serial.println();

    delay(2000);
}
