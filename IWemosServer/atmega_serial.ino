#include <SoftwareSerial.h>
class AtmegaSerial : public SoftwareSerial {
  private:
    uint16_t request_time;
    uint16_t message_max = 200;
    String message = "";
  public:
    using SoftwareSerial::SoftwareSerial;
    void begin(uint16_t speed_ = 9600, uint16_t request_time_ = 5000) {
      SoftwareSerial::begin(speed_);
      request_time = request_time_;
      message.reserve(message_max);
    }
    void appendMessage(String s) {
      if (message.length() + s.length() <= message_max) message += s;
      else message = s;
    }
    String delMessage() { String s = message; message = ""; return s; }
    String putMessage() { return message; }
    bool messageIsEmpty() { return message.equals(""); }
    void tick () {
      if (available()) {
        String s = readStringUntil('\\');
        DEBUGf("Data from atmega: ")
        DEBUG(s)
        appendMessage(s);
        appendMessage("\n");
      }
    }
    void send_command(String s) { 
      s.concat('\\');
      print(s); 
    }
    String request(String s) {
      send_command(s);
      int breaker = 0;
      while (!available() and breaker <= 5000) { delay(1); breaker++;}
      if (breaker == 5000) return "";
      s = readStringUntil('\\');
      DEBUGf("Answer from atmega: ")
      DEBUG(s)
      return s;
    }
};
AtmegaSerial atmega(PIN.ARX, PIN.ATX);
