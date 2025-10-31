// CODE RUNS ON ESP32-S3 DEV KIT
// (C) PVG 2025

#include <elapsedMillis.h>  //https://github.com/pfeerick/elapsedMillis
#include <StateMachine.h>   //https://github.com/jrullan/StateMachine
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <DatabaseOnSD.h>  //https://github.com/divinofire/DatabaseOnSD
#include <SD.h>
#include <ESP32RotaryEncoder.h>  //https://github.com/MaffooClock/ESP32RotaryEncoder

// ------------------------- //

// General
bool selectionMenu = 0;
int lastSelection = -1;
bool restartRequested = false;
// Timer
elapsedMillis timerRFID;
elapsedMillis monitor;
// StateMachine
StateMachine machine = StateMachine();
State* S1 = machine.addState(&state1);  // Idle, bitte keytag auflegen
State* S2 = machine.addState(&state2);  // Modus auswählen
State* S3 = machine.addState(&state3);  // Bezug
State* S4 = machine.addState(&state4);  // Aufladen
State* S5 = machine.addState(&state5);  // Aufladen bestätigen
// SPI
SPIClass spiBus(HSPI);  // SPI 1 für RFID und Display
// Display
#define TFT_CS 15
#define TFT_DC 16
#define TFT_RST 7
Adafruit_ST7735 tft = Adafruit_ST7735(&spiBus, TFT_CS, TFT_DC, TFT_RST);
// SD Card
#define SD_CS 5
MyTable db("keytags.csv");
// RFID
#define RFID_CS 4
MFRC522DriverPinSimple rfid_cs_pin(RFID_CS);
MFRC522DriverSPI driver{ rfid_cs_pin, spiBus };
MFRC522 mfrc522{ driver };
bool cardPresent = 0;
uint64_t uidDec = 0;
// Encoder
long rawValue = 0;
long scaledValue = 0;
unsigned long button_duration;
const uint8_t DI_ENCODER_A = 41;
const uint8_t DI_ENCODER_B = 40;
const int8_t DI_ENCODER_SW = 42;
RotaryEncoder rotaryEncoder(DI_ENCODER_A, DI_ENCODER_B, DI_ENCODER_SW);

// ------------------------ //

void setup() {
  // Serial Monitor
  Serial.begin(115200);
  delay(100);
  Serial.println("Serial i.O.");
  spiBus.begin(36, 37, 35);  // Display and RFID, SPI 1
  SPI.begin();               // GPIO 12=SCK, 13=MISO, 11=MOSI for SD Card (SPI 2)
  // SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD-Karte konnte nicht initialisiert werden");
    while (true) delay(1000);
  }
  Serial.println("SD-Karte erkannt");
  // Rotary Encoder
  rotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);
  rotaryEncoder.setBoundaries(-1000, 1000, false);
  rotaryEncoder.onTurned(&knobCallback);
  rotaryEncoder.onPressed(&buttonCallback);
  rotaryEncoder.begin();
  // Database
  //testTable.printSDstatus();  //[optional] print the initialization status of SD card
  //testTable.emptyTable();     //[optional] empty table content (make sure to call begin(rowN, colN) after emptying a table) // you could always add more rows.
  db.begin(4, 1);  //[optional] initialize an empty table with 3 rows and 2 columns (has no effect if table is not empty)
  db.writeCell(0, 0, "ID");
  db.writeCell(1, 0, "NAME");
  db.writeCell(2, 0, "SALDO");
  db.writeCell(3, 0, "COUNTER");
  // Display
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);  // Querformat: 160x128
  tft.fillScreen(ST77XX_BLACK);
  // RFID
  mfrc522.PCD_Init();
  // State Machine
  S1->addTransition(&transitionS1S2, S2);  // Vom Idle zum Menü
  S2->addTransition(&transitionS2S3, S3);  // Vom Menü zum Bezug
  S2->addTransition(&transitionS2S4, S4);  // Vom Menü zum Laden
  S3->addTransition(&transitionS3S2, S2);  // Wenn Bezug abgeschlossen zurück zum Menü
  S4->addTransition(&transitionS4S5, S5);  // Vom Aufladen zum Bestätigen
  S5->addTransition(&transitionS5S2, S2);  // Vom Aufladen bestätigen zurück zum Menü
  // Transitionen von allen Zuständen zurück zu S1
  S2->addTransition(transitionS2S1, S1);
  S3->addTransition(transitionS3S1, S1);
  S4->addTransition(transitionS4S1, S1);
  S5->addTransition(transitionS5S1, S1);
}

// ------------------------ //

void loop() {
  if (!cardPresent) {  // Beim Abziehen der Karte: Transition auf S1 egal von wo
    restartRequested = true;
  } else {
    restartRequested = false;
  }
  machine.run();
  readRFID();
  if (monitor > 250) {
    Serial.println(uidDec);
    Serial.println(cardPresent);
    Serial.println(button_duration);
    monitor = 0;
  }
}