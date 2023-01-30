#define COUNT_CHANNELS 4
struct {
  uint8_t timers_count = 16 ;
  uint8_t mode[COUNT_CHANNELS] = {0, 0, 0, 0}; 
} prefs;
/* Timer [4bite]
 * Channel[0..31] - timer:
 *  channel = 0..31
 *  pos - on/off
 *  val - time (minutes)/ other[0..65535]
 */
struct Timer {
  uint8_t channel;
  uint8_t pos;
  uint16_t val;
};
struct Data {
  uint8_t channel = 0;
  uint16_t val = 0;
};

#define MAX_COUNT_TIMERS 16
Timer timers[MAX_COUNT_TIMERS];
#define MAX_COUNT_DATA 16
Data data[MAX_COUNT_DATA];

#define ADDR_INIT 0
#define ADDR_PREFS 1
#define ADDR_TIMERS (((size_t)(&(prefs)+1)-(size_t)(&(prefs)))+1)
#define ADDR_DATA (ADDR_TIMERS+((size_t)(&(timers)+1)-(size_t)(&(timers))))

void memory_commit() {
  EEPROM.put(ADDR_PREFS, prefs);
  EEPROM.put(ADDR_TIMERS, timers);
  EEPROM.put(ADDR_DATA, data);
}
void memory_prefs_commit() { EEPROM.put(ADDR_PREFS, prefs); }
void memory_timers_commit() { EEPROM.put(ADDR_TIMERS, timers); }
void memory_data_commit() {  EEPROM.put(ADDR_DATA, data); }

void memory_reset() { EEPROM.write(ADDR_INIT, 254); }

void memory_begin() {
  if (EEPROM.read(ADDR_INIT) != INIT_KEY) {
    EEPROM.write(ADDR_INIT, INIT_KEY);
    // on-off default timer to rele0
    prefs.mode[0] = 0;
    timers[0] = Timer {0, 0, TIME(16,30)};
    timers[1] = Timer {1, 0, TIME(16,35)};
    timers[2] = Timer {2, 0, TIME(16,40)};
    timers[3] = Timer {3, 0, TIME(16,45)};
    timers[4] = Timer {0, 1, TIME(16,50)};
    timers[5] = Timer {1, 1, TIME(16,55)};
    timers[6] = Timer {2, 1, TIME(17,0)};
    timers[7] = Timer {3, 1, TIME(17,5)};
    timers[8] = Timer {0, 0, TIME(17,10)};
    timers[9] = Timer {1, 0, TIME(17,15)};
    timers[10] = Timer {2, 0, TIME(17,20)};
    timers[11] = Timer {3, 0, TIME(17,25)};
    timers[12] = Timer {0, 1, TIME(17,30)};
    timers[13] = Timer {1, 1, TIME(17,35)};
    timers[14] = Timer {2, 1, TIME(17,40)};
    timers[15] = Timer {3, 1, TIME(17,45)};
    // reset
    EEPROM.put(ADDR_PREFS, prefs);
    EEPROM.put(ADDR_TIMERS, timers);
    EEPROM.put(ADDR_DATA, data);
  }
  EEPROM.get(ADDR_PREFS, prefs);
  EEPROM.get(ADDR_TIMERS, timers);
  EEPROM.get(ADDR_TIMERS, data);
  #ifdef DEBUG_ENABLE
  d("ADDR_INIT=") D(ADDR_INIT)
  d("ADDR_PREFS=") D(ADDR_PREFS)
  d("prefs.timers_count=") D(prefs.timers_count)
  d("prefs.mode=") d(prefs.mode[0]) d(' ') d(prefs.mode[1]) d(' ') d(prefs.mode[2]) d(' ') d(prefs.mode[3]) D("")
  d("ADDR_TIMERS=") D(ADDR_TIMERS)
  D("timers[i]= channel pos val")
  for (int i=0; i<MAX_COUNT_TIMERS; i++) {
    d("timers[") d(i) d("]= ") d(timers[i].channel) d(' ') d(timers[i].pos) d(' ') d(timers[i].val) D("")
  }
  d("ADDR_DATA=") D(ADDR_DATA)
  for (int i=0; i<MAX_COUNT_DATA; i++) {
    d("data[") d(i) d("]= ") d(data[i].channel) d(' ') d(data[i].val) D("")
  }
  #endif
}
