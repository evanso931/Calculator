/* LCD.h
 * Prints Characters on LCD
 * Author: Benjamin Evans
 * Date: Dec 2020
 */

#ifndef LCD_H
#define LCD_H


// Included Headers ------------------------------------------------------------

#include <string.h>
#include <Initialise.h>
#include <PLL.h>
#include <DeviceDependent.h>


// Forward Declarations ------------------------------------------------------------

/** Prints the string  to LCD
  * Param: String
  */
void Print_String_On_LCD(char *string);

/** Initialises the LCD */
void Init_Display_Port(void);

/** Sends the byte to the LCD as two nibbles
  * Param: Byte, RS
  */
void Send_Display_Byte(unsigned long Byte, int RS);

/** Sends a nibble to the LCD
  * Param: Nibble, RS
  */
void Send_Display_Nibble(unsigned long Nibble, int RS);

/** Prints startup graphics to screen */
void Startup_Graphics();


#endif
