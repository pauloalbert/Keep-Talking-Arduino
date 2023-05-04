void morseCheck() {
  //override millisTimer for more accurate morse
  unsigned long millisTimer = millis();
  //Starting the input sequence
  if (morseButton.get()) {

    morse_start = true;
    morse_press = true;
    if (!clicked) {
      last_press = millisTimer;//only happens on press
      clicked = true;
    }
    //tone(morse_buzzer_pin, 1000, 1);
  }
  else {
    clicked = false;
  }
  if (morse_start == true && solved_modules[3] == 0) {

    if (!morseButton.get() && morse_press == true) {
      morse_press = false;
      int io;
      if (millisTimer - last_press < 270) { //Dot
        io = 0;
      }
      else { //line
        io = 1;
      }
      if (lineDotRes[morse_button_pin_loc] - '0' == io) {
        morse_button_pin_loc++;

        if (morse_button_pin_loc > morse_response.length() - 1) {
          solved_modules[3] = 1;
        }
      }
      else {
        morse_button_pin_loc = 0;
        morse_start = false;
        Serial.println(F("Morse: Error")); //ErrorPrint
        error();

      }

    }

  }

  if (millisTimer > ledTimer && solved_modules[3] == 0) {
    digitalWrite(morse_led_pin, LOW);
  }
  if (millisTimer > morseTimer) {
    morse_update();
  }

}
