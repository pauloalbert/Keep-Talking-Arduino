void render() {
  matrix.fillScreen(0);
  for (int B = 0; B < 8; B++) {
    for (int A = 0; A < 8; A++) {
      if (maze_options[maze_number][B * 2][A * 2] == 2 || (maze_options[maze_number][B * 2][A * 2] == 5 && millis() % 800 > 400) || (maze_options[maze_number][B * 2][A * 2] == 4 && millis() % 6 == 2)) {
        matrix.drawPixel(A, B, 1);
      }
    }
  }
  matrix.writeDisplay();
}
