#ifdef DEBUG_ENABLE
#define DEBUG_BEGIN Serial.begin(115200);delay(500);Serial.flush();send("\nDEBUG ON");
#define D(x) send(x);
#define d(x) send(x);
#else
#define DEBUG_BEGIN
#define D(x)
#define d(x)
#endif
