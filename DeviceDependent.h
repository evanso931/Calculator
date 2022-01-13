/* DeviceDependent.h
 * Makes all the device dependent code accessible in independent way
 * Author: Benjamin Evans
 * Date: Dec 2020
 */

#ifndef DEVICEDEPENDENT_H
#define DEVICEDEPENDENT_H

// Included Headers ----------------------------------------------------------------

#include <Initialise.h>


// Forward Declarations ------------------------------------------------------------

/* Toggles the LED attaches to PA1 */
void Toggle_LED();

/** Reads the chosen keypad column
 * Param: Column
 * Return: 1 for column is high and 0 for column is low
 */
int Read_Keypad_Column(int Column);

/** Reads the chosen keypad column
 * Param: Row
 */
void Set_Keypad_Row(int Row);

/** Reads the chosen keypad column
 * Param: Decimal_RS
 * Return: HEX RS
 */
int RS_TO_HEX(int Decimal_RS);

/** Sets EN to 1 and RS to 1 or 0
 * Param: RS
 */
void Set_EN_RS(int RS);


#endif
