void lever() {
  if (!level_started) { //to make sure it doesnt go off before it even started
    leverTimer = millis();
    for (int z = 0; z < (sizeof(solved_modules) / sizeof(solved_modules[0])); z++) {
      if (solved_modules[z] == 1)
        level_started = true;
    }
  }
  else {
    if (millis() - leverTimer > 45000) { //exploding after 45 seconds
      STRIKES = 3;
      Serial.println("Lever");//ErrorPrint
    }
    //Checking the lever
    if (joystick.getPos() > joystick_bits / 7 * 6 - 1)
    {
      leverTimer += 10;
    }
    if (leverTimer > millis())
      leverTimer = millis();

    if (millis() - leverTimer > 9000)
      digitalWrite(lever_led_pins[0], HIGH);
    else
      digitalWrite(lever_led_pins[0], LOW);
    if (millis() - leverTimer > 18000)
      digitalWrite(lever_led_pins[1], HIGH);
    else
      digitalWrite(lever_led_pins[1], LOW);
    if (millis() - leverTimer > 27000)
      digitalWrite(lever_led_pins[2], HIGH);
    else
      digitalWrite(lever_led_pins[2], LOW);
    if (millis() - leverTimer > 33000 && millis() - leverTimer < 41000 && fmod( 1 * millis() , (double)(45000 - (millis() - leverTimer))) > (45000 - (double)(millis() - leverTimer)) / 2)
      digitalWrite(lever_led_pins[3], HIGH);
    else if (millis() - leverTimer > 41000 && fmod( 1 * millis() , (double)(65)) > 30)
      digitalWrite(lever_led_pins[3], HIGH);
    else
      digitalWrite(lever_led_pins[3], LOW);
  }
}

