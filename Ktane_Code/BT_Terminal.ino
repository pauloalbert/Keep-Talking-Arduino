//Terminal in the setup phase to disable modules and set times (functions: DISABLE , ENABLE , SET_TIME , SET_DIFFICULTY, GET_SEED, SET_HARDCORE, SET_NEEDY, SET_MILLIS_TIMER,     HELP, PRINT_SETTINGS)
void terminal_commands(String cmd) {
  String command = splitString(cmd, " ", 0);
  String argument = splitString(cmd, " ", 1);
  String argument1 = splitString(cmd, " ", 2);
  command.toUpperCase();
  argument.toUpperCase();
  argument1.toUpperCase();
  if (command == "EXIT") {
    terminal_exit = true;
  }
  if (command == "START") {
    if (argument == "?" || argument == "HELP")
      Serial.println("[?] Start - stops the terminal and lets you start the bomb");
    else if (argument == "")
      terminal_exit = true;
    else
      Serial.println("[X] Error, unexpected argument sent");
  }

  if (command == "ENABLE") {
    if (argument == "WIRES" || argument == "MAZE" || argument == "BUTTON" || argument == "MORSE" || argument == "SYMBOLS") {
      toggle_module(argument, true);
      Serial.println("[@] Enabled the module " + argument);
    }
    else if (argument == "" || argument == "HELP" || argument == "?")
      Serial.println("[?] ENABLE [module name] - module names){ WIRES, MAZE, BUTTON, MORSE, SYMBOLS");
    else
      Serial.println("[X] Error, \'" + argument + "\' not recognized\n\tYou may enable the modules WIRES, MAZE, BUTTON, MORSE, SYMBOLS.");


  }

  if (command == "DISABLE") {
    if (argument == "WIRES" || argument == "MAZE" || argument == "BUTTON" || argument == "MORSE" || argument == "SYMBOLS") {
      toggle_module(argument, false);
      Serial.println("[@] Disabled the module " + argument);
    }
    else if (argument == "" || argument == "HELP" || argument == "?")
      Serial.println("[?] DISABLE [module name] - module names){ WIRES, MAZE, BUTTON, MORSE, SYMBOLS");
    else
      Serial.println("[X] Error, \'" + argument + "\' not recognized\n\tYou may disable the modules WIRES, MAZE, BUTTON, MORSE, SYMBOLS.");
  }


  if (command == "SET_TIME") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println("[?] SET_TIME [seconds] - set the time in seconds until the bomb explodes.");
    else
      timer = argument.toInt();
  }


  if ( command == "GET_SEED")
    Serial.println("[@] The current seed is){ " + seed);


  if (command == "RANDOMIZE") {
    if (argument == "?" || argument == "HELP")
      Serial.println("[?] RANDOMIZE [seed] - randomizes the bomb again. leave seed empty to create a new one.");
    else if (argument == "") {
      randomize_setup(-1);
      print_setup();
      Serial.println("[@] Randomizing bomb with new seed.");
    }
    else {
      seed = argument.toInt();
      randomize_setup(seed);
      Serial.println("[@] Randomizing bomb with the seed " + argument + ".");
    }
  }
  if ( command == "SET_NEEDY") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println("[?] SET_NEEDY [true/false] - enables or disables the needy modules.");
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        NEEDY = true;
        Serial.println("[@] Enabled needy modules.");

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        NEEDY = false;
        Serial.println("[@] Disabled needy modules.");

      }
    }
  }
  if ( command == "SET_HARDCORE") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println("[?] SET_HARDCORE [true/false] - enables or disables the hardcore mode.");
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        HARDCORE = true;
        Serial.println("[@] Enabled hardcore mode.");

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        HARDCORE = false;
        Serial.println("[@] Disabled hardcore mode.");

      }
    }
  }

  if (command == "SET_MILLIS_TIMER") {
    if (argument == "" || argument == "?" || argument == "HELP")
      Serial.println("[?] SET_MILLIS_TIMER [true/false] - when inabled the timer switches to [seconds){milliseconds] in the last minute.");
    else {
      if (argument == "TRUE" || argument == "T" || argument == "Y" || argument == "ofc") {
        MILLISTIMER = true;
        Serial.println("[@] Enabled millisecond timer.");

      }
      else if (argument == "FALSE" || argument == "F" || argument == "N" || argument == "hell no") {
        MILLISTIMER = false;
        Serial.println("[@] Disabled millisecond timer.");

      }
    }
  }

}


void toggle_module(String module, boolean enable) {
  module.toUpperCase();

  if (module == "WIRES") {
  solved_modules[0] = enable;
    solved_beep[0] = enable;
  }
  if (module  == "MAZE") {
  solved_modules[1] = enable;
    solved_beep[1] = enable;
  }
  if (module == "BUTTON") {
  solved_modules[2] = enable;
    solved_beep[2] = enable;
  }
  if (module == "MORSE") {
  solved_modules[3] = enable;
    solved_beep[3] = enable;
  }
  if (module == "SYMBOLS") {
  solved_modules[4] = enable;
    solved_beep[4] = enable;
  }

}


void toggle_module(int index, boolean enable) {
  solved_modules[index] = enable;
  solved_beep[index] = enable;
}
