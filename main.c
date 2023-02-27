
// refer file:///C:/Program%20Files/Microchip/xc8/v2.40/docs/chips/18f4520.html
#include <xc.h>

// CONFIG1H
#pragma config OSC = HS
//#pragma config OSC = INTIO67    // Oscillator Selection bits->Internal oscillator block, port function on RA6 and RA7
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF    // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled

// CONFIG2L
#pragma config PWRT = ON    // Power-up Timer Enable bit->PWRT disabled
#pragma config BOREN = SBORDIS //SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 2    // Brown Out Reset Voltage bits->VBOR set to 1.8 V nominal

// CONFIG2H
#pragma config WDT = ON    // Watchdog Timer Enable bit->WDT is controlled by SWDTEN bit of the WDTCON register
#pragma config WDTPS = 32768   // Watchdog Timer Postscale Select bits->1:32768


#pragma config MCLRE = OFF
#pragma config LPT1OSC = OFF
#pragma config PBADEN = OFF
#pragma config CCP2MX = PORTBE

#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF

#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF

#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF 
#pragma config EBTRB = OFF

#define _XTAL_FREQ 20000000

void DELAY_milliseconds(uint16_t milliseconds) {
    while(milliseconds--){ 
        __delay_ms(1); 
    }
}

void main(void) {
    // SCS FOSC; OSTS intosc; IRCF 8MHz_HFINTOSC/2; IDLEN disabled; 
    OSCCON = 0x60;
    // INTSRC disabled; PLLEN disabled; TUN 0; 
    OSCTUNE = 0x00;
//    OSCTUNE = 0x00;
//    OSCCON = 0x62; //8MHz clock
    TRISC = 0x00;
    LATC = 0x00;
    while (1) {
        LATC = 0x00;
        DELAY_milliseconds(500);
        LATC = 0xFF;
        DELAY_milliseconds(500);
        ClrWdt();
    }
}
