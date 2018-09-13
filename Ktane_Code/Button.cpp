#ifndef Button_h
#define Button_h
#include <arduino.h>

class Button {
  private:
    byte _pin;
    boolean _realState = false;
  boolean _pulseState = false;
    byte _inputMode = 1;

    unsigned long _timer;
    boolean _timerActive = false;
    int _delayPulse = 100;

    void _updatePressed() {
      _realState = digitalRead(_pin);
    }
  public:
    Button(int pin, byte inputMode) {
      _inputMode = inputMode;
      _pin = pin;
      pinMode(_pin, _inputMode);
    }

  
    void update() {
    _updatePressed();
    if(!_timerActive){
      _pulseState = false;
      if(_realState){
        _timer = millis();
        _timerActive = true;
      }
    }
    else if(_timerActive && millis() - _timer > _delayPulse){
      if(_realState)
        _pulseState = true;
      else
        _timerActive = false;
    }
    }

    //checks if the pulse returned a positive
    boolean get() {
      return _pulseState;
    }
    //gets the raw value of the button
    boolean getRaw() {
      _updatePressed();
      return _realState;
    }
};

#endif
