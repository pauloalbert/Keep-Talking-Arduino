void maze() {                                                                              //---- MAZE ---
  if (solved_Modules[1] == 0) {
    mazeOptions[mazeNumber][playery * 2][playerx * 2] = 0;
    if (digitalRead(matrix_arrows[0]) == 1 && arrows_last[0] != 1) {                         //
      if (mazeOptions[mazeNumber][playery * 2][(playerx * 2) - 1] != 1)
        playerx--;
      else {
        Serial.println("Maze: left"); //ErrorPrint
        error();
      }
    }
    if (digitalRead(matrix_arrows[1]) == 1 && arrows_last[1] != 1) {                          //   ___________
      if (mazeOptions[mazeNumber][(playery * 2) - 1][playerx * 2] != 1)                       //  |  __  |  | |
        playery--;                                                                            //  |__  | | |__|
      else {                                                                                  //  |    |
        Serial.println("Maze: up");   //ErrorPrint                                                           //     | |___|  |
        error();                                                                              //  |_|___  |   |
      }                                                                                       //  |  ___  | |_|
    }                                                                                         //  | |_____|   |
    if (digitalRead(matrix_arrows[2]) == 1 && arrows_last[2] != 1) {                          //  |_________|_|
      if (mazeOptions[mazeNumber][playery * 2][(playerx * 2) + 1] != 1)                                   //
        playerx++;
      else {
        Serial.println("Maze: right");//ErrorPrint
        error();
      }
    }
    if (digitalRead(matrix_arrows[3]) == 1 && arrows_last[3] != 1) {
      if (mazeOptions[mazeNumber][(playery * 2) + 1][(playerx * 2)] != 1)
        playery++;
      else {
        Serial.println("Maze: down");//ErrorPrint
        error();
      }
    }
    for (int b = 0; b < 4; b++) {
      arrows_last[b] = digitalRead(matrix_arrows[b]);
    }
    playery = constrain(playery, 0, 7);
    playerx = constrain(playerx, 0, 7);
    mazeOptions[mazeNumber][playery * 2][playerx * 2] = 4;
    boolean mazeDone = true;
    for (int A = 0; A < 8; A++) {                                                             // ------
      for (int B = 0; B < 8; B++) {
        if (mazeOptions[mazeNumber][A * 2][B * 2] == 5) {
          mazeDone = false;
        }
      }
    }
    if (mazeDone)
      solved_Modules[1] = 1;
    render();
  }
  else {
    if (millis() % 1000 > 500) {
      for (int A = 0; A < 6; A++) {
        digitalWrite(matrix_Pins_Col[A + 1], LOW);
        digitalWrite(matrix_Pins_Row[A + 1], HIGH);

      }
    }
    else {
      for (int A = 0; A < 8; A++) {

        digitalWrite(matrix_Pins_Col[A], HIGH);
        digitalWrite(matrix_Pins_Row[A], LOW);
      }
    }
  }
}
