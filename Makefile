CC=gcc
CFLAGS=-Werror -Wall -Wextra

run:
	./a.out

compile:
	$(CC) $(CFLAGS) ncurses.c -lncursesw
