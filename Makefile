compiler: compiler.c stack.c stack.h heap_store.c heap_store.h
	clang -o compiler compiler.c stack.c heap_store.c -fsanitize=leak


interpreter: interpreter.c stack.c stack.h heap_store.c heap_store.h
	clang -o interpreter interpreter.c stack.c heap_store.c -fsanitize=leak
