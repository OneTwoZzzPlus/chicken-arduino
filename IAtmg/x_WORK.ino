#include <microDS3231.h>
MicroDS3231 rtc;

#define RTC_SEC rtc.getSeconds()+rtc.getMinutes()*60+rtc.getHours()*3600

void relay_time(uint8_t i) {
  uint32_t rtc_sec = RTC_SEC;
  byte pin = device[slot[i].channel_device].pin;
  switch (slot[i].mode) {
    case MODE_EVENT:
      if (rtc_sec >= slot[i].sensor_on && rtc_sec < slot[i].sensor_on+slot[i].sensor_off) digitalWrite(pin, slot[i].device_on);
      else digitalWrite(pin, slot[i].device_off);
      break;
    case MODE_BORDER:
      if (rtc_sec >= slot[i].sensor_on && rtc_sec < slot[i].sensor_off) digitalWrite(pin, slot[i].device_on);
      else digitalWrite(pin, slot[i].device_off);
      break;
  }
  Serial.println(rtc.getTimeString());
}
void relay_date(uint8_t i) {
  Serial.println(rtc.getDateString());
}
void relay_temp(uint8_t i) {
  Serial.println(rtc.getTemperatureFloat());
}
void triak_time(uint8_t i) {
  Serial.println(rtc.getTimeString());
}
void triak_date(uint8_t i) {
  Serial.println(rtc.getDateString());
}
void triak_temp(uint8_t i) {
  Serial.println(rtc.getTemperatureFloat());
}
