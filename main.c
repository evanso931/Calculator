/* main.c
 * ELEC 3662 Mini Project
 * School of Electronic & Electrical Engineering
 * University of Leeds
 * Name: Benjamin Evans
 * Student ID Number:201216635
 * Date: Dec 2020
 */

// Included Headers ------------------------------------------------------------

#include <InterpretInput.h>
#include <Initialise.h>
#include <LCD.h>


// Function Definitions  ------------------------------------------------------------

int main(void){
    Run_Init();
    Startup_Graphics();

    while(1){
        Run_Calculator();
    }
}

