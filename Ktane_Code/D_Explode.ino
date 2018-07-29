void explode() {
  if (STRIKES >= 3 || (STRIKES >= 1 && HARDCORE)) {
    clockDisplay.writeDigitRaw(0, 0x00);
    clockDisplay.writeDigitRaw(1, 0x00);
    clockDisplay.drawColon(false);
    clockDisplay.writeDigitRaw(3, 0x00);
    clockDisplay.writeDigitRaw(4, 0x00);
    clockDisplay.writeDisplay();
    End();

    Serial.println("explode");
    delay(100);
    exit(1);
  }
}
