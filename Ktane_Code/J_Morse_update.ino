void morse_update() {
  //override millisTimer for more accurate morse
  unsigned long millisTimer = millis();
  
  if (morse_loc > morse_message.length())
    morse_loc = 0;
  switch (lineDot[morse_loc]) {
    case '1':
      if (!(millisTimer > ledTimer && solved_modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 300 * k);
        ledTimer = millisTimer + (300 * k);
      morseTimer = millisTimer + (380 * k);
      break;
    case '0':
      if (!(millisTimer > ledTimer && solved_modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 100 * k);
        ledTimer = millisTimer + (100 * k);
      morseTimer = millisTimer + (200 * k);
      break;
    case '2':
      morseTimer = millisTimer + (500 * k);
      break;
    case ' ':
      morseTimer = millisTimer + (250 * k);
      break;

  }
  morse_loc++;
  if (morse_loc > morse_message.length()) {
    morse_loc = 0;
    morseTimer = millisTimer + (1000 * k);
  }


}
