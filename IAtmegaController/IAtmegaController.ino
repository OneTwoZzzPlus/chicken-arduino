#include <GyverBME280.h>
#include <microDS3231.h>

/**************************************/

const struct {
  //byte RX = 0;
  //byte TX = 1;
  //byte  = 2;
  //byte  = 3;
  //byte  = 4;
  //byte  = 5;
  //byte  = 6;
  //byte  = 7;
  //byte  = 8;
  //byte  = 9;
  //byte  = 10;
  //byte  = 11;
  //byte  = 12;
  //byte  = 13;
  //byte  = A0;
  //byte  = A1;
  //byte  = A2;
  //byte  = A3;
  //byte  = A4;
  //byte SDA = A4;
  //byte SCL = A5;
} PINS;

const struct{
  byte RTC = 0x68;
  byte BME = 0x76;
} I2C_BUSS;
