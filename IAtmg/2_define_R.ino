/**************** CHANNEL ****************/
#pragma pack(push,1)
struct Channel {
  byte channel;
  byte type;
  byte pin;
  byte pin2;
};
#pragma pack(pop)

// DEVICE
#define COUNT_DEVICE_TYPE 3
String device_name[COUNT_DEVICE_TYPE] = 
{"main", "relay", "triak"};

#define COUNT_DEVICES 6
Channel device[COUNT_DEVICES] = {
  Channel{0, 2, 4, 2},
  Channel{1, 2, 5, 2},
  Channel{2, 1, 6, 255},
  Channel{3, 1, 7, 255},
  Channel{4, 1, 8, 255},
  Channel{5, 1, 9, 255},
};

// SENSOR
#define COUNT_SENSOR_TYPE 3
String sensor_name[COUNT_SENSOR_TYPE] = 
{"mtimer", "stimer", "temp"};

#define COUNT_SENSORS 3
Channel sensor[COUNT_SENSORS] = {
  Channel{0, 0, 255, 255},
  Channel{1, 1, 255, 255},
  Channel{2, 2, A4, A5},
};


/***************** SLOT *****************/
#pragma pack(push,1)
struct Slot {
  bool enable;        // ON/OFF the slot
  byte mode;          // Work mode ()
  byte channel_sensor;    // Sensor channel
  byte channel_device;   // Device channel
  int32_t sensor_on;  // Sensor border ON
  int32_t sensor_off; // Sensor border OFF
  int16_t device_on;   // Device var ON
  int16_t device_off;  // Device var OFF
};
#pragma pack(pop)
Slot default_slot = {1, 0, 0, 0, 0, 0, 0, 0};

#define COUNT_SLOTS 10
#define BYTE_SIZE_SLOT 16

/***************** KEY *****************/
#define KEY_LENGTH 10
