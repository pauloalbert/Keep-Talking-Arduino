#ifndef Button_h
#define Button_h
#include <arduino.h>

class Button {
  private:
    byte _pin;  //the input pin the button is connected to.
    boolean _realState = false; //its free real estate.
    boolean _pulseState = false; //the calculated state of the button
    byte _inputMode = 1;      //0x01 = input, 0x02 = input_pullup


    unsigned long _releaseTimer; //counts the amount of time i released the button
    boolean _releaseActive = false;
    unsigned long _timer;
    boolean _timerActive = false;

    int _delayPulseRelease = 40;
    int _delayPulse = 40;

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
      if (!_timerActive) {
        _pulseState = false;
        if (_realState) {
          _timer = millis();
          _timerActive = true;
        }
      }
      else if (_timerActive && millis() - _timer > _delayPulse) {
        if (_realState)
          _pulseState = true;
        if (_pulseState) {
          if (!_realState) {
            _releaseTimer = millis();
            _releaseActive = true;
          }

          if (_releaseActive && millis() - _releaseTimer > _delayPulseRelease) {
            if (!_realState)
              _pulseState = false;
            _releaseActive = false;
          }
        }

        if (!_pulseState) {
          _timerActive = false;
          _releaseActive = false;
        }
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

    void setTimeout(int t){
      _delayPulse = t;
    }

    void setTimeoutRelease(int t){
      _delayPulseRelease = t;
    }
};

#endif
