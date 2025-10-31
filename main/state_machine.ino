
//--------------------------STATE 2----------------------------//
void state2() {  // Auswahl Kaffee bzw. Aufladen
  if (machine.executeOnce) {
  }
  if (rawValue % 2 == 0) {
    selectionMenu = 0;
  } else {
    selectionMenu = 1;
  }
  tft.setTextSize(3);
  tft.setCursor(30, 60);
  tft.print("KAFFEE");
  tft.setCursor(30, 95);
  tft.print("LADEN");


  if (selectionMenu == 0) {
    drawArrow(30, 60);  // X/Y von dem Cursor des Texts
  }
  if (selectionMenu == 1) {
    drawArrow(30, 95);  // X/Y von dem Cursor des Texts
  }
}
bool transitionS2S3() {
    //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 0 && 1==0) {
    return true;
  }
  return false;
}
bool transitionS2S4() {
    //if (selectionMenu == 0 && buttonCallback()>50) {
  if (selectionMenu == 1 && 1==0) {
    return true;
  }
  return false;
}
//--------------------------STATE 3----------------------------//
void state3() {
  if (machine.executeOnce) {
  }
}
bool transitionS3S2() {
  if (0==1) {
    return true;
  }
  return false;
}
//--------------------------STATE 4----------------------------//
void state4() {
  if (machine.executeOnce) {
  }
}
bool transitionS4S5() {
  if (0==1) {
    return true;
  }
  return false;
}
//--------------------------STATE 5----------------------------//
void state5() {
  if (machine.executeOnce) {
  }
}
bool transitionS5S2() {
  if (0==1) {
    return true;
  }
  return false;
}