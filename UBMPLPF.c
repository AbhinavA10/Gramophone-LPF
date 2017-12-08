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

unsigned char LPFInput[10] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
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
 LIGHTS
==============================================================================*/
unsigned char lights(unsigned char height, unsigned char numLeds) {
    if (height > 193) {
        if (height < 255) {
            height = (height / 2) - 97;
        } else {
            height = 30;
        }
    } else {
        height = 0;
    }
    NeoPixel1(height, numLeds);
    NeoPixel2(height, numLeds);
    NeoPixel3(height, numLeds);
    NeoPixel4(height, numLeds);
    NeoPixel5(height, numLeds);
    NeoPixel6(height, numLeds);
    NeoPixel7(height, numLeds);
}

/*==============================================================================
 NeoPixel1
 * #define	NEOPIXEL1	LATC0		// External I/O header H1 output
==============================================================================*/
void NeoPixel1(unsigned char height, unsigned char leds) {
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,1");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,1");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,1");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,1");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATA,4");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,0");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,0");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,0");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,3");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,3");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,3");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,3");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,4");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,4");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,4");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,4");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,5");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,5");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,5");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,5");
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
    height = lights(height);
    for (leds; leds != 0; leds--) {
        temp = (leds < height) ? green : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
        temp = red; //(leds < height) ? red : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
        temp = blue; //(leds < height) ? blue : 0;
        for (i = 8; i != 0; i--) {
            asm("bsf LATC,6");
            asm("nop");
            asm("btfss _temp,7");
            asm("bcf LATC,6");
            asm("nop");
            asm("lslf _temp,f");
            asm("bcf LATC,6");
        }
    }
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
        if (tempIN > 193) {
            LPFInput[lastVal] = tempIN;
            lastVal = (lastVal == 9) ? 0 : lastVal + 1;
        }
        for (i = 0; i < 10; i++) {
            if (LPFInput[i] > max1) {
                max4 = max3;
                max3 = max2;
                max2 = max1;
                max1 = LPFInput[i];
            }
            if (LPFInput[i] > max2) {
                max4 = max3;
                max3 = max2;
                max2 = LPFInput[i];
            }
            if (LPFInput[i] > max3) {
                max4 = max3;
                max3 = LPFInput[i];
            }
            if (LPFInput[i] > max4) {
                max4 = LPFInput[i];
            }
        }
        LPFAvg = (max1 + max2 + max3 + max4) / 4;
        if (tempIN == 0) {
            LPFAvg == 0;
        }
        lights(LPFAvg, maxLEDs);
        __delay_ms(10);
        if (S1 == 0) // Enter the bootloader if S1 is pressed.
        {
            asm("movlp 0x00");
            asm("goto 0x001C");
        }
    }
}
