void morse_check() {
  //Starting the input sequence
  if (digitalRead(morse_button_pin)) {

    morse_start = true;
    morse_press = true;
    if (!clicked) {
      last_press = millis();//only happens on press
      clicked = true;
    }
    //tone(morse_buzzer_pin, 1000, 1);
  }
  else {
    clicked = false;
  }
  if (morse_start == true && solved_modules[3] == 0) {

    if (!digitalRead(morse_button_pin) && morse_press == true) {
      morse_press = false;
      int io;
      if (millis() - last_press < 270) { //Dot
        io = 0;
      }
      else { //line
        io = 1;
      }
      if (lineDot2[morse_button_pin_loc] - '0' == io) {
        morse_button_pin_loc++;

        if (morse_button_pin_loc > morse_response.length() - 1) {
          solved_modules[3] = 1;
        }
      }
      else {
        morse_button_pin_loc = 0;
        morse_start = false;
        Serial.println("Morse: Error"); //ErrorPrint
        error();

      }

    }

  }

  if (millis() > ledTimer && solved_modules[3] == 0) {
    digitalWrite(morse_led_pin, LOW);
  }
  if (millis() > morseTimer) {
    morse_update();
  }

}
