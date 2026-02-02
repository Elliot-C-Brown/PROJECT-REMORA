#include <Wire.h>
#include <SPI.h>
#include <RH_RF69.h>
#include "Adafruit_MCP23X17.h"

#define RF69_FREQ 915.0

// Teensy 4.0 ↔ RFM69HCW
#define RFM69_CS   10
#define RFM69_INT   8
#define RFM69_RST   9
#define LED         13

RH_RF69 rf69(RFM69_CS, RFM69_INT);
Adafruit_MCP23X17 solenoid;

// Number of solenoid channels used
#define NUM_SOLENOIDS 2

// Track solenoid states (optional but useful)
bool solenoidState[NUM_SOLENOIDS] = {false, false};

void activateSolenoid(uint8_t channel) {
  if (channel >= NUM_SOLENOIDS) return;

  solenoid.digitalWrite(channel, HIGH);
  solenoidState[channel] = true;

  Serial.print("Solenoid ");
  Serial.print(channel);
  Serial.println(" ACTIVATED");

  digitalWrite(LED, HIGH);
}

void deactivateSolenoid(uint8_t channel) {
  if (channel >= NUM_SOLENOIDS) return;

  solenoid.digitalWrite(channel, LOW);
  solenoidState[channel] = false;

  Serial.print("Solenoid ");
  Serial.print(channel);
  Serial.println(" DEACTIVATED");

  digitalWrite(LED, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);

  // Reset RFM69
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

  if (!solenoid.begin_I2C()) {
    Serial.println("MCP23X17 init failed!");
    while (1);
  }

  // Initialize solenoid pins
  for (uint8_t i = 0; i < NUM_SOLENOIDS; i++) {
    solenoid.pinMode(i, OUTPUT);
    solenoid.digitalWrite(i, LOW);
  }

  Serial.println("Receiver Ready (2 Solenoids)");
}

void loop() {
  if (rf69.available()) {3
  
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf69.recv(buf, &len)) {
      buf[len] = '\0';
      Serial.print("Received: ");
      Serial.println((char *)buf);

      // ----- SOLENOID 0 -----
      if (strcmp((char *)buf, "ACTIVATE_0") == 0) {
        activateSolenoid(0);
      }
      else if (strcmp((char *)buf, "DEACTIVATE_0") == 0) {
        deactivateSolenoid(0);
      }

      // ----- SOLENOID 1 -----
      else if (strcmp((char *)buf, "ACTIVATE_1") == 0) {
        activateSolenoid(1);
      }
      else if (strcmp((char *)buf, "DEACTIVATE_1") == 0) {
        deactivateSolenoid(1);
      }
    }
  }
}
