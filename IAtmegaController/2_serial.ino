void send(String s) {
  s.concat('\\');
  digitalWrite(3, !digitalRead(3));
  Serial.print(s);
}
void send(int s) {
  Serial.print(s);
  digitalWrite(3, !digitalRead(3));
  Serial.print('\\');
}

class JSONobject {
  private:
    String json = "{";
    const String s = "{";
    const String e = "}";
    const String begin = ",\"";
    const String border = "\":\"";
    const String end = "\"";
    bool isFirst = true;
  public:
    void clear() {
      json = s;
      isFirst = true;
    }
    void set(String s) {
      json = s;
    }
    void put(String key, String value) {
      if (isFirst) { json += end; isFirst = false; }
      else json += begin;
      json += key;
      json += border;
      json += value;
      json += end;
    }
    void put(String key, int value) {
      if (isFirst) { json += end; isFirst = false; }
      else json += begin;
      json += key;
      json += border;
      json += value;
      json += end;
    }
    void put(String key, float value) {
      if (isFirst) { json += end; isFirst = false; }
      else json += begin;
      json += key;
      json += border;
      json += value;
      json += end;
    }
    String get() {
      return json+e;
    }
};
JSONobject json;
