#include <Calculations.h>


// Global Variables -----------------------------------------------------------------

char Char_Input[255];
float Input_Numbers[255];
char Operators[128];
int Num_Of_Input_Numbers = 0;


// Function Definitions  ------------------------------------------------------------

void Input_Conversion(){
    int Negative_Flag = 0;
    char Temp_Input_Array[16];
    Num_Of_Input_Numbers = 0;

    // Loops through char_input array, separating operands and numbers into different arrays.
    for(int i = 0; i < strlen(Char_Input); i++) {

        // Operator encountered
        if (Char_Input[i] == '+' || (Char_Input[i] == '-' && Char_Input[i-1] != 'e') || Char_Input[i] == 'x'|| Char_Input[i] == '÷'){
            // sets negative number flag and stores numbers and operators in arrays
            if(Char_Input[i] == '-' && (i == 0 || Char_Input[i-1] == '+'|| Char_Input[i-1] == '-' || Char_Input[i-1] == 'x'|| Char_Input[i-1] == '÷')){
            Negative_Flag = 1;

            // Negative number input and not a subtract operand
            }else if (Negative_Flag == 1){
                Negative_Flag = 0;
                Input_Numbers[Num_Of_Input_Numbers] = atof(Temp_Input_Array)*-1; // Stores negative floats into an array
                Operators[strlen(Operators)] = Char_Input[i]; // Stores operators in an array
                memset(Temp_Input_Array,0,strlen(Temp_Input_Array)); // Wipes temporary array for next input number
                Num_Of_Input_Numbers++;
            }else{
                Input_Numbers[Num_Of_Input_Numbers] = atof(Temp_Input_Array); // Stores positive floats into an array
                Operators[strlen(Operators)] = Char_Input[i];
                memset(Temp_Input_Array,0,strlen(Temp_Input_Array));
                Num_Of_Input_Numbers++;
            }
        }

        // Stores digits, e and minus signs if an e is before it in temporary array
        else{
            Temp_Input_Array[strlen(Temp_Input_Array)] = Char_Input[i];
        }
    }

    // Stores the last input floats into to array cause not followed by operator
    if (Negative_Flag == 1){
        Input_Numbers[Num_Of_Input_Numbers] = atof(Temp_Input_Array)*-1;
        Num_Of_Input_Numbers++;
    }else{

        Input_Numbers[Num_Of_Input_Numbers] = atof(Temp_Input_Array);
        //Float_To_String(Input_Numbers[Num_Of_Input_Numbers]);
        Num_Of_Input_Numbers++;
    }
}


int Invalid_Inputs(){
    for(int i = 0; i < strlen(Char_Input); i++){

        // Can't input more than 1 operands or decimal point in a row apart from subtract
        if((Char_Input[i] == '+'|| Char_Input[i] == 'x'|| Char_Input[i] == '÷'|| Char_Input[i] == 'e' || Char_Input[i] == '.') &&
        (Char_Input[i-1] == '+'|| Char_Input[i-1] == 'x'|| Char_Input[i-1] == '÷'|| Char_Input[i-1] == 'e' || Char_Input[i-1] == '.')){
            return 1;

        // Can't input more than 2 or subtracts in a row
        }else if(Char_Input[i] == '-' && Char_Input[i-1] == '-' && Char_Input[i-2] == '-'){
            return 1;

        // Subtract can only lead a decimal point or minus
        }else if ((Char_Input[i] == '+' || Char_Input[i] == 'x'|| Char_Input[i] == '÷'|| Char_Input[i] == 'e') && (Char_Input[i-1] == '-')){
            return 1;

        // Subtract can't trail decimal point or plus
        }else if((Char_Input[i-1] == '.' || Char_Input[i-1] == '+') && Char_Input[i] == '-' ){
            return 1;

        // Can't finish end an operand
        }else if(Char_Input[strlen(Char_Input)-1] == '+'|| Char_Input[strlen(Char_Input)-1] == '-' || Char_Input[strlen(Char_Input)-1] == 'x'|| Char_Input[strlen(Char_Input)-1] == '÷'|| Char_Input[strlen(Char_Input)-1] == 'e'){
            return 1;
        }else if(strlen(Char_Input) == 24 && (Char_Input[i] == '+'|| Char_Input[i] == 'x'|| Char_Input[i] == '÷'|| Char_Input[i] == 'e' || Char_Input[i] == '.' || Char_Input[i] == '-' )){
            return 1;
        }
    }
    return 0;
}


void Print_Answer(){
    Get_Input(Char_Input);

    // Display answer or error on second row of LCD
    Send_Display_Byte(0xc0,0);

    // Check for invalid input
    if (Invalid_Inputs() == 1){
        Print_String_On_LCD("Syntax Error");
    }else{
        Input_Conversion();
        Calculation();
    }

    // Reset Arrays
    memset(Char_Input,'\0',strlen(Char_Input));
    memset(Operators,'\0',strlen(Operators));
    memset(Input_Numbers,0,sizeof(Input_Numbers));
}


void Calculation(){
    // Loops through operator array and performs calculations on float values
    while(strlen(Operators) > 0){
        if(Search_Array('÷') !=  999){
            int Operator_Position = Search_Array('÷');
            Input_Numbers[Operator_Position] = Input_Numbers[Operator_Position] / Input_Numbers[Operator_Position+1];
            Shift_Arrays(Operator_Position);

        }else if(Search_Array('x') !=  999){
            int Operator_Position = Search_Array('x');
            Input_Numbers[Operator_Position] = Input_Numbers[Operator_Position] * Input_Numbers[Operator_Position+1];
            Shift_Arrays(Operator_Position);


        }else if(Search_Array('-') !=  999){
            int Operator_Position = Search_Array('-');
            float x = Input_Numbers[Operator_Position];
            float y = Input_Numbers[Operator_Position+1];

            Input_Numbers[Operator_Position] = Input_Numbers[Operator_Position] - Input_Numbers[Operator_Position+1];

            // If the result of the subtraction is negative this makes sure there is a minus sign. As the above line weirdly sometimes keeps the minus and sometimes removes it.
            if (y > x && Input_Numbers[Operator_Position] > 0){
                Input_Numbers[Operator_Position] = (Input_Numbers[Operator_Position])*-1;
            }
            Shift_Arrays(Operator_Position);

        }else if(Search_Array('+') !=  999){
            int Operator_Position = Search_Array('+');
            Input_Numbers[Operator_Position] = Input_Numbers[Operator_Position] + Input_Numbers[Operator_Position+1];
            Shift_Arrays(Operator_Position);
        }
    }

    Float_To_String(Input_Numbers[0]);
}



void Shift_Arrays(int Operator_Position){
     for(int i = Operator_Position; i < Num_Of_Input_Numbers; i++){
         Input_Numbers[i+1] = Input_Numbers[i+2];
         Operators[i] = Operators[i+1];
     }

     Operators[strlen(Operators)] = '\0'; // Delete last element of operator array
}


int Search_Array(char Operator){
    for(int i = 0; i < strlen(Operators); i++){
        if(Operators[i] == Operator){
            return i;
        }
    }
    return 999;
}


void Float_To_String(float Answer){
    int Decimal_Places = 3;
    int DP_Multipler = pow(10,Decimal_Places);

    char Buffer[16] = {0};
    Answer = roundf(Answer*DP_Multipler)/DP_Multipler;

    char *str = Buffer + 16;
    uint16_t Decimals;
    int Integral;

    // Separates float into the integral part and decimal parts and converts them into integers
    if (Answer < 0) {
        Decimals= (int)(Answer * -DP_Multipler) % DP_Multipler;
        Integral = (int)(-1 * Answer);
    } else { // positive numbers
        Decimals= (int)(Answer * DP_Multipler) % DP_Multipler;
        Integral = (int)Answer;
    }

    // Adds decimals to string
    for (int i = 1; i < Decimal_Places; i++){
        *--str = (Decimals% 10) + '0';
        Decimals/= 10;
    }

    // Adds decimal point to string
    *--str = (Decimals% 10) + '0';
    *--str = '.';

    // Adds integers to string
    do  {
        *--str = (Integral % 10) + '0';
        Integral /= 10;
    }while (Integral > 0);

    // Adds minus sine to string for negative numbers
    if (Answer < 0) *--str = '-';

    // for one input stops star being printed
    if (Num_Of_Input_Numbers == 1){
        str[strlen(str)-1] = '\0';
    }

    Print_String_On_LCD(str);
}
