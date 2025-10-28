#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <elapsedMillis.h>
#include <DatabaseOnSD.h>  //https://github.com/divinofire/DatabaseOnSD
#include <SD.h>
#include <ESP32RotaryEncoder.h>  //https://github.com/MaffooClock/ESP32RotaryEncoder

#define SD_CS 5

MyTable testTable("keytags.csv");  //this will create or open a table named test.csv in the root of the SD card

#define TFT_CS 15
#define TFT_DC 16
#define TFT_RST 7
#define RFID_CS 4
elapsedMillis timerRFID;

const uint8_t DI_ENCODER_A = 41;
const uint8_t DI_ENCODER_B = 40;
const int8_t DI_ENCODER_SW = 42;
RotaryEncoder rotaryEncoder(DI_ENCODER_A, DI_ENCODER_B, DI_ENCODER_SW);

SPIClass spiBus(HSPI);
MFRC522DriverPinSimple rfid_cs_pin(RFID_CS);
MFRC522DriverSPI driver{ rfid_cs_pin, spiBus };
MFRC522 mfrc522{ driver };

bool cardPresent = 0;
uint64_t uidDec = 0;




Adafruit_ST7735 tft = Adafruit_ST7735(&spiBus, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  spiBus.begin(36, 37, 35);  // Display und RFID, erster SPI
  SPI.begin();               // nutzt GPIO 12=SCK, 13=MISO, 11=MOSI für SD Karte (zweiter SPI)

  // SD initialisieren
  if (!SD.begin(SD_CS)) {
    Serial.println("SD-Karte konnte nicht initialisiert werden");
    while (true) delay(1000);
  }

  rotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);
  rotaryEncoder.setBoundaries(0, 50, false);
  rotaryEncoder.onTurned(&knobCallback);
  rotaryEncoder.onPressed(&buttonCallback);
  rotaryEncoder.begin();

  Serial.println("SD-Karte erkannt");

  testTable.printSDstatus();  //[optional] print the initialization status of SD card
  testTable.emptyTable();     //[optional] empty table content (make sure to call begin(rowN, colN) after emptying a table) // you could always add more rows.
  testTable.begin(3, 2);      //[optional] initialize an empty table with 3 rows and 2 columns (has no effect if table is not empty)
                              //NOTE: there is no need to call begin() if table in NOT empty
  //write table content
  Serial.println("writing to table...");
  testTable.writeCell(0, 0, "NAME");
  testTable.writeCell(0, 1, "AGE");
  testTable.writeCell(1, 0, "Divino");
  testTable.writeCell(1, 1, "23");
  testTable.writeCell(2, 0, "Fire");
  testTable.writeCell(2, 1, "22");
  Serial.println("finished writing!");
  //the max size of each cell is 20 characters for the sake of memory,
  //the max cell size can be changed in header file [but I do not recommend it]

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

  Serial.println(testTable.readCell(2, 0));

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

void knobCallback(long value) {
  static long scaledValue = 0;
  scaledValue = value * 5;
  Serial.println(scaledValue);
}

void buttonCallback(unsigned long duration) {
  Serial.println(duration);
}
