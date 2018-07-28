#ifndef Button_h
#define Button_h
#include <arduino.h>

class Button{
	private:
		uint8_t _pin;
		boolean _isPressed = false;
		uint8_t _inputMode = 1;
		
		unsigned long _timer;
		boolean _timerActive = false;
		int _delayPulse = 100;
		
		boolean _lastPress = false;
		boolean _state = false;
		void updatePressed(){
			_isPressed = digitalRead(_pin);
		}
	public:
		Button(int pin, uint8_t inputMode){
			if(inputMode != INPUT && inputMode != INPUT_PULLUP)
				#error invalid inputMode
			
			_inputMode = inputMode;
			_pin = pin;
			pinMode(_pin, _inputMode);
		}
		
		//updates the digitalRead aswell
		void update(){
			updateFast();
			if(getPulse())
				if(_lastPress==false){
					_state = !_state;
					_lastPress=true;
				}
			else
				_lastPress = false;
		}
		//gets called constantly
		void updateFast(){
			pulseTimer();
		}
		//starts the delay for the pulse
		void pulseTimer(){
			updatePressed();
			if(_isPressed && !_timerActive){
				_timer = millis();
				_timerActive = true;
			}
		}
		
		//checks if the pulse returned a positive 
		boolean getPulse(){
			if(_timerActive && millis() - _timer > _delayPulse){
				updatePressed();
				if(_isPressed){
					return true;
				}
				else{
					_timerActive = false;
				}
			}
		}
		//gets the raw value of the button
		boolean getRaw(){
			updatePressed();
			return _isPressed;
		}	
		void setState(boolean state){
			_state = state;
		}
		boolean getState(){
			return _state;
		}
	
};

#endif