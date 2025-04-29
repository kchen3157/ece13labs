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

#define FAIL(...)                        \
    printf("failed: %s\n", __VA_ARGS__); \
    return -1;
#define PASS(...) printf("passed: %s\n", __VA_ARGS__);

int main(void)
{
    BOARD_Init();

    printf("\n###### Beginning CRUZID's stack test harness: ####\n\n");

    struct Stack stack;
    double temp;

    //* Check StackInit()
    // Check operation functions return errors/false on a uninitialized stack
    if (StackPush(&stack, 1) != STANDARD_ERROR)
    {
        FAIL("StackInit() Test: Uninitialized, StackPush() should return error")
    }
    if (StackPop(&stack, &temp) != STANDARD_ERROR)
    {
        FAIL("StackInit() Test: Uninitialized, StackPop() should return error")
    }
    if (StackIsEmpty(&stack) != FALSE)
    {
        FAIL("StackInit() Test: Uninitialized, StackIsEmpty() should return false")
    }
    if (StackIsFull(&stack) != FALSE)
    {
        FAIL("StackInit() Test: Uninitialized, StackIsFull() should return false")
    }
    if (StackGetSize(&stack) != SIZE_ERROR)
    {
        FAIL("StackInit() Test: Uninitialized, StackGetSize() should return error")
    }

    StackInit(&stack);

    // Check if currentItemIndex is updated correctly
    if (stack.currentItemIndex != -1)
    {
        FAIL("StackInit() Test: currentItemIndex not set properly");
    }
    // Check if StackIsEmpty is updated correctly
    if (!StackIsEmpty(&stack))
    {
        FAIL("StackInit() Test: StackIsEmpty not set properly");
        return -1;
    }
    // Check if StackIsFull is updated correctly
    if (StackIsFull(&stack))
    {
        FAIL("StackInit() Test: StackIsFull not set properly");
        return -1;
    }
    // Check if StackGetSize is updated correctly
    if (StackGetSize(&stack) != 0)
    {
        FAIL("StackInit() Test: StackGetSize not set properly");
        return -1;
    }

    PASS("StackInit() Test")

    //* Check StackPush()
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
        FAIL("StackPush() Test: currentItemIndex not set properly");
        return -1;
    }

    // Check if StackIsEmpty is updated correctly
    if (StackIsEmpty(&stack))
    {
        FAIL("StackPush() Test: StackIsEmpty not set properly");
        return -1;
    }
    // Check if StackIsFull is updated correctly
    if (StackIsFull(&stack))
    {
        FAIL("StackPush() Test: StackIsFull not set properly");
        return -1;
    }
    // Check if StackGetSize is updated correctly
    if (StackGetSize(&stack) != 7)
    {
        FAIL("StackPush() Test: StackGetSize not set properly");
        return -1;
    }

    // Check if stack is valid
    if (stack.stackItems[6] != 2 || stack.stackItems[5] != 9 || stack.stackItems[4] != 5 || stack.stackItems[3] != 1 || stack.stackItems[2] != 4 || stack.stackItems[1] != 1 || stack.stackItems[0] != 3)
    {
        FAIL("StackPush() Test: pushed items not stored properly (value incorrect)");
        return -1;
    }

    PASS("StackPush() Test")

    //* Check StackPop()
    StackPop(&stack, &temp);
    if (temp != 2)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 9)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 5)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 1)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 4)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 1)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }
    StackPop(&stack, &temp);
    if (temp != 3)
    {
        FAIL("StackPop() Test: incorrect value popped")
    }

    // Check if currentItemIndex is updated correctly
    if (stack.currentItemIndex != -1)
    {
        FAIL("StackPop() Test: currentItemIndex not set properly");
        return -1;
    }

    // Check if StackIsEmpty is updated correctly
    if (!StackIsEmpty(&stack))
    {
        FAIL("StackPop() Test: StackIsEmpty not set properly");
        return -1;
    }
    // Check if StackIsFull is updated correctly
    if (StackIsFull(&stack))
    {
        FAIL("StackPop() Test: StackIsFull not set properly");
        return -1;
    }
    // Check if StackGetSize is updated correctly
    if (StackGetSize(&stack) != 0)
    {
        FAIL("StackPop() Test: StackGetSize not set properly");
        return -1;
    }

    PASS("StackPop() Test")

    //* Check Stack handles underflow properly

    if (StackPop(&stack, &temp) != STANDARD_ERROR)
    {
        FAIL("Underflow Test: StackPop() should return error")
    }

    PASS("Underflow")

    //* Check Stack handles overflow properly
    // fill stack
    for (int i = 0; i < STACK_SIZE; i++)
    {
        if (StackPush(&stack, i) != SUCCESS)
        {
            FAIL("Overflow Test: Premature overflow")
        }
    }

    // Check if currentItemIndex is updated correctly
    if (stack.currentItemIndex != 19)
    {
        FAIL("Overflow Test: currentItemIndex not set properly");
        return -1;
    }

    // Check if StackIsEmpty is updated correctly
    if (StackIsEmpty(&stack))
    {
        FAIL("Overflow Test: StackIsEmpty not set properly");
        return -1;
    }
    // Check if StackIsFull is updated correctly
    if (!StackIsFull(&stack))
    {
        FAIL("Overflow Test: StackIsFull not set properly");
        return -1;
    }
    // Check if StackGetSize is updated correctly
    if (StackGetSize(&stack) != 20)
    {
        FAIL("Overflow Test: StackGetSize not set properly");
        return -1;
    }

    if (StackPush(&stack, 1) != STANDARD_ERROR)
    {
        FAIL("Overflow Test: StackPush() should return error")
    }

    PASS("Overflow Test")

    printf("All tests passed.\n");

    BOARD_End();
    // test stackInit:
    while (1)
        ;
    return 0;
}
