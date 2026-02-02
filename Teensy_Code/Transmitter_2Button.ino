#include <SPI.h>
#include <RH_RF69.h>

#define RF69_FREQ 915.0

// Teensy 4.0 ↔ RFM69HCW
#define RFM69_CS   10
#define RFM69_INT   8
#define RFM69_RST   9
#define LED         13

// Button pins (to GND)
#define BUTTON_0  3
#define BUTTON_1  4

RH_RF69 rf69(RFM69_CS, RFM69_INT);

// Button state tracking
bool lastButton0State = HIGH;
bool lastButton1State = HIGH;

// Timers for auto-deactivate
bool solenoid0Active = false;
bool solenoid1Active = false;

unsigned long solenoid0Timer = 0;
unsigned long solenoid1Timer = 0;

const unsigned long DEACTIVATE_DELAY = 3000; // 3 seconds

void sendMessage(const char *msg) {
  rf69.send((uint8_t *)msg, strlen(msg));
  rf69.waitPacketSent();
  Serial.println(msg);

  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);

  // Reset radio
  digitalWrite(RFM69_RST, LOW);
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 init failed");
    while (1);
  }

  rf69.setFrequency(RF69_FREQ);
  rf69.setTxPower(20, true);

  uint8_t key[] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
  rf69.setEncryptionKey(key);

  Serial.println("RFM69 Transmitter Ready (2 Buttons)");
}

void loop() {
  unsigned long now = millis();

  bool button0State = digitalRead(BUTTON_0);
  bool button1State = digitalRead(BUTTON_1);

  // ===== BUTTON 0 =====
  if (lastButton0State == HIGH && button0State == LOW) {
    sendMessage("ACTIVATE_0");
    solenoid0Active = true;
    solenoid0Timer = now;
  }

  if (solenoid0Active && (now - solenoid0Timer >= DEACTIVATE_DELAY)) {
    sendMessage("DEACTIVATE_0");
    solenoid0Active = false;
  }

  // ===== BUTTON 1 =====
  if (lastButton1State == HIGH && button1State == LOW) {
    sendMessage("ACTIVATE_1");
    solenoid1Active = true;
    solenoid1Timer = now;
  }

  if (solenoid1Active && (now - solenoid1Timer >= DEACTIVATE_DELAY)) {
    sendMessage("DEACTIVATE_1");
    solenoid1Active = false;
  }

  lastButton0State = button0State;
  lastButton1State = button1State;

  delay(20); // debounce
}
