void setup() {


  //* * Randomize and start * *
  // |||||||||||||||||||||||||||||||PINMODES|||||||||||||||||||||||||||||||||||||

  Serial.begin(9600);
  Serial.println("STARTING THE BOMB...");
  clockDisplay.begin(DISPLAY_ADDRESS);
  // Output the wires:
  pinMode(buzzer_pin, OUTPUT);
  randomSeed(analogRead(A7));
  for (int z = 0; z < (sizeof(wires_pins) / sizeof(wires_pins[0])); z++) 
    pinMode(wires_pins[z], INPUT);
  
  for (int z = 0; z < (sizeof(matrix_Pins_Row) / sizeof(matrix_Pins_Row[0])); z++) 
    pinMode(matrix_Pins_Row[z], OUTPUT);   
  for (int z = 0; z < (sizeof(matrix_Pins_Col) / sizeof(matrix_Pins_Col[0])); z++) 
    pinMode(matrix_Pins_Col[z], OUTPUT); 
  for (int z = 0; z < (sizeof(matrix_arrows) / sizeof(matrix_arrows[0])); z++)
    pinMode(matrix_arrows[z], INPUT);


  for (int z = 0; z < (sizeof(rgb_pins) / sizeof(rgb_pins[0])); z++) 
    pinMode(rgb_pins[z], OUTPUT);  
  pinMode(button_pin, INPUT);

  pinMode(morse_button_pin, INPUT);
  pinMode(morse_led_pin, OUTPUT);
  pinMode(morse_buzzer_pin, OUTPUT);

  for (int z = 0; z < (sizeof(Symbol_button_pin) / sizeof(Symbol_button_pin[0])); z++) 
    pinMode(Symbol_button_pin[z], INPUT);
    
  for (int z = 0; z < (sizeof(lever_pins) / sizeof(lever_pins[0])); z++) 
    pinMode(lever_pins[z], INPUT);
  for (int z = 0; z < (sizeof(lever_leds_pins) / sizeof(lever_leds_pins[0])); z++) 
    pinMode(lever_leds_pins[z], OUTPUT);
  


  //
  // |||||||||||||||||||||||||||||||Game randomizers|||||||||||||||||||||||||||||||||||||
  morse_wordNum = random(0, (sizeof(Words) / sizeof(Words[0])) / 2) * 2;
  mazeNumber = random(0, 6);
  batteryCount = constrain(random(0, 5) - 1, 0, 10);
  serial = serialPossibilities[random(6)];
  simpleWireCount = random(2, 4) + 1; //TBU random(2,6)
  //simpleWireCount = 4;
  button_Color = button_Colors[random(5)];
  button_Label = button_Labels[round(random(700) / 100)];
  do {
    playerx = random(1, 8); //TBU random(1,8);
    playery = random(1, 8);
  } while (mazeOptions[mazeNumber][playery * 2][playerx * 2] != 3);
  int goalx;
  int goaly;
  do {
    goalx = random(8);
    goaly = random(8);
  } while (mazeOptions[mazeNumber][goaly * 2][goalx * 2] != 3 || abs(goaly - playery) < 3 || abs(goalx - playerx) < 3);
  mazeOptions[mazeNumber][goaly * 2][goalx * 2] = 5;

  // |||||||||||||||||||||||||||||||Morse initialization & Randomization|||||||||||||||||||||||||||||||||||
  message = Words[morse_wordNum];
  response = Words[morse_wordNum + 1];
  message.toLowerCase();
  response.toLowerCase();
  char broken[message.length()];
  message.toCharArray(broken, message.length() + 1);
  for (int l = 0; l < message.length(); l++) {
    int letterInt;
    switch (broken[l]) {
      case 'a':
        letterInt = 0;
        break;
      case 'b':
        letterInt = 1;
        break;
      case 'c':
        letterInt = 2;
        break;
      case 'd':
        letterInt = 3;
        break;
      case 'e':
        letterInt = 4;
        break;
      case 'f':
        letterInt = 5;
        break;
      case 'g':
        letterInt = 6;
        break;
      case 'h':
        letterInt = 7;
        break;
      case 'i':
        letterInt = 8;
        break;
      case 'j':
        letterInt = 9;
        break;
      case 'k':
        letterInt = 10;
        break;
      case 'l':
        letterInt = 11;
        break;
      case 'm':
        letterInt = 12;
        break;
      case 'n':
        letterInt = 13;
        break;
      case 'o':
        letterInt = 14;
        break;
      case 'p':
        letterInt = 15;
        break;
      case 'q':
        letterInt = 16;
        break;
      case 'r':
        letterInt = 17;
        break;
      case 's':
        letterInt = 18;
        break;
      case 't':
        letterInt = 19;
        break;
      case 'u':
        letterInt = 20;
        break;
      case 'v':
        letterInt = 21;
        break;
      case 'w':
        letterInt = 22;
        break;
      case 'x':
        letterInt = 23;
        break;
      case 'y':
        letterInt = 24;
        break;
      case 'z':
        letterInt = 25;
        break;
      case '0':
        letterInt = 26;
        break;
      case '1':
        letterInt = 27;
        break;
      case '2':
        letterInt = 28;
        break;
      case '3':
        letterInt = 29;
        break;
      case '4':
        letterInt = 30;
        break;
      case '5':
        letterInt = 31;
        break;
      case '6':
        letterInt = 32;
        break;
      case '7':
        letterInt = 33;
        break;
      case '8':
        letterInt = 34;
        break;
      case '9':
        letterInt = 35;
        break;
      case '?':
        letterInt = 36;
        break;
      case '!':
        letterInt = 37;
        break;
      case ' ':
        letterInt = 38;
        break;
    }
    morse_message += LettersToMorse[letterInt];
    morse_message += " ";
  }
  morse_message.toCharArray(lineDot, morse_message.length() + 1);
  //BERLIN WALL OF THE RESPONES NESSAGE STUPID SENTANCE +++++++ (i think i wrote this because its a comment line between the message and the response. i was stupid two weeks ago)
  char broken2[response.length()];
  response.toCharArray(broken2, response.length() + 1);
  for (int l = 0; l < response.length(); l++) {
    int letterInt;
    switch (broken2[l]) {
      case 'a':
        letterInt = 0;
        break;
      case 'b':
        letterInt = 1;
        break;
      case 'c':
        letterInt = 2;
        break;
      case 'd':
        letterInt = 3;
        break;
      case 'e':
        letterInt = 4;
        break;
      case 'f':
        letterInt = 5;
        break;
      case 'g':
        letterInt = 6;
        break;
      case 'h':
        letterInt = 7;
        break;
      case 'i':
        letterInt = 8;
        break;
      case 'j':
        letterInt = 9;
        break;
      case 'k':
        letterInt = 10;
        break;
      case 'l':
        letterInt = 11;
        break;
      case 'm':
        letterInt = 12;
        break;
      case 'n':
        letterInt = 13;
        break;
      case 'o':
        letterInt = 14;
        break;
      case 'p':
        letterInt = 15;
        break;
      case 'q':
        letterInt = 16;
        break;
      case 'r':
        letterInt = 17;
        break;
      case 's':
        letterInt = 18;
        break;
      case 't':
        letterInt = 19;
        break;
      case 'u':
        letterInt = 20;
        break;
      case 'v':
        letterInt = 21;
        break;
      case 'w':
        letterInt = 22;
        break;
      case 'x':
        letterInt = 23;
        break;
      case 'y':
        letterInt = 24;
        break;
      case 'z':
        letterInt = 25;
        break;
      case '0':
        letterInt = 26;
        break;
      case '1':
        letterInt = 27;
        break;
      case '2':
        letterInt = 28;
        break;
      case '3':
        letterInt = 29;
        break;
      case '4':
        letterInt = 30;
        break;
      case '5':
        letterInt = 31;
        break;
      case '6':
        letterInt = 32;
        break;
      case '7':
        letterInt = 33;
        break;
      case '8':
        letterInt = 34;
        break;
      case '9':
        letterInt = 35;
        break;
      case '?':
        letterInt = 36;
        break;
      case '!':
        letterInt = 37;
        break;
      case ' ':
        letterInt = 39;
        break;
    }
    morse_response += LettersToMorse[letterInt];
  }
  morse_response.toCharArray(lineDot2, morse_response.length() + 1);


  int orange = 0;
  switch (simpleWireCount) {
    case 3:
      for (int c = 0; c < simpleWireCount; c++) {
        wires_Layout[c] = wires_Colors[random(0, 4)]; //excluding red for now
      }

      for (int o = 0; o < 6; o++) {
        if (wires_Layout[o] == "Orange")
          orange++;
      }
      if (orange == 0) {
        int temp_wires[6] = {2, 1, 1, 0, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (wires_Layout[3] == "Black") {
        int temp_wires[6] = {1, 2, 1, 0, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (4 == 42) { //TBU ADD PORT
        int temp_wires[6] = {1, 1, 2, 0, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else {
        int temp_wires[6] = {3, 3, 3, 0, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      break;

    case 4:
      for (int c = 0; c < simpleWireCount; c++) {
        wires_Layout[c] = wires_Colors[random(0, 5)]; //excluding red for now
      }
      int red = 0;
      int blue = 0;
      int yellow = 0;
      int red_pos = 0;
      int yellow_locs[6] = {1, 1, 1, 1, 0, 0};
      for (int o = 0; o < 6; o++) {
        if (wires_Layout[o] == "Red") {
          red++;
          red_pos = o;
        }

        else if (wires_Layout[o] == "Yellow") {
          yellow_locs[o] = 3;
          yellow++;
        }
        else if (wires_Layout[o] == "Blue") {
          blue++;
        }
      }

      if (red > 1 && 1 == 1) { //TBU Serial
        int temp_wires[6] = {1, 1, 1, 1, 0, 0};
        temp_wires[red_pos] = 2;
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (red == 0 && wires_Layout[3] == "Yellow") {
        int temp_wires[6] = {2, 1, 1, 1, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (blue == 1) {
        int temp_wires[6] = {1, 1, 2, 1, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (yellow > 1) {

        arrayCopy(wires_IO, yellow_locs, 6);
      }
      else {
        int temp_wires[6] = {1, 2, 1, 1, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      break;
  }
  if (batteryCount < 0) {
    batteryCount = 0;
  }
  if (!(button_Color == "Blue" && button_Label == "Abort") && !(batteryCount > 1 && button_Label == "") && !(button_Color == "Red" && 1 == 609) && (button_Label == "DickButt")) { //TBU same port
    solved_Beep[2] = 1;
    solved_Modules[2] = 1;
  }
  colrow = random(14);
  if (colrow >= 7) {
    Symbol_row = colrow % 7;
    for (int i = 0; i < 4; i++) {
      boolean check;
      do {
        check = false;
        Symbol_col = random(Symbol_array_size);
        for (int L = 0; L < i; L++) {
          if (Symbol_array[Symbol_row][Symbol_col] == chosen_Symbols[L])
            check = true;
        }
      } while (check);
      chosen_Symbols[i] = Symbol_array[Symbol_row][Symbol_col];
    }
  }
  else {
    Symbol_col = colrow;
    for (int i = 0; i < 4; i++) {
      boolean check;
      do {
        check = false;
        Symbol_row = random(Symbol_array_size);
        for (int L = 0; L < i; L++) {
          if (Symbol_array[Symbol_row][Symbol_col] == chosen_Symbols[L])
            check = true;
        }
      } while (check);
      chosen_Symbols[i] = Symbol_array[Symbol_row][Symbol_col];
    }
  }
  int locTemp = 0;
  if (colrow < 7) {
    for (int row = 0; row < Symbol_array_size; row++) {
      for (int l = 0; l < 4; l++) {
        if (Symbol_array[row][colrow] == chosen_Symbols[l]) {
          chosen_Symbols_order[locTemp] = l;
          locTemp++;
        }
      }
    }
  }
  else {
    for (int col = 0; col < Symbol_array_size; col++) {
      for (int l = 0; l < 4; l++) {
        if (Symbol_array[colrow % 7][col] == chosen_Symbols[l]) {
          chosen_Symbols_order[locTemp] = l;
          locTemp++;
        }
      }
    }
  }

  // |||||||||||||||||||||||||||||||PRINTING VARIABLES FOR SETUP|||||||||||||||||||||||||||||||||||||

  for (int c = 0; c < 6; c++) {
    Serial.println((String)(c + 1) + ":  Color - " + (String)wires_Layout[c] + "  I/O: " + (String)wires_IO[c]);
  }
  Serial.println("Color: " + button_Color + ", Label: \"" + button_Label + "\"");
  if (colrow < 7)
    Serial.println("Col: " + (String)(colrow + 1));
  else
    Serial.println("Row: " + (String)(colrow % 7 + 1));
  for (int b = 0; b < 4; b++) {
    Serial.println((String)(b + 1) + ":  Symbol - " + (String)chosen_Symbols[b]);

  }
  Serial.print("The order is: ");
  for ( int b = 0; b < 4; b++) {
    Serial.print(chosen_Symbols[chosen_Symbols_order[b]]);
    Serial.print(" ");
  }
  Serial.println(" ");
  Serial.println("Batteries: " + (String)batteryCount);
  Serial.println("Press on button when ready!");

}

void pinModeGroup(int[] pins, uint_8 output){
  for (int z = 0; z < (sizeof(pins) / sizeof(pins[0])); z++) 
    pinMode(pins[z], output);
  
}

