//turns off all pins. happens in the end of the game no matter what the outcome was.
void End() {

  for (int z = 0; z < (sizeof(lever_led_pins) / sizeof(lever_led_pins[0])); z++) {
    digitalWrite(lever_led_pins[z], LOW);
  }
  
  for (int z = 0; z < (sizeof(wires_pins) / sizeof(wires_pins[0])); z++) {
    digitalWrite(wires_pins[z], LOW);
  }
  for (int z = 0; z < (sizeof(rgb_pins) / sizeof(rgb_pins[0])); z++) {
    digitalWrite(rgb_pins[z], LOW);
  }
  matrix.fillScreen(0);
  matrix.writeDisplay();
  //printf("Time left: %02d:%02d.%02d", (timer / 60), (timer % 60), (int)((((millis() - timeTick) / (pow(2, 2 - STRIKES) / (4 - STRIKES)))) / 10));
  int buffTime = timer - (MILLISTIMER ? 0 : 1);
  Serial.print(F("Time left: "));
  Serial.print((String)(buffTime / 60 < 10 ? "0" : "") + (String)(buffTime / 60));
  Serial.print(":" + (String)(buffTime % 60 < 10 ? "0" : "") + (String)(buffTime % 60 >= 0 ? (buffTime % 60) : 0));
  Serial.println("." + (String)((int)(((millis() - timeTick) / (pow(2, 2 - STRIKES) / (4 - STRIKES))) / 10) < 10 ? "0" : "") + (String)((int)(((millis() - timeTick) / (pow(2, 2 - STRIKES) / (4 - STRIKES))) / 10)));
  digitalWrite(morse_led_pin, LOW);
}

