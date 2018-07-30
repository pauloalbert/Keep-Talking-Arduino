void loop() {                                                     //-------------LOOP------------
  if (start == false) { //Starting the game by pressing the button
    if (digitalRead(button_pin) == 1) {
      start_pressed = true;
    }
    else if (start_pressed) {
      start = true;
      startTime = millis();
    }
  }
  else { //actual loop
    if (timer <= 0) {
      STRIKES = 3;
    }
    if (NEEDY)
      lever();
    explode();
    save();
    timerLoop();
    morseCheck();
    button();
    maze();
    simpleWires();
    symbols();
    correctBeep();
  }
}
