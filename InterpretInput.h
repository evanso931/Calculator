/* InterpretInput.h
 * Interprets the Keypads Input
 * Author: Benjamin Evans
 * Date: Jan 2020
 */

#ifndef INTERPRETINPUT_H
#define INTERPRETINPUT_H


// Included Headers ---------------------------------------------------------------

#include <string.h>
#include <Calculations.h>
#include <Keypad.h>
#include <LCD.h>
#include <PLL.h>
#include <DeviceDependent.h>



// Forward Declarations ------------------------------------------------------------

/** Runs the calculator */
void Run_Calculator();

/** Copys the Input char array to the buffer input array
  * Param: buffer
  */
void Get_Input(char *buffer);

/** Stops a key being double pressed when held down */
void Stop_Double_Press();

/** Prints and adds the equivalent character of the pressed key to Input array or runs the key function
  * Param: Key
  */
void Keypad_To_Input(char Key);

/** Checks if a answer has been printed to the screen. Then when next button is pressed it clears the display and resets the flag
  * Param: Ans_FLag
  */
void Check_Printed_Answer(int Ans_Flag);

/** Toggles shift flag and LED */
void Toggle_Shift();

/** Deletes the last character on the display and the input array */
void Rubout_Last_Character();

/** Clears the display and input array */
void Clear_Display();

/** Shifts all the inputs on the display to left by 1 when inputs reach the end of the first line */
void Shift_Display();

#endif
