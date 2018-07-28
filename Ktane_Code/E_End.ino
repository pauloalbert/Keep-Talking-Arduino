//turns off all pins. happens in the end of the game no matter what the outcome was.
void End() {

  for (int z = 0; z < (sizeof(lever_leds_pins) / sizeof(lever_leds_pins[0])); z++) {
    digitalWrite(lever_leds_pins[z], LOW);
  }
  for (int z = 0; z < (sizeof(matrix_Pins_Row) / sizeof(matrix_Pins_Row[0])); z++) {
    digitalWrite(matrix_Pins_Row[z], LOW);
  }
  for (int z = 0; z < (sizeof(matrix_Pins_Col) / sizeof(matrix_Pins_Col[0])); z++) {
    digitalWrite(matrix_Pins_Col[z], LOW);
  }
  for (int z = 0; z < (sizeof(wires_pins) / sizeof(wires_pins[0])); z++) {
    digitalWrite(wires_pins[z], LOW);
  }
  for (int z = 0; z < (sizeof(rgb_pins) / sizeof(rgb_pins[0])); z++) {
    digitalWrite(rgb_pins[z], LOW);
  }
  printf("Time left: %02d:%02d.%02d", (timer / 60),(timer % 60),(int)((((millis() - timeTick) / (pow(2, 2 - strikes) / (4 - strikes)))) / 10));
  int buffTime = timer-1;
  Serial.println("Time left: " + (String)(buffTime / 60) + ":" + (String)(buffTime % 60) + "." + (String)(int)((((millis() - timeTick) / (pow(2, 2 - strikes) / (4 - strikes)))) / 10));
  digitalWrite(morse_led_pin, LOW);
}

