compiler: compiler.c stack.c stack.h heap_store.c heap_store.h
	clang -o compiler compiler.c stack.c heap_store.c -fsanitize=leak


interpreter: interpreter.c stack.c stack.h heap_store.c heap_store.h
	clang -o interpreter interpreter.c stack.c heap_store.c -fsanitize=leak

build: compiler
	./compiler input.txt
	nasm -f elf64 compile.asm -o compile.o
	ld -o compile compile.o

clean:
	rm compiler  compile.asm compile.o compile interpreter