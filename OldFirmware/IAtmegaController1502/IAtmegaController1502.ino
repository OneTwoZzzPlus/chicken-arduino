#include <EEPROM.h>
#include <GyverBME280.h>
#include <microDS3231.h>
/**************************************/
#define VERSION "v0.0"
// Смена ключа - сброс EEPROM
#define INIT_KEY 7     // 0-253
// Закоментировать при релизе!
//#define DEBUG_ENABLE 
/**************************************/
#define TIME(h,m) ((60*h)+m)
#define RTIME (rtc.getMinutes()+60*rtc.getHours())
//#define COMPILETIME ((BUILD_HOUR*60)+BUILD_MIN)
/**************************************/
bool isbme, isrtc;
GyverBME280 bme;
MicroDS3231 rtc;
/**************************************/

const struct {
  byte RELE0 = 7;
  byte RELE1 = 8;
  byte RELE2 = A2;
  byte RELE3 = A3;
  //byte RX = 0;
  //byte TX = 1;
  //byte SDA = A4;
  //byte SCL = A5;
} PIN;

const struct{
  byte RTC = 0x68;
  byte BME = 0x76;
} I2C_BUSS;
