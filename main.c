
// refer file:///C:/Program%20Files/Microchip/xc8/v2.40/docs/chips/18f4520.html
#include <xc.h>
#include "tmr0.h"
#include "displayKeyTickCPU.h"

// Configuration bits: selected in the GUI

// CONFIG1H
// #pragma config FOSC = XT    // Oscillator Selection bits->XT oscillator

#pragma config OSC = HS // INTIO67

#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF  // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled

// CONFIG2L
#pragma config PWRT = ON  // Power-up Timer Enable bit->PWRT enabled
#pragma config BOREN = ON // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 2   // Brown Out Reset Voltage bits->VBOR set to 2 V nominal

// CONFIG2H
#pragma config WDT = ON    // Watchdog Timer Enable bit->WDT is controlled by SWDTEN bit of the WDTCON register
#pragma config WDTPS = 1024 // Watchdog Timer Postscale Select bits->1:32768

// CONFIG3H
#pragma config CCP2MX = PORTC // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = OFF   // PORTB A/D Enable bit->PORTB<4:0> pins are configured as analog input channels on Reset
#pragma config LPT1OSC = OFF  // Low-Power Timer1 Oscillator Enable bit->Timer1 configured for higher power operation
#pragma config MCLRE = ON     // MCLR Pin Enable bit->MCLR pin enabled; RE3 input pin disabled

// CONFIG4L
#pragma config STVREN = ON // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config LVP = OFF   // Single-Supply ICSP Enable bit->Single-Supply ICSP disabled
#pragma config XINST = OFF // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)
#pragma config DEBUG = OFF // Background Debugger Enable bit->Background debugger disabled, RB6 and RB7 configured as general purpose I/O pins

// CONFIG5L
#pragma config CP0 = OFF // Code Protection Block 0->Block 0 (000800-001FFFh) not code-protected
#pragma config CP1 = OFF // Code Protection Block 1->Block 1 (002000-003FFFh) not code-protected
#pragma config CP2 = OFF // Code Protection Block 2->Block 2 (004000-005FFFh) not code-protected
#pragma config CP3 = OFF // Code Protection Block 3->Block 3 (006000-007FFFh) not code-protected

// CONFIG5H
#pragma config CPB = OFF // Boot Block Code Protection bit->Boot block (000000-0007FFh) not code-protected
#pragma config CPD = OFF // Data EEPROM Code Protection bit->Data EEPROM not code-protected

// CONFIG6L
#pragma config WRT0 = OFF // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected
#pragma config WRT2 = OFF // Write Protection Block 2->Block 2 (004000-005FFFh) not write-protected
#pragma config WRT3 = OFF // Write Protection Block 3->Block 3 (006000-007FFFh) not write-protected

// CONFIG6H
#pragma config WRTC = OFF // Configuration Register Write Protection bit->Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTB = OFF // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF // Data EEPROM Write Protection bit->Data EEPROM not write-protected

// CONFIG7L
#pragma config EBTR0 = OFF // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
#pragma config EBTR2 = OFF // Table Read Protection Block 2->Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
#pragma config EBTR3 = OFF // Table Read Protection Block 3->Block 3 (006000-007FFFh) not protected from table reads executed in other blocks

// CONFIG7H
#pragma config EBTRB = OFF // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks


#define _XTAL_FREQ 20000000

void DELAY_milliseconds(uint16_t milliseconds) {
    while (milliseconds--) {
        __delay_ms(1);
    }
}

void INTERRUPT_Initialize(void) {
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    RCONbits.IPEN = 0;
    // Assign peripheral interrupt priority vectors


    // TMRI - low priority
    INTCON2bits.TMR0IP = 0;
}

void __interrupt(low_priority) INTERRUPT_InterruptManagerLow(void) {
    // interrupt handler
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        TMR0_ISR();
        displayISR();
    } else {
        //Unhandled Interrupt
    }
}

void OSCILLATOR_Initialize(void) {
    // SCS INTOSC; OSTS intosc; IRCF 16MHz_HFINTOSC; IDLEN disabled; 
    OSCCON = 0x72;
    // INTSRC disabled; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x00;
}

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

void main(void) {
    INTERRUPT_Initialize();
    OSCILLATOR_Initialize();
    initDisplay();
    TMR0_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    TRISC = 0x00;
    unsigned int i = 0;
//    DISP_DATA_PORT = 0x00;
//    DISP_MUX_PORT = 0x00;
//    DISP_DATA_PORT_TRIS = 0x00;
//    DISP_MUX_PORT_TRIS = 0x00;
    while (1) {
        if (tick1000mSec) {
            tick1000mSec = 0;
            i++;
            displayInt(i, 1);
            display();
        }
        ClrWdt();
    }
}
