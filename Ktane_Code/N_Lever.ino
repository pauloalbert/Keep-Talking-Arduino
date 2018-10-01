void lever() {
  if (!lever_started) { //to make sure it doesnt go off before it even started
    leverTime = millis();
    for (int z = 0; z < (sizeof(solved_modules) / sizeof(solved_modules[0])); z++) {
      if (solved_modules[z] == 1)
        lever_started = true;
    }
  }
  else {
    if (millis() - leverTime > 45000) { //exploding after 45 seconds
      STRIKES = 3;
      Serial.println(F("Lever"));//ErrorPrint
    }
    //Checking the lever
    if (joystick.getPos() > joystick_bits / 7 * 6 - 1)
    {
      leverTime += lever_speed * (millis()-last_loop);
    }
    if (leverTime > millis())
      leverTime = millis();

    if (millis() - leverTime > 9000)
      digitalWrite(lever_led_pins[0], HIGH);
    else
      digitalWrite(lever_led_pins[0], LOW);
    if (millis() - leverTime > 18000)
      digitalWrite(lever_led_pins[1], HIGH);
    else
      digitalWrite(lever_led_pins[1], LOW);
    if (millis() - leverTime > 27000)
      digitalWrite(lever_led_pins[2], HIGH);
    else
      digitalWrite(lever_led_pins[2], LOW);
    if (millis() - leverTime > 33000 && millis() - leverTime < 41000 && fmod( 1 * millis() , (double)(45000 - (millis() - leverTime))) > (45000 - (double)(millis() - leverTime)) / 2)
      digitalWrite(lever_led_pins[3], HIGH);
    else if (millis() - leverTime > 41000 && fmod( 1 * millis() , (double)(65)) > 30)
      digitalWrite(lever_led_pins[3], HIGH);
    else
      digitalWrite(lever_led_pins[3], LOW);
  }
}
