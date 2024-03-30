/*
    display.c
     Holds various routines related to the display
    This module makes it possible to write to the display buffer
    using cartesian coordinates. 

    - Display buffer: define a buffer for the display
        - setPixel(x, y, val) : set a element in the buffer. val 0 - 255
        - send : send the buffer to the display, writing contents to screen
        - initialize
    Delimitations:
        - The screen does not need to display different levels of brightness
*/

// This file is mainly written by Gustav
#ifndef DISPLAY_C
#define DISPLAY_C

#include <pic32mx.h>

/* Definitions taken from mipslabfunc.c start*/
#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)
/* end */


// Display buffer:
// The screen has 128x32 pixels. This means the buffer has a size of 512 bytes
char DisplayBuffer[512];

void DisplayBuffer_initialize() {
    int i;
    for (i = 0; i < 512; i++) {
        DisplayBuffer[i] = 0x0;
    }
    return;
}

// alias for DisplayBuffer_initialize
void DisplayBuffer_clr() {
    DisplayBuffer_initialize();
    return;
}



// returns the value of the pixel in coordinates
int DisplayBuffer_getPixel(int x, int y) {
    if (!((x >= 0) && (x <= 127)))
        return 0;
    if (!((y >= 0) && (y <= 31)))
        return 0;
   // to be implemented
}

// Returns 1 if arguments are invalid
// Returns 0 if pixel was sucessfully set.
int DisplayBuffer_setPixel(int x, int y, int val) {
    if (!((x >= 0) && (x <= 127)))
        return 1;
    if (!((y >= 0) && (y <= 31)))
        return 1;
    if (val != 0)
        val = 1;
/*
"...The display memory is
organized as four pages of 128 bytes each. Each memory page corresponds to an 8-pixel-high stripe across the
display. Each byte in the memory page corresponds to an 8-pixel-high column on the display. The least significant
bit in a display byte is the top most pixel, and the most significant bit the bottom most pixel. The first byte in the
page corresponds to the left most pixels on the display and the last byte the right most pixels."
    - Basic shield I/O manual, p.11
*/
    int offset = y/8; // what memory page?
    // x = what byte

    // We need to change only a pixel in the byte.
    // What position is y in, in the byte?
    char y_byte_position = y % 8; // 0 - 7
    
    if (val != 0)
        DisplayBuffer[x + offset*128] |= 1 << y_byte_position; // set pixel in buffer
    else
        DisplayBuffer[x + offset*128] &= ~(1 << y_byte_position); // unset pixel in buffer
    return 0;
}

// Returns 0 if display was successfully updated
// Returns 1 if error.
// to be called every tick
// Derived from display_image in mipslabwork.c
int DisplayBuffer_send() {
    int i, j;
    for (i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
         // set page command
         spi_send_recv(0x22);
         spi_send_recv(i);
         spi_send_recv(0);
         DISPLAY_CHANGE_TO_DATA_MODE;
        for (j = 0; j < 128; j++) {
            spi_send_recv(DisplayBuffer[i*128 + j]);
        }
    }
    return 0;
}

#endif