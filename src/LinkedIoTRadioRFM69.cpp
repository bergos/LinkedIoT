#include "LinkedIoTRadioRFM69.h"
#include <SPI.h>

LinkedIoTRadioRFM69::LinkedIoTRadioRFM69(uint8_t address, uint8_t serverAddress, uint8_t slaveSelectPin, uint8_t interruptPin) : serverAddress(serverAddress) {
  driver = new RH_RF69(slaveSelectPin, interruptPin);
  manager = new RHReliableDatagram(*driver, address);
}

uint32_t LinkedIoTRadioRFM69::getMaxMessageLength() {
  return RH_RF69_MAX_MESSAGE_LEN;
}

bool LinkedIoTRadioRFM69::begin() {
  if (!manager->init()) {
    return false;
  }

  driver->setFrequency(868.0);
  driver->setTxPower(13);
  // RFM69HW -> range 14 to 20 like this:
  //driver->setTxPower(20);

  return true;
}

bool LinkedIoTRadioRFM69::send(uint8_t* buf, uint8_t len, uint8_t address) {
  if (address == 0) {
    address = serverAddress;
  }

  return manager->sendtoWait(buf, len, address);
}

void LinkedIoTRadioRFM69::sleep() {
  driver->sleep();
}

JsonObject& LinkedIoTRadioRFM69::getConfig(JsonBuffer& buffer) {
  JsonObject& json = buffer.createObject();

  json["address"] = manager->thisAddress();
  json["gateway"] = serverAddress;

  return json;
}

bool LinkedIoTRadioRFM69::setConfig(JsonObject& json) {
  manager->setThisAddress(json["address"]);
  serverAddress = json["gateway"];

  return true;
}
