#include <stdio.h>
#include "stack.h"
#include "heap_store.h"

//given a valid instruction converts it to the array index that holds the instructional function
int convert(int c);
int main(int argc, char *argv[]) {
    if (argc == 1) {printf("Bro you gotta pass an input file\n"); return -1;}


    Stack stack = create_stack();

    int c, proc;
    

    FILE *input_txt = fopen(argv[1], "r");
    if (input_txt == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    PROGRAM program = create_program();
    
    //clean sanitize and prog
    int depth = 1;
    int no_skip = 0;
    while ((c = fgetc(input_txt)) != EOF) {
        if (!no_skip && c == '[') {           // skip over brackets if we haven't even incremented something yet
            depth = 1;
            while (depth > 0) {
                c = fgetc(input_txt);
                if (c == '[') depth++;
                if (c == ']') depth--;
            }
            continue;
        }

        if (c == '+' || c == '-')       //dont skip since there are possible loops now, this is just a basic sanitization, makes converting to asm easier
            no_skip = 1;

        proc = convert(c);
        if (proc >= 0 && proc <= 7)
            add_c(program, c);
    }

    fclose(input_txt);

    rewind_program(program);

    FILE *asm_code = fopen("compile.asm", "w");
    fprintf(asm_code, "default rel\nsection .bss\ntape resb 30000\n\nsection .text\nglobal _start\n_start:\n");
    int index = 0, count;
    unsigned long long loc, tag_depth = 0, tag_pop;
    do {
        c = get_c(program);
        printf("%c", c);

        if (c == '[') {
            tag_depth++;
            stack_push(stack, tag_depth);

            fprintf(asm_code, "mov rax, [tape + %d]\n", index);
            fprintf(asm_code, "cmp rax, 0\n");
            fprintf(asm_code, "je out_tag%llu\n", tag_depth);
            fprintf(asm_code, "in_tag%llu:\n", tag_depth);
            continue;

        }

        if (c == ']') {
            stack_pop(stack, &tag_pop);

            fprintf(asm_code, "mov rax, [tape + %d]\n", index);
            fprintf(asm_code, "cmp rax, 0\n");
            fprintf(asm_code, "jne in_tag%llu\n", tag_pop);
            fprintf(asm_code, "out_tag%llu:\n", tag_pop);
            continue;
        }



        if (c == '>') {
            count = 1;
            while (advance_program(program)) {
                c = get_c(program);

                if (c != '>') break;

                count++;
            }

            decrement_program(program);

            index += count;
            continue;
        }

        if (c == '<') {
            count = 1;
            while (advance_program(program)) {
                c = get_c(program);

                if (c != '<') break;

                count++;
            }

            decrement_program(program);

            index -= count;
            continue;
        }
        
        if (c == '+') {
            count = 1;
            while (advance_program(program)) {
                c = get_c(program);
                
                if (c != '+') break;

                count++;
            }

            decrement_program(program);

            fprintf(asm_code, "mov rax, [tape + %d]\n", index);
            fprintf(asm_code, "add rax, %d\n", count);
            fprintf(asm_code, "mov [tape + %d], rax\n", index);
            continue;
        }

        if (c == '-') {
            count = 1;
            while (advance_program(program)) {
                c = get_c(program);
                
                if (c != '-') break;

                count++;
            }

            decrement_program(program);

            fprintf(asm_code, "mov rax, [tape + %d]\n", index);
            fprintf(asm_code, "sub rax, %d\n", count);
            fprintf(asm_code, "mov [tape + %d], rax\n", index);
            continue;
        }
    } while (advance_program(program));
    

    //[0] = +
    //[1] = ,
    //[2] = -
    //[3] = .
    //[4] = <
    //[5] = >
    //[6] = [
    //[7] = ]
    

    fprintf(asm_code, "\nmov rax, 60\nmov rdi, 0\nsyscall\n");

    destroy_stack(&stack);
    destroy_program(&program);
    fclose(asm_code);
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