#include "heap_store.h"
#include <stdlib.h>
#include <stdio.h>

struct program {
    char *prog;
    char *prog_pointer;
    unsigned long long capacity;
    unsigned long long size;
};

typedef struct program Program;

PROGRAM create_program() {
    Program* p = (Program *)malloc(sizeof(Program));
    if (p != NULL) {
        p->prog = (char *)malloc(1);
        p->prog_pointer = p->prog;
        p->capacity = 1;
        p->size = 0;
    }

    return p;
}
void destroy_program(PROGRAM *hProgram) {
    Program *p = (Program *)*hProgram;
    free(p->prog);
    free(p);

    *hProgram = NULL;
}

void add_c(PROGRAM hProgram, char c) {
    Program *program = (Program *)hProgram;

    if (program->capacity == program->size) { // then we have too many things in the program and need to resize
        char *old_data = program->prog;
        
        program->prog = (char *)malloc(program->capacity * 2);
        if (program->prog == NULL) {
            printf("Could not resize program\n");
            return;
        }

        for (int i = 0; i < program->capacity; i++) {
            program->prog[i] = old_data[i];
        }

        program->capacity *= 2;
        program->prog_pointer = program->prog + program->size;

        free(old_data);
    }

    *(program->prog_pointer) = c;
    program->prog_pointer++;
    program->size++;
}

char get_c(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    return *(program->prog_pointer);
}

void advance_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;
    program->prog_pointer++;
}

void decrement_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;
    program->prog_pointer--;
}

void rewind_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    program->prog_pointer = program->prog;
}

void seek_program_location(PROGRAM hProgram, void *location) {
    Program *program = (Program *)hProgram;

    program->prog_pointer = location;
}

void *get_program_location(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    return program->prog_pointer;
}