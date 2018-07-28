void error() {                                                                              //
  if (millis()>100) {
    strikes++;                                                                                //
    buzzer(3, 400, 400);                                                                      //
  }
}

void correctBeep() {
  boolean newSucc = false;

  for (int i = 0; i < 5; i++) { //TBU MORE
    if (solved_Beep[i] != solved_Modules[i]) {
      newSucc = true;
    }
    solved_Beep[i] = solved_Modules[i];
  }
  if (newSucc)
    buzzer(2, 1000, 230);
}
