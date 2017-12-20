/*/==============================================================================
    UBMP 1.0 (PIC16F1459) symbolic constant definitions.
==============================================================================*/

// TODO - Add user constant definitions for UBMP hardware here.

// Inputs read the port registers (eg. RC0). Outputs write to the port latches
// (eg. LATC0). Create two different symbolic names for any pin that will be
// used for both input and output.

// PORTA I/O device definitions

#define	S1			RA3			// S1/Reset switch input
#define	BEEPER		LATA4		// Piezo beeper P1 output
#define	P1			LATA4		// Piezo beeper P1 output
#define	LED1		LATA5		// Run LED, LED1 output
#define	RUNLED      LATA5		// Run LED, LED1 output

// PORTB I/O device definitions

#define	Q1			RB4			// Phototransistor Q1 input
#define	S2			RB4			// Switch S2 input
#define	Q2			RB5			// Phototransistor Q2 input
#define S3			RB5			// Switch S3 input
#define	S4			RB6			// Switch S4 input
#define	S5			RB7			// Switch S5 input

// PORTC I/O device definitions

#define	H1in		RC0			// External I/O header H1 input
#define	NPIXEL1     LATC0		// External I/O header H1 output
#define H2			RC1			// External I/O header H2 input
#define	NPIXEL2     LATC1		// Servo2 output (header H2)
#define	IR			RC1			// IR demodulator U2 input
#define	U2			RC1			// IR demodulator U2 input
#define	H3			RC2			// External I/O header H3 input
#define	NPIXEL3     LATC2		// Servo 3 output (header H3)
#define	H4			RC3			// External I/O header H4 input
#define	LED2		LATC3		// IR LED (LED2) output
#define	NPIXEL4     LATC3		// Servo 4 output (header H4)
#define	H5			RC4			// External I/O header H5 input
#define	LED3		LATC4		// LED3 output
#define	NPIXEL5     LATC4		// Servo 5 output (header H5)
#define	H6			RC5			// External I/O header H6 input
#define	LED4		LATC5		// LED4 output
#define	NPIXEL6     LATC5		// Servo 6 output (header H6)
#define	H7			RC6			// External I/O header H7 input
#define	LED5		LATC6		// LED5 output
#define	NPIXEL7     LATC6		// Servo 7 output (header H7)
#define	H8			RC7			// External I/O header H8 input
#define	LED6		LATC7		// LED6 output
#define	SERVOFLOWER	LATC7		// Servo 8 output (header H8)

// A-D Converter input channel definitions


#define LPFIN		0b00001100	// A-D channel 3 input

#define AN4			0b00010000	// A-D channel 4 input
#define ADH1		0b00010000	// External H1 header analogue input (Ch4))
#define	ADT1		0b00010000	// Temperature sensor T1 A-D input (Ch4)
#define AN5			0b00010100	// A-D channel 5 input
#define ADH2		0b00010100	// External H2 header analogue input (Ch5)
#define AN6			0b00011000	// A-D channel 6 input
#define ADH3		0b00011000	// External H3 header analogue input (Ch6)
#define AN7			0b00011100	// A-D channel 7 input
#define ADH4		0b00011100	// External H4 header analogue input (Ch7)
#define AN8			0b00100000	// A-D channel 8 input
#define ADH7		0b00100000	// External H7 header analogue input (Ch8)
#define AN9			0b00100100	// A-D channel 9 input
#define ADH8		0b00100100	// External H8 header analogue input (Ch9)
#define AN10		0b00101000	// A-D channel 10 input
#define	ADQ1		0b00101000	// Q1 phototransistor A-D input (Ch10)
#define AN11		0b00101100	// A-D channel 11 input
#define	ADQ2		0b00101100	// Q2 phototransistor A-D input (Ch11)
#define ADTIM		0b01110100	// PICmicro on-die temperature indicator module

// Clock frequency for delay macros and simulation

#define _XTAL_FREQ	48000000	// Set clock frequency for time delays

// TODO - Add function prototypes for all functions in UBMP.c here.

void initOsc(void); // Oscillator initialization function prototype.
void initPorts(void); // Port initialization function prototype.
void initANB(void); // Analogue PORTB initialization function