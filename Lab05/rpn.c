/**
 * @file    rpn.c
 *
 * @author Kyle Chen
 *
 * @date 2025-04-16
 */

 #include <string.h>
 #include <stdlib.h>

 #include "rpn.h"
 #include "stack.h"



 /* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 *
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 *
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate rpn_error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
 int RPN_Evaluate(char *rpn_string, double *result)
 {
    const char SPACE = ' ';
    struct Stack rpn_stack;

    char token;
    char *token_ptr = &token;

    double operand1, operand2;
    
    StackInit(&rpn_stack);

    //* Load tokens into stack
    token_ptr = strtok(rpn_string, &SPACE); // Init strtok(), read first token
    do
    {
        // End of string
        if (token_ptr == NULL)
        {
            break;
        }

        // Check if token is a number
        char* token_end_ptr;
        double token_numval = strtod(token_ptr, &token_end_ptr);

        if (*token_end_ptr == '\0') // If token is a number
        {
            StackPush(&rpn_stack, token_numval);
        }
        else // If token is operator
        {
            StackPop(&rpn_stack, &operand1);
            StackPop(&rpn_stack, &operand2);

            if (*token_end_ptr == '+')
            {
                StackPush(&rpn_stack, operand1 + operand2);
            }
            else if (*token_end_ptr == '-')
            {
                StackPush(&rpn_stack, operand1 - operand2);
            }
            else if (*token_end_ptr == '*')
            {
                StackPush(&rpn_stack, operand1 * operand2);
            }
            else if (*token_end_ptr == '/')
            {
                StackPush(&rpn_stack, operand1 / operand2);
            }
        }

        // Next token
        token_ptr = strtok((char*) NULL, &SPACE);
    } while (!(StackIsEmpty(&rpn_stack)));

    StackPop(&rpn_stack, result);
    return 0;
 }

 /**
 * This function should read through an array of characters, checking for 
 * backspace characters.  When it encounters a backspace character, it 
 * eliminates the backspace, the preceeding character (if such a character 
 * exists), and shifts all subsequent characters as appropriate.
 *
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an
 *        output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces 
 * and also strings with more backspaces than characters. It should be able 
 * to handle strings of at least 255 length. 
 * */
 int ProcessBackspaces(char *rpn_sentence)
 {
    int size_var = (sizeof(*rpn_sentence) / sizeof(char)) - 1;

    char result[size_var];
    
    for (int i = 0; i < size_var; i++)
    {
        char* result_ptr = result;
        char* rpn_sentence_ptr = rpn_sentence;
        if (*rpn_sentence == '\b')
        {
            size_var--;
            rpn_sentence_ptr++;
            continue;
        }
        *result_ptr = *rpn_sentence_ptr;
        result_ptr++;
        rpn_sentence_ptr++;
        
    }
    return size_var;
 }
