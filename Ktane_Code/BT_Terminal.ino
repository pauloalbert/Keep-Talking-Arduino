//Terminal in the setup phase to disable modules and set times (functions: DISABLE , ENABLE , SET_TIME , SET_DIFFICULTY, GET_SEED, SET_HARDCORE, SET_NEEDY, SET_MILLIS_TIMER,     HELP, PRINT_SETTINGS)
void terminal_commands(String cmd) {
  String commands[] = {"HELP", "DISPLAY", "START", "ENABLE", "DISABLE", "SET_TIME", "RANDOMIZE", "SET_NEEDY", "SET_HARDCORE", "SET_MILLIS_TIMER"};
  String command = splitString(cmd, ' ', 0);
  String argument = splitString(cmd, ' ', 1);
  String argument1 = splitString(cmd, ' ', 2);
  command.toUpperCase();
  argument.toUpperCase();
  argument1.toUpperCase();
  if (command == "HELP") {
    if (argument == "")
      Serial.println(F("[?] HELP [command] - displays a description for a command, leave empty for all commands."));
    if (argument == "DISPLAY" || argument == "")
      Serial.println(F("[?] DISPLAY/SETTINGS - shows the enabled settings"));
    if (argument == "START" || argument == "")
      Serial.println(F("[?] START/EXIT - stops the terminal and lets you start the bomb"));
    if (argument == "ENABLE" || argument == "")
      Serial.println(F("[?] ENABLE [module name] - module names: WIRES, MAZE, BUTTON, MORSE, SYMBOLS"));
    if (argument == "DISABLE" || argument == "")
      Serial.println(F("[?] DISABLE [module name] - module names: WIRES, MAZE, BUTTON, MORSE, SYMBOLS"));
    if (argument == "SET_TIME" || argument == "")
      Serial.println(F("[?] SET_TIME [seconds] - set the time in seconds until the bomb explodes."));
    if (argument == "RANDOMIZE" || argument == "")
      Serial.println(F("[?] RANDOMIZE [seed] - randomizes the bomb again. leave seed empty to create a new one."));
    if (argument == "SET_NEEDY" || argument == "")
      Serial.println(F("[?] SET_NEEDY [true/false] - enables or disables the needy modules."));
    if (argument == "SET_HARDCORE" || argument == "")
      Serial.println(F("[?] SET_HARDCORE [true/false] - enables or disables the hardcore mode."));
    if (argument == "SET_MILLIS_TIMER" || argument == "")
      Serial.println(F("[?] SET_MILLIS_TIMER [true/false] - when inabled the timer switches to [seconds){milliseconds] in the last minute."));
  }
  else if (command == "DISPLAY" || command == "SETTINGS") {
    Serial.println(F("[?] Module enabled status:"));
    Serial.print(F(" . ---> WIRES ")); Serial.println(solved_modules[0] == 0 ? "[V]" : "[X]");
    Serial.print(F(" . ---> MAZE ")); Serial.println(solved_modules[1] == 0 ? "[V]" : "[X]");
    Serial.print(F(" . ---> BUTTONS ")); Serial.println(solved_modules[2] == 0 ? "[V]" : "[X]");
    Serial.print(F(" . ---> MORSE ")); Serial.println(solved_modules[3] == 0 ? "[V]" : "[X]");
    Serial.print(F(" . ---> SYMBOLS ")); Serial.println(solved_modules[4] == 0 ? "[V]" : "[X]");
    Serial.print(F("[?] Bomb timer: ")); Serial.println(timer);
    Serial.print(F("[?] Hardcore enabled: ")); Serial.println(HARDCORE ? "[V]" : "[X]");
    Serial.println(F("[?] Bomb difficulty: Null"));                                          //TBU add difficulties
    Serial.print(F("[?] Bomb needy modules: ")); Serial.println(NEEDY ? "[V]" : "[X]");
    Serial.print(F("[?] Milliseconds enabled: ")); Serial.println(MILLISTIMER ? "[V]" : "[X]");
  }
  else if (command == "EXIT") {
    if (argument == "?" || argument == "HELP")
      Serial.println(F("[?] Start - stops the terminal and lets you start the bomb"));
    else if (argument == "")
      terminal_exit = true;
    else
      Serial.println(F("[X] Error, unexpected argument sent"));
  }

  else if (command == "START") {
    if (argument == "?" || argument == "HELP")
      Serial.println(F("[?] Start - stops the terminal and lets you start the bomb"));
    else if (argument == "")
      terminal_exit = true;
    else
      Serial.println(F("[X] Error, unexpected argument sent"));
  }

  else if (command == "ENABLE") {
    if (argument == "WIRES" || argument == "MAZE" || argument == "BUTTON" || argument == "MORSE" || argument == "SYMBOLS") {
      toggle_module(argument, true);
      Serial.print(F("[@] Enabled the module ")); Serial.println(argument);
    }
    else if (argument == "" || argument == "HELP" || argument == "?")
      Serial.println(F("[?] ENABLE [module name] - module names: WIRES, MAZE, BUTTON, MORSE, SYMBOLS"));
    else {
      Serial.print(F("[X] Error, \'")); Serial.print(argument); Serial.println(F("\' not recognized\n[?] You may enabled the modules WIRES, MAZE, BUTTON, MORSE, SYMBOLS."));
    }

  }

  else if (command == "DISABLE") {
    if (argument == "WIRES" || argument == "MAZE" || argument == "BUTTON" || argument == "MORSE" || argument == "SYMBOLS") {
      toggle_module(argument, false);
      Serial.print(F("[@] Disabled the module ")); Serial.println(argument);
    }
    else if (argument == "" || argument == "HELP" || argument == "?")
      Serial.println(F("[?] DISABLE [module name] - module names: WIRES, MAZE, BUTTON, MORSE, SYMBOLS"));
    else {
      Serial.print(F("[X] Error, \'")); Serial.print(argument); Serial.println(F("\' not recognized\n[?] You may disable the modules WIRES, MAZE, BUTTON, MORSE, SYMBOLS."));
    }
  }


  else if (command == "SET_TIME") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println(F("[?] SET_TIME [seconds] - set the time in seconds until the bomb explodes."));
    else if (argument.toInt() > 0)
      timer = argument.toInt();
    else
      Serial.println(F("Error: argument must be greater than 0"));

  }


  else if ( command == "GET_SEED") {
    Serial.print(F("[@] The current seed is: ")); Serial.println(seed);
  }

  else if (command == "RANDOMIZE") { //TBU make it actually work
    if (argument == "?" || argument == "HELP")
      Serial.println(F("[?] RANDOMIZE [seed] - randomizes the bomb again. leave seed empty to create a new one."));
    else if (argument == "") {
      randomize_setup(-1);
      print_setup();
      Serial.println(F("[@] Randomizing bomb with new seed."));
    }
    else {
      Serial.print(F("[@] Randomizing bomb with the seed ")); Serial.println(argument);

      seed = argument.toInt();
      randomize_setup(seed);
      print_setup();
    }
    Serial.println(F("[X] As of now RANDOMIZE [seed] doesn't create the same bomb twice"));
  }
  else if ( command == "SET_NEEDY") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println(F("[?] SET_NEEDY [true/false] - enables or disables the needy modules."));
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        NEEDY = true;
        Serial.println(F("[@] Enabled needy modules."));

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        NEEDY = false;
        Serial.println(F("[@] Disabled needy modules."));

      }
    }
  }
  else if ( command == "SET_HARDCORE") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println(F("[?] SET_HARDCORE [true/false] - enables or disables the hardcore mode."));
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        HARDCORE = true;
        Serial.println(F("[@] Enabled hardcore mode."));

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        HARDCORE = false;
        Serial.println(F("[@] Disabled hardcore mode."));

      }
    }
  }

  else if (command == "SET_MILLIS_TIMER") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println(F("[?] SET_MILLIS_TIMER [true/false] - when inabled the timer switches to [seconds){milliseconds] in the last minute."));
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        MILLISTIMER = true;
        Serial.println(F("[@] Enabled millisecond timer."));

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        MILLISTIMER = false;
        Serial.println(F("[@] Disabled millisecond timer."));

      }
    }
  }
  else{
    if(similar_command(command, commands) != "null"){
      Serial.print(F("[X]Unknown command. did you mean \'"));
      Serial.print(similar_command(command, commands));
      Serial.println(F("\'?"));
    }
    else
      Serial.println(F("[X]Unknown command"));
  }
  Serial.println(" ");
}


void toggle_module(String module, boolean enable) {
  module.toUpperCase();

  if (module == "WIRES") {
    solved_modules[0] = !enable;
    solved_beep[0] = !enable;
  }
  if (module  == "MAZE") {
    solved_modules[1] = !enable;
    solved_beep[1] = !enable;
  }
  if (module == "BUTTON") {
    solved_modules[2] = !enable;
    solved_beep[2] = !enable;
  }
  if (module == "MORSE") {
    solved_modules[3] = !enable;
    solved_beep[3] = !enable;
  }
  if (module == "SYMBOLS") {
    solved_modules[4] = !enable;
    solved_beep[4] = !enable;
  }

}


void toggle_module(int index, boolean enable) {
  solved_modules[index] = !enable;
  solved_beep[index] = !enable;
}


String similar_command(String s1, String s2[]) {
  for (int i = 0; i < sizeof(s2); i++) {
    int differentCount = 0;
    for (int c = 0; c < s2[i].length() && c < s1.length(); c++)
      if (s1.charAt(c) != s2[i].charAt(c) && s1.charAt(c) != (s2[i].length() > c + 1 ? s2[i].charAt(c+1) : s1.charAt(c)))
        differentCount++;
    if (differentCount <= 2 && abs(s2[i].length() - s1.length()) < 2) {
      return s2[i];
    }
  }
  return "null";
}

