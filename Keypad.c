#include <Keypad.h>


// Function Definitions  ------------------------------------------------------------

char Read_Keypad(){
    int Keypad_Colmn = Check_Keypad_Column();
    int Keypad_Row = Check_Keypad_Row();

    if (Keypad_Colmn == 1){
        if(Keypad_Row == 1){
            return '1';
        }
        else if(Keypad_Row == 2){
            return '4';
        }
        else if(Keypad_Row == 3){
            return '7';
        }
        else if(Keypad_Row == 4){
            return '*';
        }
    }else if (Keypad_Colmn == 2){
        if(Keypad_Row == 1){
            return '2';
        }
        else if(Keypad_Row == 2){
            return '5';
        }
        else if(Keypad_Row == 3){
            return '8';
        }
        else if(Keypad_Row == 4){
            return '0';
        }
    }else if (Keypad_Colmn == 3){
        if(Keypad_Row == 1){
            return '3';
        }
        else if(Keypad_Row == 2){
            return '6';
        }
        else if(Keypad_Row == 3){
            return '9';
        }
        else if(Keypad_Row == 4){
            return '#';
        }
    }else if (Keypad_Colmn == 4){
        if(Keypad_Row == 1){
            return 'A';
        }
        else if(Keypad_Row == 2){
            return 'B';
        }
        else if(Keypad_Row == 3){
            return 'C';
        }
        else if(Keypad_Row == 4){
            return 'D';
        }
    }

    return ' '; // No key or multiple keys pressed
}


int Check_Keypad_Row(){
    Set_Keypad_Row(1);
    if (Check_Keypad_Column() != 0){
        return 1;
    }

    Set_Keypad_Row(2);
    if (Check_Keypad_Column() != 0){
        return 2;
    }

    Set_Keypad_Row(3);
    if (Check_Keypad_Column() != 0){
        return 3;
    }

    Set_Keypad_Row(4);
    if (Check_Keypad_Column() != 0){
        return 4;
    }

    return 0;
}


int Check_Keypad_Column(){
    if (Read_Keypad_Column(1)){
        return 1;
    }else if (Read_Keypad_Column(2)){
        return 2;
    }else if (Read_Keypad_Column(3)){
        return 3;
    }else if (Read_Keypad_Column(4)){
        return 4;
    }else{
        return 0;
    }
}
