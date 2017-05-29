CC          =	gcc
# Flags that are sent to the compiler  change the std if you wish

CFLAGS      =	-Wall -std=c99 -pedantic -g  

suppress=missingInclude src/*.c -i ./include

prog: src/LinkedListAPI.c
	$(CC) $(CFLAGS) src/LinkedListAPI.c -Iinclude -o bin/runMe

clean:
	rm bin/*


