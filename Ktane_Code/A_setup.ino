void setup() {

  //* * Randomize and start * *
  // |||||||||||||||||||||||||||||||PINMODES|||||||||||||||||||||||||||||||||||||

  Serial.begin(9600);
  Serial.println(F("STARTING THE BOMB:"));

  Serial.println(F("[*] INITIALISING THE I2C BUS..."));
  clockDisplay.begin(DISPLAY_ADDRESS);
  matrix.begin(MATRIXRGB ? MAZE_RGB_ADDRESS : MAZE_ADDRESS);

  clockDisplay.setBrightness(MATRIX_BRIGHTNESS);
  clockDisplay.writeDisplay();

  matrix.fillScreen(0);
  matrix.setBrightness(MATRIX_BRIGHTNESS);
  matrix.setRotation(0);
  matrix.writeDisplay();

  Serial.println(F("[*] SETTING PINMODES..."));
  // Output the wires:
  pinMode(buzzer_pin, OUTPUT);

  pinModeGroup(wires_pins, INPUT);

  pinModeGroup(matrix_arrows, INPUT);

  pinModeGroup(rgb_pins, OUTPUT);
  pinMode(button_pin, INPUT);

  pinMode(morse_button_pin, INPUT);
  pinMode(morse_led_pin, OUTPUT);
  pinMode(morse_buzzer_pin, OUTPUT);

  pinModeGroup(Symbol_button_pin, INPUT);

  pinModeGroup(lever_pins, INPUT);
  pinModeGroup(lever_led_pins, OUTPUT);

  randomize_setup(-1);
  print_setup();

  Serial.println(F("[!] Starting up the KTaNE terminal"));
  Serial.println(F("[!] Type a command or write START to activate the bomb (write HELP for options)"));
  Serial.println(F("[!] Make sure to set monitor setting to \'Newline\'\n"));

  while (true) { //Terminal, gets user command, sends it to the 'terminal_commands()' function
    if (Serial.available() > 0) {
      char chr = Serial.read();
      if (chr != '\n')
        terminal_command += chr;
      else {
        terminal_commands(terminal_command);
        if (!terminal_exit)
          chr = "";
        terminal_command = "";
      }
    }
    if (terminal_exit)
      break;
  }
  if (MILLISTIMER) //If the mills timer is enabled the bomb ends at -1 instead of at 0, so the timer must go down by one to make up for the extra second.
    timer--;
  Serial.println(F("[!] Exiting terminal..."));
  Serial.println(F("Press on button when ready!"));
  //Terminal in the setup phase to disable modules and set times (functions: DISABLE , ENABLE , SET_TIME , SET_PRESET , SET_DIFFICULTY, GET_SEED, SET_HARDCORE, SET_NEEDY, SET_MILLIS_TIMER)
}



// |||||||||||||||||||||||||||||* * * * * * *|||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||* FUNCTIONS *|||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||* * * * * * *|||||||||||||||||||||||||||||||||||



//sets the pinmode for an array of pins
void pinModeGroup(byte pins[], byte output) {
  for (int z = 0; z < (sizeof(pins) / sizeof(pins[0])); z++)
    pinMode(pins[z], output);

}

//This function recieves a message, turns it into the index numbers for each letter, and turns it into a character array of numbers. read_spaces decides whether spaces are not ignored (for messages).
void morse_char_to_index(String message, boolean read_spaces, char write_array[]) {
  String index_message;
  message.toLowerCase(); //makes sure the string is in lower case

  for (int l = 0; l < message.length(); l++) {
    int letterInt;
    if ('a' <= message[l] && message[l] <= 'z')
      letterInt = message[l] - 'a';
    else if ('0' <= message[l] && message[l] <= '9')
      letterInt = message[l] - '0';
    else if (message[l] == '?')
      letterInt = 36;
    else if (message[l] == '!')
      letterInt = 37;
    else if (message[l] == ' ' && read_spaces)
      letterInt = 38;
    else
      letterInt = 39;

    index_message += letters_to_morse[letterInt];
    index_message += " ";
  }
  index_message.toCharArray(write_array, message.length());
}




void randomize_setup(int s) {
  seed = s;
  if (seed == -1)
    seed = analogRead(A7);
  randomSeed(seed);
  Serial.println(F("[*] RANDOMIZING VARIABLES AND SETTING UP MODULES..."));
  Serial.println(F("    > Getting indexes"));
  morse_wordNum = random(0, (sizeof(words) / sizeof(words[0])) / 2) * 2;      //returns a random number between 0 and the last word in intervals of 2.
  maze_number = random(0, 6);                                                 //maze index
  batteryCount = constrain(random(0, 5) - 1, 0, 4);                           //bomb count
  serial = serial_possibilities[random(6)];                                   //serial index
  simple_wire_count = random(2, 4) + 1; //TBU random(2,6)                       simple wire index
  //simple_wire_count = 4;
  button_color = button_colors[random(5)];                                    //button color
  button_label = button_labels[round(random(700) / 100)];                     //button label
  Serial.println(F("    > Setting up maze"));
  do {
    playerx = random(1, 8);
    playery = random(1, 8);
  } while (maze_options[maze_number][playery * 2][playerx * 2] != 3);
  int goalx;
  int goaly;
  do {
    goalx = random(8);
    goaly = random(8);
  } while (maze_options[maze_number][goaly * 2][goalx * 2] != 3 || abs(goaly - playery) < 3 || abs(goalx - playerx) < 3);
  maze_options[maze_number][goaly * 2][goalx * 2] = 5;

  Serial.println(F("    > Setting up morse"));
  // |||||||||||||||||||||||||||||||Morse initialization & Randomization|||||||||||||||||||||||||||||||||||
  morse_message = words[morse_wordNum];
  morse_response = words[morse_wordNum + 1];

  morse_char_to_index(morse_message, true, lineDot);
  morse_char_to_index(morse_response, false, lineDotRes);

  Serial.println(F("    > Setting up wires"));
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

  Serial.println(F("[*] DONE!"));
}

void print_setup() {
  Serial.print(F("The seed is: ")); Serial.println(seed);
  Serial.print(F("Modules: "));
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
  Serial.print(F("The order is: "));
  for ( int b = 0; b < 4; b++) {
    Serial.print(chosen_symbols[chosen_symbols_order[b]]);
    Serial.print(F(" "));
  }
  Serial.println(F(" "));
  Serial.println("Batteries: " + (String)batteryCount);
}
