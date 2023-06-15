/***************** DEBUG *****************/
#ifdef DEBUG
#define D(x) Serial.println(x);
#define d(x) Serial.print(x);
#else
#define D(x)
#define d(x)
#endif

/***************** ANSWER ****************/
#define send(x) Serial.println(x)

// CODE ANSWER
#define SEND_OK send("ATM200")
#define SEND_BAD_REQUEST send("ATM400")
#define SEND_UNAUTHORIZED send("ATM401")
#define SEND_NOT_ALLOWED send("ATM405")
#define SEND_LOCKED send("ATM423")
#define SEND_NOT_IMPLEMENTED send("ATM501")


/***************** JSON ******************/
bool json_first = true;
String json = "{";

#define CLEAR_JSON {json="{";json_first=true;}
#define SEND_JSON send(json+"}")
#define J(key,value) {if(json_first){json+="\"";json_first=false;}else{json+=",\"";}json+=key;json+="\":\"";json+=value;json+="\"";}
