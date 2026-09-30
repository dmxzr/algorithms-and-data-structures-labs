#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stack_list.h"



Stack *init_stack(void){
	Stack *stack = (Stack *)calloc(1, sizeof(Stack));

	if(stack == NULL) return NULL;
	return stack;
}


Node *add_node(char data){
	Node *node = (Node *)calloc(1, sizeof(Node));

	if(node == NULL) return NULL; 

	node->next = NULL;
	node->data = data;

	return node;
}


int push(Stack *stack, char data){
	Node *node = add_node(data);
	
	if(node == NULL || stack == NULL) return errno; 

	node->next = stack->top;
	stack->top = node;
	return 0;
}


int pop(Stack *stack, char *data){

	if(stack == NULL || stack->top == NULL) return errno; // stack is empty
	Node *node = stack->top;
	*data = stack->top->data;
	stack->top = stack->top->next;
	free(node);
	return 0; //success
		
}


int free_stack(Stack *stack){

	if(stack == NULL || stack->top == NULL) return errno;
	
	Node *node = stack->top;
	Node *tmp = node;

	while(node != NULL){
		tmp = node->next;

		free(node);
		node = tmp;
	}
	free(stack);
	free(tmp);
	free(node);
	return 0;
}



int print_stack(Stack *stack){
	printf("Stack:\t");
	if(stack == NULL || stack->top == NULL) return errno;
	Node *node = stack->top;
	while(node != NULL){
		printf("%c", node->data);
		node = node->next;
	}	

	printf("\n");
	return 0;
}
