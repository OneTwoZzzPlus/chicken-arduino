//uint16_t myInt = buf[3] << 8 | buf[4];  // shift one byte by 8 and OR the two

char key[KEY_LENGTH];

#define BYTE_SIZE_SLOT 16
#pragma pack(push,1)
struct Slot {
  bool enable;        // ON/OFF the slot
  byte mode;          // Work mode ()
  byte channel_in;    // Sensor channel
  byte channel_out;   // Device channel
  int32_t border_on;  // Sensor border ON
  int32_t border_off; // Sensor border OFF
  int16_t value_on;   // Device var ON
  int16_t value_off;  // Device var OFF
};
#pragma pack(pop)
byte null_slot[BYTE_SIZE_SLOT] = {1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

Slot slot[COUNT_SLOTS];

#define ADDR_INIT 0
#define ADDR_KEY 1
#define ADDR_KEY_END ADDR_KEY+KEY_LENGTH
#define ADDR_SLOT 16
#define ADDR_SLOT_END COUNT_SLOTS*BYTE_SIZE_SLOT+ADDR_SLOT+1

#if ADDR_KEY_END>ADDR_SLOT
#error "Too much key!"
#endif
#if ADDR_SLOT_END>1024
#error "Too much slots!"
#endif

#define GET_SLOT(i) BYTE_SIZE_SLOT*i+ADDR_SLOT

void setup_memory() {

  // FIRST START
  if (EEPROM[ADDR_INIT] != INIT_BYTE) {
    EEPROM[ADDR_INIT] = INIT_BYTE;
    EEPROM.put(ADDR_KEY, "key1234567");
    for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
      EEPROM.put(GET_SLOT(i), null_slot);
    }
  }

  // READ
  EEPROM.get(ADDR_KEY, key);
  for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
    EEPROM.get(GET_SLOT(i), slot[count_slot++]);
  }

#ifdef DEBUG_MEMORY
  Serial.println("\nMEMORY SETUP");
  Serial.println("INIT = " + String(EEPROM[ADDR_INIT]));
  Serial.println("KEY = " + String(key));
  Serial.println("Active slots = " + String(count_slot));
  for (uint16_t i = 0; i < COUNT_SLOTS; i++) {
    Slot d_slot;
    EEPROM.get(GET_SLOT(i), d_slot);
    Serial.println("\tSlot " + String(i));
    Serial.println("slot[" + String(i) + "].enable = " + String(d_slot.enable));
    Serial.println("slot[" + String(i) + "].mode = " + String(d_slot.mode));
    Serial.println("slot[" + String(i) + "].channel_in = " + String(d_slot.channel_in));
    Serial.println("slot[" + String(i) + "].channel_out = " + String(d_slot.channel_out));
  }
#endif
}

void edit_slot(int32_t n[10]) {
  slot[n[0]].enable = n[1];
  slot[n[0]].mode = n[2];
  slot[n[0]].channel_in = n[3];
  slot[n[0]].channel_out = n[4];
  slot[n[0]].border_on = n[5];
  slot[n[0]].border_off = n[6];
  slot[n[0]].value_on = n[7];
  slot[n[0]].value_off = n[8];
  EEPROM.put(GET_SLOT(n[0]), slot[n[0]]);
  get_slot(n[0]);
}
