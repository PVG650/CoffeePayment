// CODE RUNS ON ESP32-S3 DEV KIT
// (C) PVG 2025

#include <elapsedMillis.h>  //https://github.com/pfeerick/elapsedMillis
#include <StateMachine.h>   //https://github.com/jrullan/StateMachine

// ------------------------- //


// StateMachine
StateMachine machine = StateMachine();
State* S1 = machine.addState(&state1);  // Bitte Chip auflegen
State* S2 = machine.addState(&state2);  // Modus auswählen
State* S3 = machine.addState(&state3);  // Bezug
State* S4 = machine.addState(&state4);  // Aufladen
State* S5 = machine.addState(&state5);  // Aufladen bestätigen

// ------------------------ //

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Serial i.O.");
  
  // State Machine
  S1->addTransition(&transitionS1S2, S2);  // Wenn der Encoder gedreht wird
  S2->addTransition(&transitionS2S1, S1);  // Wenn Timeout 10s
  S1->addTransition(&transitionS1S4, S4);  // Wenn Mahlknopf gedrückt
  S2->addTransition(&transitionS2S3, S3);  // Wenn OK gedrückt
  S3->addTransition(&transitionS3S1, S1);  // Wenn OK gedrückt oder 30s Timeout
  S4->addTransition(&transitionS4S1, S1);  // Nach Ablauf Mahlzeit zurück
}

// ------------------------ //

void loop() {
  machine.run();
  updateButtons();
}