void render() {
  for (int c = 0; c < 8; c++) {
    digitalWrite(matrix_Pins_Col[c], HIGH);
    digitalWrite(matrix_Pins_Row[c], LOW);

  }
  for (int B = 0; B < 8; B++) {
    digitalWrite(matrix_Pins_Row[B], HIGH);                          // ------
    for (int A = 0; A < 8; A++) {
      if (mazeOptions[mazeNumber][B * 2][A * 2] == 2 || (mazeOptions[mazeNumber][B * 2][A * 2] == 5 && millis() % 800 > 400) || (mazeOptions[mazeNumber][B * 2][A * 2] == 4 && millis() % 6 == 2)) {
        digitalWrite(matrix_Pins_Col[A], LOW);
      }
    }
    digitalWrite(matrix_Pins_Row[B], LOW);
    for (int i = 0; i < 8; i++) {
      digitalWrite(matrix_Pins_Col[i], HIGH);
    }
  }
}
