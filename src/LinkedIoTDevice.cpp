#include "LinkedIoTDevice.h"
#include <SmallHttp.h>
#include <WS2812.h>

#include <ArduinoJson.h>

LinkedIoTDevice::LinkedIoTDevice(LinkedIoTRadio& radio) : radio(radio) {
  memset(id, 0, sizeof(id));
  statusLed = new WS2812(1);
}

LinkedIoTDevice::~LinkedIoTDevice() {
}

bool LinkedIoTDevice::begin() {
  pinMode(setupButtonPin, INPUT_PULLUP);

  pinMode(statusLedPinPower, OUTPUT);  
  statusLed->setOutput(statusLedPinData);

  if(!radio.begin()) {
    return false;
  }

  return true;
}

bool LinkedIoTDevice::loop() {
  if (digitalRead(setupButtonPin) == LOW) {
    if (setupButtonStart == 0) {
      Serial.println("setup pressed");
      setupButtonStart = millis();
      setStatusLed(0x404000);
    } else {
      uint32_t time = millis() - setupButtonStart;

      if (time > 3000) {
        setStatusLed(0x000040);
      }
    }
  } else {
    if (setupButtonStart != 0) {
      uint32_t time = millis() - setupButtonStart;

      Serial.print("setup released: ");
      Serial.println(time);

      if (time > 3000) {
        if (setupMode == 0) {
          startSetup();
        } else {
          endSetup();
        }
      }

      setupButtonStart = 0;
    }
  }
  
  if (setupMode != 0) {
    setupLoop();
    
    return false;
  } else {
    return true;
  }
}

void LinkedIoTDevice::startSetup() {
  if (setupMode != 0) {
    return;
  }
  
  Serial.println("start setup menu");
  setStatusLed(0x000040);

  setupMode = 1;
  setupConnection = new HttpConnection(&Serial, 300);  
}

void LinkedIoTDevice::endSetup() {
  Serial.println("end setup menu");
  setStatusLed(0);

  setupMode = 0;
  delete setupConnection;
}

void LinkedIoTDevice::setupLoop() {
  if (setupConnection->handle()) {
    HttpRequest& req = setupConnection->request;
    HttpResponse& res = setupConnection->response;

    if (req.method == "GET" && req.target == "/") {
      StaticJsonBuffer<120> buffer;

      JsonObject& json = buffer.createObject();
      json["id"] = id;
      json["radio"] = radio.getConfig(buffer);

      res.setHeader("content-type", "application/json");
      res.setHeader("content-length", String(json.measureLength()));
      //res.setHeader("link", F("<context>; rel=\"http://www.w3.org/ns/json-ld#context\"; type=\"application/ld+json\""));
      res.sendHeaders();
      json.printTo(res.connection);
    } else if (req.method == "PUT" && req.target == "/") {
      //res.statusCode = 201;

      StaticJsonBuffer<120> buffer;

      JsonObject& json = buffer.parseObject(req.connection);
      String stringId = json["id"].as<String>();
      strncpy(id, stringId.c_str(), sizeof(id)); 

      if (!radio.setConfig(json["radio"])) {
        res.statusCode = 500;
      }

      res.sendHeaders();

      //res.send(id, 36);
    }

    setupConnection->releaseRequest();
  }
}

void LinkedIoTDevice::sleep(uint32_t time) {
  uint32_t left = time;
  
  while (left > 60) {
    delay(60);
    loop();
    left -= 60;
  }

  delay(left);
}

bool LinkedIoTDevice::send(uint8_t* buf, uint8_t len, uint8_t address) {
  return radio.send(buf, len, address);
}

void LinkedIoTDevice::setStatusLed(uint32_t color) {
  if (color == 0) {
    digitalWrite(statusLedPinPower, LOW);
  } else {    
    cRGB rgb;

    rgb.r = color >> 16;
    rgb.g = (color >> 8) & 0xff;
    rgb.b = color & 0xff;

    digitalWrite(statusLedPinPower, HIGH);
    delay(2);
    statusLed->set_crgb_at(0, rgb);
    statusLed->sync();
  }
}
