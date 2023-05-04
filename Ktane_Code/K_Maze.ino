void maze() {                                                                              //---- MAZE ---
  if (solved_modules[1] == 0) {
    maze_options[maze_number][playery * 2][playerx * 2] = 0;
    if (digitalRead(matrix_arrows[0]) == 1 && arrows_last[0] != 1) {                         //
      if (maze_options[maze_number][playery * 2][(playerx * 2) - 1] != 1)
        playerx--;
      else {
        Serial.println(F("Maze: left")); //ErrorPrint
        error();
      }
    }
    if (digitalRead(matrix_arrows[1]) == 1 && arrows_last[1] != 1) {                          //   ___________
      if (maze_options[maze_number][(playery * 2) - 1][playerx * 2] != 1)                     //  |  __  |  | |
        playery--;                                                                            //  |__  | | |__|
      else {                                                                                  //  |    |
        Serial.println(F("Maze: up"));   //ErrorPrint                                            //    |  |___|  |
        error();                                                                              //  |_|___  |   |
      }                                                                                       //  |  ___  | |_|
    }                                                                                         //  | |_____|   |
    if (digitalRead(matrix_arrows[2]) == 1 && arrows_last[2] != 1) {                          //  |_________|_|
      if (maze_options[maze_number][playery * 2][(playerx * 2) + 1] != 1)                                   //
        playerx++;
      else {
        Serial.println(F("Maze: right"));//ErrorPrint
        error();
      }
    }
    if (digitalRead(matrix_arrows[3]) == 1 && arrows_last[3] != 1) {
      if (maze_options[maze_number][(playery * 2) + 1][(playerx * 2)] != 1)
        playery++;
      else {
        Serial.println(F("Maze: down"));//ErrorPrint
        error();
      }
    }
    for (int b = 0; b < 4; b++) {
      arrows_last[b] = digitalRead(matrix_arrows[b]);
    }
    playery = constrain(playery, 0, 7);
    playerx = constrain(playerx, 0, 7);
    maze_options[maze_number][playery * 2][playerx * 2] = 4;
    boolean mazeDone = true;
    for (int A = 0; A < 8; A++) {                                                             // ------
      for (int B = 0; B < 8; B++) {
        if (maze_options[maze_number][A * 2][B * 2] == 5) {
          mazeDone = false;
        }
      }
    }
    if (mazeDone)
      solved_modules[1] = 1;
    render();
  }
  else {  //If the module has been defused, play an animation
    if (millisTimer % 1000 > 500) {
      matrix.fillScreen(0);
      matrix.fillRect(2, 2, 4, 4, 1);
      matrix.writeDisplay();
    }
    else {
      matrix.fillScreen(0);
      matrix.writeDisplay();
    }
  }
}



/*
 * Available 8x8 i2c GTX matrix functions:
 *begin(address)
 *writePixel(x, y, color) / drawPixel(x, y, color)
 *setBrightness(b) #0<b<15
 *writeFastVLine(topx, topy, h, color)
 *writeFastHLine(leftx, lefty, w, color)
 *writeFillRect(x,y,w,hcolor)
 *drawRect(x,y,w,h,color)
 *drawRoundRect(x,y,w,h,r,color)
 *fillRoundRect
 *fillScreen(color)
 *drawLine(x0,y0,x1,y1,color)
 *drawCircle(x0,y0,r,color)
 *fillCircle(x0,y0,r,color)
 *drawTriangle(x0y0x1y1x2y2,color
 *filltriangle(...)
 *
 *
 */
