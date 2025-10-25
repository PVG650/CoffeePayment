#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <elapsedMillis.h>

#define TFT_CS 15
#define TFT_DC 16
#define TFT_RST 7
#define TFT_SCK 12
#define TFT_MOSI 11
#define RFID_CS 4
elapsedMillis timerRFID;

SPIClass spiBus(FSPI);
MFRC522DriverPinSimple rfid_cs_pin(RFID_CS);
MFRC522DriverSPI driver{rfid_cs_pin, spiBus};
MFRC522 mfrc522{ driver };

bool cardPresent = 0;
uint64_t uidDec = 0;




Adafruit_ST7735 tft = Adafruit_ST7735(&spiBus, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  spiBus.begin();

  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);  // deselect
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);  // Querformat: 160x128
  tft.fillScreen(ST77XX_BLACK);

  // Header: Nutzer-Nr und Saldo
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.print("SALDO NUTZER-NR 0:");
  tft.setTextSize(2);
  tft.setCursor(5, 20);
  tft.print("6,50 EUR");


  // Menüeinträge
  tft.setTextSize(3);
  tft.setCursor(30, 60);
  tft.print("KAFFEE");
  tft.setCursor(30, 95);
  tft.print("LADEN");

  drawArrow(30, 60);  // X/Y von dem Cursor des Texts

  pinMode(RFID_CS, OUTPUT);
  digitalWrite(RFID_CS, HIGH);  // deselect
  mfrc522.PCD_Init();
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

void drawArrow(int textX, int textY) {
  int arrowTipX = textX - 10;
  int arrowTipY = textY + 12;
  int size = 8;

  tft.fillTriangle(
    arrowTipX, arrowTipY,
    arrowTipX - size, arrowTipY - size,
    arrowTipX - size, arrowTipY + size,
    ST77XX_RED);
}
