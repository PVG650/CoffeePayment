//--------------------------STATE 1----------------------------//
void state1() {
  if (machine.executeOnce) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(2);
    tft.setCursor(30, 60);
    tft.print("BITTE KEYTAG AUFLEGEN");
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
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextSize(3);
    tft.setCursor(30, 60);
    tft.print("KAFFEE");
    tft.setCursor(30, 95);
    tft.print("LADEN");
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
  if (selectionMenu == 0 && 1 == 0) {
    return true;
  }
  return false;
}
bool transitionS2S4() {
  //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 1 && 1 == 0) {
    return true;
  }
  return false;
}
bool transitionS1S2() {
  if(restartRequested){
    return true;
  }
  return false;
}
//--------------------------STATE 3----------------------------//
void state3() {
  if (machine.executeOnce) {
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
  return
//--------------------------STATE 4----------------------------//
void state4() {
  if (machine.executeOnce) {
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
