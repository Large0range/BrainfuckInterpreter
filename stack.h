#ifndef STACK_H
#define STACK_H


typedef void * Stack;

Stack create_stack();
void destroy_stack(Stack hStack);

void stack_push(Stack *hStack, int data);
void stack_pop(Stack *hStack, int *data);

int stack_top(Stack *hStack);
int is_stack_empty(Stack *hStack);
#endif