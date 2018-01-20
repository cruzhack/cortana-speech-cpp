CC=gcc
CFLAGS=-I.

make:
	$(CC) clientfunc.c clientrun.c -o client -lcurl

clean:
	rm -f client

debug:
	valgrind --leak-check=full --leak-check=full --show-leak-kinds=all ./client 