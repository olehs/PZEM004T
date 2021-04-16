#ifndef PZEM004T_H
#define PZEM004T_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// #define PZEM004_NO_SWSERIAL

#if (not defined(PZEM004_NO_SWSERIAL)) && (defined(__AVR__) || defined(ESP8266))
#define PZEM004_SOFTSERIAL
#endif

#if defined(PZEM004_SOFTSERIAL)
#include <SoftwareSerial.h>
#endif

#include <IPAddress.h>

#define PZEM_DEFAULT_READ_TIMEOUT 1000
#define PZEM_ERROR_VALUE -1.0

struct PZEMCommand {
    uint8_t command;
    uint8_t addr[4];
    uint8_t data;
    uint8_t crc;
};

class PZEM004T
{
public:
    PZEM004T(uint8_t receivePin, uint8_t transmitPin);
    PZEM004T(HardwareSerial *port);

    /**
     * @brief Hardware serial constructor with custom pin mapping (ESP32)
     *
     * @param port Hardware serial object (or port number as uint)
     * @param rxpin gpio pin to map rx
     * @param txpin gpio pin to map tx
     */
#ifdef ESP32
    PZEM004T(HardwareSerial* port, uint8_t rxpin, uint8_t txpin);
#endif
    ~PZEM004T();

    void setReadTimeout(unsigned long msec);
    unsigned long readTimeout() {return _readTimeOut;}

    float voltage(const IPAddress &addr);
    float current(const IPAddress &addr);
    float power(const IPAddress &addr);
    float energy(const IPAddress &addr);

    bool setAddress(const IPAddress &newAddr);
    bool setPowerAlarm(const IPAddress &addr, uint8_t threshold);

private:

#ifdef PZEM004_SOFTSERIAL    
    // Stream has no virtual dtor, so keep the pointer
    SoftwareSerial *swserial = nullptr;
#endif

    Stream *serial;

    bool _isSoft;
    unsigned long _readTimeOut = PZEM_DEFAULT_READ_TIMEOUT;

    void send(const IPAddress &addr, uint8_t cmd, uint8_t data = 0);
    bool recieve(uint8_t resp, uint8_t *data = 0);

    uint8_t crc(uint8_t *data, uint8_t sz);
};

#endif // PZEM004T_H
