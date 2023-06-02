#include <EEPROM.h>
#include "painter.h"

#define COUNT_SLOTS 10
#define KEY_LENGTH 10
#define INIT_BYTE 'i'

#define VERSION "0.1"

#define DEBUG
#define DEBUG_MEMORY

#ifdef DEBUG
#define D(x) Serial.println(x);
#else
#define D(x)
#endif
