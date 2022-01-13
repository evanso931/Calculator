#include <InterpretInput.h>


// Global Variables -----------------------------------------------------------------

char Input[255];
volatile int Key_Pressed_Flag = 0;
volatile int Shift_Pressed_Flag = 0;
int Answer_Flag = 0;


// Function Definitions  ------------------------------------------------------------

void Run_Calculator(){
    Stop_Double_Press();
}

void Get_Input(char  *buffer){
    strcpy(buffer,Input);
}


void Stop_Double_Press(){
    char Key = Read_Keypad();

    // Stops double key press
    if(Key == ' '){
        Key_Pressed_Flag = 0;

    // Limit the max input number of inputs to 16 as LCD shifting doesn't work
    }else if(Key_Pressed_Flag == 0){
        Key_Pressed_Flag = 1;
        Keypad_To_Input(Key);
        Shift_Display();
    }
}


void Keypad_To_Input(char Key){
    Check_Printed_Answer(Answer_Flag);

    // No Shift
    if (Shift_Pressed_Flag == 0){
        if(Key == 'A'){Input[strlen(Input)] = '+';}                    // +
        else if(Key == 'B'){Input[strlen(Input)] = '-';}               // -
        else if(Key == 'C'){Input[strlen(Input)] = '.';}               // .
        else if(Key == '#'){Rubout_Last_Character();}                  // Rubout last character
        else if(Key != 'D'){Input[strlen(Input)] = Key;}               // 0 to 9;
    }

    // Shift
    else if (Shift_Pressed_Flag == 1){
        if(Key == 'A'){Input[strlen(Input)] = 'x';}                     // x
        else if(Key == 'B'){Input[strlen(Input)] = '÷';}                // ÷
        else if(Key == 'C'){Input[strlen(Input)] = 'e';}                // e
        else if(Key == '#'){Clear_Display();}                           // Clear Display
        else if(Key != 'D'){Input[strlen(Input)] = Key;}                // 0 to 9;
        if(Key != 'D'){Toggle_Shift();}                                 // Removes shift after key has been pressed
    }

    if (Key == 'D'){
        Toggle_Shift();
    }

    // Prints characters or answer to screen and adds characters to input array. Does not run if no input.
    if ((Key == '*' && Input[0] != '*') || strlen(Input) == 254){
        Print_Answer();
        Answer_Flag = 1;
    }else if (Key != '#' && Key != 'D' && Key != '*'){
        char Last_Array_Character = Input[strlen(Input)-1];
        Send_Display_Byte((0x200 + Last_Array_Character) & 0xFF,1); // Prints ASCII on LCD
    }

    // clears the input array when the equals button is pressed with no input
    if (Input[0] == '*'){
        memset(Input,'\0',strlen(Input));
    }
}


void Check_Printed_Answer(int Ans_Flag){
    if (Ans_Flag == 1 && Read_Keypad() != '*' ){
        Clear_Display();
        Answer_Flag = 0;
        Input[strlen(Input)-1] = Read_Keypad();
    }
}


void Toggle_Shift(){
    Shift_Pressed_Flag = !Shift_Pressed_Flag;     // Change Shift
    Toggle_LED();

}


void Rubout_Last_Character(){
    // Buffer to delete the last element in that array rather than input array as that was causing weird things to happen
    char Rubout_Buffer[255];
    strcpy(Rubout_Buffer,Input);

    // Less than 2 input just clear screen otherwise it breaks
    if (strlen(Input) < 2){
        Clear_Display();
    }else{
        Rubout_Buffer[strlen(Rubout_Buffer)-1] = '\0';             // Deletes last element of buffer array
        strcpy(Input,Rubout_Buffer);
        Send_Display_Byte(0x04,0);                   // Change cursor direction
        SysTick_Wait(50*80);                         // 50us delay for LCD
        Send_Display_Byte((0x200 + ' ') & 0xFF,1);   // ' '
        SysTick_Wait(50*80);                         // 50us delay for LCD
        Send_Display_Byte((0x200 + ' ') & 0xFF,1);   // ' '
        SysTick_Wait(50*80);                         // 50us delay for LCD
        Send_Display_Byte(0x06,0);                   // Change cursor direction right
        char New_Last_Array_Character = Input[strlen(Input)-1];
        Send_Display_Byte((0x200 + New_Last_Array_Character) & 0xFF,1); // Prints previous character over its self to change cursor direction
    }
}


void Clear_Display(){
    memset(Input,'\0',strlen(Input));             // Deletes all elements of input array
    Send_Display_Byte(0x01,0);                    // Clear entire entry
}


void Shift_Display(){
    if (strlen(Input) > 16){
        Send_Display_Byte(0x01,0); // CLear Display

        // Loop to reprint inputs the LCD but shifted by 1 for each input over 16
        for(int i = strlen(Input) -16; i < strlen(Input); i++) {
            Send_Display_Byte((0x200 + Input[i]) & 0xFF,1); // Prints ASCII on LCD
            SysTick_Wait(50*80); // 50us delay for LCD
        }
    }
}
