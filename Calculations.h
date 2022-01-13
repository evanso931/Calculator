/* Calculations.h
 * Does the mathematical calculations of the calculator
 * Author: Benjamin Evans
 * Date: Jan 2020
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H


// Included Headers ------------------------------------------------------------

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <InterpretInput.h>
#include <LCD.h>


// Forward Declarations ------------------------------------------------------------

/** Converts the input char array into an array of float values and operators*/
void Input_Conversion();

/** Checks for invalid inputs and sets a flag if detected
 * Return: Invalid input flag
 */
int Invalid_Inputs();

/** Checks for valid input, prints answer if there is and resets the arrays for next calculation */
void Print_Answer();

/** Does the nested calculations */
void Calculation();

/** Shifts the elements after the current operator and operated numbers to the left in their arrays
 * Param: Operator Position
 */
void Shift_Arrays(int Operator_Position);

/** Searches for the position of the operator in the operator array
 * Return: Operator location in array
 */
int Search_Array(char Operator);

/** Converts the answer float into a string a prints it to the LCD : Adapted function from stack overflow
  * Param: Answer
  */
void Float_To_String(float Answer);


#endif
