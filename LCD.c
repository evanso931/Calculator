#include <LCD.h>


// Function Definitions  ------------------------------------------------------------

void Print_String_On_LCD(char *string){
    for(int i = 0; i < strlen(string); i++) {
            Send_Display_Byte((0x200 + string[i]) & 0xFF,1); // Prints ASCII on LCD
            SysTick_Wait(50*80); // 50us delay for LCD
     }
}


void Init_Display_Port(void){
    //SysTick_Wait(50*80000); // 50ms delay for LCD > 40 ms
    Send_Display_Nibble(0x03,0); // Function Set

    SysTick_Wait(5*80000); // 5ms delay for LCD > 4.1 ms
    Send_Display_Nibble(0x03,0); // Function Set

    SysTick_Wait(110*80); // 110us delay for LCD > 100 us
    Send_Display_Nibble(0x03,0); //Function Set

    SysTick_Wait(50*80); // 50us delay for LCD
    Send_Display_Nibble(0x02,0); // Interface 4 bits long

    SysTick_Wait(50*80); // 50us delay for LCD
    Send_Display_Byte(0x28,0); // N = 1 for two lines

    SysTick_Wait(50*80); // 50us delay for LCD
    Send_Display_Byte(0x08,0); // Display off

    SysTick_Wait(50*80); // 50us delay for LCD
    Send_Display_Byte(0x01,0); // Display clear

    SysTick_Wait(50*80); // 50us delay for LCD
    Send_Display_Byte(0x06,0); // Entry mode set
    SysTick_Wait(50*80); // 50us delay for LCD
}


void Send_Display_Byte(unsigned long Byte, int RS){
    Send_Display_Nibble((Byte&0xF0)>>4,RS); //Selects one byte and sends last 4 bits
    SysTick_Wait(37*80); // 37us for display to act
    Send_Display_Nibble(Byte&0x0F,RS); // Sends first 4 bits of selected byte
    SysTick_Wait(37*80); // 37us for display to act
}


void Send_Display_Nibble(unsigned long Nibble, int RS){
    int HEX_RS = RS_TO_HEX(RS);

    Set_EN_RS(HEX_RS);
    GPIO_PORTB_DATA_R = Nibble; // Ports B equal nibble

    SysTick_Wait(450*80); //delay 50ns

    GPIO_PORTA_DATA_R = HEX_RS; // sets E to 0

    SysTick_Wait(50*80); //delay 50ns
}


void Startup_Graphics(){
    Print_String_On_LCD("        CASIO");
    SysTick_Wait(30*80000); //delay 30ms
    Send_Display_Byte(0x01,0);

}
