#include <arduino.h>
//Joystick class. the joystick classes work by turning the values of the pins into a binary number. it then takes a binary number and returns a location of that number from left to right
class Joystick {
  protected:
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int currVal = B0000;
  public:
  byte getPos() = 0;
  byte getRaw() = 0;
};
class Joystick_TwoWay : public Joystick {
  private:
    byte list[7] = {B110, B100, B101, B001, B011, B010, B000};
  public:
    Joystick_TwoWay(int pin1, int pin2, int pin3) {
      _pin1 = pin1;
      _pin2 = pin2;
      _pin3 = pin3;

    }

    byte getPos() override {
      currVal = digitalRead(_pin1) * 4 + digitalRead(_pin2) * 2 + digitalRead(_pin3);
      for (int l = 0; l < 7; l++) {
        if (list[l] == currVal)
          return 6 - l;
      }
      return 0;
    }
    byte getRaw() override {
      currVal = digitalRead(_pin1) * 4 + digitalRead(_pin2) * 2 + digitalRead(_pin3);
      return currVal;
    }
};

class Joystick_Lever : public Joystick {
  private:
    byte list[15] = {B0010, B0000, B1000, B1010, B1110, B1100, B1101, B1001, B1011, B0011, B0001, B0101, B0100, B0110, B0111};
  public:
    Joystick_Lever(int pin1, int pin2, int pin3, int pin4) {
      _pin1 = pin1;
      _pin2 = pin2;
      _pin3 = pin3;
      _pin4 = pin4;
    }

    byte getPos() override {
      currVal = digitalRead(_pin1) * 8 + digitalRead(_pin2) * 4 + digitalRead(_pin3) * 2 + digitalRead(_pin4);
      for (int l = 0; l < 15; l++) {
        if (list[l] == currVal)
          return l;
      }
      return 0;
    }
    byte getRaw() override {
      currVal = digitalRead(_pin1) * 8 + digitalRead(_pin2) * 4 + digitalRead(_pin3) * 2 + digitalRead(_pin4);
      return currVal;
    }
};



