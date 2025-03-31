/**
 * @file    part3.c
 *
 * Hello, OLED!
 *
 * @author  Roronoa Zoro (rorozoro3ucsc.edu)
 * 
 * @date    January 1, 1970
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>
#include <Oled.h>


/**
 * This time with an OLED screen.
 */
int main(void) {
    BOARD_Init();

    /***************************************************************************
     * Your code goes in between this comment and the following one with       *
     * asterisks.                                                              *
     **************************************************************************/
    OLED_Init();
    OLED_DrawString("Hello World!");
    OLED_Update();
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with       *
     * asterisks.                                                              *
     **************************************************************************/

    BOARD_End();    // Handles cleanup of the system.
    while(1);       // If embedded, we should never exit.
}

