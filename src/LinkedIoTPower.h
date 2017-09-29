#ifndef LINKED_IOT_POWER_H_
#define LINKED_IOT_POWER_H_

#include <Arduino.h>

class LinkedIoTPower {
  public:
    float referenceVoltage = 3300;
    float batteryMinVoltage = 4000;
    float batteryMaxVoltage = 5600;

    void getBatteryStatus(float* voltage, uint8_t* level);

    void sleep(uint32_t time);

    void disableADC();
    void enableADC();

    void disableSPI();
    void enableSPI();

    void disableTimer(uint8_t n);
    void enableTimer(uint8_t n);

    void disableTWI();
    void enableTWI();

    void disableUSART(uint8_t n);
    void enableUSART(uint8_t n);

    void disableUSB();
    void enableUSB();
    bool isUSBenabled();

  protected:
    uint8_t batteryVoltagePin = A0;
};

#endif // LINKED_IOT_POWER_H_
