void morse_update() {
  int k = 2;

  if (morse_loc > morse_message.length())
    morse_loc = 0;
  switch (lineDot[morse_loc]) {
    case '1':
      if (!(millis() > led_timer && solved_Modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 300 * k);
        led_timer = millis() + (300 * k);
      morse_timer = millis() + (380 * k);
      break;
    case '0':
      if (!(millis() > led_timer && solved_Modules[3] == 1))
        digitalWrite(morse_led_pin, HIGH);
      if (!morse_start)
        //tone(morse_buzzer_pin, 600, 100 * k);
        led_timer = millis() + (100 * k);
      morse_timer = millis() + (200 * k);
      break;
    case '2':
      morse_timer = millis() + (500 * k);
      break;
    case ' ':
      morse_timer = millis() + (250 * k);
      break;

  }
  morse_loc++;
  if (morse_loc > morse_message.length()) {
    morse_loc = 0;
    morse_timer = millis() + (1000 * k);
  }


}
