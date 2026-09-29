#ifndef STACK_H
#define STACK_H

typedef struct stack
{
    char *data;
    int top_value;
    int size;       // size really just points to the next empty cell in data
} Stack;

Stack create_stack(int size);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);

#endif
