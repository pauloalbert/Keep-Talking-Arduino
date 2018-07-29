void error() {                                                                              //
  if (millis() > 100) {
    STRIKES++;                                                                                //
    buzzer(3, 400, 400);                                                                      //
  }
}

void correctBeep() {
  boolean newSucc = false;

  for (int i = 0; i < 5; i++) { //TBU MORE
    if (solved_beep[i] != solved_modules[i]) {
      newSucc = true;
    }
    solved_beep[i] = solved_modules[i];
  }
  if (newSucc)
    buzzer(2, 1000, 230);
}
