#ifdef DEBUG_ENABLE
#define DEBUG_BEGIN Serial.begin(115200);delay(500);Serial.flush();Serial.println("\nDEBUG ON");
#define D(x) Serial.println(x);
#define d(x) Serial.print(x);
#else
#define DEBUG_BEGIN
#define D(x)
#define d(x)
#endif
