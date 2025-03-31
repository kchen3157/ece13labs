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
        // Declare variables.
        float fahr, celsius, kelv;
        int lower, upper, step;

        // Initialize variables.
        lower = 0;
        upper = 300;
        step = 20;
        fahr = lower;
        kelv = lower;

        

        // Print out the Fahrenheit -> Celsius table.
        printf("    F     C\n");
        while (fahr <= upper) 
        {
            celsius = (5.0 / 9.0) * (fahr - 32.0);
            printf("%7.1f %04.0f\r\n", (double) fahr, (double) celsius);
            fahr = fahr + step;
        }
        // Print out the Kelvin -> Fahrenheit table.
        printf("    K    F\n");
        while (kelv <= upper)
        {
            fahr = (kelv - 273.15) * (9.0 / 5.0) + 32.0;
            printf("%7.3f %6.1f\r\n", (double) kelv, (double) fahr);
            kelv += step;
        }
        

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
