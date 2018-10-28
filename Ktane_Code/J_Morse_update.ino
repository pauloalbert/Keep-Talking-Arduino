void morse_update() {
  //if(!morse_start)
  if (millis() - last_morse > morse_delay) {
    switch (lineDot[morse_loc]) {
      case '1':
        if (millis() - last_morse < morse_led_delay)
          digitalWrite(morse_led_pin, HIGH);
          //tone(morse_buzzer_pin, 600, 300 * morse_constant);
        morse_led_delay = 300 * morse_constant;
        morse_delay = 380 * morse_constant;
        break;
      case '0':
        if (millis() - last_morse < morse_led_delay)
          digitalWrite(morse_led_pin, HIGH);
          //tone(morse_buzzer_pin, 600, 100 * morse_constant);
        morse_led_delay = 100 * morse_constant;
        morse_delay = 200 * morse_constant;
        break;
      case '2':
        morse_delay = 500 * morse_constant;
        break;
      case ' ':
        morse_delay = 250 * morse_constant;
        break;

    }
    morse_loc++;
    if (morse_loc > morse_message.length()) {
      morse_loc = 0;
      morse_delay = 1000 * morse_constant;
    }
    last_morse = millis();
  }
  if(millis() - last_morse > morse_led_delay)
    digitalWrite(morse_led_pin, LOW);
}
