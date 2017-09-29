#ifndef LINKED_IOT_DEVICE_H_
#define LINKED_IOT_DEVICE_H_

#include "LinkedIoTPower.h"
#include "LinkedIoTRadio.h"

class HttpConnection;
class WS2812;

class LinkedIoTDevice {
  public:
    char id[37];
    LinkedIoTPower power;
    uint8_t setupButtonPin = 9;
    uint8_t statusLedPinPower = 4;
    uint8_t statusLedPinData = 5;

    LinkedIoTDevice(LinkedIoTRadio& radio);
    virtual ~LinkedIoTDevice();

    virtual bool begin();

    virtual bool loop();

    virtual void setupLoop();

    virtual void sleep(uint32_t time);

    virtual bool send(uint8_t* buf, uint8_t len, uint8_t address=0);

    virtual void setStatusLed(uint32_t color);

  protected:
    LinkedIoTRadio& radio;
    WS2812* statusLed;
    uint32_t setupButtonStart = 0;
    uint8_t setupMode = 0;
    HttpConnection* setupConnection = 0;
    
    virtual void startSetup();
    virtual void endSetup();
};

#endif // LINKED_IOT_DEVICE_H_
