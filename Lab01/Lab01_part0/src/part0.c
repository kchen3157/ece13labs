/**
* @file part0.c
*
* Every file should start with a header like this.
*
* @author Roronoa Zoro (rorozoro3@ucsc.edu)
*
* @date 1 Jan 1970
*/

// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <BOARD.h>

/**
* Hello Nucleo!
*/
int main(void) {
BOARD_Init();
while(1) // In embedded systems, main should never exit.
{
printf("Hello World!\r\n");
HAL_Delay(333); // Add a delay, in ms, before the next iteration.
}
BOARD_End(); // Handles cleanup of the system.
}
