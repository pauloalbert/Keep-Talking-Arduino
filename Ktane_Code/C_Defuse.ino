//if you manage to defuse the bomb
void save() { 
  SOLVED = true;
  for (int i = 0; i < sizeof(solved_modules) / sizeof(solved_modules[0]); i++) {
    if (solved_modules[i] == 0)
      SOLVED = false;
  }
  if (SOLVED) {
    End();
    Serial.println("SOLVED");
    delay(100);                                                                          
    exit(1);                                                                           
  }                                                                               
}         
