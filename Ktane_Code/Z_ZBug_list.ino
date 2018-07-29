/*ADD comments(like this for instance!)
 V fix i2c once and for all some how (just try re installing everything again, using two new pins as i2c or using a smart i2c library) (maybe did it by pulling out the voltage, starting and re starting but not sure)
 * fast digitalWrite/using rpi for calculations (rpi c)
 * symbols
 * maybe another module who knows (three button needy / regular module and more wires
 ? fix morse pulsing
 V add decimals to timer in case of last second win
 * maybe add strike numbers again
 * Check all of the tbu like wires 5 & 6.
 * fix rgb pulsing
 * put in one place all the variables i can change per game & add some (like DIFFICULTY)
 * ???
 * profit
 */

/* List by order of what i should actually do:

 *  Maze: get a new 8x8 led. DONE
 *        Test it out
 * Wires: Add 5 and 6 wires
 * Button: Make colors more clear.
 *         calculate resistors  
 * Timer: 
 *      add the leds for the STRIKES
        maybe add striked numbers again (makes button really fucking hard, would recommend to check first if its intuitive, but the alphabet letters should be removed completely) 
 *         Try and make random more random by:
 *               A) installing a library that does shit for you
 *               B) adding a potentiometer to A0 and just spin it around
 *               C) use the current date/time at randomSeed()
 *         Speaking of which you(i) can make it less random by: (note this mostly talks about wires and button)
 *               A) removing unnecesiary options
 *               B) weighted randoms (like preffering specific amounts of wires per say)
 *               C) alot of pre built situations and you randomize betrween them. 
 *               D) a more complicaded random where you have some built in and the rest you randomize but make sure they dont affect the situation.(hardest) (pre determined two red wires, the rest are random non reds)
 *        Add the extra add ons to the bomb:
 *              1) ports.
 *              2) Serial.
 *              3) different types of batteries
 *        Possible extras include:
 *              A) those LIT indicators
 *              B) a voltage switch of 10V 5V and 3V
 *        adding these and trying to implement them further on in the bomb (3v could make leds turn off, adding generally alot of switching around in the game)
 * after everything is done you add:
 * Difficulties: one of the following
 *        A) an int that controls the intensity of the games.
 *        B) missions: unique games like in the original bomb EG: NEEDY module on 20 seconds, 2 STRIKES at start, harder randoms, wires only, 
 *        C) add misc things to the mix like walky talkies or alarms.
 * once the coding side is done:
 * Manual:
 *      write down an orginised final version of the rules
 *      find out how pdf is converted to html
 *      Scan symbols, create drawings of each module, make a rip off logo, find a font
 *      add noise to the photos.
 *      Make a manual for setting up the bomb.
 * Building:
 *      Try out what scale works for the bomb
 *      Buy a box from plastelina
 *      maybe model things in cad beforehand (more interesting wires setup)
 *      sketch the whole thing before with a pencil of the locations.
 *      find ports.
 *      
 */
 /*
  * When adding something new make sure to:
  * A. add the pin in the variables.
  * B. pinMode in setup.
  * C. create a function in a new tab.
  * D. turn it off in End tab
  * E. add it in the correct array.
  * F.add the function in the loop.
  */

  /* Markers:
   *  TBU: things to add later on
   *  ErrorPrint: printing when an error happens. should be removed later on.
   */



/*
 * REVISITING THE ARDUINO:
 * Electronics:
 ?      Rework it all???
 ?      color code the wires?
 *      Find correct resistors for the RGB
 *      Use pullups for all inputs
 *      connect the 8x8 matrix to the i2c
 *      fix the timer
 * Programming:
 *      clean up the code
 *      use github
 *      change the maze code to be i2c
 *      fix the button.cpp
 *      fix the missing second glitch
 */


