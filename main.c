#include <stdio.h>
#include "stack.h"
#include "heap_store.h"

unsigned char tape[30000] = { 0 };

//given a valid instruction converts it to the array index that holds the instructional function
int convert(int c);

void move_pointer_increment(unsigned char **pointer, PROGRAM *program, Stack *stack);
void move_pointer_decrement(unsigned char **pointer, PROGRAM *program, Stack *stack);

void pointer_increment(unsigned char **pointer, PROGRAM *program, Stack *stack);
void pointer_decrement(unsigned char **pointer, PROGRAM *program, Stack *stack);

void print_out(unsigned char **pointer, PROGRAM *program, Stack *stack);
void input_in(unsigned char **pointer, PROGRAM *program, Stack *stack);

void loop1(unsigned char **pointer, PROGRAM *program, Stack *stack);
void loop2(unsigned char **pointer, PROGRAM *program, Stack *stack);

int main(int argc, char *argv[]) {
    if (argc == 1) {printf("Bro you gotta pass an input file\n"); return -1;}


    unsigned char *data_pointer = tape;
    int c, proc;
    
    Stack stack = create_stack();

    FILE *input_txt = fopen(argv[1], "r");
    if (input_txt == NULL) {
        printf("Could not open %s\n", argv[1]);
        destroy_stack(stack);
        return 1;
    }

    PROGRAM program = create_program();
    
    //clean sanitize and prog
    while ((c = fgetc(input_txt)) != EOF) {
        //proc = convert(c);
        //if (proc >= 0 && proc <= 7)
        add_c(program, c);
    }

    fclose(input_txt);

    rewind_program(program);
    

    //[0] = +
    //[1] = ,
    //[2] = -
    //[3] = .
    //[4] = <
    //[5] = >
    //[6] = [
    //[7] = ]
    void (*instructions[8])(unsigned char **, PROGRAM *, Stack *) = { // function pointers to interpreter calls
        &pointer_increment,
        &input_in,
        &pointer_decrement,
        &print_out,
        &move_pointer_decrement,
        &move_pointer_increment,
        &loop1,
        &loop2
    };


    do {
        proc = convert(get_c(program));
        if (proc >= 0 && proc <= 7)
            (*instructions[proc])(&data_pointer, &program, &stack);
    } while (advance_program(program));
    



    destroy_stack(stack);
    destroy_program(&program);
    return 0;
}


//sanitize and clean, e.g only process valid commands, everything else is out of the proc limit
int convert(int c) {
    int n = -1;
    if (c == '+') n = 0;
    if (c == ',') n = 1;
    if (c == '-') n = 2;
    if (c == '.') n = 3;
    if (c == '<') n = 4;
    if (c == '>') n = 5;
    if (c == '[') n = 6;
    if (c == ']') n = 7;

    return n;
}

void move_pointer_increment(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    if (*pointer < tape + 29999)  // stay within tape
        (*pointer)++;

}

void move_pointer_decrement(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    if (*pointer > tape)           // don't go below start
        (*pointer)--;

}

void pointer_increment(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    (**pointer)++;
}

void pointer_decrement(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    (**pointer)--;
}

void print_out(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    printf("%c", **pointer);
}

void input_in(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    scanf("%c", *pointer);
}

void loop1(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    if (**pointer == 0) {
        int c, depth = 0;
        do {
            c = get_c(*program);                     // make sure we exit on the right depth, this will avoid nested loops from quitting when seeing the first ]
            
            if (c == '[') depth++;
            if (c == ']') depth--;

        } while (advance_program(*program) && depth > 0);               // make sure that we have resolved every []
    } else {
        stack_push(*stack, get_program_location(*program));      // push to the stack as we might need to return here after the loop body executes
    }


}

void loop2(unsigned char **pointer, PROGRAM *program, Stack *stack) {
    if (**pointer != 0) {
        if (!is_stack_empty(*stack)) {         // check if the stack is empty and if not then seek out the loop 
            unsigned long long top = stack_top(*stack); // safe 
            seek_program_location(*program, top);
            
        }
    } else {
        if (!is_stack_empty(*stack)) {      // again check if the stack is empty, this time pop because we are leaving the loop
            stack_pop(*stack, NULL);    // ignore the pop value as we do not need it this time
        }
    }
}

