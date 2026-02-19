#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack_item;
struct stack;

typedef struct stack_item {
    struct stack_item *below;
    int data;
} StackItem;

typedef struct stack {
    struct stack_item *top;
} STACK;



Stack create_stack() {
    STACK *pStack = (STACK *)malloc(sizeof(STACK)); // cast to known type
    if (pStack == NULL) {                                // check if allocation can be made
        printf("Could not create new stack\n");   // alert user if we cannot create a new stack
        return NULL;                                     
    }

    pStack->top = NULL;      // setup the stack so there is no top value

    return pStack; 
}

void destroy_stack(Stack hStack) {
    STACK *pStack = (STACK *)hStack;
    int a; //throw away variable to store the popping

    while (!is_stack_empty(hStack)) {
        stack_pop(hStack, &a);
    }

    free(hStack); // free the stack at the end
}


//push an item onto the stack
void stack_push(Stack *hStack, int data) {
    STACK *pStack = (STACK *)hStack; 

    StackItem *new_item = (StackItem *)malloc(sizeof(StackItem));  //create our new stack item
    if (new_item == NULL) {  // check if it fails and return, alerting the user if it does fail
        printf("Could not create new item\n");
        return;
    }

    new_item->below = pStack->top;  //point our top item to the top item in the stack
    new_item->data = data; 

    pStack->top = new_item; //make our new item the top of the stack pointing downwards at the former first item
}

void stack_pop(Stack *hStack, int *data) { 
    STACK *pStack = (STACK *)hStack; 
    StackItem *pTopItem = pStack->top;               //get the item on top of the stack

    if (pTopItem == NULL) {                      //if the stack is empty then return, there is nothing to pop
        return;
    }

    pStack->top = pTopItem->below;        //make our top item the one below
    *data = pTopItem->data;               //get the data of the former top item

    free(pTopItem);                  //free the top item, the user does not have access to StackItem so we free to avoid a memory leak
}

int stack_top(Stack *hStack) {
    STACK *pStack = (STACK *)hStack;
    
    return pStack->top->data;           //return the data of the top item
}

int is_stack_empty(Stack *hStack) {
    STACK *pStack = (STACK *)hStack;

    return (pStack->top == NULL);        //check if there is a top item
}