//-------------------------------------------//
void readRFID() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    uidDec = 0;
    for (byte i = mfrc522.uid.size - 2; i < mfrc522.uid.size; i++) {
      uidDec = (uidDec << 8) | mfrc522.uid.uidByte[i];
    }
    timerRFID = 0;
    cardPresent = 1;
  }
  if (timerRFID > 500) {
    cardPresent = 0;
  }
}
//-------------------------------------------//
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
//-------------------------------------------//
void clearArrow(int textX, int textY) {
  int arrowTipX = textX - 10;
  int arrowTipY = textY + 12;
  int size = 8;

  // Gleiche Koordinaten wie drawArrow, aber mit Hintergrundfarbe
  tft.fillTriangle(
    arrowTipX, arrowTipY,
    arrowTipX - size, arrowTipY - size,
    arrowTipX - size, arrowTipY + size,
    ST77XX_BLACK);  // Hintergrundfarbe
}
//-------------------------------------------//
void knobCallback(long value) {
  scaledValue = 0.0;
  scaledValue = value * 5.0;
  rawValue = scaledValue / 5;
  //Serial.println(scaledValue);
  if (current_state == 4) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setCursor(5, 5);
    tft.print("SALDO");
    tft.setCursor(40, 5);
    tft.print(nutzerNummer);
    tft.setTextSize(2);
    tft.setCursor(5, 20);
    tft.print(saldo);
    tft.setCursor(70, 20);
    tft.print("EUR");
    tft.setTextSize(2);
    tft.setCursor(10, 60);
    tft.print("Aufladen um:");
    tft.setCursor(10, 80);
    tft.print(scaledValue);
    tft.setCursor(80, 80);
    tft.print("EUR");
  }
}
//-------------------------------------------//
void updateArrow(int selectionMenu) {
  if (selectionMenu != lastSelection) {
    // Alten Pfeil löschen
    if (lastSelection == 0) clearArrow(30, 60);
    else if (lastSelection == 1) clearArrow(30, 95);

    // Neuen Pfeil zeichnen
    if (selectionMenu == 0) drawArrow(30, 60);
    else if (selectionMenu == 1) drawArrow(30, 95);

    lastSelection = selectionMenu;
  }
}
//-------------------------------------------//
void updateButton() {
  if (debounce > 20) {
    ok_button = !digitalRead(DI_ENCODER_SW);
    debounce = 0;
  }
}
//-------------------------------------------//
