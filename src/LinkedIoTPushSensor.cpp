#include "LinkedIoTPushSensor.h"

LinkedIoTPushSensor::LinkedIoTPushSensor(LinkedIoTRadio& radio) : LinkedIoTDevice(radio) {
}

LinkedIoTPushSensor::~LinkedIoTPushSensor() {
  if (messageBuffer) {
    delete[] messageBuffer;
  }
}

bool LinkedIoTPushSensor::push(JsonObject& json) {
  uint8_t* message = getMessageBuffer();

  json.printTo(message, radio.getMaxMessageLength());

  return send(message, strlen(message));
}

uint8_t* LinkedIoTPushSensor::getMessageBuffer() {
  if (messageBuffer == 0) {
    messageBuffer = new uint8_t[radio.getMaxMessageLength()];
  }

  return messageBuffer;
}
