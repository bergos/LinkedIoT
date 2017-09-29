#ifndef LINKED_IOT_PUSH_SENSOR_H
#define LINKED_IOT_PUSH_SENSOR_H

#include "LinkedIoTDevice.h"
#include <ArduinoJson.h>

class LinkedIoTPushSensor : public LinkedIoTDevice {
  public:
    LinkedIoTPushSensor(LinkedIoTRadio& radio);
    virtual ~LinkedIoTPushSensor();

    virtual bool push(JsonObject& json);

  protected:
    uint8_t* messageBuffer = 0;

    uint8_t* getMessageBuffer();
};

#endif // LINKED_IOT_PUSH_SENSOR_H
