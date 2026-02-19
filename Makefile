main: main.c stack.c stack.h
	clang -o main main.c stack.c -fsanitize=leak
