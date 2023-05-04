void loop() {
  bigButton.update();
  morseButton.update();
  
  if (start == false) { //Starting the game by pressing the button
    if (bigButton.get()) {
      start_pressed = true;
    }
    else if (start_pressed) {
      start = true;
      timer_setup();
    }
  }
  else { //actual loop
    millisTimer = millis();
    if (timer < 0 || (timer == 0 && !MILLISTIMER)) {
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
  last_loop = millis();
}
