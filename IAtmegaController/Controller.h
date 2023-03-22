#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <GyverBME280.h>
#include <microDS3231.h>

class CCC {
  public:
    void setColor(byte color);
  private:
    byte _color;
};
extern CCC con;

void CCC::setColor(byte color) {
  _color = color;
}
