SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra
LDLIBS = -lmt19937
RM     = rm -f

Sources    = tests.c
Executable = tests

.PHONY: clean

$(Executable): $(Sources)

clean:
	$(RM) $(Executable)
