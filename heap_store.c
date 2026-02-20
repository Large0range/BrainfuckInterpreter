#include "heap_store.h"
#include <stdlib.h>
#include <stdio.h>

struct program {
    char *prog;
    unsigned long long offset;

    unsigned long long capacity;
    unsigned long long size;
};

typedef struct program Program;

PROGRAM create_program() {
    Program* p = (Program *)malloc(sizeof(Program));
    if (p != NULL) {
        p->prog = (char *)malloc(1);
        p->offset = 0;
        p->capacity = 1;
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


        program->size = program->capacity;
        program->capacity *= 2;

        free(old_data);
    }

    program->prog[program->size] = c;
    program->size++;
}

char get_c(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    return program->prog[program->offset];
}

int advance_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;
    if (program->offset + 1 < program->capacity) {
        program->offset++;
        //printf("%llu %llu\n", program->offset, program->capacity);
        return 1;
    }

    return 0;
}

void decrement_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;
    program->offset--;
}

void rewind_program(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    program->offset = 0;
}

void seek_program_location(PROGRAM hProgram, unsigned long long location) {
    Program *program = (Program *)hProgram;

    program->offset = location;
}

unsigned long long get_program_location(PROGRAM hProgram) {
    Program *program = (Program *)hProgram;

    return program->offset;
}