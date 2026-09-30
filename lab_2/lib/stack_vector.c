#include <stdio.h>
#include <stdlib.h>
#include "stack_vector.h"

Stack *init_stack(int stack_size){
	Stack *stack = (Stack *)malloc(1 * sizeof(Stack));

	if(stack == NULL) return NULL; 

	stack->size = stack_size;
	stack->top = 0;
	stack->data = (char *)malloc(stack_size * sizeof(char));

	if(stack->data == NULL) return NULL; // bad alloc
	return stack;
}


int push(Stack *stack, char data){
	if(stack->top == stack->size) return 1; //overflow	
	stack->data[stack->top] = data;
	(stack->top)++;

	return 0;
}


int pop(Stack *stack, char *data){
	
	if(stack->top == 0) return 1; // stack is empty
	(stack->top)--;
	*data = stack->data[stack->top];

	
	return 0;
}


int free_stack(Stack *stack){
	free(stack->data);
	free(stack);
	return 0;
}

int print_stack(Stack *stack){
	printf("Stack:\t");

	if(stack->top == 0) return 1; //stack is empty
	else{
		for(int i = stack->top - 1; i >= 0; i--)
			printf("%c", stack->data[i]);
		printf("\n");
	}
	return 0;
}
