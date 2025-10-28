// Debounce and update okButton and grindButton
void updateButtons() {
  if (debounce_timer.debounce(!digitalRead(pin_ok))) {
    value_ok = 1;
  }
  if (debounce_timer.debounce(digitalRead(pin_ok))) {
    value_ok = 0;
  }
  if (debounce_timer_2.debounce(!digitalRead(pin_grindButton))) {
    value_grindButton = 1;
  }
  if (debounce_timer_2.debounce(digitalRead(pin_grindButton))) {
    value_grindButton = 0;
  }
}