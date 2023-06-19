class AtmegaSerial : public SoftwareSerial {
  private:
    uint16_t request_timeout;
    String request_string = "";
  public:
    using SoftwareSerial::SoftwareSerial;
    void begin(uint16_t speed_ = 9600, uint16_t request_timeout_ = 2000) {
      SoftwareSerial::begin(speed_);
      request_timeout = request_timeout_;
      request_string.reserve(32);
    }

    void send(String s) {
      println(s);
    }
    void arg(String s) {
      s+="=";
      print(s);
    }
    void end() {
      println("");
    }
    String wait() {
      int breaker = 0;
      while (!available()) {
        delay(1);
        breaker++;
        if (breaker >= request_timeout) {
          Df("TIMEOUT EXCEEDED!")
          return F("ATM405 (TIMEOUT)");
        }
      }
      String s = readStringUntil('\n');
      df("WAIT: ") D(s)
      return s;
    }
    
    // OLD REQUEST
    void new_request(String s) {
      request_string = s;
      request_string += "\n";
    }
    void arg_request(String s) {
      request_string += s;
      request_string += "<";
    }
    void arg_request(int s) {
      request_string += s;
      request_string += "<";
    }
    String request() {
      if (request_string == "") return "";
      print(request_string);
      df("WMS: ")  D(request_string)  
      request_string = "";

      int breaker = 0;
      while (!available()) {
        delay(1);
        breaker++;
        if (breaker >= request_timeout) {
          return "";
          Df("TIMEOUT EXCEEDED!")
        }
      }

      String s = readStringUntil('\\');
      df("ATM: ") D(s)
      return s;
    }
    void NArequest() {
      if (request_string == "") return;
      print(request_string);
      df("WMS: ")  D(request_string)  
      request_string = "";
    }

    void tick () {
      if (Serial.available()) { // from PC
          send(Serial.readString());
        }
      if (available()) { // from ATMEGA
        String s = readStringUntil('\n');
        df("ATM: ") D(s)        
      }
    }

};

AtmegaSerial atmega(PIN.ARX, PIN.ATX);
