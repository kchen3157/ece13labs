/**
 * @file    Lab05_main.c
 *
 * @author
 *
 * @date
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Course library.
#include "BOARD.h"

// User libraries.
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input.
#define MAX_INPUT_LENGTH 60

int main(void)
{
    BOARD_Init();

    // What follows is starter code. You will need to modify it!
    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf(
        "Welcome to CRUZID'S RPN calculator.  Compiled on %s %s\n",
        __DATE__,
        __TIME__);
    while (TRUE)
    {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof(rpn_sentence), stdin);

        // get rid of last \n following input
        char *rpn_sentence_ptr = rpn_sentence;
        while (TRUE)
        {
            if (*rpn_sentence_ptr == '\n')
            {
                *rpn_sentence_ptr = '\0';
                break;
            }
            rpn_sentence_ptr++;
        }

        int error = RPN_Evaluate(rpn_sentence, &result);

        switch (error)
        {
        case RPN_NO_ERROR:
            printf("result = %f\n", result);
            break;
        case RPN_ERROR_STACK_OVERFLOW:
            printf("Error: Stack overflow.\n");
            break;
        case RPN_ERROR_STACK_UNDERFLOW:
            printf("Error: Stack underflow.\n");
            break;
        case RPN_ERROR_INVALID_TOKEN:
            printf("Error: Invalid token/operator.\n");
            break;
        case RPN_ERROR_DIVIDE_BY_ZERO:
            printf("Error: Cannot divide by 0.\n");
            break;
        case RPN_ERROR_TOO_FEW_ITEMS_REMAIN:
            printf("Error: Too few operands to complete computation.\n");
            break;
        case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
            printf("Error: More than one item on stack following computation. Too few operators.\n");
            break;
        default:
            printf("Error: Unknown error.\n");
        }
    }

    while (TRUE)
        ;
}
