all: main

main: main.c
	gcc -Wall -O2 -Wall -lval -lsres -lssl -lcrypto -I/Users/ahf/val/include -I/Users/ahf/lib $< -o $@
