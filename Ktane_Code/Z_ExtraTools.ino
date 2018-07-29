void arrayCopy(int arrChange[], int arrEdit[], int sizes) {
  for (int i = 0 ; i < sizes; i++) {
    arrChange[i] = arrEdit[i];
  }
}
void buzzer(int priority, int pitch, int timer) {
  if (millis() > buzzerTimer)
    priorityB = 0;
  if (priority >= priorityB) {
    tone(buzzer_pin, pitch, timer);
    buzzerTimer = millis() + timer;
    priorityB = priority;
  }
}
