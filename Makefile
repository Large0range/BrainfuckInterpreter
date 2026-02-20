main: main.c stack.c stack.h heap_store.c heap_store.h
	clang -o main main.c stack.c heap_store.c -fsanitize=leak
