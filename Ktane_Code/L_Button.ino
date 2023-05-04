void button() {

  if (bigButton.get() && button_last) {
    rgb_color = random(5);
    digitalWrite(rgb_pins[0], LOW);
    digitalWrite(rgb_pins[1], LOW);
    digitalWrite(rgb_pins[2], LOW);

    if (button_color == "Blue" && button_label == "Abort") {
      mode = 1;
    }
    else if (batteryCount > 1 && button_label == "") {
      mode = 0;
    }
    else if (button_color == "Red" && 1 == 609) { //TBU Port
      mode = 0;
    }
    else if (button_label == "DickButt") {
      mode = 2;
    }
    else if (button_color == "White" && batteryCount == 2) {
      mode = 1;
    }
    else if ((timer / 60) % 2 == 1) {
      mode = 0;
    }
    else {
      mode = 1;
    }

    buttonTimer = millis();
    rgb_color = random(5);
    button_last = false;
  }
  if (millis() - buttonTimer > 300 && button_last == false) {

    if (rgb_color == 0) { //blue
      digitalWrite(rgb_pins[0], LOW);
      digitalWrite(rgb_pins[1], LOW);
      analogWrite(rgb_pins[2], 100);
    }
    else if (rgb_color == 1) { //purple
      
      analogWrite(rgb_pins[0], 200);
      digitalWrite(rgb_pins[1], LOW);
      analogWrite(rgb_pins[2], 10);
    }
    else if (rgb_color == 2) { //red
      analogWrite(rgb_pins[0], 255);
      digitalWrite(rgb_pins[1], LOW);
      digitalWrite(rgb_pins[2], LOW);
    }
    else if (rgb_color == 3) { //green
      digitalWrite(rgb_pins[0], LOW);
      analogWrite(rgb_pins[1], 100);
      digitalWrite(rgb_pins[2], LOW);
    }
    else if (rgb_color == 4) { //white
      analogWrite(rgb_pins[0], 200);
      analogWrite(rgb_pins[1], 200);
      analogWrite(rgb_pins[2], 200);
    }
    Serial.println(rgb_color);
  }
  else {
    digitalWrite(rgb_pins[0], LOW);
    digitalWrite(rgb_pins[1], LOW);
    digitalWrite(rgb_pins[2], LOW);
  }
  if (!bigButton.get() && button_last == false) {
    if (mode == 0 && millis() - buttonTimer < 300) {
      solved_modules[2] = 1;
    }
    else if (mode == 1 && rgb_color == 0 && (timer / 60 == 3 || timer - (timer / 10) * 10 == 3 || timer % 60 / 10 == 3)) {
      solved_modules[2] = 1;
    }
    else if (mode == 1 && rgb_color == 1 && (timer / 60 + (timer - (timer / 10) * 10) == 8)) {
      solved_modules[2] = 1;
    }
    else if (mode == 1 && rgb_color == 2 && (timer / 60 + (timer - (timer / 10) * 10) + ( timer % 60 / 10)) % 2 == 0) {
      solved_modules[2] = 1;
    }
    else if (mode == 1 && (rgb_color == 3 || rgb_color == 4) && (timer / 60 + (timer - (timer / 10) * 10) + ( timer % 60 / 10)) % 2 == 0) { //TBU real thing
      solved_modules[2] = 1;
    }
    else {
      Serial.println(F("Button: error")); //ErrorPrint
      error();

    }
    button_last = true;
    buttonTimer = 9999999;
  }

}
