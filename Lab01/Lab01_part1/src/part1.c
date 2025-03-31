/**
 * @file    part1.c
 *
 * A brief journey through the debugging and styling of C code.  
 *
 * @author  Roronoa Zoro (rorozoro3@ucsc.edu)
 * 
 * @date    January 1, 1970
 */
// **** Include libraries up here. ****
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>


/**
 * main()
 * 
 * Put some information about this function here.
 *
 * @return (int) Describe what is returned by a function here. In this case,
 *               the int 0 is returned to indicate successful program execution.
 *
 *               NOTE: In C, the main() function does this implicitly so you
 *                     can skip the "@return" portion of this description, as
 *                     well as omit the "return" statement on the last line
 *                     of this function.
 *               
 *               NOTE: You can also omit the title of "main()" above since there
 *                     can only be one "main()" function per program.
 */
int main(void) {
    BOARD_Init();
    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

    // Sort the array in place.
    int i, j;
    for (i = 0; i < 5; i++) {
        int aTemp = valsToBeSorted[i];
        for (j = i - 1; j >= 0; j--) {
            if (valsToBeSorted[j] <= aTemp)
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];
        }
        valsToBeSorted [j + 1] = aTemp;
    }

    // Print out the array.
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\r\n", valsToBeSorted[i]);

    // Sorted array: [4, 41, 45, 70, 207]

    BOARD_End();
    /* Returning from main() is bad form in embedded environments. So we
     * sit and spin.                                                          */
    while(1);
}
