#ifndef Button_h
#define Button_h
#include <arduino.h>
/****************************************************
 * 
 * Created by: PauloK
 * This program is copyright free, probably because nobody will use it
 * and i just added this part in to feel proffesional.
 * Feel free to modify this for your own personal use.
 * 
 * This class attempts to drown out spikes in the input caused by
 * the spring bouncing back within the button.
 * 
 * @param: pin - the digital pin the button is reading from.
 *         inputMode - 0x01: INPUT, 0x02: INPUTPULLUP  
 * 
 * boolean get(): returns the regulated state of the button.
 * 
 * boolean getRaw(): returns the raw state of the button.
 * 
 * void setTimeout(): sets the delay for drowning spikes of the button.
 * 
 * void setTimeoutRelease(): sets the delay for drowning reverse spikes
 * where the button sends 0 while held.
 * 
 ***************************************************/
class Button {
  private:
    byte _pin;  //the input pin the button is connected to.
    boolean _realState = false; //its free real estate.
    boolean _pulseState = false; //the calculated state of the button
    byte _inputMode = 1;      //0x01 = input, 0x02 = input_pullup


    unsigned long _releaseTimer; //counts the amount of time the button is pressed
    boolean _releaseActive = false; //tells whether the release timer is being used
    unsigned long _timer; //counts the amount of time since i pressed down the button.
    boolean _timerActive = false; //tells whether the timer is being used

    
    int _delayPulseRelease = 40; 
    int _delayPulse = 40;

    //updates the state of the pinread.
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
