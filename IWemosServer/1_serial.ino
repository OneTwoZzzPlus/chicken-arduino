#include <SoftwareSerial.h>
class AtmegaSerial : public SoftwareSerial {
  private:
    uint16_t request_timeout;
    String request_string = "";
  public:
    using SoftwareSerial::SoftwareSerial;
    void begin(uint16_t speed_ = 9600, uint16_t request_timeout_ = 5000) {
      SoftwareSerial::begin(speed_);
      request_timeout = request_timeout_;
      request_string.reserve(32);
    }

    // REQUEST
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
      DEBUGf(F("WMS: "))  DEBUG(request_string)  
      request_string = "";

      int breaker = 0;
      while (!available()) {
        delay(1);
        breaker++;
        if (breaker >= request_timeout) {
          return "";
          DEBUG(F("TIMEOUT EXCEEDED!"))
        }
      }

      String s = readStringUntil('\\');
      DEBUGf(F("ATM: ")) DEBUG(s)
      return s;
    }
    void NArequest() {
      if (request_string == "") return;
      print(request_string);
      DEBUGf(F("WMS: "))  DEBUG(request_string)  
      request_string = "";
    }

    void tick () {
      if (Serial.available()) { // from PC
          new_request(Serial.readString());
          NArequest();
        }
      if (available()) { // from ATMEGA
        String s = readStringUntil('\\');
        DEBUGf(F("ATM: ")) DEBUG(s)        
      }
    }

};

AtmegaSerial atmega(PIN.ARX, PIN.ATX);
