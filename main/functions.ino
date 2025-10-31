//-------------------------------------------//
void readRFID() {
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
void knobCallback(long value) {
  scaledValue = 0;
  scaledValue = value * 5;
  rawValue = scaledValue/5;
  Serial.println(scaledValue);
}
//-------------------------------------------//
void buttonCallback(unsigned long duration) {
  button_duration = duration;
  Serial.println(duration);
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
    ST77XX_BLACK); // Hintergrundfarbe
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
