#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


Stack create_stack(int size)
{
    return (Stack){.data= malloc(sizeof(char) * size), .size = 0};
}

void push(Stack *stack, int value)
{
    stack->data[stack->size] = value;
    stack->top_value = stack->data[stack->size];
    stack->size++;
}

int pop(Stack *stack)
{
    if(!stack->size) return 0;

    int top_value = stack->top_value;
    int temp_index = --stack->size;
    stack->data[temp_index] = 0;
    if(temp_index == 0)
    {
        stack->top_value = stack->data[temp_index];
        return top_value;
    }
    stack->top_value = stack->data[--temp_index];

    return top_value;
}

int peek(Stack *stack)
{
    return stack->top_value;
}
