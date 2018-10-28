void loop() {
  
  if (start == false) { //Starting the game by pressing the button
    if (digitalRead(button_pin) == 1) {
      start_pressed = true;
    }
    else if (start_pressed) {
      start = true;
      timer_setup();
    }
  }
  else { //actual loop
    if (timer < 0 || (timer == 0 && !MILLISTIMER)) {
      STRIKES = 3;
    }
    if (NEEDY)
      lever();
    explode();
    save();
    timerLoop();
    if(solved_modules[3] == 0){
      morseCheck();
      morse_update();
    }
    else 
      digitalWrite(morse_led_pin, LOW);
    button();
    maze();
    simpleWires();
    symbols();
    correctBeep();
  }
  last_loop = millis();
}
