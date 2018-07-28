//if you manage to defuse the bomb
void save() { 
  solved = true;
  for (int i = 0; i < sizeof(solved_Modules) / sizeof(solved_Modules[0]); i++) {
    if (solved_Modules[i] == 0)
      solved = false;
  }
  if (solved) {
    End();
    Serial.println("SOLVED);
    delay(100);                                                                          
    exit(1);                                                                           
  }                                                                               
}         
