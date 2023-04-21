SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -I../include
LDLIBS = -lm
RM     = rm -f

Sources    = tests.c $(wildcard ../lib/mt19937*.c)
Executable = tests

.PHONY: clean

$(Executable): $(Sources)
	$(CC) $(CFLAGS) -o $(Executable) $(Sources) $(LDLIBS)

clean:
	$(RM) $(Executable)
