SHELL  = /bin/sh
CC     = gcc
CFLAGS = -O2 -std=c11 -Wall -Wextra -I./include
LDLIBS = -lm
RM     = rm -f

Sources    = $(wildcard src/*.c)
Objects    = $(Sources:.c=.o)
Executable = solve_sudoku

.PHONY: comp clean

comp: $(Objects)
	$(LINK.c) -o $(Executable) $(Objects) $(LDLIBS)

clean:
	$(RM) $(Objects) $(Executable)
