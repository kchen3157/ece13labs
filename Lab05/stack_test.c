/**
 * @file    stack_test.c
 *
 * @author
 *
 * @date
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course library.
#include "BOARD.h"

// User libraries.
#include "stack.h"


int main(void)
{
    BOARD_Init();

    printf("\n###### Beginning CRUZID's stack test harness: ####\n\n");

    // What follows is starter code. You will need to modify it!
    
    struct Stack stack;

    //* Check Stack initializes properly
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    StackInit(&stack);
    if (stack.currentItemIndex != -1)
    {
        printf("failed\n");
    }
    printf("passed\n");

    //* Check Stack stores values properly
    printf("Does StackPush() store values properly?\n");
    // Push digits of pi
    StackPush(&stack, 3);
    StackPush(&stack, 1);
    StackPush(&stack, 4);
    StackPush(&stack, 1);
    StackPush(&stack, 5);
    StackPush(&stack, 9);
    StackPush(&stack, 2);

    // Check if currentItemIndex is updated correctly
    if (stack.currentItemIndex != 6)
    {
        printf("failed\n");
    }

    // Check if stack is valid
    if (stack.stackItems[6] != 2 
        || stack.stackItems[5] != 9 
        || stack.stackItems[4] != 5 
        || stack.stackItems[3] != 1 
        || stack.stackItems[2] != 4 
        || stack.stackItems[1] != 1 
        || stack.stackItems[0] != 3)
    {
        printf("failed\n");
    } 

    printf("passed\n");

    //* Check Stack handles overflow properly

    // Pop digits of pi
    double value;
    StackPop(&stack, &value);
    if (value != 2) {
        printf("failed\n");
    }
    StackPop(&stack, &value);
    if (value != 9) {
        printf("failed\n");
    }
    
    BOARD_End();
    //test stackInit:
    while (1);
    return 0;
}


