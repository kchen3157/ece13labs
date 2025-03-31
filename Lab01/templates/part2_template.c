/**
 * @file    part2.c
 *
 * Convert temperatures from Fahrenheit to Celsius and Kelvin.
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


/**
 * There can be only one!
 */
int main(void) {
    BOARD_Init();
    while(1)
    {
        /***********************************************************************
         * Your code goes in between this comment and the following one with   *
         * asterisks.                                                          *
         **********************************************************************/

        /***********************************************************************
         * Your code goes in between this comment and the preceding one with   *
         * asterisks.                                                          *
         **********************************************************************/
        HAL_Delay(3333);
    }
    BOARD_End();
    // Returning from main() is bad form in embedded environments.
    // So we sit and spin.
    while(1);
}
