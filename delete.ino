#include "Adafruit_FONA.h"

// Define RX and TX pins for FONA communication
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

#include <SoftwareSerial.h>
SoftwareSerial fonaSS(FONA_TX, FONA_RX);
Adafruit_FONA fona(FONA_RST);

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  Serial.println(F("FONA SMS Delete Test"));

  // Begin communication with the FONA module
  fonaSS.begin(4800);
  if (!fona.begin(fonaSS)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is ready"));

  // Delete all SMS messages
  if (deleteAllSMS()) {
    Serial.println(F("All SMS messages deleted successfully"));
  } else {
    Serial.println(F("Failed to delete SMS messages"));
  }
}

void loop() {
  // Empty loop since the SMS deletion happens in setup
}

// Function to delete all SMS messages
bool deleteAllSMS() {
  Serial.println(F("Deleting all SMS messages..."));
  
  // Send AT command to delete all messages from memory
  // The command is `AT+CMGD=1,4`
  if (fona.sendCheckReply(F("AT+CMGD=1,4"), F("OK"), 5000)) {
    return true; // Deletion successful
  } else {
    Serial.println(F("Error deleting SMS messages"));
    return false; // Deletion failed
  }
}
