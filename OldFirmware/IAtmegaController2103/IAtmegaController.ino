#include <EEPROM.h>
#include <GyverBME280.h>
#include <microDS3231.h>
/**************************************/
#define VERSION "v0.0"
// Смена ключа [0-253] - сброс EEPROM
#define INIT_KEY 3
// ! Закоментировать при релизе:
#define DEBUG_ENABLE 
/*MACRO********************************/
#define TIME(h,m) ((60*h)+m)
#define RTIME (rtc.getMinutes()+60*rtc.getHours())
uint16_t rtime;
//#define RTIME ((BUILD_HOUR*60)+BUILD_MIN)
/*I2C**********************************/
bool isbme, isrtc;
GyverBME280 bme;
MicroDS3231 rtc;
const struct{
  byte RTC = 0x68;
  byte BME = 0x76;
} I2C_BUSS;
/*PIN**********************************/
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
/*DEBUG********************************/
#ifdef DEBUG_ENABLE
#define DEBUG_BEGIN Serial.begin(115200);delay(500);Serial.flush();Serial.println("\nDEBUG ON");
#define D(x) Serial.println(x);
#define d(x) Serial.print(x);
#else
#define DEBUG_BEGIN
#define D(x)
#define d(x)
#endif
