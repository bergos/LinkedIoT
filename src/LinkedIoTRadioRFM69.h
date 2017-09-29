#ifndef LINKED_IOT_RADIO_RFM69_H_
#define LINKED_IOT_RADIO_RFM69_H_

#include "LinkedIoTRadio.h"
#include <RHReliableDatagram.h>
#include <RH_RF69.h>

class LinkedIoTRadioRFM69 : public LinkedIoTRadio {
  public:
    LinkedIoTRadioRFM69(uint8_t address, uint8_t serverAddress=0, uint8_t slaveSelectPin=10, uint8_t interruptPin=7);

    virtual uint32_t getMaxMessageLength();

    virtual bool begin();

    virtual void sleep();

    virtual bool send(uint8_t* buf, uint8_t len, uint8_t address);

    virtual JsonObject& getConfig(JsonBuffer& buffer);
    virtual bool setConfig(JsonObject& json);

  protected:
    uint8_t serverAddress;
    RH_RF69* driver;
    RHReliableDatagram* manager;
};

#endif // LINKED_IOT_RADIO_RFM69_H_
