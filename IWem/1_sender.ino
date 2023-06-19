/***************** DEBUG *****************/
#ifdef DEBUG
bool debug_state = false;
#define DEBUG_BEGIN Serial.begin(115200);/*delay(100);Serial.flush();*/Serial.println(F("\nDEBUG ON"));
#define Df(x) Serial.println(F(x));
#define D(x) Serial.println(x);
#define df(x) Serial.print(F(x));
#define d(x) Serial.print(x);
#else
#define DEBUG_BEGIN
#define Df(x)
#define D(x)
#define df(x)
#define d(x)
#endif

/***************** ANSWER ****************/
#define ANSWER(x) server.send(200,"text/plain",x)

// CODE ANSWER
#define SEND_OK server.send(200,"text/plain","WEM200")
#define SEND_ACCEPTED server.send(200,"text/plain","WEM202")
#define SEND_BAD_REQUEST server.send(200,"text/plain","WEM400")
#define SEND_UNAUTHORIZED server.send(401,"text/plain","WEM401")
#define SEND_NOT_ALLOWED server.send(405,"text/plain","WEM405")
#define SEND_REQUEST_TIMEOUT server.send(408,"text/plain","WEM408")
#define SEND_LOCKED server.send(423,"text/plain","WEM423")
#define SEND_NOT_IMPLEMENTED server.send(200,"text/plain","WEM501")


/***************** JSON ******************/
bool json_first = true;
String json = "{";

#define CLEAR_JSON {json="{";json_first=true;}
#define SEND_JSON ANSWER(json+"}")
#define J(key,value) {if(json_first){json+="\"";json_first=false;}else{json+=",\"";}json+=key;json+="\":\"";json+=value;json+="\"";}


/***************** INT ******************/
bool checkInt(String s, int down, int up) {
  if (s=="") return false;
  int n = 0;
  for (int i = 0; i < s.length(); i++) {
    if ('0' <= s[i] && s[i] <= '9') n = (10 * n) + (s[i] - '0');
    else {
      return false;
    }
  }
  return (down <= n && n <= up);
  }
