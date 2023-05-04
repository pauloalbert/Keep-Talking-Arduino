void render() {
  matrix.fillScreen(0);
  for (int B = 0; B < 8; B++) {
    for (int A = 0; A < 8; A++) {
      if (!MATRIXRGB)
        if (maze_options[maze_number][B * 2][A * 2] == 2 || (maze_options[maze_number][B * 2][A * 2] == 5 && millisTimer % 800 > 400) || (maze_options[maze_number][B * 2][A * 2] == 4 && millisTimer % 6 == 2))
          matrix.drawPixel(A, B, 1);
        else {
          if (maze_options[maze_number][B * 2][A * 2] == 2)
            matrix.drawPixel(A, B, LED_YELLOW);
          if (maze_options[maze_number][B * 2][A * 2] == 5)
            matrix.drawPixel(A, B, LED_GREEN);
          if (maze_options[maze_number][B * 2][A * 2] == 4)
            matrix.drawPixel(A, B, LED_RED);
        }
    }
  }
  matrix.writeDisplay();
}
