#ifndef HEAP_STORE_H
#define HEAP_STORE_H

typedef void * PROGRAM;

PROGRAM create_program();
void destroy_program(PROGRAM *);

void add_c(PROGRAM, char);
char get_c(PROGRAM);

int advance_program(PROGRAM);
void decrement_program(PROGRAM);
void rewind_program(PROGRAM);

void seek_program_location(PROGRAM, unsigned long long);
unsigned long long get_program_location(PROGRAM);

#endif 