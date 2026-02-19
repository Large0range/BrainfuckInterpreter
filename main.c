#include <stdio.h>

struct instruction {
    void *function;
    char character;
};



//given a valid instruction converts it to the array index that holds the instructional function
int convert(char c);

void move_pointer_increment(unsigned char **pointer, FILE *stream);
void move_pointer_decrement(unsigned char **pointer, FILE *stream);

void pointer_increment(unsigned char **pointer, FILE *stream);
void pointer_decrement(unsigned char **pointer, FILE *stream);

void print_out(unsigned char **pointer, FILE *stream);
void input_in(unsigned char **pointer, FILE *stream);

void loop1(unsigned char **pointer, FILE *stream);
void loop2(unsigned char **pointer, FILE *stream);

int main(int argc, char *argv[]) {
    if (argc == 1) return -1;

    unsigned char tape[20] = { 0 };
    unsigned char *data_pointer = tape;

    FILE *input_txt = fopen(argv[1], "r");

    //[0] = +
    //[1] = ,
    //[2] = -
    //[3] = .
    //[4] = <
    //[5] = >
    //[6] = [
    //[7] = ]
    void (*instructions[8])(unsigned char **, FILE *) = { // function pointers to interpreter calls
        &pointer_increment,
        &input_in,
        &pointer_decrement,
        &print_out,
        &move_pointer_decrement,
        &move_pointer_increment,
        &loop1,
        &loop2
    };

    char c;
    int proc;

    while ((c = fgetc(input_txt)) != EOF) {

        proc = convert(c);     // check if this is a valid input, one that is from the instruction set
        if (proc >= 0 && proc <= 7)       // if this is withing our instructional range
            (*instructions[proc])(&data_pointer, input_txt);     // call with our current data pointer and input file (merely for jumping the pointer)

    }



    fclose(input_txt);
    return 0;
}

int convert(char c) {
    int n = c - 43;
    if (n == 17) n = 4;
    if (n == 19) n = 5;
    if (n == 48) n = 6;
    if (n == 50) n = 7;

    return n;
}

void move_pointer_increment(unsigned char **pointer, FILE *stream) {
    (*pointer)++;
}

void move_pointer_decrement(unsigned char **pointer, FILE *stream) {
    (*pointer)--;
}

void pointer_increment(unsigned char **pointer, FILE *stream) {
    (**pointer)++;
}

void pointer_decrement(unsigned char **pointer, FILE *stream) {
    (**pointer)--;
}

void print_out(unsigned char **pointer, FILE *stream) {
    printf("%d", **pointer);
}

void input_in(unsigned char **pointer, FILE *stream) {
    scanf("%c", *pointer);
}

void loop1(unsigned char **pointer, FILE *stream) {
    char c;
    if (**pointer == 0) {
        do {
            c = fgetc(stream);
        } while (c != EOF && c != ']');
    }  // jump the pointer

}
void loop2(unsigned char **pointer, FILE *stream) {
    if (**pointer != 0) {

    }
}

