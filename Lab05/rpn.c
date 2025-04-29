/**
 * @file    rpn.c
 *
 * @author Kyle Chen
 *
 * @date 2025-04-16
 */

// Standard library includes
#include <string.h>
#include <stdlib.h>

// User includes
#include "rpn.h"
#include "stack.h"

int ProcessOperator(struct Stack *rpn_stack_ptr, char operator);

int RPN_Evaluate(char *rpn_string, double *result)
{
    // user defined vars
    struct Stack rpn_stack;

    StackInit(&rpn_stack);

    //* Process tokens via stack
    char *token_ptr = strtok(rpn_string, " "); // Init strtok(), read first token
    while (token_ptr != NULL)
    {
        //* Check if token is a number
        char *token_end_ptr;
        double token_numval = strtod(token_ptr, &token_end_ptr);

        if (*token_end_ptr == '\0') // If token is a number, push to stack
        {
            if (StackPush(&rpn_stack, token_numval) == STANDARD_ERROR)
            {
                return RPN_ERROR_STACK_OVERFLOW;
            }
        }
        else // If token is operator, perform operation on stack
        {
            int error_status = ProcessOperator(&rpn_stack, *token_end_ptr);
            if (error_status != RPN_NO_ERROR)
            {
                return error_status;
            }
        }

        // Next token
        token_ptr = strtok((char *)NULL, " ");
    }

    // RPN eval processing complete. Check if singular answer remains
    if (StackGetSize(&rpn_stack) > 1)
    {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    else if (StackGetSize(&rpn_stack) < 1)
    {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }

    if (StackPop(&rpn_stack, result) == STANDARD_ERROR)
    {
        //! Should never get here. All cases should be handled by RPN_ERROR_TOO_FEW_ITEMS_REMAIN
        return RPN_ERROR_STACK_UNDERFLOW;
    }

    return RPN_NO_ERROR;
}

int ProcessOperator(struct Stack *rpn_stack_ptr, char operator)
{
    double operand1, operand2;

    if (operator != '-' && operator != '+' && operator != '*' && operator != '/')
    {
        return RPN_ERROR_INVALID_TOKEN;
    }

    if (StackGetSize(rpn_stack_ptr) < 2)
    {
        return RPN_ERROR_STACK_UNDERFLOW;
    }

    if (StackPop(rpn_stack_ptr, &operand1) == STANDARD_ERROR)
    {
        //! Should never get here. All cases should be handled by above
        return RPN_ERROR_STACK_UNDERFLOW;
    }
    if (StackPop(rpn_stack_ptr, &operand2) == STANDARD_ERROR)
    {
        //! Should never get here. All cases should be handled by above
        return RPN_ERROR_STACK_UNDERFLOW;
    }

    if (operator== '+')
    {
        if (StackPush(rpn_stack_ptr, operand2 + operand1) == STANDARD_ERROR)
        {
            //! Should never get here. Operators decrease stack size
            return RPN_ERROR_STACK_OVERFLOW;
        }
    }
    else if (operator== '-')
    {
        if (StackPush(rpn_stack_ptr, operand2 - operand1) == STANDARD_ERROR)
        {
            //! Should never get here. Operators decrease stack size
            return RPN_ERROR_STACK_OVERFLOW;
        }
    }
    else if (operator== '*')
    {
        if (StackPush(rpn_stack_ptr, operand2 * operand1) == STANDARD_ERROR)
        {
            //! Should never get here. Operators decrease stack size
            return RPN_ERROR_STACK_OVERFLOW;
        }
    }
    else if (operator== '/')
    {
        if (operand1 == 0)
        {
            return RPN_ERROR_DIVIDE_BY_ZERO;
        }

        if (StackPush(rpn_stack_ptr, operand2 / operand1) == STANDARD_ERROR)
        {
            //! Should never get here. Operators decrease stack size
            return RPN_ERROR_STACK_OVERFLOW;
        }
    }

    return RPN_NO_ERROR;
}

int ProcessBackspaces(char *rpn_sentence)
{
    int size_var = (sizeof(*rpn_sentence) / sizeof(char)) - 1;

    char *save_ptr = rpn_sentence;
    char *read_ptr = rpn_sentence;

    while (*read_ptr != '\0')
    {
        if (*read_ptr == '\b')
        {
            size_var -= 2;
            read_ptr++;
            save_ptr--;
            continue;
        }
        else
        {
            *save_ptr = *read_ptr;
            read_ptr++;
            save_ptr++;
        }
    }

    *save_ptr = '\0';

    return size_var;
}
