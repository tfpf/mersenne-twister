SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm
RM     = rm -f

Sources    = $(wildcard lib/*.c)
Objects    = $(Sources:.c=.o)
Executable = solve_sudoku

.PHONY: clean

$(Executable): $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

clean:
	$(RM) $(Objects) $(Executable)
