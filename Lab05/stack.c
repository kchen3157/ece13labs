/**
 * @file    stack.c
 *
 * @author Kyle Chen
 *
 * @date 2025-04-16
 */


 #include "stack.h"

 void StackInit(struct Stack *stack)
 {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
 }

 int StackPush(struct Stack *stack, double value)
 {
    if (stack->currentItemIndex >= (STACK_SIZE - 1) || !(stack->initialized == TRUE))
    {
        return STANDARD_ERROR;
    }
    stack->currentItemIndex++;
    stack->stackItems[stack->currentItemIndex] = value;
    return SUCCESS;
 }

 int StackPop(struct Stack *stack, double *value)
 {
    if (stack->currentItemIndex <= -1 || !(stack->initialized == TRUE))
    {
        return STANDARD_ERROR;
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex--;
    return SUCCESS;
 }

 int StackIsEmpty(const struct Stack *stack)
 {
    return ((stack->initialized == TRUE) && stack->currentItemIndex <= -1) ? TRUE : FALSE;
 }

 int StackIsFull(const struct Stack *stack)
 {
    return ((stack->initialized == TRUE) && stack->currentItemIndex >= (STACK_SIZE - 1)) ? TRUE : FALSE;
 }

 int StackGetSize(const struct Stack *stack)
 {
    if (!(stack->initialized == TRUE))
    {
        return SIZE_ERROR;
    }
    return (stack->currentItemIndex + 1);
 }
