#include <Initialise.h>


// Function Definitions  ------------------------------------------------------------

void PortA_Init(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_GPIOABE; // 1) ABE clock
      while((SYSCTL_PRGPIO_R&0x10)==0){};       // allow time for clock to stabilize
      GPIO_PORTA_LOCK_R = 0x4C4F434B;           // 2) unlock PortB PF0
      GPIO_PORTA_CR_R = 0x0F;                   // allow changes to PF4-0
      GPIO_PORTA_AMSEL_R = 0x00;                // 3) disable analog function
      GPIO_PORTA_PCTL_R = 0x00000000;           // 4) GPIO clear bit PCTL
      GPIO_PORTA_DIR_R = 0x0E;                  // 5) PA1, PA2, PA3 to output
      GPIO_PORTA_AFSEL_R = 0x00;                // 6) no alternate function
      GPIO_PORTA_DEN_R = 0x0F;                  // 7) enable digital pins PF4-PF0
}


void PortB_Init(void){
      GPIO_PORTB_LOCK_R = 0x4C4F434B;           // 2) unlock PortB PF0
      GPIO_PORTB_CR_R = 0x0F;                   // allow changes to PF4-0
      GPIO_PORTB_AMSEL_R = 0x00;                // 3) disable analog function
      GPIO_PORTB_PCTL_R = 0x00000000;           // 4) GPIO clear bit PCTL
      GPIO_PORTB_DIR_R = 0x0F;                  // 5) PB0, PB1, PB2, PB3 to output
      GPIO_PORTB_AFSEL_R = 0x00;                // 6) no alternate function
      GPIO_PORTB_DEN_R = 0x0F;                  // 7) enable digital pins PF4-PF0
}


void PortD_Init(void){
      GPIO_PORTD_LOCK_R = 0x4C4F434B;           // 2) unlock PortE PF0
      GPIO_PORTD_CR_R = 0x0F;                   // allow changes to PF4-0
      GPIO_PORTD_AMSEL_R = 0x00;                // 3) disable analog function
      GPIO_PORTD_PCTL_R = 0x00000000;           // 4) GPIO clear bit PCTL
      GPIO_PORTD_DIR_R = 0x00;                  // 5) PD0, PD1, PD2, PD3 to inputs
      GPIO_PORTD_AFSEL_R = 0x00;                // 6) no alternate function
      GPIO_PORTD_DEN_R = 0x0F;                  // 7) enable digital pins PF4-PF0
}


void PortE_Init(void){
      GPIO_PORTE_LOCK_R = 0x4C4F434B;           // 2) unlock PortE PF0
      GPIO_PORTE_CR_R = 0x0F;                   // allow changes to PF4-0
      GPIO_PORTE_AMSEL_R = 0x00;                // 3) disable analog function
      GPIO_PORTE_PCTL_R = 0x00000000;           // 4) GPIO clear bit PCTL
      GPIO_PORTE_DIR_R = 0x0F;                  // 5) PE0, PE1, PE2, PE3 to output
      GPIO_PORTE_AFSEL_R = 0x00;                // 6) no alternate function
      GPIO_PORTE_DEN_R = 0x0F;                  // 7) enable digital pins PF4-PF0
}

void Run_Init(){
    PortA_Init();
    PortB_Init();
    PortD_Init();
    PortE_Init();
    PLL_Init();
    SysTick_Init();
    Init_Display_Port();
}
