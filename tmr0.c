
#include <xc.h>
#include "tmr0.h"

volatile uint8_t timer0ReloadVal;

void TMR0_Initialize(void) {
    // Set TMR0 to the options selected in the User Interface

    // TMR0H 0; 
    TMR0H = 0x00;

    // TMR0L 217; 
    TMR0L = 0xD9;


    // Load TMR0 value to the 8-bit reload variable
    timer0ReloadVal = 217;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // T0PS 1:256; T08BIT 8-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    T0CON = 0xD7;
    // Start the Timer by writing to TMR0ON bit
//    T0CONbits.TMR0ON = 1;
}

void TMR0_ISR(void) {

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    TMR0L = timer0ReloadVal;

    // add your TMR0 interrupt custom code
}

/**
  End of File
 */