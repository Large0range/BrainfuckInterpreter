#ifndef HEAP_STORE_H
#define HEAP_STORE_H

typedef void * PROGRAM;

PROGRAM create_program();
void destroy_program(PROGRAM *);

void add_c(PROGRAM, char);
char get_c(PROGRAM);

void advance_program(PROGRAM);
void decrement_program(PROGRAM);
void rewind_program(PROGRAM);

void seek_program_location(PROGRAM, void *);
void *get_program_location(PROGRAM);

#endif 