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
// TODO Set Instruction Freq. to 12MHz for simulator debugging

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
unsigned char servoPos = 0;

const char maxLEDs = 24;

unsigned char temp;
unsigned char i;

/* min LPF is 88
max LPF is 198
Range is 110 values, across 24 LEDs, (8 groups of 3 LEDs on each side of the gramophone)
Therefore, each LED will repeat 4 times in the table, 5 times for even, 4 for odd
 */
const unsigned char LPFLookupTable[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // last value is 31st index
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // last value is 63th index
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 83, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, // last value is 95th index
    2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 8, 9, 9, 9, 9, // last value is 127th index
    10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 16, // last value is 159th index
    17, 17, 17, 17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 23, 23, 23, 23, // last value is 191th index
    24, 24, 24, 24, 24, 24, 24, 0, 0, 0, 202, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 220, 0, 0, 0, // last value is 223rd index
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // last value is 255th index
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
 TURN SERVO
==============================================================================*/
unsigned char turnServo(unsigned char value) {
    SERVOFLOWER = 1;
    __delay_us(980);
    for (unsigned char i = 255 - value; i != 0; i--) {
        __delay_us(4);
    }
    SERVOFLOWER = 0;
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
        //temp = 0b01010101;
        for (i = 8; i != 0; i--) { // check total time after for loop step
            asm("bsf LATC,6");
            asm("nop"); // extend 0high pulse or 1 high
            asm("nop"); // extend 0 pulse
            asm("btfss _temp,7");
            /* if the MSB is a 1, then it'll skip the next step
                which means that the high pulse will be extended for the number of 
                no-ops below */
            /* if the MSB is a 0, then it'll do the next step
                which means that the high pulse will be cut off, and the
             low pulse will be for the number of no-ops below (till end of for loop  */
            asm("bcf LATC,6"); // 0high pulse ends here
            asm("nop"); //extending 0low or 1high
            asm("nop"); //extending 0low or 1high
            asm("lslf _temp,f");
            asm("bcf LATC,6"); // 1high pulse ends here
        }
        /*
         When temp = 0b01010101;
         Current Timing Specs
         0High pulse: 333 or 416 ns
         0Low pulse: 917 or 834ns
         Total 0 Pulse: 1250ns
         
         1High pulse: 666 or 750 ns
         1Low pulse: 584 or 500ns
         Total 1 Pulse: 1250ns
                         
         * Ideal Timing Specs
         Total Time: 1.25us, tolerance of 600ns
         Each alone is 150ns tolerance
        
         0High 350ns
         0Low 800ns
         
         1High 700ns
         1Low 600ns
         */
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("nop");
            asm("btfss _temp,7"); //bit test, skip if set
            asm("bcf LATC,6");
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
    //initANB();    // Optional - Initialize PORTB analogue inputs
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
        turnServo(servoPos);
        if (S1 == 0) {
            servoPos = 255;
        } else {
            servoPos = 0;
        }
        //__delay_ms(25); // don't need a delay anymore, since pulsing servo
        /*if (S1 == 0) // Enter the bootloader if S1 is pressed.
        {
            asm("movlp 0x00");
            asm("goto 0x001C");
        }*/
    }
}
