#define send(x) Serial.println(x)

// CODE ANSWER
#define SEND_OK send("ATM200")
#define SEND_BAD_REQUEST send("ATM400")
#define SEND_UNAUTHORIZED send("ATM401")
#define SEND_NOT_ALLOWED send("ATM405")
#define SEND_LOCKED send("ATM423")
#define SEND_NOT_IMPLEMENTED send("ATM501")


// JSON class translate to macro
/*#define JSON_S "{"
  #define JSON_E "}"
  #define JSON_BEGIN ",\""
  #define JSON_BORDER "\":\""
  #define JSON_END "\""*/

bool json_first = true;
String json = "{";

#define CLEAR_JSON {json="{";json_first=true;}
#define SEND_JSON send(json+"}")
#define J(key,value) {if(json_first){json+="\"";json_first=false;}else{json+=",\"";}json+=key;json+="\":\"";json+=value;json+="\"";}


// Create slot's JSON
void get_slots_list() {
  for (uint16_t i = 0; i < count_slot; i++) {
    J(slot[i].channel_out, slot[i].mode);
  }
}

void get_slot(int n) {
  J("index", n);
  J("enable", slot[n].enable);
  J("mode", slot[n].mode);
  J("channel_in", slot[n].channel_in);
  J("channel_out", slot[n].channel_out);
  J("border_on", slot[n].border_on);
  J("border_off", slot[n].border_off);
  J("value_on", slot[n].value_on);
  J("value_off", slot[n].value_off);
}
