void Button() {

  if (digitalRead(button_pin) == 1 && button_last) {
    rgb_Color = random(5);
    digitalWrite(rgb_pins[0], LOW);
    digitalWrite(rgb_pins[1], LOW);
    digitalWrite(rgb_pins[2], LOW);

    if (button_Color == "Blue" && button_Label == "Abort") {
      mode = 1;
    }
    else if (batteryCount > 1 && button_Label == "") {
      mode = 0;
    }
    else if (button_Color == "Red" && 1 == 609) { //TBU Port
      mode = 0;
    }
    else if (button_Label == "DickButt") {
      mode = 2;
    }
    else if (button_Color == "White" && batteryCount == 2) {
      mode = 1;
    }
    else if ((timer / 60) % 2 == 1) {
      mode = 0;
    }
    else {
      mode = 1;
    }

    button_Timer = millis();
    rgb_Color = random(5);
    button_last = false;
  }
  if (millis() - button_Timer > 300 && button_last == false) {

    if (rgb_Color == 0) {
      digitalWrite(rgb_pins[0], LOW);
      digitalWrite(rgb_pins[1], LOW);
      analogWrite(rgb_pins[2], 150);
    }
    else if (rgb_Color == 1) {
      analogWrite(rgb_pins[0], 200);
      digitalWrite(rgb_pins[1], LOW);
      analogWrite(rgb_pins[2], 200);
    }
    else if (rgb_Color == 2) {
      analogWrite(rgb_pins[0], 200);
      digitalWrite(rgb_pins[1], LOW);
      digitalWrite(rgb_pins[2], LOW);
    }
    else if (rgb_Color == 3) {
      analogWrite(rgb_pins[1], 200);
      digitalWrite(rgb_pins[0], LOW);
      digitalWrite(rgb_pins[2], LOW);
    }
    else if (rgb_Color == 4) {
      analogWrite(rgb_pins[0], 200);
      analogWrite(rgb_pins[1], 200);
      analogWrite(rgb_pins[2], 200);
    }
    Serial.println(rgb_Color);
  }
  else {
    digitalWrite(rgb_pins[0], LOW);
    digitalWrite(rgb_pins[1], LOW);
    digitalWrite(rgb_pins[2], LOW);
  }
  if (digitalRead(button_pin) == 0 && button_last == false) {
    if (mode == 0 && millis() - button_Timer < 300) {
      solved_Modules[2] = 1;
    }
    else if (mode == 1 && rgb_Color == 0 && (timer / 60 == 3 || timer - (timer / 10) * 10 == 3 || timer % 60 / 10 == 3)) {
      solved_Modules[2] = 1;
    }
    else if (mode == 1 && rgb_Color == 1 && (timer / 60 + (timer - (timer / 10) * 10) == 8)) {
      solved_Modules[2] = 1;
    }
    else if (mode == 1 && rgb_Color == 2 && (timer / 60 + (timer - (timer / 10) * 10) + ( timer % 60 / 10)) % 2 == 0) {
      solved_Modules[2] = 1;
    }
    else if (mode == 1 && (rgb_Color == 3 || rgb_Color == 4) && (timer / 60 + (timer - (timer / 10) * 10) + ( timer % 60 / 10)) % 2 == 0) { //TBU real thing
      solved_Modules[2] = 1;
    }
    else {
      Serial.println("Button: error"); //ErrorPrint
      error();

    }
    button_last = true;
    button_Timer = 9999999;
  }

}
