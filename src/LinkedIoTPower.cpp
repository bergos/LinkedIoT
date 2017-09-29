#include "LinkedIoTPower.h"
#include <Battery.h>

#if defined (__AVR__)
  #include <avr/sleep.h>
  #include <avr/wdt.h>
  #include <avr/power.h>
  #include <avr/interrupt.h>
#else
  #error "Processor architecture is not supported."
#endif

void LinkedIoTPower::getBatteryStatus(float* voltage, uint8_t* level) {  
  float value = analogRead(batteryVoltagePin) * 2.0 * referenceVoltage / 1024.0;

  if (voltage != 0) {
    *voltage = value / 1000.0;
  }

  if (level != 0) {
    *level = map(value, batteryMinVoltage, batteryMaxVoltage, 0, 100);
  }
}

void LinkedIoTPower::sleep(uint32_t time) {
  delay(time);
}

#if defined __AVR_ATmega32U4__

void LinkedIoTPower::disableADC() {
  ADCSRA &= ~(1 << ADEN);
  power_adc_disable();
}

void LinkedIoTPower::enableADC() {
  power_adc_enable();
  ADCSRA |= (1 << ADEN);
}

void LinkedIoTPower::disableSPI() {
  power_spi_disable();
}

void LinkedIoTPower::enableSPI() {
  power_spi_enable();
}

void LinkedIoTPower::disableTimer(uint8_t n) {
  switch(n) {
    case 0:
      return power_timer0_disable();
    case 1:
      return power_timer1_disable();
    /*case 2:
      return power_timer2_disable();*/
    case 3:
      return power_timer3_disable();
    /*case 4:
      return power_timer4_disable();*/
  }
}

void LinkedIoTPower::enableTimer(uint8_t n) {
  switch(n) {
    case 0:
      return power_timer0_enable();
    case 1:
      return power_timer1_enable();
    /*case 2:
      return power_timer2_enable();*/
    case 3:
      return power_timer3_enable();
    /*case 4:
      return power_timer4_enable();*/
  }
}

void LinkedIoTPower::disableTWI() {
  power_twi_disable();
}

void LinkedIoTPower::enableTWI() {
  power_twi_enable();
}

void LinkedIoTPower::disableUSART(uint8_t n) {
  switch(n) {
    case 1:
      return power_usart1_disable();
  }
}

void LinkedIoTPower::enableUSART(uint8_t n) {
  switch(n) {
    case 1:
      return power_usart1_enable();
  }
}

void LinkedIoTPower::disableUSB() {
  power_usb_disable();
}

void LinkedIoTPower::enableUSB() {
  power_usb_enable();
}

#else

void LinkedIoTPower::disableADC() {}
void LinkedIoTPower::enableADC() {}

void LinkedIoTPower::disableSPI() {}
void LinkedIoTPower::enableSPI() {}

void LinkedIoTPower::disableTimer(uint8_t n) {}
void LinkedIoTPower::enableTimer(uint8_t n) {}

void LinkedIoTPower::disableTWI() {}
void LinkedIoTPower::enableTWI() {}

void LinkedIoTPower::disableUSART(uint8_t n) {}
void LinkedIoTPower::enableUSART(uint8_t n) {}

void LinkedIoTPower::disableUSB() {}
void LinkedIoTPower::enableUSB() {}

#endif
