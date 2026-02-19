#include <stdio.h>
#include "stack.h"

unsigned char tape[30000] = { 0 };

//given a valid instruction converts it to the array index that holds the instructional function
int convert(int c);

void move_pointer_increment(unsigned char **pointer, FILE *stream, Stack *stack);
void move_pointer_decrement(unsigned char **pointer, FILE *stream, Stack *stack);

void pointer_increment(unsigned char **pointer, FILE *stream, Stack *stack);
void pointer_decrement(unsigned char **pointer, FILE *stream, Stack *stack);

void print_out(unsigned char **pointer, FILE *stream, Stack *stack);
void input_in(unsigned char **pointer, FILE *stream, Stack *stack);

void loop1(unsigned char **pointer, FILE *stream, Stack *stack);
void loop2(unsigned char **pointer, FILE *stream, Stack *stack);

int main(int argc, char *argv[]) {
    if (argc == 1) {printf("Bro you gotta pass an input file\n"); return -1;}


    unsigned char *data_pointer = tape;
    int c, proc;
    
    Stack stack = create_stack();

    FILE *input_txt = fopen(argv[1], "r");
    if (input_txt == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }


    

    //[0] = +
    //[1] = ,
    //[2] = -
    //[3] = .
    //[4] = <
    //[5] = >
    //[6] = [
    //[7] = ]
    void (*instructions[8])(unsigned char **, FILE *, Stack *) = { // function pointers to interpreter calls
        &pointer_increment,
        &input_in,
        &pointer_decrement,
        &print_out,
        &move_pointer_decrement,
        &move_pointer_increment,
        &loop1,
        &loop2
    };

    while ((c = fgetc(input_txt)) != EOF) {
        proc = convert(c);     // check if this is a valid input, one that is from the instruction set
        if (proc >= 0 && proc <= 7)       // if this is withing our instructional range, protecting from ones that get passed through convert
            (*instructions[proc])(&data_pointer, input_txt, &stack);     // call with our current data pointer, input file (merely for jumping the pointer), and stack
    }



    fclose(input_txt);
    destroy_stack(stack);
    return 0;
}


//sanitize and clean, e.g only process valid commands, everything else is out of the proc limit
int convert(int c) {
    int n = -1;
    if (c == 43) n = 0;
    if (c == 44) n = 1;
    if (c == 45) n = 2;
    if (c == 46) n = 3;
    if (c == 60) n = 4;
    if (c == 62) n = 5;
    if (c == 91) n = 6;
    if (c == 93) n = 7;

    return n;
}

void move_pointer_increment(unsigned char **pointer, FILE *stream, Stack *stack) {
    if (*pointer < tape + 29999)  // stay within tape
        (*pointer)++;

}

void move_pointer_decrement(unsigned char **pointer, FILE *stream, Stack *stack) {
    if (*pointer > tape)           // don't go below start
        (*pointer)--;

}

void pointer_increment(unsigned char **pointer, FILE *stream, Stack *stack) {
    (**pointer)++;
}

void pointer_decrement(unsigned char **pointer, FILE *stream, Stack *stack) {
    (**pointer)--;
}

void print_out(unsigned char **pointer, FILE *stream, Stack *stack) {
    printf("%c", **pointer);
}

void input_in(unsigned char **pointer, FILE *stream, Stack *stack) {
    scanf("%c", *pointer);
}

void loop1(unsigned char **pointer, FILE *stream, Stack *stack) {
    if (**pointer == 0) {
        int c, depth = 1;
        do {

            c = fgetc(stream);
            if (c == '[') depth++;
            if (c == ']') depth--;

        } while (c != EOF && depth > 0);
    } else {
        stack_push(*stack, ftell(stream));
    }


}

void loop2(unsigned char **pointer, FILE *stream, Stack *stack) {
    if (**pointer != 0) {
        if (!is_stack_empty(stack)) {
            unsigned long long top = stack_top(*stack); // safe peek
            fseek(stream, top, SEEK_SET);
        } else {
            // cell != 0 but stack empty? just continue
        }
    } else {
        if (!is_stack_empty(*stack)) {
            unsigned long long dummy;
            stack_pop(stack, &dummy);
        }
    }
}

