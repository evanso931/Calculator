/* keypad.h
 * Reads Keypad input
 * Author: Benjamin Evans
 * Date: Jan 2020
 */

#ifndef KEYPAD_H
#define KEYPAD_H


// Included Headers ----------------------------------------------------------------

#include <DeviceDependent.h>


// Forward Declarations ------------------------------------------------------------

/** Finds which key is pressed on the keypad by comparing rows and columns
  * Return: The Pressed Key
  */
char Read_Keypad();

/** Finds the Row of the pressed key
  * Return: Row Number
  */
int Check_Keypad_Row();

/** Finds the column of the pressed key
  * Return: Column Number
  */
int Check_Keypad_Column();


#endif
