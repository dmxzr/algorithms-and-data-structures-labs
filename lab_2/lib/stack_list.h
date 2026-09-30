#include <stdio.h>

#ifndef STACK_LIST_H
#define STACK_LIST_H

typedef struct Node{
	char data;
	struct Node *next;
} Node;

typedef struct Stack{
	Node *top;
} Stack;



int push(Stack *stack, char data);
int pop(Stack *stack, char *data);
Node *add_node(char data);
Stack *init_stack(void);
int free_stack(Stack *stack);
int print_stack(Stack *stack);

#endif
