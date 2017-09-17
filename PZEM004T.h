#ifndef PZEM004T_H
#define PZEM004T_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>
#include <IPAddress.h>

struct PZEMCommand {
    uint8_t command;
    uint8_t addr[4];
    uint8_t data;
    uint8_t crc;
};

struct meter_t;

class PZEM004T
{
public:
    PZEM004T(uint8_t receivePin, uint8_t transmitPin);
    PZEM004T(HardwareSerial *port);
    ~PZEM004T();

    void setReadTimeout(unsigned long msec);
    unsigned long readTimeout() {return _readTimeOut;}

    float voltage(const IPAddress &addr);
    float current(const IPAddress &addr);
    float power(const IPAddress &addr);
    float energy(const IPAddress &addr);

    bool setAddress(const IPAddress &newAddr);
    bool setPowerAlarm(const IPAddress &addr, uint8_t threshold);

    struct meter_t {
	float voltage = 0.0f;
	float current = 0.0f;
	float power   = 0.0f;
	float energy  = 0.0f;
	inline float pf() {		// calculate power-factor
	    if (voltage == 0 || current == 0) return 0.0f;
	    float pf = power / voltage / current;
	    if (pf > 1) return 1.0f;
	    return pf;
	}
    };

    // pull all data from meter to struct provided
    meter_t &fetchAll(const IPAddress &addr, meter_t &data);

private:
    Stream *serial;

    unsigned long _readTimeOut;
    bool _isSoft;

    void send(const IPAddress &addr, uint8_t cmd, uint8_t data = 0);
    bool recieve(uint8_t resp, uint8_t *data = 0);

    uint8_t crc(uint8_t *data, uint8_t sz);
};

#endif // PZEM004T_H
