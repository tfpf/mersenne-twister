SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -I../include
RM     = rm -f

Sources    = tests.c ../lib/mt19937.c
Executable = tests

.PHONY: clean

$(Executable): $(Sources) ../lib/mt19937_common.c
	$(CC) $(CFLAGS) -o $(Executable) $(Sources)

clean:
	$(RM) $(Executable)
