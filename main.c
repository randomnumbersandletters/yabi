#include <stdio.h>
#include <stdint.h>
#include "utils/stack.h"

constexpr int MEMORY_SIZE = 30000;
uint32_t DATA_POINTER = 0;
uint32_t PROGRAM_POINTER = 0;
Stack parenthesis_stack;


void skip_loop(char *program)
{
    while(program[PROGRAM_POINTER] != ']')
    {
        PROGRAM_POINTER++;
    }
}


void evaluate_loop()
{
    if(!parenthesis_stack.size) return; // if parenthesis stack is empty (there is no loop) return to caller

    PROGRAM_POINTER = pop(&parenthesis_stack);
    PROGRAM_POINTER--;                  // move it back one cell so that the next loop eval stores [ in stack again
}


void interpret_token(char token, uint8_t *memory, char *program)
{
    switch(token)
    {
        case '+':
            memory[DATA_POINTER]++;
            break;

        case '-':
            memory[DATA_POINTER]--;
            break;

        case '>':
            if(DATA_POINTER == MEMORY_SIZE)
            {
                DATA_POINTER = 0;
                return;
            }
            DATA_POINTER++;
            break;

        case '<':
            if(!DATA_POINTER) return;
            DATA_POINTER--;
            break;

        case '.':
            putchar(memory[DATA_POINTER]);
            break;

        case ',':
            memory[DATA_POINTER] = getc(stdin);
            while(getc(stdin) != '\n'){}        // BF can only read ONE character from the user, this loop flushes STDIN
            break;

        case '[':
            if(!memory[DATA_POINTER])
            {
                skip_loop(program);
                return;
            }
            push(&parenthesis_stack, PROGRAM_POINTER);
            break;

        case ']':
            if(memory[DATA_POINTER] == 0)
            {
                pop(&parenthesis_stack);
                break;
            }
            evaluate_loop();
            break;
        
        default:
            break;
    }
}


int main(int argc, char **argv)
{
    uint8_t memory[MEMORY_SIZE] = {0};
    char program[300] = {0};
    parenthesis_stack = create_stack(100);

    if(argc != 2)
    {
        printf("USAGE: ./yabi <your bf program>\n");
        return 0;
    }

    FILE *bf_file = fopen(argv[1], "r");
    if(!bf_file)
    {
        printf("COULD NOT OPEN FILE!\n");
        return 1;
    }
    fread(program, 1, 300, bf_file);

    for(PROGRAM_POINTER; program[PROGRAM_POINTER]; PROGRAM_POINTER++)
    {
        interpret_token(program[PROGRAM_POINTER], memory, program);
    }

    destroy_stack(&parenthesis_stack);

    return 0;
}
