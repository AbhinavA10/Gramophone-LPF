/*==============================================================================
	UBMP 1.0 (PIC16F1459) hardware initialization and user functions.
==============================================================================*/

#include	"xc.h"				// XC compiler general include file

#include	"stdint.h"			// Include integer definitions
#include	"stdbool.h"			// Include Boolean (true/false) definitions

#include	"UBMP.h"			// Include UBMP constant symbols and functions

// TODO Initialize oscillator, ports and other PIC/UBMP hardware features here.

// Initialize oscillator

void initOsc(void)
{
	OSCCON = 0xFC;				// 3x PLL enabled from 16MHz HFINTOSC
	ACTCON = 0x90;				// Enable active clock tuning from USB
	while(!PLLRDY);				// Wait for PLL lock
}

// Initialize hardware ports and peripherals. Set starting conditions.

void initPorts(void)
{
    /*FROM PAGE 125 in http://ww1.microchip.com/downloads/en/DeviceDoc/40001639B.pdf
     * 
     * TRISs are data directions  - 0 is output, 1 is input
     * PORTs are inputs
     * LATs are outputs
     * WPUs are weak pull-ups
     * ANSELs are analog selects - 0 is digital, 1 is analog
     */
	OPTION_REG = 0b01010111;	// Enable port pull-ups, TMR0 internal, div-256
	
	LATA = 0b00000000;			// Clear Port A latches before configuring PORTA
	ANSELA = 0b00010000;		// Make RA4 Analogue, rest stay digital
	TRISA =  0b00011011;	    // Set RUNLED(RA5) as output, RA4 as input, RA0, RA1 are used for USB, RA2:3 can't be changed.

	LATB = 0b00000000;			// Clear Port B latches before configuring PORTB
	ANSELB = 0b00000000;		// Make all Port B pins digital
	TRISB = 0b11110000;			// Set Port B pins for switch S2-S5 input
	
	LATC = 0b00000000;			// Clear Port C latches before configuring PORTC
	ANSELC = 0b00000000;		// Make all Port C pins digital
	TRISC = 0b00000000;			// Set Neopixel LED and Servo outputs (headers))

	// Enable interrupts, if needed.
}

// Initialize analogue PORTB inputs. Call initANB after initPorts if PORTB 
// analogue inputs will be used. 

void initANB(void)
{
	LATB = 0b00000000;			// Clear Port B latches before configuring PORTB
	ANSELB = 0b00110000;		// Enable RRB4 and RB5 analogue inputs
	ADCON0 = 0b00101000;		// Analogue channel AN10, A/D converter off,
	ADCON1 = 0b01100000;		// left justified, FOSC/64 A-D clock, +VDD ref.
	ADCON2 = 0b00000000;		// Autoconversion trigger disabled
	TRISB = 0b11110000;			// Set all Port B pins as inputs
}