void arrayCopy(int arrChange[], int arrEdit[], int sizes) {
  for (int i = 0 ; i < sizes; i++) {
    arrChange[i] = arrEdit[i];
  }
}
void buzzer(int priority, int pitch, int timer) {
  if (millisTimer > buzzerTimer)
    priorityB = 0;
  if (priority >= priorityB) {
    tone(buzzer_pin, pitch, timer);
    buzzerTimer = millisTimer + timer;
    priorityB = priority;
  }
}

String splitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

