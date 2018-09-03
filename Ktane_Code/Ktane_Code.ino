#include <Wire.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "Button.cpp"
#include "Joystick.cpp"

#define DISPLAY_ADDRESS 0x70
#define MAZE_ADDRESS 0x72
#define MAZE_RGB_ADDRESS 0x72
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
//Debugging values:
boolean MATRIXRGB = false;
Adafruit_8x8matrix matrix = Adafruit_8x8matrix(); //IF MATRIXRGB IS TRUE Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//Changable values:
boolean MILLISTIMER = true; //if to show the milliseconds once the timer hits 0:59
int timer = 300;            //STARTING TIME IN SECONDS
boolean HARDCORE = false;   //1 strike
boolean NEEDY = true;       //uses NEEDY modules
byte DIFFICULTY = 0;         //Null

//General bomb:
// 1:Wires 2:Maze 3:Button 4:morse 5:Symbols
byte solved_beep[5] = {0, 1, 0, 0, 0};     //TMP {0,0,0,1,1}
byte solved_modules[5] = {0, 1, 0, 0, 0};  //TBU more
byte SOLVED = false;                   //Did the player win?
int STRIKES = 0;

enum {_10V, _5V, _33V} voltage = _10V;   //null, future appendix TBU
String serial_possibilities[6] = {"E33BAP", "DAB", "C", "D", "E", "F"}; //null, future appendix
String serial;                            //the CHOSEN ONE
int batteryCount;                         //appendix value

boolean start = false;  //starting the code
boolean start_pressed = false; //if the start button is pressed

String terminal_command = ""; //stores the command text
boolean terminal_exit = false;

int seed = -1; //the seed that randomizes. set to -1 if not predefined

// ~ ~ ~ ~ Possibilities: ~ ~ ~ ~ ~
//Each number is assosiated a symbol
static int symbol_array[7][7] = {
  { 11, 24, 10,  7, 30,  2,  9},
  { 28,  3, 27,  8, 15, 29,  7},
  { 22, 25,  2, 11, 14, 24, 13},
  { 21, 20,  6,  1,  8, 16,  4},
  { 18, 15, 23, 12, 21, 19, 17},
  { 17, 16, 22, 18,  1, 20,  6},
  { 13, 23, 28, 10,  9, 26,  3}
};
int maze_options[6][15][15] = {{ //1:Wall, 2:Indicators(Circles), 3:Spaces you can walk on, 4:The player, 5:The goal(Triangle)
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
String wires_colors[6] = {"Yellow", "Orange", "Black", "Blue", "Red", "White"};
String button_colors[5] = {"Blue", "Red", "White", "Green", "Black"};
String button_labels[] = {"", "", "Hold", "Abort", "Detonator", "Smash", "DickButt"};
String letters_to_morse[40] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000", "00", "0111", "101", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1", "001", "0001", "011", "1001", "1011", "1100", "11111", "01111", "00111", "00011", "00001", "00000", "10000", "11000", "11100", "11110", "001100", "101011", "2", ""};
String words[] = {"Send help", "no", "Sos", "Sorry", "wire", "cut", "defuse", "bomb", "what?", "Sup", "West", "East", "Sorry", "What?", "Alt", "F4", "You know", "Ha ha!", "morse", "code", "3141", "592", "Cake", "Lie", "Webo", "Sass", "House", "City", "Bomb", "SOS", "Maze", "Move", "Hear", "speak", "mental", "again", "Hold", "Press", "Care", "que"};


//Wires; Maze; Button; Morse; Symbols; Lever
//all random, odds array timers, pins, general

//Clock:
int centiTimer = 0;
boolean BLINKCOLON = false;
#define DISPLAY_ADDRESS 0x70
#define DISPLAY_BRIGHTNESS 15
Adafruit_7segment clockDisplay = Adafruit_7segment();

//Wires:
int simple_wire_count;
String wires_layout[6]; //Color order that was chosen
int wires_IO[6]; //Which wires need to be cut
boolean wire_cut;       //Wire_cut

//Maze:
#define MATRIX_BRIGHTNESS 15
byte maze_number;
byte playerx;
byte playery;
byte arrows_last[4];

//Button:
String button_color;
String button_label;
int mode; // 0 - press 1- hold 2 - leave
int rgb_color; // 0 - blue 1-yellow 2-red 3-green 4-white.
boolean button_last = true;

//Morse
int morse_wordNum;
char lineDot[20]; //split chars of all morse message
char lineDotRes[20];//split chars of all morse response
String morse_message, morse_response;
int morse_loc = 0; //What character is the blinking on.
int morse_button_pin_loc = 0; //What character is the button on.
boolean clicked = false; //trigger.
boolean morse_start = false, morse_press = false;

//Symbols:
byte colrow;
byte symbol_loc; //index of the current symbol to press
byte chosen_symbols[4];
byte chosen_symbols_order[4];
int symbol_array_size = sizeof(symbol_array) / sizeof(symbol_array[0]);
byte symbol_col, symbol_row;

//Lever:
byte joystick_bits = 7; //seven for YY018B and fourteen for YY008A
const byte lever_pins[4] = {36, 39, 38, 41};    //pins (needed before creating the lever)
Joystick_TwoWay joystick = Joystick_TwoWay(lever_pins[1], lever_pins[2], lever_pins[3]);
//Joystick_Lever joystick = Joystick_Lever(lever_pins[0],lever_pins[1],lever_pins[2],lever_pins[3]);
boolean lever_started = false;


// * * Timers * *
unsigned long timeTick;
unsigned long wireTimer = 4294960000;
unsigned long buttonTimer = 9999999;
unsigned long buzzerTimer = 9999999;
int priorityB = 0;  //buzzer current priority
unsigned long startTime; // time in millis when the bomb started
unsigned long leverTimer; // reverse way of counting time.
unsigned long morseTimer;
unsigned long ledTimer = 0;
unsigned long last_press;




// * * Wires * *
const byte buzzer_pin = 3;
const byte strike_pin[2] = {55, 55};

const byte wires_pins[6] = {14, 15, 16, 17, 55, 55};

const byte matrix_arrows[4] = {6, 5, 7, 4};//left up right down

const byte rgb_pins[3] = {9, 11, 12};
const byte button_pin = 30;

const byte morse_button_pin = 37;
const byte morse_led_pin = 35;
const byte morse_buzzer_pin = 8;

const byte Symbol_button_pin[4] = {47, 46, 45, 44};


const byte lever_led_pins[4] = {8, 19, 40, 10};



