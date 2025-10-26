#include <ESP32RotaryEncoder.h>  //https://github.com/MaffooClock/ESP32RotaryEncoder

const uint8_t DI_ENCODER_A = 40;
const uint8_t DI_ENCODER_B = 41;
const int8_t DI_ENCODER_SW = 42;

RotaryEncoder rotaryEncoder(DI_ENCODER_A, DI_ENCODER_B, DI_ENCODER_SW);

void knobCallback(long value) {
  Serial.println(value);
}

void buttonCallback(unsigned long duration) {
  Serial.println(duration);
}

void setup() {
  Serial.begin(115200);
  rotaryEncoder.setEncoderType(EncoderType::HAS_PULLUP);
  rotaryEncoder.setBoundaries(0, 50, false);
  rotaryEncoder.onTurned(&knobCallback);
  rotaryEncoder.onPressed(&buttonCallback);
  rotaryEncoder.begin();
  //rotaryEncoder.setEncoderValue(eeprom_target);
}

void loop() {
  // put your main code here, to run repeatedly:
}
