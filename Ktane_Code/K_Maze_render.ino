void render() {
  for (int c = 0; c < 8; c++) {
    digitalWrite(matrix_pins_col[c], HIGH);
    digitalWrite(matrix_pins_row[c], LOW);

  }
  for (int B = 0; B < 8; B++) {
    digitalWrite(matrix_pins_row[B], HIGH);                          // ------
    for (int A = 0; A < 8; A++) {
      if (maze_options[maze_number][B * 2][A * 2] == 2 || (maze_options[maze_number][B * 2][A * 2] == 5 && millis() % 800 > 400) || (maze_options[maze_number][B * 2][A * 2] == 4 && millis() % 6 == 2)) {
        digitalWrite(matrix_pins_col[A], LOW);
      }
    }
    digitalWrite(matrix_pins_row[B], LOW);
    for (int i = 0; i < 8; i++) {
      digitalWrite(matrix_pins_col[i], HIGH);
    }
  }
}
