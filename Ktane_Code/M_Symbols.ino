boolean Symbol_pressed = false;
void Symbols() {
  if (Symbol_pressed) {
    Symbol_pressed = false;
    for (int i = 0 ; i < 4; i ++) {
      if (digitalRead(Symbol_button_pin[i]) == HIGH) {
        Symbol_pressed = true;
      }
    }
  }
  for (int i = 0 ; i < 4; i ++) {
    if (digitalRead(Symbol_button_pin[i]) == HIGH && solved_modules[4] != 1 && !Symbol_pressed) {
      Symbol_pressed = true;

      if (chosen_symbols_order[Symbol_loc] == i) {
        Symbol_loc++;
        if (Symbol_loc == 4) {
          solved_modules[4] = 1;
        }

      }
      else {
        error();

        Serial.println("Button: error " + String(i)); //ErrorPrint
        Symbol_loc = 0;
      }
    }
  }

}

