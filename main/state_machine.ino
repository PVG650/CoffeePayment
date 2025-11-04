//--------------------------STATE 1----------------------------//
void state1() {  // Idle, bitte Keytag auflegen
  if (machine.executeOnce) {
    current_state = 1;
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(20, 40);
    tft.print("BITTE");

    tft.setCursor(20, 60);
    tft.print("KEYTAG");

    tft.setCursor(20, 80);
    tft.print("AUFLEGEN");
  }
}
bool transitionS1S2() {
  if (cardPresent) {
    return true;
  }
  return false;
}
//--------------------------STATE 2----------------------------//
void state2() {  // Auswahl Kaffee bzw. Aufladen
  if (machine.executeOnce) {
    current_state = 2;
    foundUID = false;
    numRows = db.countRows();
    for (i = 1; i < numRows; ++i) {  // Nach Nutzer suchen
      if (db.readCell(i, 0).toInt() == uidDec) {
        nutzerNummer = i;  // Zeile in der der Nutzer gefunden wurde. Beginnt in Zeile 1 weil Zeile 0 der Header ist
        foundUID = true;
      }
    }
    if (i == numRows && !foundUID) {  // Neuen Nutzer anlegen wenn noch nicht in der Liste vorhanden
      db.appendEmptyRow();
      numRows = db.countRows();
      db.writeCell(numRows - 1, 0, uidDec);
      Serial.println("NEUE ID GESCHRIEBEN");
    }
    saldo = db.readCell(nutzerNummer, 2).toFloat();
    if (db.readCell(nutzerNummer, 1).length() < 1) {  // Wenn kein Name eingetragen wurde abbruch
      Serial.println("Noch kein Name vorhanden");
    } else {
      Serial.println(db.readCell(nutzerNummer, 1));
    }
    // Header: Nutzer-Nr und Saldo
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setCursor(5, 5);
    tft.print("SALDO");
    tft.setCursor(40, 5);
    tft.print(db.readCell(nutzerNummer, 1));
    tft.setTextSize(2);
    tft.setCursor(5, 20);
    tft.print(saldo);
    tft.setCursor(70, 20);
    tft.print("EUR");
    // Menü
    tft.setTextSize(3);
    tft.setCursor(30, 60);
    tft.print("KAFFEE");
    tft.setCursor(30, 95);
    tft.print("LADEN");
    // Neuen Pfeil zeichnen
    if (selectionMenu == 0) drawArrow(30, 60);
    else if (selectionMenu == 1) drawArrow(30, 95);
  }
  if (rawValue % 2 == 0) {
    selectionMenu = 0;
  } else {
    selectionMenu = 1;
  }
  updateArrow(selectionMenu);
}
bool transitionS2S3() {
  //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 0 && ok_button) {
    bezug = 0;  // timer für die Dauer des "state: bezug" starten
    return true;
  }
  return false;
}
bool transitionS2S4() {
  //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 1 && ok_button) {
    stateJump = 0;  // Verhindert, dass wir mit dem aktuellen "OK" den nächsten State direkt überspringen
    return true;
  }
  return false;
}
bool transitionS2S1() {
  if (restartRequested) {
    return true;
  }
  return false;
}
//--------------------------STATE 3----------------------------//
void state3() {  // Kaffeebezug
  if (machine.executeOnce) {
    current_state = 3;
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor((160 - 3 * 12) / 2, 40);  // "..." → 3 Zeichen * 12px bei TextSize 2
    tft.print("...");
    tft.setCursor((160 - 8 * 12) / 2, 80);  // "-0,25 EUR" → 8 Zeichen * 12px
    tft.print("-0,25 EUR");
  }
}
bool transitionS3S2() {
  if (bezug > 5000) {
    return true;
  }
  return false;
}
bool transitionS3S1() {
  if (restartRequested) {
    return true;
  }
  return false;
}
//--------------------------STATE 4----------------------------//
void state4() {  // Aufladen
  if (machine.executeOnce) {
    current_state = 4;
    rotaryEncoder.setBoundaries(0, 10, false);
    // Header: Nutzer-Nr und Saldo
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setCursor(5, 5);
    tft.print("SALDO");
    tft.setCursor(40, 5);
    tft.print(db.readCell(nutzerNummer, 1));
    tft.setTextSize(2);
    tft.setCursor(5, 20);
    tft.print(saldo);
    tft.setCursor(70, 20);
    tft.print("EUR");
    tft.setTextSize(2);
    tft.setCursor(10, 60);
    tft.print("Aufladen um:");
  }
}
bool transitionS4S5() {
  if (ok_button && stateJump > 2000) {
    db.writeCell(nutzerNummer, 2, saldo+scaledValue);
    rotaryEncoder.setBoundaries(-1000, 1000, false);
    return true;
  }
  return false;
}
bool transitionS4S1() {
  if (restartRequested) {
    return true;
  }
  return false;
}

//--------------------------STATE 5----------------------------//
void state5() {  // Aufladen bestätigen
  if (machine.executeOnce) {
    current_state = 5;
    tft.fillScreen(ST77XX_BLACK);
  }
}
bool transitionS5S2() {
  if (0 == 1) {
    return true;
  }
  return false;
}
bool transitionS5S1() {
  if (restartRequested) {
    return true;
  }
  return false;
}
