void morse_update() {
  int k = 2;

  if (morse_loc > morse_message.length())
    morse_loc = 0;
  switch (lineDot[morse_loc]) {
    case '1':
      if (!(millis() > ledTimer && solved_modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 300 * k);
        ledTimer = millis() + (300 * k);
      morseTimer = millis() + (380 * k);
      break;
    case '0':
      if (!(millis() > ledTimer && solved_modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 100 * k);
        ledTimer = millis() + (100 * k);
      morseTimer = millis() + (200 * k);
      break;
    case '2':
      morseTimer = millis() + (500 * k);
      break;
    case ' ':
      morseTimer = millis() + (250 * k);
      break;

  }
  morse_loc++;
  if (morse_loc > morse_message.length()) {
    morse_loc = 0;
    morseTimer = millis() + (1000 * k);
  }


}
