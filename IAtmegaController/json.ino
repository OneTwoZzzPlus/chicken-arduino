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
    String get() {
      return json+e;
    }
};
