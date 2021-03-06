void timerLoop() {
  if (!MILLISTIMER || timer > 59) {
    if (millis() - last_timer_update > 1000 * pow(2, 2 - STRIKES) / (4 - STRIKES)) {   //1000 * 4/4, 2/3, 1/2 //TBU add strike nums again
      timer--;
      if (timer != 0) {
        buzzer(1, 800, 100);
        clockDisplay.writeDigitNum(4, timer % 60 % 10, false); //seconds
        clockDisplay.writeDigitNum(3, timer % 60 / 10, false); //tenths
        clockDisplay.writeDigitNum(1, timer / 60 % 10, false); //minutes
        clockDisplay.writeDigitNum(0, timer / 600, false); //tenminutes
        BLINKCOLON = !BLINKCOLON;
        clockDisplay.drawColon(BLINKCOLON);
        clockDisplay.writeDisplay();
      }
      last_timer_update = millis();
    }
  }
  else {
    double k = 50;
    if (millis() - last_timer_update > (k * pow(2, 2 - STRIKES) / (4 - STRIKES)) - 1) { //1000 * 4/4, 2/3, 1/2 //TBU add strike nums again

      centiTimer++;
      if (centiTimer >= ((1000 / k) * 1)) {

        BLINKCOLON = !BLINKCOLON;
        buzzer(1, 800, 100);
        centiTimer = 0;
        timer--;
      }
      if (timer >= 0) {
        clockDisplay.writeDigitNum(3, int(((1000 / k) - centiTimer)*k / 100 / (pow(2, 2 - STRIKES) / (4 - STRIKES))) % 10, false); //centiseconds
        clockDisplay.writeDigitNum(4, random(1, 10), false); //deciseconds //int((100-centiTimer)/(pow(2, 2 - STRIKES) / (4 - STRIKES))) / 10
        clockDisplay.writeDigitNum(0, (timer) % 60 / 10, false); //tenths
        clockDisplay.writeDigitNum(1, (timer) % 60 % 10, BLINKCOLON); //seconds


        clockDisplay.drawColon(false);
        clockDisplay.writeDisplay();
      }
      last_timer_update = millis();
    }
  }
}
