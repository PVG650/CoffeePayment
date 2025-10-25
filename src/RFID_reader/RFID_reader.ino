#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <elapsedMillis.h>

elapsedMillis timerRFID;

MFRC522DriverPinSimple ss_pin(4);
MFRC522DriverSPI driver{ ss_pin };
MFRC522 mfrc522{ driver };

bool cardPresent = 0;
uint64_t uidDec = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("huhu");
  mfrc522.PCD_Init();
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);
  Serial.println("Scan to see UID");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    uidDec = 0;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidDec = (uidDec << 8) | mfrc522.uid.uidByte[i];
    }
    timerRFID = 0;
    cardPresent = 1;
  }
  if (timerRFID > 500) {
    cardPresent = 0;
  }
  Serial.println(uidDec);
  Serial.println(cardPresent);
  delay(200);
}
