/*==============================================================================
    Project: UBMP LPF
    Version: 1.01 				Date: December 1st, 2017
    Target: UBMP2.0             Processor: PIC16F1459

    A simple input program to demonstrate three different types of button logic
    while also testing the buttons and LEDs.
==============================================================================*/

#include	"xc.h"				// XC general include file

#include	"stdint.h"			// Include integer definitions
#include	"stdbool.h"			// Include Boolean (true/false) definitions

#include	"UBMP.h"			// Include UBMP constant symbols and functions

// TODO Set linker ROM ranges to 'default,-0-C03' under "Memory model" pull-down.
// TODO Set linker Code offset to '0xC04' under "Additional options" pull-down.

unsigned char LPFInput[10] = {127, 127, 127, 127, 127, 127, 127, 127, 127, 127};
unsigned char lastVal = 0;
unsigned char LPFAvg;
unsigned char tempIN;
unsigned char max1 = 0, max2 = 0, max3 = 0, max4 = 0;

unsigned char red = 0;
unsigned char green = 64;
unsigned char blue = 0;

unsigned char tempRed;
unsigned char tempGreen;
unsigned char tempBlue;

const char maxLEDs = 30;

unsigned char temp;
unsigned char i;

// max LPF is 251
// min LPF is 230?
// there will be 8 groups of 3 LEDs on each side of the gramophone
const unsigned char LPFLookupTable[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 31
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //63
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, // 95
    3, 3, 4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 12, 12,
    12, 12, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 20, 20, 20, 20, 21, 21,
    21, 22, 22, 22, 22, 23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 30, 30, 30, //191
    30, 30, 30, 30, 30, 30, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 0, 1, 2, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 22, 24, 26, 27, 28, 29, 30, 30, 30, 30, 30 // first 30 is 251th index
};

/*==============================================================================
 ADCONVERT
==============================================================================*/
unsigned char adConvert(unsigned char chan) {
    ADON = 1;
    ADCON0 = (ADCON0 & 0b10000011);
    ADCON0 = (ADCON0 | chan);
    __delay_us(2);

    GO = 1;
    while (GO);

    ADON = 0;
    return (ADRESH);
}

/*==============================================================================
 NeoPixel1
 * #define	NEOPIXEL1	LATC0		// External I/O header H1 output
==============================================================================*/
void NeoPixel1(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
    }
}

/*==============================================================================
 NeoPixel2
 * #define	NEOPIXEL2	LATC1		// Servo2 output (header H2)
==============================================================================*/
void NeoPixel2(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,1");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,1");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,1");
        }
    }
}

/*==============================================================================
 NeoPixel3
 * #define	NEOPIXEL3	LATC2		// Servo 3 output (header H3)
==============================================================================*/

void NeoPixel3(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATA,4");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
    }
}

/*==============================================================================
 NeoPixel4
 * #define	NEOPIXEL4	LATC3		// External I/O header H1 output
==============================================================================*/
void NeoPixel4(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,3");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,3");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,3");
        }
    }
}

/*==============================================================================
 NeoPixel5
 * #define	NEOPIXEL5	LATC4		// External I/O header H1 output
==============================================================================*/
void NeoPixel5(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,4");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,4");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,4");
        }
    }
}

/*==============================================================================
 NeoPixel6
 * #define	NEOPIXEL6	LATC5		// External I/O header H1 output
==============================================================================*/
void NeoPixel6(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,5");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,5");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,5");
        }
    }
}

/*==============================================================================
 NeoPixel7
 * #define	NEOPIXEL7	LATC6		// External I/O header H1 output
==============================================================================*/
void NeoPixel7(unsigned char height, unsigned char leds) {
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
    }
}

/*==============================================================================
 LIGHTS
==============================================================================*/
void lights(unsigned char height2, unsigned char numLeds) {
    NeoPixel1(height2, numLeds);
    NeoPixel2(height2, numLeds);
    NeoPixel3(height2, numLeds);
    NeoPixel4(height2, numLeds);
    NeoPixel5(height2, numLeds);
    NeoPixel6(height2, numLeds);
    NeoPixel7(height2, numLeds);
}

/*==============================================================================
    Main program loop. The main() function is called first by the compiler.
==============================================================================*/
int main(void) {
    initOsc(); // Initialize oscillator
    initPorts(); // Initialize I/O pins and peripherals
    //	initANB();					// Optional - Initialize PORTB analogue inputs
    __delay_us(200);


    while (1) {
        max1 = 0;
        max2 = 0;
        max3 = 0;
        max4 = 0;
        tempIN = adConvert(LPFIN);
        LPFInput[lastVal] = tempIN;
        lastVal = (lastVal == 9) ? 0 : lastVal + 1;
        for (i = 0; i < 10; i++) {
            if (LPFInput[i] > max1) {
                max4 = max3;
                max3 = max2;
                max2 = max1;
                max1 = LPFInput[i];
            } else if (LPFInput[i] > max2) {
                max4 = max3;
                max3 = max2;
                max2 = LPFInput[i];
            } else if (LPFInput[i] > max3) {
                max4 = max3;
                max3 = LPFInput[i];
            } else if (LPFInput[i] > max4) {
                max4 = LPFInput[i];
            }
        }
        LPFAvg = (max1 + max2 + max3 + max4) / 4;
        lights(LPFLookupTable[LPFAvg], maxLEDs);
        __delay_ms(25);
        if (S1 == 0) // Enter the bootloader if S1 is pressed.
        {
            asm("movlp 0x00");
            asm("goto 0x001C");
        }
    }
}
