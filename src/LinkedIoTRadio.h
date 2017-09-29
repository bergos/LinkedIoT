#ifndef LINKED_IOT_RADIO_H_
#define LINKED_IOT_RADIO_H_

#include <Arduino.h>
#include <ArduinoJson.h>

class LinkedIoTRadio {
  public:
    virtual uint32_t getMaxMessageLength() = 0;

    virtual bool begin() = 0;

    virtual void sleep() = 0;

    virtual bool send(uint8_t* buf, uint8_t len, uint8_t address=0) = 0;
    
    virtual JsonObject& getConfig(JsonBuffer& buffer) = 0;
    virtual bool setConfig(JsonObject& json) = 0;
};

#endif // LINKED_IOT_RADIO_H_
