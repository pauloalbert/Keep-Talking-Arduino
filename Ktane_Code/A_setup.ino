void setup() {

  //* * Randomize and start * *
  // |||||||||||||||||||||||||||||||PINMODES|||||||||||||||||||||||||||||||||||||

  Serial.begin(9600);  
  Serial.println("STARTING THE BOMB...");
  clockDisplay.begin(DISPLAY_ADDRESS);
  randomSeed(analogRead(A7));

  // Output the wires:
  pinMode(buzzer_pin, OUTPUT);

  pinModeGroup(wires_pins, INPUT);

  pinModeGroup(matrix_pins_row, OUTPUT);
  pinModeGroup(matrix_pins_row, OUTPUT);
  pinModeGroup(matrix_arrows, INPUT);

  pinModeGroup(rgb_pins, OUTPUT);
  pinMode(button_pin, INPUT);

  pinMode(morse_button_pin, INPUT);
  pinMode(morse_led_pin, OUTPUT);
  pinMode(morse_buzzer_pin, OUTPUT);

  pinModeGroup(Symbol_button_pin, INPUT);

  pinModeGroup(lever_pins, INPUT);
  pinModeGroup(lever_led_pins, OUTPUT);


  //
  // |||||||||||||||||||||||||||||||Game randomizers|||||||||||||||||||||||||||||||||||||
  morse_wordNum = random(0, (sizeof(words) / sizeof(words[0])) / 2) * 2;      //returns a random number between 0 and the last word in intervals of 2.
  maze_number = random(0, 6);                                                 //maze index
  batteryCount = constrain(random(0, 5) - 1, 0, 4);                           //bomb count
  serial = serial_possibilities[random(6)];                                   //serial index
  simple_wire_count = random(2, 4) + 1; //TBU random(2,6)                       simple wire index
  //simple_wire_count = 4;
  button_color = button_colors[random(5)];                                    //button color
  button_label = button_labels[round(random(700) / 100)];                     //button label
  do {
    playerx = random(1, 8); //TBU random(1,8);
    playery = random(1, 8);
  } while (maze_options[maze_number][playery * 2][playerx * 2] != 3);
  int goalx;
  int goaly;
  do {
    goalx = random(8);
    goaly = random(8);
  } while (maze_options[maze_number][goaly * 2][goalx * 2] != 3 || abs(goaly - playery) < 3 || abs(goalx - playerx) < 3);
  maze_options[maze_number][goaly * 2][goalx * 2] = 5;

  // |||||||||||||||||||||||||||||||Morse initialization & Randomization|||||||||||||||||||||||||||||||||||
  message = words[morse_wordNum];
  response = words[morse_wordNum + 1];

  morse_char_to_index(message,false).toCharArray(lineDot2, morse_char_to_index(message,false).length() + 1);
  morse_char_to_index(response,false).toCharArray(lineDot2, morse_char_to_index(response,false).length() + 1);


  int orange = 0;
  switch (simple_wire_count) {
    case 3:
      for (int c = 0; c < simple_wire_count; c++) {
        wires_layout[c] = wires_colors[random(0, 4)]; //excluding red for now
      }

      for (int o = 0; o < 6; o++) {
        if (wires_layout[o] == "Orange")
          orange++;
      }
      if (orange == 0) {
        int temp_wires[6] = {2, 1, 1, 0, 0, 0};
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (wires_layout[3] == "Black") {
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
      for (int c = 0; c < simple_wire_count; c++) {
        wires_layout[c] = wires_colors[random(0, 5)]; //excluding red for now
      }
      int red = 0;
      int blue = 0;
      int yellow = 0;
      int red_pos = 0;
      int yellow_locs[6] = {1, 1, 1, 1, 0, 0};
      for (int o = 0; o < 6; o++) {
        if (wires_layout[o] == "Red") {
          red++;
          red_pos = o;
        }

        else if (wires_layout[o] == "Yellow") {
          yellow_locs[o] = 3;
          yellow++;
        }
        else if (wires_layout[o] == "Blue") {
          blue++;
        }
      }

      if (red > 1 && 1 == 1) { //TBU Serial
        int temp_wires[6] = {1, 1, 1, 1, 0, 0};
        temp_wires[red_pos] = 2;
        arrayCopy(wires_IO, temp_wires, 6);
      }
      else if (red == 0 && wires_layout[3] == "Yellow") {
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
  if (!(button_color == "Blue" && button_label == "Abort") && !(batteryCount > 1 && button_label == "") && !(button_color == "Red" && 1 == 609) && (button_label == "DickButt")) { //TBU same port 
    solved_beep[2] = 1;
    solved_modules[2] = 1;
  }
  colrow = random(14);
  if (colrow >= 7) {
    symbol_row = colrow % 7;
    for (int i = 0; i < 4; i++) {
      boolean check;
      do {
        check = false;
        symbol_col = random(symbol_array_size);
        for (int L = 0; L < i; L++) {
          if (symbol_array[symbol_row][symbol_col] == chosen_symbols[L])
            check = true;
        }
      } while (check);
      chosen_symbols[i] = symbol_array[symbol_row][symbol_col];
    }
  }
  else {
    symbol_col = colrow;
    for (int i = 0; i < 4; i++) {
      boolean check;
      do {
        check = false;
        symbol_row = random(symbol_array_size);
        for (int L = 0; L < i; L++) {
          if (symbol_array[symbol_row][symbol_col] == chosen_symbols[L])
            check = true;
        }
      } while (check);
      chosen_symbols[i] = symbol_array[symbol_row][symbol_col];
    }
  }
  int locTemp = 0;
  if (colrow < 7) {
    for (int row = 0; row < symbol_array_size; row++) {
      for (int l = 0; l < 4; l++) {
        if (symbol_array[row][colrow] == chosen_symbols[l]) {
          chosen_symbols_order[locTemp] = l;
          locTemp++;
        }
      }
    }
  }
  else {
    for (int col = 0; col < symbol_array_size; col++) {
      for (int l = 0; l < 4; l++) {
        if (symbol_array[colrow % 7][col] == chosen_symbols[l]) {
          chosen_symbols_order[locTemp] = l;
          locTemp++;
        }
      }
    }
  }

  // |||||||||||||||||||||||||||||||PRINTING VARIABLES FOR SETUP|||||||||||||||||||||||||||||||||||||

  for (int c = 0; c < 6; c++) {
    Serial.println((String)(c + 1) + ":  Color - " + (String)wires_layout[c] + "  I/O: " + (String)wires_IO[c]);
  }
  Serial.println("Color: " + button_color + ", Label: \"" + button_label + "\"");
  if (colrow < 7)
    Serial.println("Col: " + (String)(colrow + 1));
  else
    Serial.println("Row: " + (String)(colrow % 7 + 1));
  for (int b = 0; b < 4; b++) {
    Serial.println((String)(b + 1) + ":  Symbol - " + (String)chosen_symbols[b]);

  }
  Serial.print("The order is: ");
  for ( int b = 0; b < 4; b++) {
    Serial.print(chosen_symbols[chosen_symbols_order[b]]);
    Serial.print(" ");
  }
  Serial.println(" ");
  Serial.println("Batteries: " + (String)batteryCount);
  Serial.println("Press on button when ready!");

}



void pinModeGroup(int[] pins, byte output) {
  for (int z = 0; z < (sizeof(pins) / sizeof(pins[0])); z++)
    pinMode(pins[z], output);

}

//This function recieves a message and returns an array of chars that are in morse. read_spaces decides whether spaces are ignored (for responses).
char[] morse_char_to_index(String message, boolean read_spaces) {
  
  char split_message[message.length()];      //creates a char array with the length of the string
  message.toLowerCase();                     //makes sure the string is in lower case
  message.toCharArray(split_message, message.length() + 1);  //splits the string into the char array
  
  for (int l = 0; l < message.length(); l++) {
    int letterInt;
    if ('a' <= split_message[l] && split_message[l] <= 'z')
      letterInt = split_message[l] - 'a';
    else if ('0' <= split_message[l] && split_message[l] <= '9')
      letterInt = split_message[l] - '0';
    else if (split_message[l] == '?')
      letterInt = 36;
    else if (split_message[l] == '!')
      letterInt = 37;
    else if (split_message[l] == ' ' && read_spaces)
      letterInt = 38;
    else
      letterInt = 39;

    morse_message += letters_to_morse[letterInt];
  }
  return morse_message;
}

