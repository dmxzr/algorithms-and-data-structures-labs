#include <stdio.h>

#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

typedef struct Stack{
	int size;
	int top;
	char *data;
} Stack;

int push(Stack *stack, char data);
int pop(Stack *stack, char *data);
Stack *init_stack(int stack_size);
int free_stack(Stack *stack);
int print_stack(Stack *stack);

#endif
