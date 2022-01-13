#include <DeviceDependent.h>


// Function Definitions  ------------------------------------------------------------

void Toggle_LED(){
    GPIO_PORTA_DATA_R ^= 0x02;                    // toggles led
}


int Read_Keypad_Column(int Column){
    if (Column ==  1 && GPIO_PORTD_DATA_R == 0x01){
        return 1;
    }else if (Column == 2 && GPIO_PORTD_DATA_R == 0x02){
        return 1;
    }else if (Column == 3 && GPIO_PORTD_DATA_R == 0x04){
        return 1;
    }else if (Column == 4 && GPIO_PORTD_DATA_R == 0x08){
        return 1;
    }

    return 0;
}


void Set_Keypad_Row(int Row){
    if (Row == 1){
        GPIO_PORTE_DATA_R = 0x01;
    }else if (Row == 2){
        GPIO_PORTE_DATA_R = 0x02;
    }else if (Row == 3){
        GPIO_PORTE_DATA_R = 0x04;
    }else if (Row == 4){
        GPIO_PORTE_DATA_R = 0x08;
    }
}


int RS_TO_HEX(int Decimal_RS){
    // Convert RS to Hex
    if (Decimal_RS == 1){
        return 0x08; // PA3
    }else{
        return 0x00;
    }
}

void Set_EN_RS(int RS){
    GPIO_PORTA_DATA_R = RS|0x04; //EN is PA2
}
