#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "lib/stack_list.h"

int is_operator(char symbol){
	return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/');
}

int priority(char symbol){
	switch(symbol){
		case '+':
			return 1;
		case '-': 
			return 1;
		case '*':
			return 2;
		case '/':
			return 2;
		default:
			return 0;
	}
}


int main(){
	Stack *stack = init_stack();
	//Stack *postfix = init_stack();

	char *symbol = NULL; 
	symbol =(char *)calloc(1, sizeof(char));

	
	//ввод выражения

	char *infix;
	infix = readline("Введите выражение в инфиксном виде: ");
	

	//преобразование
	char *postfix = NULL;
	postfix = (char *)calloc((strlen(infix) + 1), sizeof(char));
	unsigned long j = 0;
	for(unsigned long i = 0 ; i < strlen(infix); i++){

		if(!is_operator(infix[i]) && infix[i] != '(' && infix[i] != ')'){
			postfix[j++] = infix[i];
		}

		else{
			if(is_operator(infix[i])){
				if(stack->top == NULL || stack->top->data == '('){
					push(stack, infix[i]);}
				if(priority(infix[i]) > priority(stack->top->data)){
					push(stack, infix[i]);
				}			
				else{
					while(stack->top != NULL && (stack->top->data != '(' || priority(stack->top->data) >= priority(infix[i]))){
						pop(stack, symbol);
						postfix[j++] = *symbol;
						}
					push(stack, infix[i]);
				}
			}
			
			if(infix[i] == '('){
				push(stack, infix[i]);
			}
			if(infix[i] == ')'){
				while(stack->top->data != '('){
					pop(stack, symbol);
					postfix[j++] = *symbol;
				}
				pop(stack, symbol);
			}
			
		}
	

	}
	while(stack->top != NULL){
		pop(stack, symbol);
		postfix[j++] = *symbol;
		
	
	}

		
	// вывод и фри
	//	print_stack(stack);
		free_stack(stack);
		printf("Постфиксная форма записи: ");
		for(unsigned long k= 0; k < j; k++) {
			printf("%c", postfix[k]);}
		free(infix);
		free(postfix);
		free(symbol);
	}
	
	
	


/*
int main(){
	char *data = NULL; 
	data =(char *)malloc(1 * sizeof(char));
	Stack *stack = init_stack();
	char a = 'Z', b = 'X';
	push(stack, a);
	push(stack, b);
	print_stack(stack);

	char x = 'Y';
	push(stack, x);
	pop(stack, data);
	print_stack(stack);
	free_stack(stack);
	printf("data: %c\n", *data);
}
*/
