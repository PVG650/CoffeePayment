#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 15
#define TFT_DC 16
#define TFT_RST 7
#define TFT_SCK 12
#define TFT_MOSI 11

SPIClass spiBus(FSPI);
Adafruit_ST7735 tft = Adafruit_ST7735(&spiBus, TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  spiBus.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);

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
}

void loop() {
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
