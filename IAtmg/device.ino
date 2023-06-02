#define COUNT_SENSORS 3
#define COUNT_DEVICES 6

#define COUNT_DEVICE_NAME 3
String device_name[COUNT_DEVICE_NAME] = {F("main"), F("relay"), F("triak")};
#define COUNT_SENSOR_NAME 3
String sensor_name[COUNT_SENSOR_NAME] = {F("mtimer"), F("stimer"), F("temp")};

#pragma pack(push,1)
struct Channel {
  byte channel;
  byte type;
  byte pin;
  byte pin2;
}
#pragma pack(pop)

Channel device[COUNT_DEVICES] = {
  Device{0, 2, 4, 2},
  Device{1, 2, 5, 2},
  Device{2, 1, 6, 255},
  Device{3, 1, 7, 255},
  Device{4, 1, 8, 255},
  Device{5, 1, 9, 255},
}

Channel sensor[COUNT_DEVICES] = {
  Device{0, 0, 255, 255},
  Device{1, 1, 255, 255},
  Device{2, 2, A4, A5},
}
