//--------------------------STATE 1----------------------------//
void state1() {
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
    // Header: Nutzer-Nr und Saldo
    tft.setTextSize(1);
    tft.setCursor(5, 5);
    tft.print("SALDO NUTZER-NR 0:");
    tft.setTextSize(2);
    tft.setCursor(5, 20);
    tft.print("6,50 EUR");
    // Menü
    tft.fillScreen(ST77XX_BLACK);
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
    return true;
  }
  return false;
}
bool transitionS2S4() {
  //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 1 && ok_button) {
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
void state3() {
  if (machine.executeOnce) {
    current_state = 3;
    tft.fillScreen(ST77XX_BLACK);
  }
}
bool transitionS3S2() {
  if (0 == 1) {
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
void state4() {
  if (machine.executeOnce) {
    current_state = 4;
    rotaryEncoder.setBoundaries(0, 50, false);
    tft.fillScreen(ST77XX_BLACK);
  }
}
bool transitionS4S5() {
  if (0 == 1) {
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
void state5() {
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
