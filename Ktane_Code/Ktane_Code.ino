 #include <TimeLib.h>

#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "Joystick.cpp"

/* How to activate:
   1.close Eventghost or Serial if open.
   2. upload the 'Ktane_Code' file to make sure
   it is on the newest version.
   3. open EventGhost.
   4. read the input serial from the eventghost
   and do as it says.
   5. flick the lever to 10V when 3. is done.
   6. don't die ;p*

  not neceserall
*/
 
//Changable values:
boolean millisTimer = true; //if to show the milliseconds once the timer hits 0:59

int timer = 300; //STARTING TIME IN SECONDS
boolean hardcore = false; //1 strike
boolean needy = true; //uses needy modules
int difficulty = 0; //Null

//General bomb:
// 1:Wires 2:Maze 3:Button 4:morse 5:Symbols
int solved_Beep[5] = {0, 1, 0, 0, 0}; //TMP {0,0,0,1,1}
int solved_Modules[5] = {0, 1, 0, 0, 0}; //TBU more
boolean solved = false; //Did the player win?
int strikes = 0;

enum {_10V, _5V, _33V} voltage = _10V;
String serialPossibilities[6] = {"E33BAP", "DAB", "C", "D", "E", "F"};
String serial;
int batteryCount;

boolean start = false;
boolean start_pressed = false;


// ~ ~ ~ ~ Possibilities: ~ ~ ~ ~ ~
static int Symbol_array[7][7] = { 
                           { 11, 24, 10,  7, 30,  2,  9}, 
                           { 28,  3, 27,  8, 15, 29,  7}, 
                           { 22, 25,  2, 11, 14, 24, 13}, 
                           { 21, 20,  6,  1,  8, 16,  4}, 
                           { 18, 15, 23, 12, 21, 19, 17},
                           { 17, 16, 22, 18,  1, 20,  6}, 
                           { 13, 23, 28, 10,  9, 26,  3}
                         };
int mazeOptions[6][15][15] = {{
    {3, 0, 3, 0, 3, 0, 3, 1, 3, 0, 3, 1, 3, 0, 3},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 1, 3, 1, 2, 1, 2, 1, 3},
    {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 3, 0, 3},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 3, 0, 3, 1, 3},
    {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 1, 3, 0, 3, 1, 3, 0, 3, 0, 3},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    {3, 1, 2, 1, 3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {3, 1, 2, 1, 2, 1, 3, 0, 3, 0, 3, 0, 3, 1, 0}
  },
  {
    {3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {3, 1, 3, 1, 2, 1, 3, 1, 3, 1, 2, 1, 3, 1, 3},
    {0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 2, 1, 0, 1, 0},
    {3, 1, 3, 1, 2, 1, 3, 1, 3, 1, 2, 1, 3, 1, 3},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {3, 1, 3, 0, 3, 1, 3, 1, 3, 1, 3, 0, 3, 1, 3},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 0, 3},
    {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
    {0, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
    {0, 1, 3, 0, 3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 0}
  },
  {
    {3, 0, 3, 0, 3, 1, 3, 1, 3, 1, 3, 0, 3, 0, 3},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    {3, 0, 3, 1, 3, 1, 3, 1, 3, 0, 3, 0, 3, 0, 3},
    {1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
    {3, 0, 3, 1, 3, 1, 3, 1, 3, 1, 3, 0, 3, 0, 3},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 1, 3, 0, 3, 1, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
    {3, 1, 3, 1, 3, 1, 2, 2, 2, 1, 3, 1, 3, 1, 3},
    {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
    {3, 1, 3, 1, 3, 1, 3, 0, 3, 1, 3, 1, 3, 0, 3},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    {3, 1, 3, 0, 3, 1, 3, 1, 3, 1, 3, 1, 2, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0},
    {3, 0, 3, 0, 3, 0, 3, 1, 3, 0, 3, 1, 2, 1, 0}
  }, {
    {3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {3, 0, 3, 1, 3, 0, 3, 1, 3, 0, 3, 0, 3, 0, 3},
    {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
    {3, 0, 3, 0, 3, 1, 3, 0, 3, 1, 2, 2, 2, 1, 3},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 2, 1, 0},
    {3, 1, 2, 1, 3, 0, 3, 1, 3, 0, 3, 1, 2, 1, 3},
    {0, 1, 2, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},
    {3, 1, 2, 2, 2, 1, 3, 0, 3, 1, 3, 0, 3, 1, 3},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {3, 0, 3, 0, 3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3},
    {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {3, 1, 3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 0}
  }, {
    {3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 0, 3, 1, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {3, 1, 3, 1, 2, 2, 2, 1, 3, 0, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 0},
    {3, 1, 3, 1, 3, 1, 2, 1, 3, 1, 3, 0, 3, 1, 3},
    {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0},
    {3, 1, 3, 0, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {3, 0, 3, 1, 3, 1, 3, 0, 3, 0, 3, 1, 3, 1, 3},
    {1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
    {2, 1, 3, 1, 3, 0, 3, 0, 3, 0, 3, 1, 3, 1, 0},
    {2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
    {2, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 0}
  }, {
    {3, 0, 3, 0, 3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    {3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 3, 1, 3, 0, 3},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 1, 3, 0, 3, 0, 3, 1, 2, 1, 3},
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0},
    {3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 2, 1, 3},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 0, 3, 1, 3, 1, 3, 0, 3},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {3, 1, 3, 0, 3, 0, 3, 0, 3, 0, 3, 1, 3, 1, 3},
    {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {3, 0, 3, 1, 2, 1, 3, 0, 3, 1, 3, 0, 3, 1, 0},
    {0, 1, 1, 1, 2, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
    {3, 1, 2, 2, 2, 1, 3, 1, 3, 0, 3, 0, 3, 1, 0}
  }
};
String wires_Colors[6] = {"Yellow", "Orange", "Black", "Blue", "Red", "White"}; 
String button_Colors[5] = {"Blue", "Red", "White", "Green", "Black"}; 
String button_Labels[] = {"", "", "Hold", "Abort", "Detonator", "Smash", "DickButt"};
String LettersToMorse[40] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000", "00", "0111", "101", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1", "001", "0001", "011", "1001", "1011", "1100", "11111", "01111", "00111", "00011", "00001", "00000", "10000", "11000", "11100", "11110", "001100", "101011", "2", ""};
String Words[] = {"Send help", "no", "Sos", "Sorry", "wire", "cut", "defuse", "bomb", "what?", "Sup", "West", "East", "Sorry", "What?", "Alt", "F4", "You know", "Ha ha!", "morse", "code", "3141", "592", "Cake", "Lie", "Webo", "Sass", "House", "City", "Bomb", "SOS", "Maze", "Move", "Hear", "speak", "mental", "again", "Hold", "Press", "Care", "que"};


//Wires; Maze; Button; Morse; Symbols; Lever
//all random, odds array timers, pins, general

//Clock:
int centiTimer=0;
boolean blinkColon = false;
#define DISPLAY_ADDRESS   0x70
Adafruit_7segment clockDisplay = Adafruit_7segment();

//Wires:
int simpleWireCount;
String wires_Layout[6]; //Color order that was chosen
int wires_IO[6]; //Which wires need to be cut
boolean wireCut;

//Maze:
int mazeNumber;
int playerx;
int playery;
int arrows_last[4];

//Button:
String button_Color;
String button_Label;
int mode; // 0 - press 1- hold 2 - leave
int rgb_Color; // 0 - blue 1-yellow 2-red 3-green 4-white.
boolean button_last = true;

//Morse
int morse_wordNum;
char lineDot[100];
char lineDot2[100];
String message, response, morse_message, morse_response;
int morse_loc = 0; //What character is the blinking on.
int morse_button_pin_loc = 0; //What character is the button on.
boolean clicked = false; //trigger.
boolean morse_start = false, morse_press = false;

//Symbols:
int colrow;
int Symbol_loc;
int chosen_Symbols[4];
int chosen_Symbols_order[4];
int Symbol_array_size = sizeof(Symbol_array) / sizeof(Symbol_array[0]);
int Symbol_col, Symbol_row;

//Lever:
int joystick_bits = 7; //seven for YY018B and fourteen for YY008A
const int lever_pins[4] = {36,39,38,41};
Joystick_TwoWay joystick = Joystick_TwoWay(lever_pins[1],lever_pins[2],lever_pins[3]);
//Joystick_Lever joystick = Joystick_Lever(lever_pins[0],lever_pins[1],lever_pins[2],lever_pins[3]);
boolean lever_Started = false;


// * * Timers * *
unsigned long timeTick;
unsigned long wireTimer = 4294960000;
unsigned long button_Timer = 9999999;
unsigned long timerB = 9999999;
int priorityB = 0;  //buzzer current priority
unsigned long startTime; // time in millis when the bomb started
unsigned long leverTimer; // reverse way of counting time.
unsigned long morse_timer;
unsigned long led_timer = 0;
unsigned long last_press;




// * * Wires * *
const int buzzer_pin = 3;
const int strike_pin[2] = {55,55};

const int wires_pins[6] = {14, 15, 16, 17, 55, 55}; 

const int matrix_arrows[4] = {6, 5, 7, 4};//left up right down
const int matrix_Pins_Row[8] = {27, 2, 31, 30, 22, 29, 24, 25}; //2 + 13 + 22-34
const int matrix_Pins_Col[8] = {13, 26, 28, 23, 33, 32, 18, 34};

const int rgb_pins[3] = {9, 11, 12};
const int button_pin = A0;

const int morse_button_pin = 37;
const int morse_led_pin = 35;
const int morse_buzzer_pin = 8;

const int Symbol_button_pin[4] = {47,46,45,44};


const int lever_leds_pins[4] = {8,19,40,10};



