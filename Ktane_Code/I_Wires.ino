void simpleWires() {
  for (int i = 0; i < 4; i++) { //TBU 6

    if (wires_IO[i] == 3) {
      if (digitalRead(wires_pins[i]) == 0) {
        if (wire_cut == false) {

          wireTimer = millisTimer;
          wire_cut = true;
        }
      }
      if (millisTimer - wireTimer > 550) {
        boolean werror = false;
        for (int a = 0; a < 6; a++) {
          if (wires_IO[a] == 3) {
            if (digitalRead(wires_pins[a]) == 1) {
              werror = true;

            }
            else {

              wires_IO[a] = 0;
            }
          }
        }
        if (werror == true) {
          Serial.println(F("Wires: Multiple"));
          wireTimer = 4294960000;
          error();
          werror = false;
          wire_cut = false;
        }
        else {
          solved_modules[0] = 1;
        }
      }
    }
    else if (wires_IO[i] == 2) {
      if (digitalRead(wires_pins[i]) == 0) {
        solved_modules[0] = 1;
      }
    }
    else {
      if (digitalRead(wires_pins[i]) != wires_IO[i]) {
        Serial.print(F("Wires: ")); Serial.println(i + 1);
        error();
        wires_IO[i] = digitalRead(wires_pins[i]);
      }
    }
  }
}
/*
  void numberWrite(int num, int arr[7], int STRIKESdone) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(arr[i], LOW);
  }
  switch (STRIKESdone) {
    case 0:
      switch (num) {
        case 0:
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
        case 1:
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          break;
        case 2:
          digitalWrite(arr[0], HIGH);                                               //  ________________
          digitalWrite(arr[1], HIGH);                                               // |                |\|
          digitalWrite(arr[6], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[4], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[3], HIGH);                                               // |  |          |  | |
          break;                                                                    // |  |          |  | |
        case 3:                                                                     // |  `----------|  | |
          digitalWrite(arr[0], HIGH);                                               // |             |  | |
          digitalWrite(arr[1], HIGH);                                               // |             |  | |
          digitalWrite(arr[2], HIGH);                                               // |             |  | |
          digitalWrite(arr[3], HIGH);                                               // |             |  | |
          digitalWrite(arr[6], HIGH);                                               // |________________| |
          break;                                                                    //  \______   _______\|
        case 4:
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[6], HIGH);
          break;
        case 5:
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[3], HIGH);
          break;
        case 6:
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
        case 7:
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          break;
        case 8:
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
        case 9:
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
      }
      break;
    case 1:
      switch (num) {
        case 0:
          digitalWrite(arr[6], HIGH);
          break;
        case 1:
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[0], HIGH);

          break;                                                                    //  ________________
        case 2:                                                                     // |   __________   |\|
          // |                | |
          digitalWrite(arr[5], HIGH);                                               // |                | |
          digitalWrite(arr[2], HIGH);                                               // |                | |
          break;                                                                    // |                | |
        case 3:                                                                     // |  |             | |
          digitalWrite(arr[4], HIGH);                                               // |  |             | |
          digitalWrite(arr[5], HIGH);                                               // |  |             | |
          digitalWrite(arr[4], HIGH);                                               // |  |             | |
          digitalWrite(arr[5], HIGH);                                               // |  |__________   | |
          digitalWrite(arr[4], HIGH);                                               // |________________| |
          break;                                                                    //  \______   _______\|
        case 4:
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          break;
        case 5:
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[4], HIGH);
          break;
        case 6:
          digitalWrite(arr[1], HIGH);
          break;
        case 7:
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[6], HIGH);
          break;
        case 8:
          break;
        case 9:
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[3], HIGH);
          break;
      }
      break;

    case 2:
      switch (num) {
        case 1:  //A
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[6], HIGH);
          break;
        case 9://i
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[4], HIGH);
          break;
        case 4: //d

          digitalWrite(arr[1], HIGH);                                               //  ________________
          digitalWrite(arr[2], HIGH);                                               // |   __________   |\|
          digitalWrite(arr[3], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[4], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[6], HIGH);                                               // |  |          |  | |
          break;                                                                    // |  |          |  | |
        case 5:  //E                                                                // |  `----------|  | |
          digitalWrite(arr[0], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[4], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[5], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[3], HIGH);                                               // |  |          |  | |
          digitalWrite(arr[6], HIGH);                                               // |________________| |
          break;                                                                    //  \______   _______\|
        case 6://F
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[6], HIGH);
          break;
        case 3: //c
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[3], HIGH);
          break;
        case 8://h

          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
        case 0://j
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[4], HIGH);
          break;
        case 2:  //b
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[3], HIGH);
          digitalWrite(arr[4], HIGH);
          digitalWrite(arr[5], HIGH);
          break;
        case 7://g
          digitalWrite(arr[6], HIGH);
          digitalWrite(arr[0], HIGH);
          digitalWrite(arr[1], HIGH);
          digitalWrite(arr[2], HIGH);
          digitalWrite(arr[5], HIGH);
          digitalWrite(arr[3], HIGH);
          break;
      }
  }
  }*/
